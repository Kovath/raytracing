#include "primitive.h"

float Primitive::get_ambient_c() {
	return ambient_c;
}

float Primitive::get_diffuse_c() {
	return diffuse_c;
}

float Primitive::get_specular_c() {
	return specular_c;
}

unsigned int Primitive::get_specular_power() {
	return specular_power;
}



void Primitive::set_ambient_c(float ambient) {
	ambient_c = ambient;
}

void Primitive::set_diffuse_c(float diffuse) {
	diffuse_c = diffuse;
}

void Primitive::set_specular_c(float specular) {
	specular_c = specular;
}

void Primitive::set_specular_power(float specular_pow) {
	specular_power = specular_pow;
}
	
void Primitive::set_shading_c(float ambient, float diffuse, float specular, unsigned int specular_pow) {
	ambient_c = ambient;
	diffuse_c = diffuse;
	specular_c = specular;
	specular_power = specular_pow;
}