#include "directionallight.h"


DirectionalLight::DirectionalLight() {}
DirectionalLight::DirectionalLight(Vector3f direction, Color intensity): direction(direction) {set_intensity(intensity);}

void DirectionalLight::set_direction(Point3f p) {
    direction = p;
}

Point3f DirectionalLight::get_direction() {
    return direction;
}
