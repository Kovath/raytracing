#include "triangle.h"

bool Triangle::did_ray_hit(Ray ray, float *intersection_t) {
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
    float bottom = n.dot(ray.point);

    // if the bottom is 0 then the ray is parallel to the plane (return false)
    if (bottom == 0) return false;

    float intersection_plane_t = (n.dot(p0) - n.dot(ray.origin)) / bottom;

    // if the time the ray hits the plane is negative, the plane is behind the ray
    if (intersection_plane_t < 0) return false;

    // calculate the point on the play that the ray hits
    Q = ray.origin + intersection_plane_t*ray.point;

    // to test if the point Q is inside the plane, we compare the normal of the plane
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