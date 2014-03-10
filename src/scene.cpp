#include "scene.h"
#include "point.h"

Scene::Scene() {

}

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

Color calc_specular(Primitive *obj, Light *light, Vector3f reflected_v, Vector3f viewer_v) {
    float right_side = pow(fmax(reflected_v.dot(viewer_v), 0), obj->get_specular_power());
    return obj->get_specular_c() * light->get_intensity() * right_side;
}

Color Scene::handle_ray(Ray r, int limit /* = 1 */) {
    // base case for the recursive function
    if (limit <= 0) return Color(0, 0, 0);

    float temp = 0;
    float *t = &temp;
    int hit = 0;
    Color ret(0, 0, 0);

    Primitive *obj = NULL;
    Light *lite = NULL;
    // if we hit a light return that value and quit
    if (did_collide_light(r, t, &lite)) {
        return lite->get_intensity();
    }
    // if we hit an object
    if (did_collide(r, t, &obj)) {
        Transform<float, 3, Affine> inverse_tr = obj->T.get_inverse_transformation();
        Transform<float, 3, Affine> tr = obj->T.get_transformation();

        // transform the ray
        r.set_origin(inverse_tr*r.get_origin());
        r.set_point(inverse_tr*r.get_point());
        Point3f collision_point = r.point_at_time(*t);

        // normal of the point hit and viewer vector won't change
        Matrix3f normal_transform = tr.linear().inverse().transpose();
        Vector3f normal_v = normal_transform * obj->get_normal(collision_point);

        // transform the collision point back to world space
        collision_point = tr * collision_point;
        // transform the ray back to the world space
        r.set_origin(tr*r.get_origin());
        r.set_point(tr*r.get_point());

        Vector3f viewer_v = (tr*r.get_origin() - collision_point);
        // calculate the reflected ray
        Ray reflected(collision_point, collision_point + -viewer_v + 2*(normal_v.dot(viewer_v))*normal_v);
        Vector3f reflected_v = -viewer_v + 2*(normal_v.dot(viewer_v))*normal_v;
        reflected_v.normalize();
        viewer_v.normalize();

        // go through all the lights checking if a ray from that point would hit the light
        for (unsigned int i=0; i<lights.size(); i++) {
            int num = 0;
            int *n = &num;
            // get positions to interpolate the light from
            Point3f *pos_array = lights[i]->get_positions(n);

            Vector3f jitter(0,0,0);
            bool jit = false;
            if (*n > 1) {
                srand(collision_point[0] + 12345*collision_point[1] + 231*collision_point[2]);
                jit = true;
            }

            Color add(0, 0, 0);
            for (int j=0; j<*n; j++) {
                // jitter the jitter
                if (jit) {
                    float scale = 10;
                    jitter = Vector3f((((rand() % 100) / 100.0) - 0.5) * scale,
                            (((rand() % 100) / 100.0) - 0.5) * scale,
                            (((rand() % 100) / 100.0) - 0.5) * scale);
                }
                Primitive *e = NULL;
                // if the ray from the point on the object hits this light
                if (!did_collide(Ray(collision_point, pos_array[j] + jitter), t, &e)) {
                    hit++;
                    Vector3f light_v = (pos_array[j] + jitter - collision_point);
                    light_v.normalize();
                    Vector3f light_reflected_v = -light_v + 2*(light_v.dot(normal_v))*normal_v;
                    light_reflected_v.normalize();

                    // DIFFUSE AND SPECULAR TERMS HERE
                    add = add + calc_diffuse(obj, lights[i], light_v, normal_v);
                    add = add + calc_specular(obj, lights[i], light_reflected_v, viewer_v);
                }
            }
            // average the color added by the number of points checked
            add /= *n;

            // AMBIENT TERM
            add += lights[i]->get_intensity()*obj->get_ambient_c();

            // add color of the light to the color returned
            ret += add;
        }

        // recursively go through the reflected ray to add a color to the object
        // with strength reflection_c for the object
        ret += obj->get_reflection_c() * handle_ray(reflected, limit-1);
    }

    return ret;
}

bool Scene::did_collide_light(Ray r, float *t, Light **lite) {
    float temp = 0;
    float *tmp = &temp;
    for (unsigned int i=0; i<lights.size(); i++) {
        if (lights[i]->did_ray_hit(r, tmp)) {
            *t = *tmp;
            *lite = lights[i];
            return true;
        }
    }
    return false;
}

bool Scene::did_collide(Ray r, float *t, Primitive **obj) {
    float min_time = -1;
    // the amount of leeway the ray gets (prevents self-shading)
    float epsilon = 0.002;

    float temp = 0;
    float *tmp = &temp;
    Primitive *tmpy;
    for (unsigned int i=0; i<objects.size(); i++) {
        if (objects[i]->did_ray_hit(r, tmp, epsilon)) {
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

