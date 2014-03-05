#include "raytracer.h"
#include "lodepng.h"

RayTracer::RayTracer(vector<Setting>& settings) {
    eye = Point3f(0, 0, 100);

    // create a rectangle viewport on the xy plane at z=50
    Quad port(Point3f(-50, 50, 50), Vector3f(100, 0, 0), Vector3f(0, -100, 0));
    Vector2i resolution(400, 400);
    viewport = RectViewport(port, resolution);

	// BE EXRTREMEMLY CAREFUL YOU DO NOT ASSIGN TO THE ARRAY. IF YOU DO
	// YOU MAY HAVE A MEMORY LEAK. DO NOT ASSIGN TO THE COLOR ARRAY
    color_buf = new Color*[resolution[0]];
    for(int i=0; i<resolution[0]; i++)
        color_buf[i] = new Color[resolution[1]];
    Sphere *s = new Sphere(Point3f(0,0,0), 50);
    scene.add_object(s);
    PointLight *pl = new PointLight(Point3f(-100,100,100), Color(1,1,1));
    scene.add_light(pl);
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
}

void RayTracer::trace(Cell c, int x, int y) {
    // create jittered ray grid here later
    Ray r(eye, c.get_center());

    color_buf[x][y] = scene.handle_ray(r);
}

void RayTracer::save() {
	Vector2i resolution = viewport.get_resolution();
	unsigned int width = resolution[0];
	unsigned int height = resolution[1];

	unsigned char* image = new unsigned char[width * height * 3];
	for(unsigned int x = 0; x < width; x++) {
		for(unsigned int y = 0; y < height; y++) {
			image[y * width * 3 + x * 3 + 0] = ((int)(color_buf[x][y].r*255)) & 0xff;
			image[y * width * 3 + x * 3 + 1] = ((int)(color_buf[x][y].g*255)) & 0xff;
			image[y * width * 3 + x * 3 + 2] = ((int)(color_buf[x][y].b*255)) & 0xff;
		}
	}

	// DLETE
	filename = "img/0.png";
	lodepng_encode24_file(filename, image, width, height);
	delete[] image;
}
