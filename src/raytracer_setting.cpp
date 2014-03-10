#include "raytracer_setting.h"

Setting::Setting(SettingType type) {
	this->type = type;
}

void Setting::add_argument(String arg) {
	args.push_back(arg);
}

vector<String> Setting::get_arguments() const {
	return args;
}

SettingType Setting::get_type() const {
	return type;
}