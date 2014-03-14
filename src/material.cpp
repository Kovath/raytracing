#include "material.h"

Material::Material() {

}

Material::Material(String filename, int width, int height) {
    _max_width = 0;
    _min_width = 99999;

    _max_height = 0;
    _min_height = 999999;

    _width = width;
    _height = height;
    _rgb_size = 3;
    _max = width * height * _rgb_size;

    data = new unsigned char[_max + _rgb_size];
    lodepng_decode24_file(&data, (unsigned int *)&width, (unsigned int *)&height, filename.data());
}

// get color based on spherical coords (u and v should be from -1 to 1)
Color Material::get_color(float u, float v) {
    if (u < -1 || v < -1 || u > 1 || v > 1) {
        printf("error: u and v should be between -1 and 1\n");
        printf("u:%f and v:%f\n", u, v);
        return Color(0,0,0);
    }

    if (u < 0) u = 0;
    if (v < 0) v = 0;

    //int x = (int)(_width/2.0 + u*(_width/2.0));
    //int y = (int)(_height/2.0 + v*(_height/2.0));
    int x = (int)(u*_width);
    int y = (int)(v*_height);

    /*
    // DEBUG USE ONLY
    printf("x:%d, y:%d\n", x, y);
    if (x > _max_width) {
        _max_width = x;
    }
    if (x < _min_width) {
        _min_width = x;
    }
    if (y > _max_height) {
        _max_height = y;
    }
    if (y < _min_height) {
        _min_height = y;
    }
    printf("min_width:%d, max_width:%d || min_height:%d, max_height:%d\n", _min_width, _max_width, _min_height, _max_height);
    */

    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x > _width) x = _width;
    if (y > _height) y = _height;
    // points to the bytes
    unsigned char *ptr = data+(x + y*_width)*_rgb_size;

    // memory leak preventage
    if ((x + y*_width)*_rgb_size + 2 >= _max) {
        return Color(0,0,0);
    }

    float r = *ptr / 255.0;
    float g = *(ptr + 1) / 255.0;
    float b = *(ptr + 2) / 255.0;

    return Color(r, g, b);
}
