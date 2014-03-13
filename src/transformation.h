#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "include.h"

typedef enum {
    ROTATION,
    TRANSLATION,
    SCALE
} TransformationType;

class Transformation {
    public:
        // constructors
        Transformation();

        void apply_transformation(TransformationType t, float x, float y, float z);
        void apply_transformation(TransformationType t, Vector3f r, float degrees);

        Transform<float,3,Affine> get_inverse_transformation();
        Transform<float,3,Affine> get_transformation();
    private:
        // T is the transform matrix of all the transformations applied to the object
        Transform<float,3,Affine> T;


};

#endif // TRANSFORMATION_H
