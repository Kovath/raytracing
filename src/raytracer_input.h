#ifndef CS184_RAYTRACER_INPUT_H
#define CS184_RAYTRACER_INPUT_H
#include "include.h"

#include <istream>
#include "raytracer_setting.h"

class RTInputParser {
public:
	RTInputParser(istream& in);
	
	list<Setting> get_settings();
	
private:
	list<Setting> settings;
};

#endif