#include "raytracer.h"

#include "tinythread.h"
#include "lodepng.h"

using namespace tthread;
typedef thread Thread;

RayTracer::RayTracer(vector<Setting>& settings) {
    eye = Point3f(0, 0, 100);

    // create a rectangle viewport on the xy plane at z=50
    Quad port(Point3f(-50, 50, 50), Vector3f(100, 0, 0), Vector3f(0, -100, 0));
    Vector2i resolution(400, 400);
    viewport = RectViewport(port, resolution);

	// BE EXRTREMEMLY CAREFUL YOU DO NOT ASSIGN TO THE ARRAY. IF YOU DO
	// YOU MAY HAVE A MEMORY LEAK. DO NOT ASSIGN TO THE COLOR ARRAY
    color_buf = new Color*[resolution[0]];
    for(int i=0; i<resolution[0]; i++)
        color_buf[i] = new Color[resolution[1]];
    Sphere *s = new Sphere(Point3f(0,0,0), 50);
    s->set_shading_c(Color(0.5, 0.1, 0), Color(0.5, 0.2, 0), Color(0.8, 0.8, 0.8), 80);
    scene.add_object(s);
    PointLight *pl = new PointLight(Point3f(-100,100,100), Color(1,1,1));
    scene.add_light(pl);
}

RayTracer::~RayTracer() {
    for (int i=0; i<viewport.get_resolution()[0]; i++)
        delete (color_buf[i]);
    delete (color_buf);
}

void RayTracer::render() {
	int thread_count = 8;

	list<Thread*> threads;
	ThreadData* data = new ThreadData[thread_count];

	for(int i = 0; i < thread_count; i++) {
		data[i].thread_count = thread_count;
		data[i].thread_number = i;
		data[i].tracer = this;

		Thread* thread = new Thread(thread_trace, (void*)(&(data[i])));
		threads.push_back(thread);
	}
	for(list<thread*>::iterator i = threads.begin(); i != threads.end(); i++) {
		Thread* thread = *i;
		thread->join();
		delete thread;
	}
	delete[] data;
}

void thread_trace(void* d) {
	// Retrieving data from ThreadData
	ThreadData* data = (ThreadData*)d;
	RayTracer* tracer = data->tracer;
	int thread_count = data->thread_count;
	int thread_number = data->thread_number;

	// pulling extra info
	Vector2i resolution = tracer->viewport.get_resolution();
    int width = resolution[0];
    int height = resolution[1];

	int workload = (height / thread_count);
	int start_row = thread_number * workload;
	int end_row = (thread_number + 1) * workload;

	if((thread_number + 1) == thread_count) {
		end_row += ((thread_number + 1) == thread_count) ? height % thread_count : 0;
	}

	// fill out the color array
    for (int j = start_row; j < end_row; j++) {
        for (int i = 0; i < width; i ++) {
            tracer->trace(tracer->viewport.get_cell(i, j), i, j);
        }
    }
}

void RayTracer::trace(Cell c, int x, int y) {
    // create jittered ray grid with size
    int gridx = 5;
    int gridy = 5;

    Vector3f grid_w = c.get_width() / gridx;
    Vector3f grid_h = c.get_height() / gridy;

    Color total_c(0,0,0);
    for (int j=0; j<gridy; j++) {
        for (int i=0; i<gridx; i++) {
            // the seed must be the same for each ray x, y, i, j
            srand(x*4321 + y*1234 + i*12 + j*21);

            // [-0.3 -- 0.3] * grid_w x value * grid_h y value
            Vector3f jitter((((rand() % 60) / 1000) - 0.3) * grid_w[0],
                            (((rand() % 60) / 1000) - 0.3) * grid_h[1],
                            0);
            Ray r(eye, c.get_top_left() + grid_w/2 + grid_h/2 + jitter
                    + grid_w*i + grid_h*j);
            total_c += scene.handle_ray(r);
        }
    }
    total_c /= gridx * gridy;
    if (total_c.r > 1.0) total_c.r = 1.0;
    if (total_c.g > 1.0) total_c.g = 1.0;
    if (total_c.b > 1.0) total_c.b = 1.0;
    color_buf[x][y] = total_c;
}

void RayTracer::save() {
	Vector2i resolution = viewport.get_resolution();
	unsigned int width = resolution[0];
	unsigned int height = resolution[1];

	unsigned char* image = new unsigned char[width * height * 3];
	for(unsigned int x = 0; x < width; x++) {
		for(unsigned int y = 0; y < height; y++) {
			image[y * width * 3 + x * 3 + 0] = (int)(color_buf[x][y].r * 255.0);
			image[y * width * 3 + x * 3 + 1] = (int)(color_buf[x][y].g * 255.0);
			image[y * width * 3 + x * 3 + 2] = (int)(color_buf[x][y].b * 255.0);
		}
	}

	// DLETE
	filename = "img/0.png";
	lodepng_encode24_file(filename, image, width, height);
	delete[] image;
}

