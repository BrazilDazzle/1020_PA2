#include "functions.h"

Image removeNoiseAverage(vector<Image> image){
    int i = 0, j = 0, k = 0, z = 0;
    Image output(image.at(i));
    i += 1;
    int num_pixels = output.header().height() * output.header().width();
    vector<Pixel> pixels(num_pixels);
    for(j = 0; j < output.header().height(); j++){
        for(k = 0; k < output.header().width(); k++, z++){
            while(i < 10){
                pixels.at(z) += image.at(i)(j, k);
            }
        pixels.at(z) /= 10;
        output(j, k) = pixels.at(z);
        }
    }
    return output;
}

void openInputFiles(string name, vector<ifstream> files){
    int numFiles = files.size();
    int i = 0;
    stringstream ss;
    while(i < numFiles){
        //Google says this is the best way to clear a stringstream
        ss.str(string());
        ss << name << "_" << setw(3) << setfill('0') << i + 1;
        //files[i].open(ss);
    }
}