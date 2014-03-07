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
#include "triangle.h"
#include "rectviewport.h"
#include "pointlight.h"
#include "arealight.h"

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
	// Configuration
	bool antialiasing;
	unsigned int thread_count;
	String filename;

	// Internal members
    Eye eye;
    RectViewport viewport;
    Color** color_buf;
    Scene scene;

	friend void thread_trace(void*);
    void trace(Cell c, int x, int y);
};

#endif
