#ifndef RAY_H
#define RAY_H

#include "include.h"
#include "point.h"

class Ray {
    public:
        // constructors
        Ray();
        // ray can be defined by the origin and a point at t = 1
        Ray(Point3f origin, Point3f pointAtT1);

        Point3f point_at_time(float t);

        friend ostream& operator<< (ostream& ostream, const Ray r);

        // setter functions
        void set_origin(Point3f origin);
        void set_pointAtT1(Point3f pointAtT1);

        // getter functions
        Point3f get_origin();
        Point3f get_point();

    private:
        // origin is the start point, point is the vector traversed every t (NOT THE
        // SAME AS THE POINT AT t = 1)
        Point3f origin, point;
};

#endif // RAY_H
