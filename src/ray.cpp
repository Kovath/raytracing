#include "ray.h"

Ray::Ray() {}
Ray::Ray(Point3f origin, Point3f pointAtT1): origin(origin) {
	point = pointAtT1 - origin;
}



void Ray::set_origin(Point3f new_origin) {
    origin = new_origin;
}

void Ray::set_pointAtT1(Point3f pointAtT1) {
    point = pointAtT1 - origin;
}

void Ray::set_point(Point3f thePoint) {
    point = thePoint;
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

ostream& operator<< (ostream& ostream, const Ray r) {
    Point3f o = r.origin;
    Point3f p = r.point;
    return ostream << "Ray: o(" << o[0] << ", " <<
        o[1] << "," <<
        o[2] << ") p(" <<
        p[0] << ", " <<
        p[1] << ", " <<
        p[2] << ")" << endl;
}
