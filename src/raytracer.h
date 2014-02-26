#ifndef CS184_RAYTRACER_H
#define CS184_RAYTRACER_H

#include "include.h"


// RAYTRACER
class RayTracer {
public:



private:


};




// RAY TRACER CONFIGURATION
class SettingType {
public:
	SettingType(String short_name, String long_name, int argc);

	String get_short_name();
	String get_long_name();
	int    get_argc();

private:
	String short_name;
	String long_name;
	int    argc;
}

class Setting {
public:
	RayTracerOption();
    RayTracerOption(SettingType type);

	void add_argument(String arg);
    vector<String> get_arguments();
	SettingType get_setting_type();

private:
	SettingType type;
	vector<String> args;
};
#endif
