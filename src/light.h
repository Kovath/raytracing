#ifndef LIGHT_H
#define LIGHT_H

#include "include.h"
#include "color.h"
#include "point.h"
#include "ray.h"

class Light {
    public:
		// num_ptr is written with the number of elements in the array returned
        virtual Point3f* get_positions(int *num_ptr);

        virtual bool did_ray_hit(Ray r, float *t) {return false;};

        // setter functions
        void set_intensity(Color new_i);

        // getter functions
        Color get_intensity();

    protected:
        Color intensity;
};

#endif // LIGHT_H
