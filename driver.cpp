#include <iostream>
#include <string>
#include <sstream>
#include "image/Pixel.h"
#include "image/Header.h"
#include "image/Image.h"
#include "image/Filter.h"
#include "image/functions.h"

int main(int argc, char const *argv[]) {
  if (argc != 3) {
    std::cerr << "USAGE: ./out <in.ppm> <out.ppm>" << std::endl;
    return 1;
  }
  unsigned int k = 0;
  if(argv[1] == "average"){
    vector<ifstream> files(10);
    openInputFiles(argv[1], files);
    while(k < files.size()){
      files.at(k).close();
    } 
    return 0;
  }
  // Open files
  std::ifstream in(argv[1]);

  if (!(in)) {
    std::cerr << "ERROR: Could not open input for reading." << std::endl;
    return 1;
  }

  // Create two filenames from one argument representing sharpened images
  stringstream k3out;
  k3out << "k3_" << argv[2];
  stringstream k5out;
  k5out << "k5_" << argv[2];

  std::ofstream out3(k3out.str());
  std::ofstream out5(k5out.str());

  if (!(out3 && out5)) {
    std::cerr << "ERROR: Could not open output for writing." << std::endl;
    return 1;
  }

  // ifstream constructor
  // Create two of the same image so we can apply both filters
  Image puppy(in);
  // Point to beginning of image to make second copy
  in.seekg(0, ios::beg);
  Image puppy2(in);

  Filter::sharpen(puppy, Filter::K3);
  Filter::sharpen(puppy2, Filter::K5);
  puppy.write_to(out3);
  puppy2.write_to(out5);

  in.close();
  out3.close();
  out5.close();
  
  return 0;
}
