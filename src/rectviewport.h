#ifndef RECT_VIEWPORT_H
#define RECT_VIEWPORT_H

#include "include.h"
#include "viewport.h"
#include "quad.h"

class RectViewport : public Viewport {
    public:
        // constructors
        RectViewport();
        RectViewport(Quad port);
        RectViewport(Quad port, Vector2i new_resolution);

        // override pure virtual function
        Cell get_cell(int x, int y);
        void recompute_cell_properties();

        // setter functions
        void set_port(Quad new_port);

        // getter functions
        Quad get_port();

    private:
        Quad port;
        Vector3f cell_width, cell_height;
};

#endif // RECT_VIEWPORT_H
