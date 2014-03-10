#include "object.h"
#include <fstream>
#include <sstream>

Object::FaceVertex::FaceVertex() : v(FaceVertex::INVALID_VALUE), vt(FaceVertex::INVALID_VALUE), vn(FaceVertex::INVALID_VALUE) {}

Object::Object(String filename) {
	// parse all the data from the file into memory
	ifstream fin(filename.c_str());
	if(fin.is_open()) {
		while(fin.good()) {
			String line; getline(fin, line);
			
			istringstream sin(line);
			String token; sin >> token;	
			if(token == "v") {
				float x, y, z;
				sin >> x; sin >> y; sin >> z;
				v.push_back(Point3f(x, y, z));
				
			} else if(token == "vt") {
				float x, y, z;
				sin >> x; sin >> y; sin >> z;
				vt.push_back(Point3f(x, y, z));
			
			} else if(token == "vn") {
				float x, y, z;
				sin >> x; sin >> y; sin >> z;
				vn.push_back(Vector3f(x, y, z));
			
			} else if(token == "f") {
				Face face;
				while(sin.good()) {
					sin >> token;
					istringstream indexes(token);
					
					FaceVertex vertex;
					indexes >> vertex.v;
					if(indexes.get() == '/') {
						if(indexes.peek() != '/') {
							indexes >> vertex.vt;
						} else {
							vertex.vt = FaceVertex::INVALID_VALUE;
						}
					}
					if(indexes.get() == '/') {
						indexes >> vertex.vn;
					}
					face.vertices.push_back(vertex);
				}
				
				if(face.vertices.size() < 3) continue;
				f.push_back(face);
			}
		}
	} else {
		return;
	}
	
	for(unsigned int i = 0; i < v.size(); i++) {
		cout << "v " << v[i] << endl;
	}
	cout << endl;
	for(unsigned int i = 0; i < vn.size(); i++) {
		cout << "vn " << vn[i] << endl;
	}
	cout << endl;
	for(unsigned int i = 0; i < vt.size(); i++) {
		cout << "vt " << vt[i] << endl;
	}
	cout << endl;
	for(unsigned int i = 0; i < f.size(); i++) {
		cout << "f ";
		for(unsigned int j = 0; j < f[i].vertices.size(); j++) {
			cout << f[i].vertices[j].v << "/" << f[i].vertices[j].vt << "/" << f[i].vertices[j].vn << " ";
		}
		cout << endl;
	}
}


bool Object::did_ray_hit(Ray ray, float *intersection_t, float epsilon) {
	
	
	return false;
}

Vector3f Object::get_normal(Point3f point) {
	// kind of unsure how this goes
	return Vector3f(0.0, 0.0, 0.0);
}