#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "include.h"
#include "ray.h"
#include "color.h"

// base class for anything being rendered on the scene
class Primitive {
    public:
        virtual bool did_ray_hit(Ray r, float* intersection_t, float epsilon=0) { printf("primitive did_ray_hit!!!!\n"); return false; }
        virtual Vector3f get_normal(Point3f point) { printf("primitive get_normal??\n"); return Vector3f(0, 0, 0); }

		// getters
		Color get_ambient_c();
		Color get_diffuse_c();
		Color get_specular_c();
		unsigned int get_specular_power();

        // setters
        void set_shading_c(Color ambient, Color diffuse, Color specular, unsigned int specular_pow);
		void set_ambient_c(Color ambient);
		void set_diffuse_c(Color diffuse);
		void set_specular_c(Color specular);
		void set_specular_power(float specular_power);

        // cout <<
        friend ostream& operator<< (ostream& ostream, const Primitive p) { return ostream << "Primitive" << endl; };

	private:
		// terms for determining the reflection
        Color ambient_c, diffuse_c, specular_c;
        unsigned int specular_power;
};

#endif // PRIMITIVE_H
