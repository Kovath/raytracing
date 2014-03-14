#include "primitive.h"

bool Primitive::did_ray_hit(Ray r, float* intersection_t, float epsilon) {
	printf("primitive did_ray_hit!!!!\n");
	return false;
}

Vector3f Primitive::get_normal(Point3f point) {
	printf("primitive get_normal??\n");
	return Vector3f(0, 0, 0);
}

Color Primitive::get_material_color_for_point(Point3f point, Material *m) {
    printf("primitive get_material_color??\n");
    return Color(0, 0, 0);
}

Vector3f Primitive::get_up_v() {
    return up_v;
}

Vector3f Primitive::get_direction_v() {
    return direction_v;
}

Color Primitive::get_ambient_c() {
	return ambient_c;
}

Color Primitive::get_diffuse_c() {
	return diffuse_c;
}

Color Primitive::get_specular_c() {
	return specular_c;
}

unsigned int Primitive::get_specular_power() {
	return specular_power;
}

float Primitive::get_reflection_c() {
    return reflection_c;
}

float Primitive::get_refraction_c() {
    return refraction_c;
}


void Primitive::set_ambient_c(Color ambient) {
	ambient_c = ambient;
}

void Primitive::set_diffuse_c(Color diffuse) {
	diffuse_c = diffuse;
}

void Primitive::set_specular_c(Color specular) {
	specular_c = specular;
}

void Primitive::set_specular_power(unsigned int specular_pow) {
	specular_power = specular_pow;
}

void Primitive::set_reflection_c(float new_reflection) {
    reflection_c = new_reflection;
}

void Primitive::set_refraction_c(float new_refraction) {
    refraction_c = new_refraction;
}

void Primitive::set_up_v(Vector3f new_up_v) {
    up_v = new_up_v;
}

void Primitive::set_direction_v(Vector3f new_direction_v) {
    direction_v = new_direction_v;
}

// set the reflection and refraction both
void Primitive::set_rnr(float new_reflection, float new_refraction) {
    reflection_c = new_reflection;
    refraction_c = new_refraction;
}

void Primitive::set_shading_c(Color ambient, Color diffuse, Color specular, unsigned int specular_pow) {
	ambient_c = ambient;
	diffuse_c = diffuse;
	specular_c = specular;
	specular_power = specular_pow;
}

ostream& operator<< (ostream& ostream, const Primitive p) {
	return ostream << "Primitive" << endl;
};
