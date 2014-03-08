#include "raytracer_setting.h"

const SettingType SettingType::NO_TYPE("", "", 0);
const SettingType SettingType::POINT_LIGHT("pl", "point-light", 6);
const SettingType SettingType::DIRECTION_LIGHT("dl", "direction-light", 6);
const SettingType SettingType::THREADING("t", "threading", 1);
const SettingType SettingType::OBJECT("obj", "object", 1);

const SettingType* SettingType::TYPES[] = {
	&SettingType::NO_TYPE,
	&SettingType::POINT_LIGHT,
	&SettingType::DIRECTION_LIGHT,
	&SettingType::THREADING,
	&SettingType::OBJECT
};


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

bool SettingType::matches(String option) const {
	if(option[0] == '-' && option[1] == '-') {
		return option == get_long_command();
	} else if(option[0] == '-') {
		return option == get_short_command();
	}
	
	return false;
}

String SettingType::get_short_name() const {
	return short_name;
}

String SettingType::get_short_command() const {
	return "-" + get_short_name();
}

String SettingType::get_long_name() const {
	return long_name;
}

String SettingType::get_long_command() const {
	return "--" + get_long_name();
}

int SettingType::get_argc() const {
	return argc;
}






Setting::Setting(SettingType type) {
	this->type = type;
}

Setting::Setting(String option) {
	for(int i = 0; i < (int)(sizeof(SettingType::TYPES) / sizeof(SettingType)); i++) {
		if(SettingType::TYPES[i]->matches(option)) {
			type = *(SettingType::TYPES[i]);
		}
	}
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