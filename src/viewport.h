#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "include.h"
#include "cell.h"

// base class for all sorts of viewports
class Viewport {
    public:
        // returns a cell given pixel indices
        virtual Cell get_cell(int x, int y) { return Cell(); };

        // setter functions
        void set_resolution(Vector2i new_resolution);

        // getter functions
        Vector2i get_resolution();

    private:
        // [ w ]
        // [ h ]
        Vector2i resolution;
};

#endif // VIEWPORT_H
