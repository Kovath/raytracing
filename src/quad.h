#ifndef CS184_QUAD_H
#define CS184_QUAD_H

#include "include.h"
#include "point.h"

class Quad {
public:
	Quad();
	Quad(Point3f top_left, Vector3f width, Vector3f height);
	
	// Get significant points on the quad
	Point3f get_center();
	Point3f get_top_left();
	Point3f get_top_right();
	Point3f get_bottom_left();
	Point3f get_bottom_right();
	
	// Get vectors FROM THE TOP LEFT.
	// REPEAT FROM THE TOP LEFT
	Vector3f get_width();
	Vector3f get_height();
	
private:
	Point3f top_left;
	Vector3f width, height;
};

#endif