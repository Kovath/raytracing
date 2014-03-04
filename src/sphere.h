#ifndef SPHERE_H
#define SPHERE_H

#include "include.h"
#include "primitive.h"

class Sphere : public virtual Primitive {
    public:
        // constructors
        Sphere();
        Sphere(Point3f center, float radius);

        // sets the intersection time to float pointer t if ray hits object
        bool did_ray_hit(Ray ray, float *intersection_t);

		// setters
		void set_center(Point3f center);
		void set_radius(float radius);

		// getters
		Point3f get_center();
		float get_radius();

	private:
		// center and radius define a sphere
        Point3f center;
        float radius;
};

#endif // SPHERE_H
