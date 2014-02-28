#include "quad.h"

Quad::Quad() {}
Quad::Quad(Point3f topleft, Vector3f w, Vector3f h) : top_left(topleft), width(w), height(h) {}



Point3f Quad::get_center() {
	return top_left + width/2.0 + height/2.0;
}

Point3f Quad::get_top_left() {
	return top_left;
}

Point3f Quad::get_top_right() {
	return top_left + width;
}

Point3f Quad::get_bottom_left() {
	return top_left + height;
}

Point3f Quad::get_bottom_right() {
	return top_left + width + height;
}



Vector3f Quad::get_width() {
	return width;
}

Vector3f Quad::get_height() {
	return height;
}