#include "timer.h"
#include "raytracer_input.h"
#include "raytracer.h"
#include <unistd.h>

int main(int argc, char** argv) {
	Timer program_timer;
	Timer task_timer;

	program_timer.start();
	
	// parse command line inputs
	cout << "Parsing input: ";
	task_timer.start();
	
	vector<Setting> settings = RTInputParser(argc, argv).get_settings();
	
	task_timer.stop();
	cout << task_timer.get_duration_s() << " s" << endl;
	
	
	
    // create raytracer and RENDER
	cout << "Raytracer Rendering: ";
	task_timer.start();
	
	RayTracer rayTracer(settings);
    rayTracer.render();
	
	task_timer.stop();
	cout << task_timer.get_duration_s() << " s" << endl;
	
	
	
	// draw to image
    cout << "Saving to image: ";
	task_timer.start();
	
	rayTracer.save();
	
	task_timer.stop();
	cout << task_timer.get_duration_s() << " s" << endl;
	
	
	program_timer.stop();
	cout << endl << "Total Time: " << program_timer.get_duration_s() << " s" << endl;
	
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