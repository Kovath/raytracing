#include "raytracer_input.h"
#include "raytracer.h"

int main(int argc, char** argv) {
	// parse command line inputs
	cout << "Parsing input" << endl;
	vector<Setting> settings = RTInputParser(argc, argv).get_settings();

    // create raytracer and EXECUTE
	RayTracer rayTracer(settings);
    
    return 0;
}