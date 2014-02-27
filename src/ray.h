#ifndef RAY_H
#define RAY_H

#include "include.h"

class Ray {
    // ray can be defined by the origin and a point at t = 1
    Eigen::Vector3f origin, point;

    // constructors
    Ray() {}
    Ray(Eigen::Vector3f origin, Eigen::Vector3f point): origin(origin), point(point) {}

};

#endif // RAY_H
