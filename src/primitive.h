#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "include.h"
#include "ray.h"

// abstract base class for anything being rendered on the scene
class Primitive {
    public:
        // pure virtual function
        virtual bool did_ray_hit(Ray r, float* intersection_t) = 0;

        // terms for determining the reflection
        float ambient_c, diffuse_c, specular_c;
        unsigned int specular_power;

        // setting function
        void set_shading_c(float ambient, float diffuse, float specular, unsigned int specular_pow) {
            ambient_c = ambient;
            diffuse_c = diffuse;
            specular_c = specular;
            specular_power = specular_pow;
        }
};

#endif // PRIMITIVE_H
