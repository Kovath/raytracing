#include "raytracer.h"
#include "tinythread.h"
#include "lodepng.h"

// THREADING
using namespace tthread;
typedef thread Thread;
void thread_trace(void* data);
struct ThreadData {
	int thread_number;
	RayTracer* tracer;
};

RayTracer::RayTracer(vector<Setting>& settings) {
	// default configuration
	antialiasing = false;
	thread_count = 4;
	filename = "img/0.png";

	// load settings
	for(vector<Setting>::iterator it = settings.begin(); it != settings.end(); ++it) {
		
	}
	antialiasing = false;
	thread_count = 8;



	// generate internal members
    eye = Point3f(0, 0, 125);

    // create a rectangle viewport on the xy plane at z=50
    Quad port(Point3f(-50, 50, 75), Vector3f(100, 0, 0), Vector3f(0, -100, 0));
    Vector2i resolution(1000, 1000);
    viewport = RectViewport(port, resolution);

	color_buf = new Color*[resolution[0]];
    for(int i=0; i<resolution[0]; i++)
        color_buf[i] = new Color[resolution[1]];


	// loading primitives
    // left sphere
	Primitive *s = new Sphere(Point3f(-55,0,0), 25);
    s->set_shading_c(Color(0.3, 0.05, 0.1), Color(0.6, 0.1, 0.1), Color(0.6, 0.6, 0.6), 80);
    // set reflection strength to 0.8 and refraction strength to 1.0
    s->set_rnr(0.1, 0);
    scene.add_object(s);

    // middle sphere
	s = new Sphere(Point3f(0,0,0), 25);
    s->set_shading_c(Color(0.3, 0.05, 0.1), Color(0.6, 0.1, 0.1), Color(0.6, 0.6, 0.6), 80);
    // set reflection strength to 0.8 and refraction strength to 1.0
    s->set_rnr(0.2, 0);
    scene.add_object(s);

    // right sphere
	s = new Sphere(Point3f(55,0,0), 25);
    s->set_shading_c(Color(0.3, 0.05, 0.1), Color(0.6, 0.1, 0.1), Color(0.6, 0.6, 0.6), 80);
    // set reflection strength to 0.8 and refraction strength to 1.0
    s->set_rnr(0.3, 0);
    scene.add_object(s);

    /*
    // equilateral triangle in middle
	Primitive *t = new Triangle(Vector3f(0, 92.3760430703, 0), Vector3f(-80, -46.188, 0), Vector3f(80, -46.188, 0));
    t->set_shading_c(Color(0.15, 0.08, 0.25), Color(0.4, 0.1, 0.2), Color(0.8, 0.8, 0.8), 80);
    scene.add_object(t);
    */

    /*
    // create a back wall at z
    int z = -50;
    float size = 200;

    Color amb(0.02, 0.02, 0.15);
    Color dif(0.2, 0.05, 0.1);
    Color spec(0.05, 0.05, 0.05);
    int power = 80;

    Primitive *left_t = new Triangle(Vector3f(-size, size, z), Vector3f(-size, -size, z), Vector3f(size, -size, z));
    left_t->set_shading_c(amb, dif, spec, power);
    scene.add_object(left_t);

    Primitive *right_t = new Triangle(Vector3f(-size, size, z), Vector3f(size, -size, z), Vector3f(size, size, z));
    right_t->set_shading_c(amb, dif, spec, power);
    scene.add_object(right_t);
    */

	// creating lights
	PointLight *pl = new PointLight(Point3f(-100,100,100), Color(1,1,1));
    scene.add_light(pl);
}

RayTracer::~RayTracer() {
    for (int i=0; i<viewport.get_resolution()[0]; i++)
        delete (color_buf[i]);
    delete (color_buf);
}

void RayTracer::render() {
	list<Thread*> threads;
	ThreadData* data = new ThreadData[thread_count];

	for(unsigned int i = 0; i < thread_count; i++) {
		data[i].thread_number = i;
		data[i].tracer = this;

		threads.push_back(new Thread(thread_trace, (void*)(&(data[i]))));
	}

	for(list<thread*>::iterator i = threads.begin(); i != threads.end(); ++i) {
		Thread* thread = *i;
		thread->join();
		delete thread;
	}

	delete[] data ;
}

void thread_trace(void* d) {
	// Retrieving data from ThreadData
	RayTracer* tracer = ((ThreadData*)d)->tracer;
	int thread_count = tracer->thread_count;
	int thread_number = ((ThreadData*)d)->thread_number;

	// pulling extra info
	Vector2i resolution = tracer->viewport.get_resolution();
    int width = resolution[0];
    int height = resolution[1];

	int workload = (height / thread_count);
	int start_row = thread_number * workload;
	int end_row = (thread_number + 1) * workload;

	if((thread_number + 1) == thread_count) {
		end_row += height % thread_count;
	}

	// fill out the color array
    for (int j = start_row; j < end_row; j++) {
        for (int i = 0; i < width; i ++) {
            tracer->trace(tracer->viewport.get_cell(i, j), i, j);
        }
    }
}

void RayTracer::trace(Cell c, int x, int y) {
    Color total_c(0,0,0);

    if (antialiasing) {
        // create jittered ray grid with size
        int gridx = 5;
        int gridy = 5;

        Vector3f grid_w = c.get_width() / gridx;
        Vector3f grid_h = c.get_height() / gridy;

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
                total_c += scene.handle_ray(r, 3);
            }
        }
        total_c /= gridx * gridy;
    }
    else {
        Ray r(eye, c.get_center());
        total_c = scene.handle_ray(r, 3);
    }
    if (total_c.r > 1.0) total_c.r = 1.0;
    if (total_c.g > 1.0) total_c.g = 1.0;
    if (total_c.b > 1.0) total_c.b = 1.0;
    color_buf[x][y] = total_c;
}

void RayTracer::save() {
	Vector2i resolution = viewport.get_resolution();
	int width = resolution[0];
	int height = resolution[1];

	unsigned char* image = new unsigned char[width * height * 3];
	for(int x = 0; x < width; x++) {
		for(int y = 0; y < height; y++) {
			image[(y * width + x) * 3 + 0] = (int)(color_buf[x][y].r * 255.0);
			image[(y * width + x) * 3 + 1] = (int)(color_buf[x][y].g * 255.0);
			image[(y * width + x) * 3 + 2] = (int)(color_buf[x][y].b * 255.0);
		}
	}

	// DLETE
	lodepng_encode24_file(filename.data(), image, width, height);
	delete[] image;
}

