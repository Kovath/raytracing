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
#include "rectcamera.h"
#include "transformation.h"

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
    bool depth_of_field;
	unsigned int thread_count;
	String filename;
    int _aa_sizex, _aa_sizey;

	// Internal members
    RectCamera *camera;
    Color** color_buf;
    Scene scene;

	friend void thread_trace(void*);
    void trace(Cell c, int x, int y);

    // compute color for cell
    Color aa_compute(Cell c, int x, int y);
    Color dof_compute(Cell c, int x, int y);
    Color compute(Cell c, int x, int y);

};

#endif
