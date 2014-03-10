#ifndef CS184_RAYTRACER_INPUT_H
#define CS184_RAYTRACER_INPUT_H
#include "include.h"

#include <istream>
#include "raytracer_setting.h"

class RTInputParser {
public:
	RTInputParser(int argc, char* argv[]);
	RTInputParser(istream& in);
	
	vector<Setting> get_settings();
	
private:
	vector<Setting> settings;
};

#endif