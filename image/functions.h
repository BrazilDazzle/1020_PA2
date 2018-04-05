#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "Image.h"
#include <sstream>
#include <iomanip>

Image removeNoiseAverage(vector<Image>);
Image removeNoiseMedian(vector<Image>);
void openInputFiles(const char*, vector<ifstream>);


#endif