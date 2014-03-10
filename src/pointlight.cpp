#include "pointlight.h"

void PointLight::set_position(Point3f p) {
    position = p;
}

bool PointLight::did_ray_hit(Ray r, float *t) {
    return false;
    // the vector of the ray
    Vector3f ray_v = r.get_point() - r.get_origin();
    ray_v.normalize();
    // the vector from the ray origin to the pointlight's point
    Vector3f light_v = position - r.get_origin();
    light_v.normalize();
    // if the dot product is near 1 then we have a collision
    if (ray_v.dot(light_v) > 0.9995)
        return true;
    else
        return false;
}

Point3f PointLight::get_position() {
    return position;
}

Point3f *PointLight::get_positions(int *num_ptr) {
    *num_ptr = 1;
    return &position;
}
