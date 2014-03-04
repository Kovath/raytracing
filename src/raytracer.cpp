#include "raytracer.h"
#include "lodepng.h"

RayTracer::RayTracer(vector<Setting>& settings) {
    eye = Point3f(0, 0, 100);

    // create a rectangle viewport on the xy plane at z=50
    Quad port(Point3f(-50, 50, 50), Vector3f(100, 0, 0), Vector3f(0, -100, 0));
    Vector2i resolution(1000, 1000);
    RectViewport viewport(port, resolution);

    color_buf = new Color*[resolution[0]];
    for(int i=0; i<resolution[0]; i++)
        color_buf[i] = new Color[resolution[1]];

    scene.add_object(Sphere(Point3f(0,0,0), 25));
}

RayTracer::~RayTracer() {
    for (int i=0; i<viewport.get_resolution()[0]; i++)
        delete (color_buf[i]);
    delete (color_buf);
}

void RayTracer::render() {
    Vector2i resolution = viewport.get_resolution();
    int width = resolution[0];
    int height = resolution[1];

    // fill out the color array
    int i, j;
    for (j=0; j<height; j++) {
        for (i=0; i<width; i++) {
            trace(viewport.get_cell(i, j), i, j);
        }
    }

    // write to the image file
}

void RayTracer::trace(Cell c, int x, int y) {
    // create jittered ray grid here later
    Ray r(eye, c.get_center());

    color_buf[x][y] = scene.handle_ray(r);
}

void RayTracer::save() {
	
}
