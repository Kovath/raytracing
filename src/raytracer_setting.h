#ifndef CS_184_RAYTRACER_SETTING
#define CS_184_RAYTRACER_SETTING
#include "include.h"

class SettingType {
public:
	static const SettingType* TYPES[];
	static const SettingType NO_TYPE; // "", "", 0
	
	// scene configuration
	static const SettingType POINT_LIGHT; // "pl", "point-light", 6
	static const SettingType DIRECTION_LIGHT; // "dl", "direction-light", 6
	static const SettingType OBJECT; // "obj", "object", 1
	
	// render settings
	static const SettingType THREADING; // "t", "threading", 1
	static const SettingType ANTIALIASING; // "aa", "anti-aliasing", 1
	
	
	bool   matches(String option) const;
	
	String get_short_name() const;
	String get_short_command() const;
	String get_long_name() const;
	String get_long_command() const;
	int    get_argc() const;
	
	friend class Setting;
	
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
    Setting(String option);
	
	void add_argument(String arg);
    vector<String> get_arguments() const;
	SettingType get_type() const;
	
private:
	SettingType type;
	vector<String> args;
};

#endif