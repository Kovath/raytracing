#ifndef RECT_CAMERA_H
#define RECT_CAMERA_H

#include "include.h"
#include "camera.h"
#include "rectviewport.h"
#include "ray.h"

class RectCamera : public Camera {
    public:
        // constructors
        RectCamera();
        RectCamera(Point3f position, Vector3f direction, Vector3f up);

        Point3f compute_focal_intersection(Ray r);
        void create_viewport();
        void create_focal_plane();
    private:
        Quad quad_at_direction(Vector3f direction);
        Quad focal_plane;
        bool _dof_created;
};

#endif // RECT_CAMERA_H
