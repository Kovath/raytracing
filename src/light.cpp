#include "light.h"

Point3f* Light::get_positions(int *num_ptr) { 
	return NULL; 
}

Color Light::get_intensity() {
    return intensity;
}

void Light::set_intensity(Color new_i) {
    if (new_i.r < 0 || new_i.g < 0 || new_i.b < 0) {
        printf("ERROR :: RGB values of intensity cannot be less than 0\n");
    }
    else {
        intensity = new_i;
    }
}
