#include "triangle.h"

Triangle::Triangle() {
    refraction_c = 0;
    reflection_c = 0;
}

Triangle::Triangle(Vector3f p0, Vector3f p1, Vector3f p2): p0(p0), p1(p1), p2(p2) {
    refraction_c = 0;
    reflection_c = 0;
}

bool Triangle::did_ray_hit(Ray ray, float *intersection_t, float epsilon /* = 0 */) {
    Point3f ray_point = ray.get_point();
    Point3f ray_origin = ray.get_origin();

    ray_origin = T.get_inverse_transformation() * ray_origin;
    ray_point = T.get_inverse_transformation() * ray_point;

    // edges of the triangle and normal
    Vector3f e0, e1, n;
    // Q = point on the plane
    Vector3f Q;
    // results of the inside-edge comparison test
    float r0, r1, r2;

    // B - A
    e0 = p1 - p0;
    // C - A
    e1 = p2 - p0;

    // normal is cross product of the edges
    n = e0.cross(e1);

    // we can now find the time the ray hits the plane the triangle is on
    // t = (dot(n, point of triangle) - dot(n, ray.origin)) / (dot(n, ray.point))
    float bottom = n.dot(ray_point);

    // if the bottom is 0 then the ray is parallel to the plane (return false)
    if (bottom == 0) return false;

    float intersection_plane_t = (n.dot(p0) - n.dot(ray_origin)) / bottom;

    // if the time the ray hits the plane is less than epsilon, the plane is behind the ray
    if (intersection_plane_t < epsilon) return false;

    // calculate the point on the plane that the ray hits
    Q = ray_origin + intersection_plane_t*ray_point;

    // to test if the point Q is inside the triangle, we compare the normal of the plane
    // with the cross product of each edge of the triangle
    r0 = (e0.cross(Q - p0)).dot(n);
    // if the result is negative, the point is outside the triangle (relies on the
    // ordering of the cross product
    if (r0 < 0) return false;
    r1 = ((p2 - p1).cross(Q - p1)).dot(n);
    if (r1 < 0) return false;
    r2 = ((p0 - p2).cross(Q - p2)).dot(n);
    if (r2 < 0) return false;

    // if we've made it this far then Q is inside the triangle!
    *intersection_t = intersection_plane_t;
    return true;
}

Vector3f Triangle::get_normal(Point3f point) {
    Vector3f ret = (p1 - p0).cross(p2 - p0);
    ret.normalize();
    return ret;
}

void Triangle::set_p0(Vector3f point) {
    p0 = point;
}

void Triangle::set_p1(Vector3f point) {
    p1 = point;
}

void Triangle::set_p2(Vector3f point) {
    p2 = point;
}

Vector3f Triangle::get_p0() {
    return p0;
}

Vector3f Triangle::get_p1() {
    return p1;
}

Vector3f Triangle::get_p2() {
    return p2;
}
