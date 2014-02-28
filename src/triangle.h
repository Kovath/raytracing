#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "include.h"
#include "primitive.h"
#include "point.h"

class Triangle : public virtual Primitive {
    public:
        // constructors
        Triangle();
        Triangle(Point3f p0, Vector3f p1, Vector3f p2);

        // sets the intersection time to float pointer t if ray hits object
        bool did_ray_hit(Ray ray, float *intersection_t);

        // setter functions
        void set_p0(Point3f p);
        void set_p1(Point3f p);
        void set_p2(Point3f p);

        // getter functions
        Point3f get_p0();
        Point3f get_p1();
        Point3f get_p2();

    private:
        // a triangle is defined by three points
        // these MUST be passed in countclockwise order in order for
        // one-sided triangles to exist
        Point3f p0, p1, p2;
};

#endif // TRIANGLE_H
