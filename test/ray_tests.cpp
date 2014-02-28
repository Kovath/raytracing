#include "../src/include.h"

#include "../src/sphere.h"
#include "../src/triangle.h"
#include "../src/ray.h"

// using this means we don't have to qualify Eigen:: (but we still can if we want to)
using Eigen::Vector3f;

void run_basic_sphere_tests(int *results);
void run_basic_triangle_tests(int *results);

int main(int argc, char** argv) {
    // create array for results
    int results[2];
    // BASIC SPHERE TESTS
    run_basic_sphere_tests(results);
    int basic_sphere_results[2] = { results[0], results[1] };
    // BASIC TRIANGLE TESTS
    run_basic_triangle_tests(results);
    int basic_triangle_results[2] = { results[0], results[1] };

    printf("\n");
    printf("RESULT || Basic sphere test: %d/%d passed.\n", basic_sphere_results[0], basic_sphere_results[1]);
    printf("RESULT || Basic triangle test: %d/%d passed.\n", basic_triangle_results[0], basic_triangle_results[1]);
    printf("\n");

    return 0;
}

void run_basic_triangle_tests(int *results) {
    // triangle with vertices (0, -1, 0) (1, 1, 0) (-1, 1, 0)
    Triangle tri(Vector3f(0, -1, 0), Vector3f(1, 1, 0), Vector3f(-1, 1, 0));

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

    int t_test_count = 9;
    int t_pass_count = 0;

    float temp = 0;
    float *t = &temp;
    // TRIANGLE TESTS
    printf("\n");
    printf("BEGIN || Triangle Tests\n");
    if (tri.did_ray_hit(r0, t)) {
        printf("r0 hit at %.02f\n", *t);
        t_pass_count++;
    } else {
        printf("r0 miss\n");
    }
    if (tri.did_ray_hit(r1, t)) {
        printf("r1 hit at %.02f\n", *t);
        t_pass_count++;
    } else {
        printf("r1 miss\n");
    }
    if (tri.did_ray_hit(r2, t)) {
        printf("r2 hit at %.02f\n", *t);
        t_pass_count++;
    } else {
        printf("r2 miss\n");
    }
    if (tri.did_ray_hit(r3, t)) {
        printf("r3 hit at %.02f\n", *t);
    } else {
        printf("r3 miss\n");
        t_pass_count++;
    }
    if (tri.did_ray_hit(r4, t)) {
        printf("r4 hit at %.02f\n", *t);
        t_pass_count++;
    } else {
        printf("r4 miss\n");
    }
    if (tri.did_ray_hit(r5, t)) {
        printf("r5 hit at %.02f\n", *t);
    } else {
        printf("r5 miss\n");
        t_pass_count++;
    }
    if (tri.did_ray_hit(r6, t)) {
        printf("r6 hit at %.02f\n", *t);
    } else {
        printf("r6 miss\n");
        t_pass_count++;
    }
    if (tri.did_ray_hit(r7, t)) {
        printf("r7 hit at %.02f\n", *t);
        t_pass_count++;
    } else {
        printf("r7 miss\n");
    }
    if (tri.did_ray_hit(r8, t)) {
        printf("r8 hit at %.02f\n", *t);
    } else {
        printf("r8 miss\n");
        t_pass_count++;
    }

    results[0] = t_pass_count;
    results[1] = t_test_count;
}

void run_basic_sphere_tests(int *results) {
    // sphere at origin with radius 1
    Sphere sph(Vector3f(0, 0, 0), 1);

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

    int s_test_count = 9;
    int s_pass_count = 0;

    float temp = 0;
    float *t = &temp;
    // SPHERE TESTS
    printf("\n");
    printf("BEGIN || Sphere Tests\n");
    if (sph.did_ray_hit(r0, t)) {
        printf("r0 hit at %.02f\n", *t);
    } else {
        printf("r0 miss\n");
        s_pass_count++;
    }
    if (sph.did_ray_hit(r1, t)) {
        printf("r1 hit at %.02f\n", *t);
        s_pass_count++;
    } else {
        printf("r1 miss\n");
    }
    if (sph.did_ray_hit(r2, t)) {
        printf("r2 hit at %.02f\n", *t);
    } else {
        printf("r2 miss\n");
        s_pass_count++;
    }
    if (sph.did_ray_hit(r3, t)) {
        printf("r3 hit at %.02f\n", *t);
        s_pass_count++;
    } else {
        printf("r3 miss\n");
    }
    if (sph.did_ray_hit(r4, t)) {
        printf("r4 hit at %.02f\n", *t);
        s_pass_count++;
    } else {
        printf("r4 miss\n");
    }
    if (sph.did_ray_hit(r5, t)) {
        printf("r5 hit at %.02f\n", *t);
        s_pass_count++;
    } else {
        printf("r5 miss\n");
    }
    if (sph.did_ray_hit(r6, t)) {
        printf("r6 hit at %.02f\n", *t);
    } else {
        printf("r6 miss\n");
        s_pass_count++;
    }
    if (sph.did_ray_hit(r7, t)) {
        printf("r7 hit at %.02f\n", *t);
        s_pass_count++;
    } else {
        printf("r7 miss\n");
    }
    if (sph.did_ray_hit(r8, t)) {
        printf("r8 hit at %.02f\n", *t);
    } else {
        printf("r8 miss\n");
        s_pass_count++;
    }

    results[0] = s_pass_count;
    results[1] = s_test_count;
}
