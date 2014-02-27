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

        // sets the intersection time to float pointer t if ray hits object
        bool did_ray_hit(Ray ray, float *intersection_t);
};

#endif // SPHERE_H
