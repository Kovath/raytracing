#include "viewport.h"

void Viewport::set_resolution(Vector2f new_resolution) {
    resolution = new_resolution;
}

Vector2f Viewport::get_resolution() {
    return resolution;
}
