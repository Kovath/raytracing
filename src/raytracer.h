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
	friend class Setting;

	static const SettingType NO_TYPE; // "", "", 0
	static const SettingType POINT_LIGHT; // "pl", "point-light", 6
	static const SettingType DIRECTION_LIGHT; // "dl", "direction-light", 6
	
	//SettingType();
	
	bool   match(String option);
	String get_short_name();
	String get_long_name();
	int    get_argc();

private:
	SettingType();
	SettingType(String short_name, String long_name, int argc);

	String short_name;
	String long_name;
	int    argc;
};


class Setting {
public:
    Setting(SettingType type = SettingType::NO_TYPE);
    
	void add_argument(String arg);
    vector<String> get_arguments();
	SettingType get_type();
	
private:
	SettingType type;
	vector<String> args;
};
#endif
