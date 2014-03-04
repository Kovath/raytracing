#include "pointlight.h"

void PointLight::set_position(Point3f p) {
    position = p;
}

Point3f PointLight::get_position() {
    return position;
}

Point3f *PointLight::get_positions(int *num_ptr) {
    *num_ptr = 1;
    return &position;
}
