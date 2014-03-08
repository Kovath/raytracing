#include "rectviewport.h"

RectViewport::RectViewport() {}
RectViewport::RectViewport(Quad port): port(port) {
	recompute_cell_properties();
}

RectViewport::RectViewport(Quad port, Vector2i new_resolution): port(port) {
	set_resolution(new_resolution);
	recompute_cell_properties();
}




// the origin (0, 0) is the top left of the quad
Cell RectViewport::get_cell(int x, int y) {
    Point3f top_left = port.get_top_left() + x*cell_width + y*cell_height;
	Cell c( top_left,
            cell_width,
            cell_height);
    return c;
}

void RectViewport::recompute_cell_properties() {
    // compute the cell height and width
    cell_width = port.get_width()/(get_resolution()[0]);
    cell_height = port.get_height()/(get_resolution()[1]);

}

void RectViewport::set_port(Quad new_port) {
    port = new_port;
    recompute_cell_properties();
}

Quad RectViewport::get_port() {
    return port;
}
