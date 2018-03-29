#include <iostream>
#include <string>
#include <sstream>
#include "image/Pixel.h"
#include "image/Header.h"
#include "image/Image.h"
#include "image/Filter.h"

int main(int argc, char const *argv[]) {
  if (argc != 3) {
    std::cerr << "USAGE: ./out <in.ppm> <out.ppm>";
    return 1;
  }

  // Open files
  std::ifstream in(argv[1]);

  stringstream k3out;
  k3out << "k3_" << argv[2];
  stringstream k5out;
  k5out << "k5_" << argv[2];

  std::ofstream out3(k3out.str());
  std::ofstream out5(k5out.str());

  if (!(in && out3 && out5)) {
    std::cerr << "Could not open input/output\n";
    return 1;
  }

  // ifstream constructor
  //Create two of the same image so we can apply both filters
  Image puppy(in);
  Image puppy2(in);

  //Matrix is a 2d vector of ints
  //3x3 Sharpen Filter
  Matrix k3 = {
    { 0,-1, 0},
    {-1, 5,-1},
    { 0,-1, 0}
  };

  //5x5 Sharpen Filter
  Matrix k5 = {
    { 0, 0,-1, 0, 0},
    { 0, 0,-1, 0, 0},
    {-1,-1, 9,-1,-1},
    { 0, 0,-1, 0, 0},
    { 0, 0,-1, 0, 0}
  };
  Filter::sharpen(puppy, k3);
  Filter::sharpen(puppy2, k5);

  puppy.write_to(out3);
  puppy2.write_to(out5);

  in.close();
  out3.close();
  out5.close();

  return 0;
}
