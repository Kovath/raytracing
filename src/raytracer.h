#ifndef CS184_RAYTRACER_H
#define CS184_RAYTRACER_H

#include "include.h"
#include "raytracer_setting.h"
#include "viewport.h"
#include "point.h"

typedef Point3f Eye;

// RAYTRACER
class RayTracer {
public:
	RayTracer(vector<Setting>& settings);

	void render();
	void save();
	
private:

	//void trace(Point samplePoint);
};

#endif
