#ifndef CS184_OBJECT_H
#define CS184_OBJECT_H
#include "include.h"

#include <map>
#include "triangle.h"
#include "primitive.h"

class Object : public Primitive {
public:
	Object(String filename);

	bool did_ray_hit(Ray ray, float *intersection_t, float epsilon = 0);
	Vector3f get_normal(Point3f point);
	
private:
	struct Vertex {
		static const int INVALID_VALUE = -1;
	
		int v, vt, vn;
		Vertex();
	};

	vector<Triangle> f;
};

#endif