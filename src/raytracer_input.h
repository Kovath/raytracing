#ifndef CS184_RAYTRACER_INPUT_H
#define CS184_RAYTRACER_INPUT_H
#include "include.h"

#include "raytracer_setting.h"

class RTInputParser {
public:
	RTInputParser(int argc, char* argv[]);
	
	vector<Setting> get_settings();
	
private:
	vector<Setting> settings;
};

#endif