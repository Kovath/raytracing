#ifndef RAY_H
#define RAY_H

#include "include.h"

class Ray {
    public:
        // origin is the start point, point is the vector traversed every t (NOT THE
        // SAME AS THE POINT AT t = 1)
        Eigen::Vector3f origin, point;

        // constructors
        Ray() {}
        // ray can be defined by the origin and a point at t = 1
        Ray(Eigen::Vector3f origin, Eigen::Vector3f pointAtT1): origin(origin) {
            point = pointAtT1 - origin;
        }

};

#endif // RAY_H
