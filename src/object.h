#ifndef CS184_OBJECT_H
#define CS184_OBJECT_H
#include "include.h"

#include "primitive.h"

class Object : public Primitive {
public:
	Object(String filename);

	bool did_ray_hit(Ray ray, float *intersection_t, float epsilon = 0);
	Vector3f get_normal(Point3f point);
	
private:
	struct FaceVertex {
		static const int INVALID_VALUE = -1;
	
		int v, vt, vn;
		FaceVertex();
	};
	
	struct Face {
		vector<FaceVertex> vertices;
	};

	vector<Point3f> v;
	vector<Point3f> vt;
	vector<Vector3f> vn;
	vector<Face> f;
};

#endif