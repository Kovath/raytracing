#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "include.h"
#include "ray.h"
#include "color.h"
#include "transformation.h"

// base class for anything being rendered on the scene
class Primitive {
    public:
        virtual bool did_ray_hit(Ray r, float* intersection_t, float epsilon = 0);
        virtual Vector3f get_normal(Point3f point);

		// getters
		Color get_ambient_c();
		Color get_diffuse_c();
		Color get_specular_c();
		unsigned int get_specular_power();

        float get_reflection_c();
        float get_refraction_c();

        // setters
        void set_shading_c(Color ambient, Color diffuse, Color specular, unsigned int specular_pow);
		void set_ambient_c(Color ambient);
		void set_diffuse_c(Color diffuse);
		void set_specular_c(Color specular);
		void set_specular_power(unsigned int specular_power);

        void set_reflection_c(float new_reflection);
        void set_refraction_c(float new_refraction);
        // set the reflection and refraction both
        void set_rnr(float new_reflection, float new_refraction);

        // cout <<
        friend ostream& operator<< (ostream& ostream, const Primitive p);

        // object that stores the transformation done on the object
        Transformation T;

	private:
		// terms for determining the reflection
        Color ambient_c, diffuse_c, specular_c;
        unsigned int specular_power;

        // terms for determining reflected strength and refraction strength
        // should be from 0 - 1
        float reflection_c, refraction_c;

};

#endif // PRIMITIVE_H
