#ifndef RAY_H
#define RAY_H

#include "include.h"
#include "vector3f.h"

class Ray {
    // ray can be defined by the origin and a point at t = 1
    Vector3f origin, point;

    // constructors
    Ray() {}
    Ray(Vector3f origin, Vector3f point) origin(origin) point(point) {}

}

#endif // RAY_H
