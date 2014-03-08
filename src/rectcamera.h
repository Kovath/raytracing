#ifndef RECT_CAMERA_H
#define RECT_CAMERA_H

#include "include.h"
#include "camera.h"
#include "rectviewport.h"

class RectCamera : public Camera {
    public:
        // constructors
        RectCamera();
        RectCamera(Point3f position, Vector3f direction, Vector3f up);

    protected:
        void create_viewport();
};

#endif // RECT_CAMERA_H
