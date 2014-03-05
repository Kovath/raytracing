#ifndef SCENE_H
#define SCENE_H

#include "include.h"
#include "primitive.h"
#include "light.h"
#include "color.h"
#include "point.h"

class Scene {
    public:
        // constructors
        Scene() {}

        // adds an object to the object list
        void add_object(Primitive *p);
        // adds a light to the light list
        void add_light(Light *l);

        // returns a color after bouncing the ray through the scene
        Color handle_ray(Ray r);
        // returns true or false based on whether the ray hits an object
        // and sets the time t the ray hits an object in the scene
        // sets the primtive being pointed to if ray hits an object
        bool did_collide(Ray r, float *t, Primitive **obj);

    private:
        vector<Primitive*> objects;
        vector<Light*> lights;
};

#endif // SCENE_H
