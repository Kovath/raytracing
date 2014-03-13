#include "sphere.h"

Sphere::Sphere() {
    set_refraction_c(0);
    set_reflection_c(0);
}

Sphere::Sphere(Point3f center, float radius) : center(center), radius(radius) {
    set_refraction_c(0);
    set_reflection_c(0);
}

bool Sphere::did_ray_hit(Ray ray, float *intersection_t, float epsilon /* = 0 */) {
    Point3f ray_origin = ray.get_origin();
    Point3f ray_point = ray.get_point();

    // code to apply inverse transformation of the object on the ray
    /*
    Vector3f ray_v = ray_point - ray_origin;
    //cout << "untouched ray_v: " << ray_v << endl;
    //cout << "inverse transformation: " << T.get_inverse_transformation().linear() << endl;
    ray_v = T.get_inverse_transformation() * ray_v;
    // the new ray_point is the transformed vector + the origin
    //cout << "afterwards ray_v: " << ray_v << endl;
    ray_point = ray_origin + ray_v;
    */
    ray_origin = T.get_inverse_transformation() * ray_origin;
    ray_point = T.get_inverse_transformation() * ray_point;


    // a = dot(point, point)
    float a = ray_point.dot(ray_point);
    // b = 2*dot((origin-center), point)
    float b = 2 * ray_point.dot(ray_origin - center);
    // c = dot((origin - center), (origin - center)) - radius^2
    float c = (ray_origin - center).dot(ray_origin - center) - (radius*radius);
    // DEBUG: printf("a: %.01f, b: %.01f, c: %.01f\n", a, b, c);

    // inside_root is the part inside the root of the quadratic equation
    // b^2 - 4ac
    float inside_root = b*b - 4*a*c;

    // if the inside_root is negative, we get a complex result therefore ray doesn't hit
    if (inside_root < 0) return false;

    float t0 = (-b + sqrt(inside_root))/(2*a);
    float t1 = (-b - sqrt(inside_root))/(2*a);

    // make t0 is smaller than t1 for simplicity
    if (t0 > t1)
    {
        // swap if t0 is greater than t1
        float temp = t0;
        t0 = t1;
        t1 = temp;
    }

    // DEBUG:: printf("t0: %.01f, t1: %.01f\n", t0, t1);

    // if the greater time is less than epsilon, we don't hit the object (behind the camera)
    if (t1 < epsilon) {
        return false;
    }
    // if the smaller time is the only one negative, then the ray starts inside the sphere
    // intersection time is at the non-negative time (t1)
    if (t0 < epsilon) {
        *intersection_t = t1;
        return true;
    }
    // otherwise the intersection time is at the smaller time (t0)
    else {
        *intersection_t = t0;
        return true;
    }
}

Vector3f Sphere::get_normal(Point3f point) {
    Vector3f normal_v = point - center;
    normal_v.normalize();
    return normal_v;
}

// setters
void Sphere::set_center(Point3f center) {
	this->center = center;
}

void Sphere::set_radius(float radius) {
	this->radius = radius;
}

// getters
Point3f Sphere::get_center() {
	return center;
}

float Sphere::get_radius() {
	return radius;
}

// cout <<
ostream& operator<< (ostream& ostream, const Sphere s) {
    return ostream << "Sphere: center(" << vectorString(s.center).c_str() << ") radius:" << s.radius << endl;
}
