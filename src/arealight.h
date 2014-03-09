#ifndef AREA_LIGHT_H
#define AREA_LIGHT_H

#include "include.h"
#include "light.h"
#include "quad.h"
#include "triangle.h"

class AreaLight : public Light {
    public:
        Point3f* get_positions(int *num_ptr);
        bool did_ray_hit(Ray r, float *t);

        // constuctors
        AreaLight();
        AreaLight(Quad area, Color intensity);

        ~AreaLight();

        void set_sample_size(int x, int y);

    private:
        void compute_triangles();
        void compute_positions();

        // split the quad into triangles to run ray intersection tests on
        Triangle *bl, *tr;
        int _samplex, _sampley;

        bool _positions_computed, _triangles_computed;
        Quad area;
        Point3f *positions;
};

#endif // AREA_LIGHT_H
