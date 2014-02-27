#include "raytracer.h"
#include "lib/Eigen/Dense"

using Eigen::MatrixXd;

int main(int argc, char** argv) {
	MatrixXd m(2,2);
	m(0,0) = 3;
	m(1,0) = 2.5;
	m(0,1) = -1;
	m(1,1) = m(1,0) + m(0,1);
	std::cout << m << std::endl;


    // parse command line inputs
	vector<Setting> settings;
	for(int i = 0; i < argc; i++) {
		Setting setting;
		
		
		int argCount = 0;
		while(argCount < setting.get_type().get_argc()) {
			setting.add_argument(argv[++i]);
			argCount++;
		}
		
		settings.push_back(setting);
	}
    
	//cout << settings << endl;
    // create raytracer and EXECUTE
    
    return 0;
}