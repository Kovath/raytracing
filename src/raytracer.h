#ifndef CS184_RAYTRACER_H
#define CS184_RAYTRACER_H
#include "include.h"

#include "raytracer_setting.h"
#include "point.h"

// RAYTRACER
class RayTracer {
public:
	RayTracer(vector<Setting>& settings);

	void render();

private:
	//void trace(Point samplePoint);
};

#endif
