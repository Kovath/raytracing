#include "raytracer_input.h"
#include <sstream>

RTInputParser::RTInputParser(istream& in) {
	String line;
	while(in.good()) {
		String keyword;
		Setting setting;
		
		getline(in, line);
		istringstream sin(line);
		
		// figure out which keyword this is
		sin  >> keyword;
		if     (keyword == "thread") setting = Setting(CONFIG_THREADED);
		else if(keyword == "antialiasing") setting = Setting(CONFIG_ANTIALIASING);
		else if(keyword == "depthoffield") setting = Setting(CONFIG_DEPTH_OF_FIELD);
		else if(keyword == "output") setting = Setting(CONFIG_OUTPUT_FILE); 
		
		else if(keyword == "cam_position") setting = Setting(CAMERA_POSITION);
		else if(keyword == "cam_direction") setting = Setting(CAMERA_DIRECTION);
		else if(keyword == "cam_fov") setting = Setting(CAMERA_FOV); 
		else if(keyword == "cam_orientation") setting = Setting(CAMERA_ORIENTATION); 
		else if(keyword == "cam_resolution") setting = Setting(CAMERA_RESOLUTION); 
		
		else if(keyword == "point_light") setting = Setting(LIGHT_POINT);
		else if(keyword == "direction_light") setting = Setting(LIGHT_DIRECTION);
		else if(keyword == "area_light") setting = Setting(LIGHT_AREA);
		
		else if(keyword == "sphere") setting = Setting(OBJECT_SPHERE);
		else if(keyword == "triangle") setting = Setting(OBJECT_TRIANGLE);
		else if(keyword == "object") setting = Setting(OBJECT_OBJECT);
		
		else if(keyword == "ambient") setting = Setting(MATERIAL_AMBIENCE); 
		else if(keyword == "diffuse") setting = Setting(MATERIAL_DIFFUSE); 
		else if(keyword == "specular") setting = Setting(MATERIAL_SPECULAR); 
		else if(keyword == "specular_power") setting = Setting(MATERIAL_SPECULAR_POWER);
		else if(keyword == "refraction") setting = Setting(MATERIAL_REFRACTION);
		else if(keyword == "reflection") setting = Setting(MATERIAL_REFLECTION);
		
		else if(keyword == "translate") setting = Setting(TRANSFORM_TRANSLATE); 
		else if(keyword == "rotate") setting = Setting(TRANSFORM_ROTATE); 
		else if(keyword == "scale") setting = Setting(TRANSFORM_SCALE); 
		else continue;
		
		// IF NEED TO EXPAND 
		//else if(keyword == "") setting = Setting();
		
		
		// read in arguments
		String arg;
		while(sin.good()) {
			sin >> arg;
			setting.add_argument(arg);
		}
		
		settings.push_back(setting);
	}
}
	
list<Setting> RTInputParser::get_settings() {
	return settings;
}