#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "include.h"
#include "point.h"
#include "light.h"

class DirectionalLight : public Light {
    public:
        Point3f* get_positions(int *num_ptr) { *num_ptr = 0; return NULL; } ;
        bool did_ray_hit(Ray r, float *t) { return false; };

        // constructors
        DirectionalLight();
        DirectionalLight(Vector3f direction, Color intensity);

        // setter functions
        void set_direction(Point3f p);

        // getter functions
        Vector3f get_direction();

    private:
        Vector3f direction;
};

#endif // DIRECTIONAL_LIGHT_H
