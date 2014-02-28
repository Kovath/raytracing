#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "include.h"
#include "primitive.h"

class Triangle : public virtual Primitive {
    public:
        // constructors
        Triangle();
        Triangle(Vector3f p0, Vector3f p1, Vector3f p2);

        // sets the intersection time to float pointer t if ray hits object
        bool did_ray_hit(Ray ray, float *intersection_t);

        // setter functions
        void set_p0(Vector3f p);
        void set_p1(Vector3f p);
        void set_p2(Vector3f p);

        // getter functions
        Vector3f get_p0();
        Vector3f get_p1();
        Vector3f get_p2();

    private:
        // a triangle is defined by three points
        // these MUST be passed in countclockwise order in order for
        // one-sided triangles to exist
        Vector3f p0, p1, p2;
};

#endif // TRIANGLE_H
