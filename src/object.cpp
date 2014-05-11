#include "object.h"
#include "triangle.h"
#include <fstream>
#include <sstream>

Object::Vertex::Vertex() : v(Vertex::INVALID_VALUE), vt(Vertex::INVALID_VALUE), vn(Vertex::INVALID_VALUE) {}

Object::Object(String filename) {
	// parse all the data from the file into memory
	vector<Point3f> v;
	vector<Vector3f> vt;
	vector<Vector3f> vn;
	
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
				vector<Vertex> vertices;
				
				while(sin.good()) {
					sin >> token;
					istringstream indexes(token);
					Vertex vertex;
					
					indexes >> vertex.v;
					if(indexes.get() == '/') {
						if(indexes.peek() != '/') {
							indexes >> vertex.vt;
						} else {
							vertex.vt = Vertex::INVALID_VALUE;
						}
					}
					if(indexes.get() == '/') {
						indexes >> vertex.vn;
					}
					
					vertex.v--; vertex.vt--; vertex.vn--;
					vertices.push_back(vertex);
				}
				
				// generate triangles for each part of the face. assume convex
				for(unsigned int i = 2; i < vertices.size(); i++) {
					f.push_back(Triangle(v[vertices[0].v], v[vertices[i - 1].v], v[vertices[i].v]));
				}
			}
		}
	} else {
		return;
	}
	
	// cout << endl;
	// for(unsigned int i = 0; i < f.size(); i++) {
		// cout << "Triangle " << i << ":\t";
		// cout << "(" << f[i].get_p0()[0] << ", " << f[i].get_p0()[1] << ", " << f[i].get_p0()[2] << ")" << "\t";
		// cout << "(" << f[i].get_p1()[0] << ", " << f[i].get_p1()[1] << ", " << f[i].get_p1()[2] << ")" << "\t";
		// cout << "(" << f[i].get_p2()[0] << ", " << f[i].get_p2()[1] << ", " << f[i].get_p2()[2] << ")" << "\t";
		// cout << endl;
	// }
}

bool Object::did_ray_hit(Ray ray, float *intersection_t, float epsilon) {
	ray.set_origin(T.get_inverse_transformation() * ray.get_origin());
	ray.set_point(T.get_inverse_transformation().linear() * ray.get_point());
	
	float INVALID_T = 0.0;
	float closest_t = INVALID_T;
	for(unsigned int i = 0; i < f.size(); i++) {
		float ray_hit_t = 0.0;
		if(f[i].did_ray_hit(ray, &ray_hit_t, epsilon)) {
			if(closest_t == INVALID_T || ray_hit_t < closest_t) {
				closest_t = ray_hit_t;
			}
		}
	}
	if(closest_t == INVALID_T) return false;
	
	*intersection_t = closest_t;
	return true;
}

Vector3f Object::get_normal(Point3f point) {
	Vector3f normal(0, 0, 0);
	bool has = false;
	for(vector<Triangle>::iterator it = f.begin(); it != f.end(); it++) {
		if((*it).contains_point(point)) {
			has = true;
			normal += (*it).get_normal(point);
		}
	}
	
	if(!has) return Vector3f(0, 0, 1);
	normal.normalize();
	return normal;
}