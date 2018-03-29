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
  std::ifstream out(argv[2]);

  if (!(in && out)) {
    std::cerr << "Could not open input/output\n";
    return 1;
  }

  // ifstream constructor
  //Create two of the same image so we can apply both filters
  Image puppy(in);
  Image puppy2(in);

  sstream k3out << "k3_" << out;
  sstream k5out << "k5_" << out;

  //Matrix is a 2d vector of ints
  //3x3 Sharpen Filter
  Matrix k3 = {
    { 0,-1, 0}
    {-1, 5,-1}
    { 0,-1, 0}
  }

  //5x5 Sharpen Filter
  Matrix k5 = {
    { 0, 0,-1, 0, 0}
    { 0, 0,-1, 0, 0}
    {-1,-1, 9,-1,-1}
    { 0, 0,-1, 0, 0}
    { 0, 0,-1, 0, 0}
  }
  Filter::sharpen(puppy, k3);
  Filter::sharpen(puppy2, k5);

  puppy.write_to(k3out);
  puppy2.write_to(k5out);

  in.close();
  out.close();

  return 0;
}
