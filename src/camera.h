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
        Camera();
        Camera(Point3f position, Vector3f direction, Vector3f up);

        // getter functions
        Point3f get_position();
        Viewport get_viewport();
        Vector3f get_direction();
        Vector3f get_up();
        Vector2i get_resolution();
        Vector2i get_aperature_ray_count();
        float get_fov_x();
        float get_fov_y();
        float get_focal_length();
        int get_aperature_size();

        // setter functions
        void set_resolution(Vector2i new_resolution);
        // field of view stored in angles (degrees)
        void set_fov(float x, float y);
        // subclasses implement this
        virtual void create_viewport() {};

        void set_position(Point3f pos);
        void set_viewport(Viewport view);
        void set_direction(Vector3f dir);
        void set_up(Vector3f new_up);
        void set_fov_x(float new_fov_x);
        void set_fov_y(float new_fov_y);
        void set_focal_length(float new_focal);
        void set_aperature_ray_count(Vector2i new_rays);
        void set_aperature_size(int new_size);

    protected:
        Viewport *viewport;
        Point3f position;
        Vector3f direction, up;
        Vector2i resolution, aperature_ray_count;
        // angle in degrees
        float fov_x, fov_y;

        float focal_length;
        int aperature_size;

        bool _created;
};

#endif // CAMERA_H
