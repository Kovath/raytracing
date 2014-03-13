#ifndef CS184_INCLUDE_H
#define CS184_INCLUDE_H

#ifdef _WIN32
//#define EIGEN_DONT_ALIGN_STATICALLY

#define EIGEN_DONT_VECTORIZE 
#define EIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT
#endif

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <list>
#include <cmath>
#include <Eigen/Dense>


using namespace std;
using namespace Eigen;

typedef string String;

#endif
