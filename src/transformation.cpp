#include "transformation.h"

#define PI 3.14159265359

Transformation::Transformation() {
    T.setIdentity();
    I.setIdentity();
}

void Transformation::apply_transformation(TransformationType t, float x, float y, float z) {
    // create the matrix
    switch(t) {
        case SCALE:
            T.scale(Vector3f(x, y, z));
            I.prescale(Vector3f(1.0f/x, 1.0f/y, 1.0f/z));
            /*
            // inverse of scale is flipped
            m << 1/x,   0,   0, 0,
                   0, 1/y,   0, 0,
                   0,   0, 1/z, 0;
            */
            break;
        case TRANSLATION: {
            Vector3f trans(x, y, z);
            Vector3f trans_i(-x, -y, -z);
            T = T*Translation3f(trans);
            I = Translation3f(trans_i)*I;
            /*
            // inverse of translation is negated
            m << 1, 0, 0, -x,
                 0, 1, 0, -y,
                 0, 0, 1, -z;
            */
        } break;
        default:
            printf("apply_transformation called with non-valid transformationType! (scale or translation)\n");
            return;
            break;
    }
}

void Transformation::apply_transformation(TransformationType t, Vector3f r, float degrees) {
    if (t != ROTATION) {
        printf("apply_transformation called with non-valid transformationType! (rotation)\n");
        return;
    }
    // make sure r is the normal vector
    r.normalize();

    AngleAxisf a(PI/2, r);
    float radians = (degrees * PI / 180);
    Vector3f z = r*sin(radians/2);
    Quaternionf q(cos(radians/2), z[0], z[1], z[2]);
    Quaternionf q_i(cos(-radians/2), z[0], z[1], z[2]);

    T = T*q;
    I = q_i*I;
}

Transform<float, 3, Affine> Transformation::get_inverse_transformation() {
    return I;
}

Transform<float,3,Affine> Transformation::get_transformation() {
    return T;
}
