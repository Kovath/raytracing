#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "include.h"
#include "primitive.h"

using Eigen::Vector3f;

class Triangle : public virtual Primitive {
    public:
        // a triangle is defined by three points
        // these MUST be passed in countclockwise order in order for
        // one-sided triangles to exist
        Vector3f p0, p1, p2;

        // constructors
        Triangle() {}
        Triangle(Vector3f p0, Vector3f p1, Vector3f p2): p0(p0), p1(p1), p2(p2) {}

        // sets the intersection time to float pointer t if ray hits object
        bool did_ray_hit(Ray ray, float *intersection_t);
};

#endif // TRIANGLE_H