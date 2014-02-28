#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "include.h"
#include "cell.h"

// base class for all sorts of viewports
class Viewport {
    public:
        // returns a cell given pixel indices
        Cell virtual get_cell(int x, int y) =0;

        // setter functions
        void set_resolution(Vector2f new_resolution);

        // getter functions
        Vector2f get_resolution();

    protected:
        // [ w ]
        // [ h ]
        Vector2f resolution;
};

#endif // VIEWPORT_H
