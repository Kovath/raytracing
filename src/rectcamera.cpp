#include "rectcamera.h"

#define PI 3.14159265

// constructors
RectCamera::RectCamera() {}
RectCamera::RectCamera(Point3f position, Vector3f direction, Vector3f up) {
    this->position = position;
    this->direction = direction;
    this->up = up;
}

void RectCamera::create_viewport() {
    // get the direction of the left vector (from the center point to the mid-left point)
    Vector3f left_v = up.cross(direction);
    left_v.normalize();
    // solve tan(angle) = opposite / adj to get the magnitude of the left vector
    // norm() returns magnititude of the vector
    float left_mag = direction.norm() * tan(fov_x * PI / 180.0);
    // multiple normalized vector with magnitude to get the final left vector
    left_v *= left_mag;

    // repeat process for upwards vector
    Vector3f upwards_v = up;
    upwards_v.normalize();
    // solve for magnitude of the up vector (dependent on the field of view y angle)
    float upwards_mag = direction.norm() * tan(fov_y * PI / 180.0);
    upwards_v *= upwards_mag;

    // the top left point is the combination of the two vectors
    // and the position+direction start point
    Point3f top_left_point = position + direction + left_v + upwards_v;
    // the width is the twice the negative of the left vector (since width heads to the right side)
    Vector3f width = -2 * left_v;
    // the height heads down so should be -2*height as well
    Vector3f height = -2 * upwards_v;
    // create the port
    Quad port(top_left_point, width, height);

    if (_created) {
        delete[] viewport;
    }

    // port is created here, but resolution is stored in the class
    viewport = new RectViewport(port, resolution);
    _created = true;
}
