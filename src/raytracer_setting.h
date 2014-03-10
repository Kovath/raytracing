#ifndef CS_184_RAYTRACER_SETTING
#define CS_184_RAYTRACER_SETTING
#include "include.h"


enum SettingType {
	NO_TYPE,

	// render stuff
	CONFIG_OUTPUT_FILE,
	CONFIG_THREADED, 
	CONFIG_ANTIALIASING,
	CONFIG_DEPTH_OF_FIELD,
	
	// camera
	CAMERA_POSITION,
	CAMERA_DIRECTION,
	CAMERA_FOV,
	CAMERA_ORIENTATION,
	CAMERA_RESOLUTION,
	
	// scene
	LIGHT_POINT, 
	LIGHT_DIRECTION, 
	LIGHT_AREA,
	OBJECT_SPHERE, 
	OBJECT_TRIANGLE, 
	OBJECT_OBJECT,
	
	// material
	MATERIAL_AMBIENCE,
	MATERIAL_DIFFUSE,
	MATERIAL_SPECULAR,
	MATERIAL_SPECULAR_POWER,
	
	// transformations
	TRANSFORM_TRANSLATE,
	TRANSFORM_SCALE,
	TRANSFORM_ROTATE
};


class Setting {
public:
    Setting(SettingType type = NO_TYPE);
	
	void add_argument(String arg);
    vector<String> get_arguments() const;
	SettingType get_type() const;
	
private:
	SettingType type;
	vector<String> args;
};

#endif