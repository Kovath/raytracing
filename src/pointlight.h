#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "include.h"
#include "light.h"

class PointLight : Light {
    public:
        Point3f* get_positions(int *num_ptr);

        // setter functions
        void set_position(Point3f p);

        // getter functions
        Point3f get_position();

    private:
        Point3f position;

};

#endif // POINT_LIGHT_H
