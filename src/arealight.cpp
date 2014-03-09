#include "arealight.h"

Point3f* AreaLight::get_positions(int *num_ptr) {
    if (_positions_computed == false) {
        compute_positions();
    }
    *num_ptr = _samplex * _sampley;
    return positions;
}

bool AreaLight::did_ray_hit(Ray r, float *t) {
    if (bl->did_ray_hit(r, t)) return true;
    if (tr->did_ray_hit(r, t)) return true;
    return false;
}

AreaLight::AreaLight() {
    _positions_computed = false;
    _triangles_computed = false;
}

AreaLight::AreaLight(Quad n_quad, Color n_intensity) {
    area = n_quad;
    intensity = n_intensity;
    _positions_computed = false;
    _triangles_computed = false;
    compute_triangles();
}

AreaLight::~AreaLight() {
    delete[] positions;
    delete[] bl;
    delete[] tr;
}

void AreaLight::set_sample_size(int x, int y) {
    _samplex = x;
    _sampley = y;
}

void AreaLight::compute_triangles() {
    if (_triangles_computed) {
        cout << "compute triangles called again!" << endl;
        return;
    }
    bl = new Triangle(area.get_top_left(), area.get_bottom_left(), area.get_bottom_right());
    tr = new Triangle(area.get_top_left(), area.get_bottom_right(), area.get_top_right());
    _triangles_computed = true;
}

void AreaLight::compute_positions() {
    if (_positions_computed) {
        cout << "position compute called again!" << endl;
        return;
    }

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
