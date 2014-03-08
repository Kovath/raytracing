#include "viewport.h"

Viewport::~Viewport() {

}

void Viewport::set_resolution(Vector2i new_resolution) {
    resolution = new_resolution;
}

Vector2i Viewport::get_resolution() {
    return resolution;
}
