#include <fstream>
#include "timer.h"
#include "raytracer_input.h"
#include "raytracer.h"
#include "object.h"

int main(int argc, char** argv) {
	for(int i = 1; i < argc; i++) {
		cout << "Rendering " << argv[i] << endl;
		Timer program_timer, task_timer;
		program_timer.start();
		
		// parse command line inputs and initialize
		cout << "Parsing input: ";
		task_timer.start();
		
		ifstream render_stream(argv[i]);
		list<Setting> settings = RTInputParser(render_stream).get_settings();
		RayTracer rayTracer(settings);
		
		task_timer.stop();
		cout << task_timer.get_duration_s() << " s" << endl;
		
		
		// create raytracer and RENDER
		cout << "Raytracer Rendering: ";
		task_timer.start();
		
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
		cout << "Total Time: " << program_timer.get_duration_s() << " s" << endl << endl;
	}
	
	return 0;
}