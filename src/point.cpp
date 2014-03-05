#include "point.h"

void printVector(Vector3f v) {
    cout << "[" << v[0] << ", " << v[1] << ", " << v[2] << "]" << endl;
};

String vectorString(Vector3f v) {
    String ret = "[";
    ret += v[0];
    ret += ", ";
    ret += v[1];
    ret += ", ";
    ret += v[2];
    ret += "]";
    return ret;
}

