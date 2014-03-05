#include "scene.h"

void Scene::add_object(Primitive *p) {
    objects.push_back(p);
}

void Scene::add_light(Light *l) {
    lights.push_back(l);
}

Color calc_diffuse(Primitive *obj, Light *light, Vector3f light_v, Vector3f normal_v) {
    Color color = obj->get_diffuse_c() * light->get_intensity() * light_v.dot(normal_v);
    if (color.r < 0) color.r = 0;
    if (color.g < 0) color.g = 0;
    if (color.b < 0) color.b = 0;
    return color;
}

Color calc_specular(Primitive *obj, Light *light, Vector3f light_v, Vector3f normal_v, Vector3f viewer_v) {
    Vector3f reflected_v = -light_v + 2*(light_v.dot(normal_v))*normal_v;
    float tough = fmax(reflected_v.dot(viewer_v), 0);
    tough = pow(tough, obj->get_specular_power());
    Color final_c = obj->get_specular_c() * light->get_intensity() * tough;
    if (tough > 0.05)
        cout << "final specular: " << final_c << endl;

    return final_c;
}

Color Scene::handle_ray(Ray r) {
    float temp = 0;
    float *t = &temp;
    Color ret(0, 0, 0);

    int hit = 0;
    Primitive *obj = NULL;
    if (did_collide(r, t, &obj)) {
        Point3f collision_point = r.point_at_time(*t);
        // go through all the lights checking if a ray from that point would hit the light
        for (unsigned int i=0; i<lights.size(); i++) {
            int num = 0;
            int *n = &num;
            // get positions to interpolate the light from
            Point3f *pos_array = lights[i]->get_positions(n);

            Color add(0, 0, 0);
            for (int j=0; j<*n; j++) {
                Primitive *e = NULL;
                // if the ray from the point on the object hits this light
                if (!did_collide(Ray(collision_point, pos_array[j]), t, &e)) {
                    hit++;
                    Vector3f light_v = (pos_array[j] - collision_point);
                    light_v.normalize();
                    Vector3f normal_v = obj->get_normal(collision_point);
                    Vector3f viewer_v = (r.get_origin() - collision_point);
                    viewer_v.normalize();
                    // DIFFUSE AND SPECULAR TERMS HERE
                    add = add + calc_diffuse(obj, lights[i], light_v, normal_v);
                    add = add + calc_specular(obj, lights[i], light_v, normal_v, viewer_v);
                }
            }
            // average the color added by the number of points checked
            add = add / *n;

            // AMBIENT TERM
            add = add + obj->get_ambient_c();

            // add color of the light to the color returned
            ret = ret + add;
        }
    }

    return ret;
}

bool Scene::did_collide(Ray r, float *t, Primitive **obj) {
    float min_time = -1;

    float temp = 0;
    float *tmp = &temp;
    Primitive *tmpy;
    for (unsigned int i=0; i<objects.size(); i++) {
        if (objects[i]->did_ray_hit(r, tmp, 0.05)) {
            if (*tmp < min_time || min_time == -1) {
                min_time = *tmp;
                tmpy = objects[i];
            }
        }
    }

    if (min_time == -1) {
        return false;
    } else {
        *t = min_time;
        *obj = tmpy;
        return true;
    }
}

