#include <fstream>
#include "timer.h"
#include "raytracer_input.h"
#include "raytracer.h"
#include "object.h"

int main(int argc, char** argv) {
	for(int i = 1; i < argc; i++) {
		Timer program_timer, task_timer;
		program_timer.start();
	
		// parse command line inputs and initialize
		cout << "Initializing:\t"; cout.flush();
		task_timer.start();
	
		ifstream render_stream(argv[1]);
		list<Setting> settings = RTInputParser(render_stream).get_settings();
		RayTracer rayTracer(settings);
	
		task_timer.stop();
		cout << task_timer.get_duration_s() << " s" << endl;
	
	
		// create raytracer and RENDER
		cout << "Rendering:\t"; cout.flush();
		task_timer.start();
	
		rayTracer.render();
	
		task_timer.stop();
		cout << task_timer.get_duration_s() << " s" << endl;
	
	
	
		// draw to image
		cout << "Saving:\t\t"; cout.flush();
		task_timer.start();
	
		rayTracer.save();
	
		task_timer.stop();
		cout << task_timer.get_duration_s() << " s" << endl;
	
		program_timer.stop();
		cout << "Total Time:\t" << program_timer.get_duration_s() << " s" << endl;
	}
	
	return 0;
}
