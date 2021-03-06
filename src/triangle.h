#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "include.h"
#include "primitive.h"
#include "point.h"

class Triangle : public Primitive {
    public:
        // constructors
        Triangle();
        // p0, p1, p2 should be in counter clockwise order
        Triangle(Point3f p0, Point3f p1, Point3f p2);

        // sets the intersection time to float pointer t if ray hits object
        bool did_ray_hit(Ray ray, float *intersection_t, float epsilon=0);
        // returns the normalized normal vector of a point
        Vector3f get_normal(Point3f point);
		// checks if point is in triangle
		bool contains_point(Point3f point, float epsilon = 0.000001);
        // returns the color for a point
        Color get_material_color_for_point(Point3f point, Material *m);

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
