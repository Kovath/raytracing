#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "include.h"
#include "ray.h"

// base class for anything being rendered on the scene
class Primitive {
    public:
        virtual bool did_ray_hit(Ray r, float* intersection_t, float epsilon=0) { printf("primitive did_ray_hit!!!!\n"); return false; };

		// getters
		float get_ambient_c();
		float get_diffuse_c();
		float get_specular_c();
		unsigned int get_specular_power();

        // setters
        void set_shading_c(float ambient, float diffuse, float specular, unsigned int specular_pow);
		void set_ambient_c(float ambient);
		void set_diffuse_c(float diffuse);
		void set_specular_c(float specular);
		void set_specular_power(float specular_power);

        // cout <<
        friend ostream& operator<< (ostream& ostream, const Primitive p) { return ostream << "Primitive" << endl; };

	private:
		// terms for determining the reflection
        float ambient_c, diffuse_c, specular_c;
        unsigned int specular_power;
};

#endif // PRIMITIVE_H
