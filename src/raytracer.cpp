#include "raytracer.h"
const SettingType SettingType::NO_TYPE("", "", 0);
const SettingType SettingType::POINT_LIGHT("pl", "point-light", 6);
const SettingType SettingType::DIRECTION_LIGHT("dl", "direction-light", 6);

SettingType::SettingType() {
	this->short_name = "";
	this->long_name = "";
	this->argc = 0;
}

SettingType::SettingType(String short_name, String long_name, int argc) {
	this->short_name = short_name;
	this->long_name = long_name;
	this->argc = argc;
}

bool SettingType::match(String option) {
	if(option[0] == '-') {
		return option == ("-" + short_name);
	} else if(option[0] == '-' && option[1] == '-') {
		return option == ("--" + long_name);
	}
	
	return false;
}

String SettingType::get_short_name() {
	return short_name;
}

String SettingType::get_long_name() {
	return long_name;
}

int SettingType::get_argc() {
	return argc;
}






Setting::Setting(SettingType type) {
	this->type = type;
}

void Setting::add_argument(String arg) {
	args.push_back(arg);
}

vector<String> Setting::get_arguments() {
	return args;
}

SettingType Setting::get_type() {
	return type;
}