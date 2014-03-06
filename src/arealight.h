#ifndef AREA_LIGHT_H
#define AREA_LIGHT_H

#include "include.h"
#include "light.h"
#include "quad.h"

class AreaLight : public Light {
    public:
        Point3f* get_positions(int *num_ptr);

        // constuctors
        AreaLight() {_positions_computed = false;}
        AreaLight(Quad area, Color intensity): area(area) {_positions_computed = false; set_intensity(intensity);}

        ~AreaLight();

        void set_sample_size(int x, int y);

    private:
        void compute_positions();
        int _samplex, _sampley;

        bool _positions_computed;
        Quad area;
        Point3f *positions;
};

#endif // AREA_LIGHT_H
