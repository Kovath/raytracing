#ifndef CS184_RAYTRACER_H
#define CS184_RAYTRACER_H

#include "include.h"
#include "raytracer_setting.h"
#include "viewport.h"
#include "point.h"
#include "cell.h"
#include "color.h"
#include "scene.h"
#include "sphere.h"
#include "rectviewport.h"
#include "pointlight.h"

typedef Vector3f Eye;

typedef Point3f Eye;

// RAYTRACER
class RayTracer {
public:
	RayTracer(vector<Setting>& settings);
    ~RayTracer();

	void render();
	void save();

private:
	// Image drwaing configuration
    Eye eye;
    RectViewport viewport;
    Color** color_buf;
    Scene scene;

	// output file string
	const char* filename;

	friend void thread_trace(void*);
    void trace(Cell c, int x, int y);
};




//
// FOR THREADING!
//
void thread_trace(void* data);
struct ThreadData {
	int thread_count;
	int thread_number;
	RayTracer* tracer;
};

#endif
