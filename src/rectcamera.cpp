#include "rectcamera.h"

#define PI 3.14159265

// constructors
RectCamera::RectCamera() {
    _dof_created = false;
}
RectCamera::RectCamera(Point3f position, Vector3f direction, Vector3f up) {
    this->position = position;
    this->direction = direction;
    this->up = up;
    _dof_created = false;
}

void RectCamera::create_viewport() {
    Quad port = quad_at_direction(this->direction);

    if (_created) {
        delete[] viewport;
    }

    // port is created here, but resolution is stored in the class
    viewport = new RectViewport(port, resolution);
    _created = true;
}

void RectCamera::create_focal_plane() {
    Vector3f direction = this->direction * focal_length;
    focal_plane = quad_at_direction(direction);
    _dof_created = true;
}

Point3f RectCamera::compute_focal_intersection(Ray r) {
    if (!_dof_created) return Point3f(0, 0, 0);

    Point3f ray_point = r.get_point();
    Point3f ray_origin = r.get_origin();

    // B - A
    Point3f e0 = focal_plane.get_height();
    // C - A
    Point3f e1 = focal_plane.get_width();

    // normal is cross product of the edges
    Point3f n = e0.cross(e1);

    // we can now find the time the ray hits the plane
    // t = (dot(n, point of triangle) - dot(n, ray.origin)) / (dot(n, ray.point))
    float bottom = n.dot(ray_point);

    // if the bottom is 0 then the ray is parallel to the plane (return false)
    if (bottom == 0) return Point3f(0,0,0);

    float intersection_plane_t = (n.dot(focal_plane.get_top_left()) - n.dot(ray_origin)) / bottom;

    // if the time the ray hits the plane is less than 0, the plane is behind the ray
    if (intersection_plane_t < 0)
        return Point3f(0, 0, 0);
    // otherwise calculate the point on the plane that the ray hits
    else
        return ray_origin + intersection_plane_t*ray_point;
}

Quad RectCamera::quad_at_direction(Vector3f direction) {
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
    return Quad(top_left_point, width, height);
}
