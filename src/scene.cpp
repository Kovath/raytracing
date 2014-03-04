#include "scene.h"

void Scene::add_object(Primitive p) {
    objects.push_back(p);
}

void Scene::add_light(Light l) {
    lights.push_back(l);
}

Color Scene::handle_ray(Ray r) {
    float temp = 0;
    float *t = &temp;
    Color ret(0, 0, 0);

    if (did_collide(r, t)) {
        Point3f collision_point = r.point_at_time(*t);
        // go through all the lights checking if a ray from that point would hit the light
        for (int i=0; i<lights.size(); i++) {
            int num = 0;
            int *n = &num;
            // get positions to interpolate the light from
            Point3f *pos_array = lights[i].get_positions(n);

            Color add(0, 0, 0);
            for (int j=0; j<*n; j++) {
                if (!did_collide(Ray(collision_point, pos_array[j]), t)) {
                    // HACK FOR TESTING PURPOSE DELETE LATER
                    add = add + Color(20, 0, 0);
                }
            }
            // average the color added by the number of points checked
            add = add / *n;
            // add color of the light to the color returned
            ret = ret + add;
        }
    }

    return ret;
}

bool Scene::did_collide(Ray r, float *t) {
    float min_time = -1;

    float temp = 0;
    float *tmp = &temp;
    for (int i=0; i<objects.size(); i++) {
        if (objects[i].did_ray_hit(r, tmp)) {
            if (*tmp < min_time || min_time == -1) {
                min_time = *tmp;
            }
        }
    }

    if (min_time == -1) {
        return false;
    } else {
        *t = min_time;
        return true;
    }
}

