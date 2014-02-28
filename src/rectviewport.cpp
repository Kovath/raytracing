#include "rectviewport.h"

// the origin (0, 0) is the top left of the quad
Cell RectViewport::get_cell(int x, int y) {
    Cell c(port.get_top_left() + x*cell_width - y*cell_height,
            cell_width,
            cell_height);
    return c;
}

void RectViewport::recompute_cell_properties() {
    // compute the cell height and width
    cell_width = port.get_height()/resolution[0];
    cell_height = port.get_width()/resolution[1];
}

void RectViewport::set_port(Quad new_port) {
    port = new_port;
    recompute_cell_properties();
}

Quad RectViewport::get_port() {
    return port;
}
