#include "raytracer.h"

int main(int argc, char** argv) {
    // parse command line inputs
	vector<RayTracerSetting> settings;
	for(int i = 0; i < argc; i++) {
		RayTracerSetting setting(String(argv[i]));
		
		
		
		settings.push_back(setting);
	}
    
    // create raytracer and EXECUTE
    
    return 0;
}