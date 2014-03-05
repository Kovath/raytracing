#include "primitive.h"

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



void Primitive::set_ambient_c(Color ambient) {
	ambient_c = ambient;
}

void Primitive::set_diffuse_c(Color diffuse) {
	diffuse_c = diffuse;
}

void Primitive::set_specular_c(Color specular) {
	specular_c = specular;
}

void Primitive::set_specular_power(float specular_pow) {
	specular_power = specular_pow;
}

void Primitive::set_shading_c(Color ambient, Color diffuse, Color specular, unsigned int specular_pow) {
	ambient_c = ambient;
	diffuse_c = diffuse;
	specular_c = specular;
	specular_power = specular_pow;
}
