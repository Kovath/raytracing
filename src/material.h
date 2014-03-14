#ifndef MATERIAL_H
#define MATERIAL_H

#include "include.h"
#include "lodepng.h"
#include "color.h"

class Material {
    public:
        // constructors
        Material();
        Material(String filename, int width, int height);

        Color get_color(float u, float v);

    private:
        unsigned char *data;
        int _width, _height, _rgb_size, _max;

        int _max_width, _min_height, _min_width, _max_height;
};

#endif // MATERIAL_H
