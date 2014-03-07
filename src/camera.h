#ifndef CAMERA_H
#define CAMERA_H

#include "include.h"
#include "viewport.h"
#include "point.h"
#include "cell.h"

class Camera {
    public:
        Cell get_cell(int x, int y);

        // constructors
        Camera() {_created = false;}
        Camera(Point3f position, Vector3f direction, Vector3f up): position(position), direction(direction), up(up) {_created = false;}

        // getter functions
        Point3f get_position();
        Viewport get_viewport();
        Vector3f get_direction();
        Vector3f get_up();
        Vector2i get_resolution();
        float get_fov_x();
        float get_fov_y();

        // setter functions
        void set_resolution(Vector2i new_resolution);
        // field of view stored in angles (degrees)
        void set_fov(float x, float y);

        void set_position(Point3f pos);
        void set_viewport(Viewport view);
        void set_direction(Vector3f dir);
        void set_up(Vector3f new_up);
        void set_fov_x(float new_fov_x);
        void set_fov_y(float new_fov_y);

    protected:
        // subclasses implement this
        virtual void create_viewport() {};

        Viewport *viewport;
        Point3f position;
        Vector3f direction, up;
        Vector2i resolution;
        // angle in degrees
        float fov_x, fov_y;
        bool _created;
};

#endif // CAMERA_H
