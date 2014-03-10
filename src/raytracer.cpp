#include "raytracer.h"
#include "tinythread.h"
#include "lodepng.h"

#include "point.h"
#include "rectcamera.h"
#include "sphere.h"
#include "triangle.h"
#include "object.h"
#include "pointlight.h"
#include "arealight.h"

// THREADING
using namespace tthread;
typedef thread Thread;
void thread_trace(void* data);
struct ThreadData {
	int thread_number;
	RayTracer* tracer;
};

RayTracer::RayTracer(list<Setting>& settings) {
	//// default configuration
	antialiasing = true;
    _aa_sizex = 3;
    _aa_sizey = 3;
	thread_count = 8;
	filename = "img/0.png";
    depth_of_field = false;
	camera = new RectCamera();
	
	/*
	// loading primitives
    // left sphere
	Primitive *s = new Sphere(Point3f(-50,50,0), 25);
    s->set_shading_c(Color(0.3, 0.05, 0.1), Color(0.6, 0.1, 0.1), Color(0.6, 0.6, 0.6), 210);
    s->set_rnr(0.1, 0);
    scene.add_object(s);

    // middle sphere
	s = new Sphere(Point3f(0,-50,0), 25);
    s->set_shading_c(Color(0.3, 0.05, 0.1), Color(0.6, 0.1, 0.1), Color(0.6, 0.6, 0.6), 210);
    s->set_rnr(0.2, 0);
    scene.add_object(s);

    // right sphere
	s = new Sphere(Point3f(50,0,0), 25);
    s->set_shading_c(Color(0.3, 0.05, 0.1), Color(0.6, 0.1, 0.1), Color(0.6, 0.6, 0.6), 210);
    s->set_rnr(0.3, 0);
    scene.add_object(s);

    // create a back wall at z
    int z = -25;
    float size = 500;

    Color amb(0.12, 0.12, 0.25);
    Color dif(0.3, 0.05, 0.2);
    Color spec(0.05, 0.05, 0.05);
    int power = 80;

    Primitive *left_t = new Triangle(Vector3f(-size, size, z), Vector3f(-size, -size, z), Vector3f(size, -size, z));
    left_t->set_shading_c(amb, dif, spec, power);
    left_t->set_rnr(0.1, 0);
    scene.add_object(left_t);

    Primitive *right_t = new Triangle(Vector3f(-size, size, z), Vector3f(size, -size, z), Vector3f(size, size, z));
    right_t->set_shading_c(amb, dif, spec, power);
    right_t->set_rnr(0.1, 0);
    scene.add_object(right_t);

	// creating lights
	PointLight *pl = new PointLight(Point3f(-100,100,100), Color(0.7,0.7,0.7));
    scene.add_light(pl);

    pl = new PointLight(Point3f(100, 100, 0), Color(0.6, 0.6, 0.6));
    scene.add_light(pl);

    pl = new PointLight(Point3f(25, -100, 0), Color(0.3, 0.3, 0.3));
    scene.add_light(pl);

    AreaLight *al = new AreaLight(Quad(Point3f(-100, 100, 100), Vector3f(40, 0, 0), Vector3f(0, -40, 0)), Color(1,1,1));
    // x*y points on the area light to check
    al->set_sample_size(3, 3);
    scene.add_light(al);

    al = new AreaLight(Quad(Point3f(150, 20, 50), Vector3f(0, -40, 0), Vector3f(0, 0, -20)), Color(1,1,1));
    // x*y points on the area light to check
    al->set_sample_size(3, 3);
    scene.add_light(al);
	*/
	
	
	Primitive* current_obj = NULL;
	for(list<Setting>::iterator it = settings.begin(); it != settings.end(); it++) {
		SettingType type = (*it).get_type();
		vector<String> args = (*it).get_arguments();
		
		switch(type) {
			// RENDER CONFIGURATIONS
			case CONFIG_OUTPUT_FILE: {
				filename = args[0];
			} break;
			
			case CONFIG_THREADED: {
				thread_count = atoi(args[0].c_str());
			} break;
				
			case CONFIG_ANTIALIASING: {
			
			} break;
			
			case CONFIG_DEPTH_OF_FIELD: {
				
			} break;
				
		
		
			// CAMERA CONFIGURATIONS
			case CAMERA_POSITION: {
				float x = atof(args[0].c_str());
				float y = atof(args[1].c_str());
				float z = atof(args[2].c_str());
				camera->set_position(Point3f(x, y, z));
			} break;
			
			case CAMERA_DIRECTION: {
				float x = atof(args[0].c_str());
				float y = atof(args[1].c_str());
				float z = atof(args[2].c_str());
				camera->set_direction(Vector3f(x, y, z));
			} break;
			
			case CAMERA_FOV: {
				float x = atof(args[0].c_str());
				float y = atof(args[1].c_str());
				camera->set_fov(x, y);
			} break;
				
			case CAMERA_ORIENTATION: {
				float x = atof(args[0].c_str());
				float y = atof(args[1].c_str());
				float z = atof(args[2].c_str());
				camera->set_up(Vector3f(x, y, z));
			} break;
				
			case CAMERA_RESOLUTION: {
				int w = atoi(args[0].c_str());
				int h = atoi(args[1].c_str());
				camera->set_resolution(Vector2i(w, h));
			} break;
				
				
				
			// LIGHT CONFIGURATION
			case LIGHT_POINT: {
				float x = atof(args[0].c_str()); float y = atof(args[1].c_str()); float z = atof(args[2].c_str());
				float r = atof(args[3].c_str()); float g = atof(args[4].c_str()); float b = atof(args[5].c_str());
				
				Light* light = new PointLight(Point3f(x, y, z), Color(r, g, b));
				scene.add_light(light);
			} break;
				
			case LIGHT_AREA: {
				float x1 = atof(args[0].c_str()); float y1 = atof(args[1].c_str()); float z1 = atof(args[2].c_str());
				float x2 = atof(args[3].c_str()); float y2 = atof(args[4].c_str()); float z2 = atof(args[5].c_str());
				float x3 = atof(args[6].c_str()); float y3 = atof(args[7].c_str()); float z3 = atof(args[8].c_str());
				float r  = atof(args[9].c_str()); float g = atof(args[10].c_str()); float b  = atof(args[11].c_str());
				
				Light* light = new AreaLight(Quad(Point3f(x1, y1, z1), Vector3f(x2, y2, z2), Vector3f(x3, y3, z3)), Color(r, g, b));
				((AreaLight*)light)->set_sample_size(3, 3);
				scene.add_light(light);
			} break;
			
			case LIGHT_DIRECTION: {
				
			} break;
				
			
			
			// OBJECT CONFIGURATION
			case OBJECT_SPHERE: {
				if(current_obj != NULL) scene.add_object(current_obj);
				float x = atof(args[0].c_str());
				float y = atof(args[1].c_str());
				float z = atof(args[2].c_str());
				float radius = atof(args[3].c_str());
				
				current_obj = new Sphere(Point3f(x, y, z), radius);
			} break;
			
			case OBJECT_TRIANGLE: {
				if(current_obj != NULL) scene.add_object(current_obj);
				float x1 = atof(args[0].c_str()); float y1 = atof(args[1].c_str()); float z1 = atof(args[2].c_str());
				float x2 = atof(args[3].c_str()); float y2 = atof(args[4].c_str()); float z2 = atof(args[5].c_str());
				float x3 = atof(args[6].c_str()); float y3 = atof(args[7].c_str()); float z3 = atof(args[8].c_str());
			
				current_obj = new Triangle(Point3f(x1, y1, z1), Point3f(x2, y2, z2), Point3f(x3, y3, z3));
			} break;
			
			case OBJECT_OBJECT: {
				if(current_obj != NULL) scene.add_object(current_obj);
				current_obj = new Object(args[0]);
			} break;
			
			
			
			// MATERIAL CONFIGURATION
			case MATERIAL_AMBIENCE: {
				float r = atof(args[0].c_str());
				float g = atof(args[1].c_str());
				float b = atof(args[2].c_str());
			
				current_obj->set_ambient_c(Color(r, g, b));
				break;
			}
			
			case MATERIAL_DIFFUSE: {
				float r = atof(args[0].c_str());
				float g = atof(args[1].c_str());
				float b = atof(args[2].c_str());
			
				current_obj->set_diffuse_c(Color(r, g, b));
				break;
			}
			
			case MATERIAL_SPECULAR: {
				float r = atof(args[0].c_str());
				float g = atof(args[1].c_str());
				float b = atof(args[2].c_str());
			
				current_obj->set_specular_c(Color(r, g, b));
				break;
			}
			
			case MATERIAL_SPECULAR_POWER: {
				unsigned int power = atoi(args[0].c_str());
				
				current_obj->set_specular_power(power);
				break;
			}
			
			
			
			// TRANSFORMATIONS
			case TRANSFORM_TRANSLATE: {
				break;
			}
			
			case TRANSFORM_SCALE: {
				break;
			}
			
			case TRANSFORM_ROTATE: {
				break;
			}
			
			
			
			default: break;
		}
	}
	if(current_obj != NULL) scene.add_object(current_obj);
	
	camera->create_viewport();
	// DEPTH OF FIELD SETUP
    // determines size of sampling for a single focal point
    // (determines how blurry out-of-focus-objects are)
    camera->set_aperature_size(150);
    // focal length (determines the z-distance in the scene that will be in focus)
    // multiplied against the direction length to place the focus plane
    camera->set_focal_length(3.2);
    // number of rays send through the aperture (4 by 4 grid)
    camera->set_aperature_ray_count(Vector2i(4, 4));
    camera->create_focal_plane();
	
	color_buf = new Color*[camera->get_resolution()[0]];
    for(int i=0; i<camera->get_resolution()[0]; i++) {
        color_buf[i] = new Color[camera->get_resolution()[1]];
	}	
}

RayTracer::~RayTracer() {
	for (int i=0; i<camera->get_resolution()[0]; i++)
        delete[] color_buf[i];
    delete[] color_buf;
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

	delete[] data;
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
	for (int i = 0; i < width; i ++) {
		for (int j = start_row; j < end_row; j++) {
            tracer->trace(tracer->camera->get_cell(j, i), j, i);
        }
    }
}

Color RayTracer::dof_compute(Cell c, int x, int y) {
    Color total_c(0,0,0);

    Ray r(camera->get_position(), c.get_center());
    // to find the focal_point (the point that the ray intersects on the focal plane)
    Point3f focal_point = camera->compute_focal_intersection(r);

    int aperature_size = camera->get_aperature_size();
    Vector2i ray_count = camera->get_aperature_ray_count();
    int ray_w = ray_count[0];
    int ray_h = ray_count[1];

    // split the aperature into a grid with ray_count
    Vector3f cell_w = c.get_width()*(float)aperature_size/(float)ray_w;
    Vector3f cell_h = c.get_height()*(float)aperature_size/(float)ray_h;

    for(int j=-ray_w/2; j<ray_w/2; j++) {
        for(int i=-ray_h/2; i<ray_h/2; i++) {
            srand(x*54321 + y*123 + 5872*i + 912*j);
            Vector3f jitter_w = cell_w * (((rand() % 60) / 100.0) - 0.3);
            Vector3f jitter_h = cell_h * (((rand() % 60) / 100.0) - 0.3);
            Ray r(c.get_center() + cell_w*i + cell_h*j + jitter_w + jitter_h, focal_point);
            total_c += scene.handle_ray(r, 2);
        }
    }
    total_c /= ray_h * ray_w;

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

    color_buf[x][y] += total_c;
}

void RayTracer::save() {
	Vector2i resolution = camera->get_resolution();
	int rgb_size = 3;
	int width = resolution[0];
	int height = resolution[1];

	unsigned char* image = new unsigned char[width * height * rgb_size];
	for(int x = 0; x < width; x++) {
		for(int y = 0; y < height; y++) {
			image[(y * width + x) * rgb_size + 0] = (int)(color_buf[x][y].r * 255.0);
			image[(y * width + x) * rgb_size + 1] = (int)(color_buf[x][y].g * 255.0);
			image[(y * width + x) * rgb_size + 2] = (int)(color_buf[x][y].b * 255.0);
		}
	}

	lodepng_encode24_file(filename.data(), image, width, height);
	delete[] image;
}

