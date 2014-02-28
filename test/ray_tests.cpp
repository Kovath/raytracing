#include <stdio.h>
#include "../src/include.h"

#include "../src/sphere.h"
#include "../src/ray.h"

int main(int argc, char** argv) {
    // sphere at origin with radius 1
    Sphere s(Eigen::Vector3f(0, 0, 0), 1);

    //      rays going down the z axis plane like so
    //       r0 * -- * -- * (1, 1)
    //          |    |    |
    //          * -- * -- * (center is the origin)
    //          |    |    |
    // (-1, -1) * -- * -- * r8
    Ray r0(Eigen::Vector3f(-1, 1, 2),Eigen::Vector3f(-1, 1, 1));
    Ray r1(Eigen::Vector3f(0, 1, 2),Eigen::Vector3f(0, 1, 1));
    Ray r2(Eigen::Vector3f(1, 1, 2),Eigen::Vector3f(1, 1, 1));
    Ray r3(Eigen::Vector3f(-1, 0, 2),Eigen::Vector3f(-1, 0, 1));
    Ray r4(Eigen::Vector3f(0, 0, 2),Eigen::Vector3f(0, 0, 1));
    Ray r5(Eigen::Vector3f(1, 0, 2),Eigen::Vector3f(1, 0, 1));
    Ray r6(Eigen::Vector3f(-1, -1, 2),Eigen::Vector3f(-1, -1, 1));
    Ray r7(Eigen::Vector3f(0, -1, 2),Eigen::Vector3f(0, -1, 1));
    Ray r8(Eigen::Vector3f(1, -1, 2),Eigen::Vector3f(1, -1, 1));

    float temp = 0;
    float *t = &temp;
    if (s.did_ray_hit(r0, t)) {
        printf("r0 hit at %.02f\n", *t);
    } else {
        printf("r0 miss\n");
    }
    if (s.did_ray_hit(r1, t)) {
        printf("r1 hit at %.02f\n", *t);
    } else {
        printf("r1 miss\n");
    }
    if (s.did_ray_hit(r2, t)) {
        printf("r2 hit at %.02f\n", *t);
    } else {
        printf("r2 miss\n");
    }
    if (s.did_ray_hit(r3, t)) {
        printf("r3 hit at %.02f\n", *t);
    } else {
        printf("r3 miss\n");
    }
    if (s.did_ray_hit(r4, t)) {
        printf("r4 hit at %.02f\n", *t);
    } else {
        printf("r4 miss\n");
    }
    if (s.did_ray_hit(r5, t)) {
        printf("r5 hit at %.02f\n", *t);
    } else {
        printf("r5 miss\n");
    }
    if (s.did_ray_hit(r6, t)) {
        printf("r6 hit at %.02f\n", *t);
    } else {
        printf("r6 miss\n");
    }
    if (s.did_ray_hit(r7, t)) {
        printf("r7 hit at %.02f\n", *t);
    } else {
        printf("r7 miss\n");
    }
    if (s.did_ray_hit(r8, t)) {
        printf("r8 hit at %.02f\n", *t);
    } else {
        printf("r8 miss\n");
    }

    return 0;
}
