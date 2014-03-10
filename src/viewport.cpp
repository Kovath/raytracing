#include "viewport.h"

Cell Viewport::get_cell(int x, int y) { 
	return Cell(); 
};

void Viewport::set_resolution(Vector2i new_resolution) {
    resolution = new_resolution;
}

Vector2i Viewport::get_resolution() {
    return resolution;
}
