#include "arealight.h"

Point3f* AreaLight::get_positions(int *num_ptr) {
    if (_positions_computed == false) {
        compute_positions();
    }
    *num_ptr = _samplex * _sampley;
    return positions;
}

AreaLight::~AreaLight() {
    delete[] positions;
}

void set_sample_size(int x, int y) {
    _samplex = x;
    _sampley = y;
}

void AreaLight::compute_positions() {
    if (_positions_computed) return;

    Vector3f cell_w = area.get_width() / _samplex;
    Vector3f cell_h = area.get_height() / _sampley;

    positions = new Point3f[9];

    int curr = 0;
    for(int j=0; j<_samplex; j++) {
        for(int i=0; i<_sampley; i++) {
            positions[curr] = area.get_top_left() + i*cell_w + j*cell_h;
            curr++;
        }
    }

    _positions_computed = true;
}
