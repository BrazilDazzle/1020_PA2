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
  cout << "dickbutt" << endl;
  in.seekg(0, ios::beg);
  Image puppy2(in);
  //cout << puppy2.header().height() << endl;

  Filter::sharpen(puppy, Filter::K3);
  //cout << "buttdick" << endl;
  Filter::sharpen(puppy2, Filter::K5);
  //cout << "cockcheese" << endl;
  puppy.write_to(out3);
  puppy2.write_to(out5);

  in.close();
  out3.close();
  out5.close();

  return 0;
}
