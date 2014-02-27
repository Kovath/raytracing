#ifndef OBJECT_H
#define OBJECT_H

#include "include.h"
#include "ray.h"

// abstract base class for anything being rendered on the scene
class Object {
    public:
        // pure virtual function
        virtual bool did_ray_hit(Ray r) =0;
};

#endif
