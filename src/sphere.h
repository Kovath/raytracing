#ifndef SPHERE_H
#define SPHERE_H

#include "include.h"
#include "object.h"
#include "vector3f.h"
#include "point3f.h"

class Sphere : public virtual Object {
    public:
        // center and radius define a sphere
        Point3f center;
        float radius;

        // constructors
        Sphere() {}
        Sphere(Point3f center, float radius): center(center) radius(radius) {}
};

#endif // SPHERE_H
