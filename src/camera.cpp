#include "camera.h"

// constructors
Camera::Camera() {
	_created = false;
}

Camera::Camera(Point3f position, Vector3f direction, Vector3f up): position(position), direction(direction), up(up) {
	_created = false;
}

// getter functions
Point3f Camera::get_position() {
    return position;
}

Viewport Camera::get_viewport() {
    return *viewport;
}

Vector3f Camera::get_direction() {
    return direction;
}

Vector2i Camera::get_resolution() {
    return resolution;
}

Vector3f Camera::get_up() {
    return up;
}

float Camera::get_fov_x() {
    return fov_x;
}

float Camera::get_fov_y() {
    return fov_y;
}

// setter functions
void Camera::set_fov(float x, float y) {
    fov_x = x;
    fov_y = y;
    create_viewport();
}

void Camera::set_position(Point3f pos) {
    position = pos;
}

void Camera::set_viewport(Viewport view) {
    delete[] viewport;
    *viewport = view;
}

void Camera::set_direction(Vector3f dir) {
    direction = dir;
}

void Camera::set_resolution(Vector2i new_resolution) {
    resolution = new_resolution;
}

void Camera::set_up(Vector3f new_up) {
    up = new_up;
}

void Camera::set_fov_x(float new_fov_x) {
    fov_x = new_fov_x;
}

void Camera::set_fov_y(float new_fov_y) {
    fov_y = new_fov_y;
}

Cell Camera::get_cell(int x, int y) {
    return viewport->get_cell(x, y);
}
