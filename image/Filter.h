#ifndef FILTER_H
#define FILTER_H
#include "Image.h"
#include <cmath>
using namespace std;
using Matrix = vector<vector<int>>;

namespace Filter{
    extern Matrix K3, K5;
    Image& sharpen(Image&, Matrix&);
    Pixel apply_kernel(Image&, int, int, Matrix&);
    int clamp(int, int, int);
}

#endif