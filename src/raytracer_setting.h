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

    // material
    NEW_MATERIAL,

	// scene
	LIGHT_POINT,
	LIGHT_DIRECTION,
	LIGHT_AREA,
	OBJECT_SPHERE,
	OBJECT_TRIANGLE,
	OBJECT_OBJECT,

	// object properties
    OBJECT_USING_MATERIAL,
    OBJECT_UP_VECTOR,
    OBJECT_DIRECTION_VECTOR,
    OBJECT_REFLECTION,
    OBJECT_REFRACTION,
	OBJECT_AMBIENCE,
	OBJECT_DIFFUSE,
	OBJECT_SPECULAR,
	OBJECT_SPECULAR_POWER,

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
