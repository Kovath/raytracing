#include "ray.h"

void Ray::set_origin(Point3f new_origin) {
    origin = new_origin;
}

void Ray::set_pointAtT1(Point3f pointAtT1) {
    point = pointAtT1 - origin;
}

Point3f Ray::get_origin() {
    return origin;
}

Point3f Ray::get_point() {
    return point;
}

Point3f Ray::point_at_time(float t) {
    return origin + t*point;
}
