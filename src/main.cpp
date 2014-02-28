#include "timer.h"
#include "raytracer_input.h"
#include "raytracer.h"
#include <unistd.h>

int main(int argc, char** argv) {
	Timer timer;

	// parse command line inputs
	cout << "Parsing input: ";
	timer.start();
	
	vector<Setting> settings = RTInputParser(argc, argv).get_settings();
	
	timer.stop();
	cout << timer.get_duration_s() << " s" << endl;
	
	
	
    // create raytracer and RENDER
	cout << "Raytracer Rendering: ";
	timer.start();
	
	RayTracer rayTracer(settings);
    rayTracer.render();
	
	timer.stop();
	cout << timer.get_duration_s() << " s" << endl;
	
	
	
	// draw to image
    cout << "Saving to image: ";
	timer.start();
	
	cout << "NOT IMPLMENTED ";
	
	timer.stop();
	cout << timer.get_duration_s() << " s" << endl;
	
	return 0;
}


// CODE FOR OUTPUTTING COMMAND LINE ARGUMENTS
// for(unsigned int i = 0; i < settings.size(); i++) {
	// Setting setting = settings[i];
	// vector<String> args = setting.get_arguments();
	
	// cout << setting.get_type().get_short_command() << " ";
	// for(unsigned int j = 0; j < args.size(); j++) {
		// cout << args[j] << " ";
	// }
	// cout << endl;
// }