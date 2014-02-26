#include "raytracer.h"

SettingType::SettingType(String short_name, String long_name, int argc) {
	this->short_name = short_name;
	this->long_name = long_name;
	this->argc = argc;
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






Setting::Setting() {
	this->type = 
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

SettingType Setting::get_setting_type() {
	return type;
}





RayTracerSetting::RayTracerSetting() {
	this->option = "";
}

RayTracerSetting::RayTracerSetting(String option) {
	this->option = option;
}


RayTracerSetting::add_argument(String arg) {
	args.push_back(arg);
}

RayTracerSetting::~RayTracerSetting() {

}