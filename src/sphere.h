#ifndef SPHERE_H
#define SPHERE_H

#include "include.h"
#include "object.h"

class Sphere : public virtual Object {
    public:
        // center and radius define a sphere
        Eigen::Vector3f center;
        float radius;

        // constructors
        Sphere() {}
        Sphere(Eigen::Vector3f center, float radius): center(center), radius(radius) {}

        bool did_ray_hit(Ray r);
};

#endif // SPHERE_H
