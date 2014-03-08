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
	//// default configuration
	antialiasing = false;
    depth_of_field = false;

    // camera location
    Point3f eye(0, -200, 25);
    // camera direction
    Vector3f direction(0, 20, 0);
    // camera orientation
    Vector3f up(0, 0, 20);
    camera = new RectCamera(eye, direction, up);
    // set the resolution first
    camera->set_resolution(Vector2i(1000, 1000));
    // set x and y field of views to be 45 degrees
    camera->set_fov(45, 45);
    camera->create_viewport();

    // DEPTH OF FIELD SETUP
    // determines size of sampling for a single focal point
    // (determines how blurry out-of-focus-objects are)
    camera->set_aperature_size(600);
    // focal length (determines the z-distance in the scene that will be in focus)
    // multiplied against the direction length to place the focus plane
    camera->set_focal_length(7);
    // number of rays send through the aperture
    camera->set_aperature_ray_count(16);
    camera->create_focal_plane();

    // anti-aliasing grid is 5x5
    _aa_sizex = 5;
    _aa_sizey = 5;
	thread_count = 8;
	filename = "img/0.png";

	// load settings
	for(vector<Setting>::iterator it = settings.begin(); it != settings.end(); ++it) {

	}
    antialiasing = false;
    depth_of_field = true;

	color_buf = new Color*[camera->get_resolution()[0]];
    for(int i=0; i<camera->get_resolution()[0]; i++)
        color_buf[i] = new Color[camera->get_resolution()[1]];


	// loading primitives
    // left sphere
	Primitive *s = new Sphere(Point3f(-60,-50,0), 25);
    s->set_shading_c(Color(0.3, 0.05, 0.1), Color(0.6, 0.1, 0.1), Color(0.6, 0.6, 0.6), 80);
    // set reflection strength to 0.8 and refraction strength to 1.0
    s->set_rnr(0.1, 0);
    scene.add_object(s);

    // middle sphere
	s = new Sphere(Point3f(0,50,0), 25);
    s->set_shading_c(Color(0.3, 0.05, 0.1), Color(0.6, 0.1, 0.1), Color(0.6, 0.6, 0.6), 80);
    // set reflection strength to 0.8 and refraction strength to 1.0
    s->set_rnr(0.2, 0);
    scene.add_object(s);

    // right sphere
	s = new Sphere(Point3f(50,0,0), 25);
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

    // create a back wall at z
    int z = -25;
    float size = 500;

    Color amb(0.12, 0.12, 0.25);
    Color dif(0.3, 0.05, 0.2);
    Color spec(0.05, 0.05, 0.05);
    int power = 80;

    Primitive *left_t = new Triangle(Vector3f(-size, size, z), Vector3f(-size, -size, z), Vector3f(size, -size, z));
    left_t->set_shading_c(amb, dif, spec, power);
    scene.add_object(left_t);

    Primitive *right_t = new Triangle(Vector3f(-size, size, z), Vector3f(size, -size, z), Vector3f(size, size, z));
    right_t->set_shading_c(amb, dif, spec, power);
    scene.add_object(right_t);

	// creating lights
	PointLight *pl = new PointLight(Point3f(-100,100,100), Color(0.7,0.7,0.7));
    scene.add_light(pl);

    pl = new PointLight(Point3f(100, 100, 0), Color(0.6, 0.6, 0.6));
    scene.add_light(pl);

    pl = new PointLight(Point3f(25, -100, 0), Color(0.3, 0.3, 0.3));
    scene.add_light(pl);

    /*
    AreaLight *al = new AreaLight(Quad(Point3f(-100, 100, 100), Vector3f(40, 0, 0), Vector3f(0, -40, 0)), Color(1,1,1));
    // x*y points on the area light to check
    al->set_sample_size(4, 4);
    scene.add_light(al);
    */
}

RayTracer::~RayTracer() {
    for (int i=0; i<camera->get_resolution()[0]; i++)
        delete (color_buf[i]);
    delete (color_buf);
}

void RayTracer::render() {
	list<Thread*> threads;
	ThreadData* data = new ThreadData[thread_count];

	for(unsigned int i = 0; i < thread_count; i++) {
		data[i].thread_number = i;
		data[i].tracer = this;

		Thread* thread = new Thread(thread_trace, (void*)(&(data[i])));
		threads.push_back(thread);
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
	Vector2i resolution = tracer->camera->get_resolution();
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
            tracer->trace(tracer->camera->get_cell(i, j), i, j);
        }
    }
}

Color RayTracer::dof_compute(Cell c, int x, int y) {
    Color total_c(0,0,0);

    Ray r(camera->get_position(), c.get_center());
    // to find the focal_point (the point that the ray intersects on the focal plane)
    Point3f focal_point = camera->compute_focal_intersection(r);

    Vector3f cell_w = c.get_width();
    Vector3f cell_h = c.get_height();

    int aperature_size = camera->get_aperature_size();
    for(int i=0; i<camera->get_aperature_ray_count(); i++) {
        srand(x*54321 + y*123 + 5872*i);
        Vector3f jitter_w = cell_w * aperature_size * (((rand() % 100) / 100.0) - 0.5);
        Vector3f jitter_h = cell_h * aperature_size * (((rand() % 100) / 100.0) - 0.5);
        Ray r(c.get_center() + jitter_w + jitter_h, focal_point);
        total_c += scene.handle_ray(r, 2);
    }
    total_c /= camera->get_aperature_ray_count();

    return total_c;
}

Color RayTracer::aa_compute(Cell c, int x, int y) {
    Color total_c(0,0,0);
    // create jittered ray grid with size
    int gridx = _aa_sizex;
    int gridy = _aa_sizey;

    Vector3f grid_w = c.get_width() / gridx;
    Vector3f grid_h = c.get_height() / gridy;

    for (int j=0; j<gridy; j++) {
        for (int i=0; i<gridx; i++) {
            // the seed must be the same for each ray x, y, i, j
            srand(x*4321 + y*1234 + i*12 + j*21);

            // [-0.3 -- 0.3] * grid_w x value * grid_h y value
            Vector3f jitter_w = grid_w * (((rand() % 60) / 100.0) - 0.3);
            Vector3f jitter_h = grid_h * (((rand() % 60) / 100.0) - 0.3);
            Ray r(camera->get_position(), c.get_top_left() + grid_w/2 + grid_h/2 + jitter_w + jitter_h
                    + grid_w*i + grid_h*j);
            total_c += scene.handle_ray(r, 2);
        }
    }
    total_c /= gridx * gridy;
    return total_c;
}

Color RayTracer::compute(Cell c, int x, int y) {
    Ray r(camera->get_position(), c.get_center());
    return scene.handle_ray(r, 2);
}


void RayTracer::trace(Cell c, int x, int y) {
    Color total_c;

    if (depth_of_field) {
        total_c = dof_compute(c, x, y);
    }
    else {
        if (antialiasing) {
            total_c = aa_compute(c, x, y);
        }
        else {
            total_c = compute(c, x, y);
        }
    }

    // make sure to ceil the floats
    if (total_c.r > 1.0) total_c.r = 1.0;
    if (total_c.g > 1.0) total_c.g = 1.0;
    if (total_c.b > 1.0) total_c.b = 1.0;
    color_buf[x][y] += total_c;
}

void RayTracer::save() {
	Vector2i resolution = camera->get_resolution();
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

