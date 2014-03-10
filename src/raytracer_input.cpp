#include "raytracer_input.h"
#include <sstream>

RTInputParser::RTInputParser(int argc, char* argv[]) {
	for(int i = 0; i < argc; i++) {
		if(argv[i][0] != '-') continue;
		Setting setting(argv[i]);
		
		int argCount = 0;
		while(argCount < setting.get_type().get_argc()) {
			setting.add_argument(argv[++i]);
			argCount++;
		}
		
		settings.push_back(setting);
	}
}

RTInputParser::RTInputParser(istream& in) {
	String line;
	String keyword;
	
	while(in.good()) {
		getline(in, line);
		
		istringstream sin(line);
		sin >> keyword;
	}
}
	
vector<Setting> RTInputParser::get_settings() {
	return settings;
}