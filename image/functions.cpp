#include "functions.h"

Image removeNoiseAverage(vector<Image> image){
    /* i is for to count through number of files
     * j is for image height
     * k is for image width
     * z is for number of pixels
     */
    int i = 0, j = 0, k = 0, z = 0;
    // Copy one of the images to an output image, mostly for header
    Image output(image.at(i));
    // Increment i so the first file at(0) is not added twice
    i += 1;
    // number of pixels determined to create a pixel vector for output image
    int num_pixels = output.header().height() * output.header().width();
    vector<Pixel> pixels(num_pixels);
    // Loop through height
    for(j = 0; j < output.header().height(); j++){
        // Loop through row
        for(k = 0; k < output.header().width(); k++, z++){
            // Loop through each input file
            while(i < 10){
                // Add pixel of each image to created pixel vector
                pixels.at(z) += image.at(i)(j, k);
            }
        // Divide value of pixel at z by 10 to give average
        pixels.at(z) /= 10;
        // Put value of pixel at z into output image
        output(j, k) = pixels.at(z);
        }
    }
    return output;
}

void openInputFiles(const char* name, vector<ifstream> files){
    // Size of the vector has to be specified before passing in the vector
    // Creates an int of the number of files
    int numFiles = files.size();
    int i = 0;
    stringstream ss;
    while(i < numFiles){
        //Google says this is the best way to clear a stringstream
        ss.str(string());
        // Read in the name of the file to be opened into the stringstream
        ss << name << "_" << setw(3) << setfill('0') << i + 1 << ".ppm";
        // Open the file with the name in the stringstream
        files[i].open(ss.str());
        // Check to see if the file could be opened
        if(!files[i]){
            cout << "Error: failed to open input files" << endl;
            exit(1);
        }
    }
}