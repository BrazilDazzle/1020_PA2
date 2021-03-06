#include "Filter.h"

Matrix Filter::K3 =
    {{ 0,-1, 0},
     {-1, 5,-1},
     { 0,-1, 0}};

Matrix Filter::K5 =
    {{ 0, 0,-1, 0, 0},
     { 0, 0,-1, 0, 0},
     {-1,-1, 9,-1,-1},
     { 0, 0,-1, 0, 0},
     { 0, 0,-1, 0, 0}};

Image& Filter::sharpen(Image& img, Matrix& K) {
  // K.size represents the height of the 2d Matrix
  // kMid evaluated to 1 and 2, respectively
  int kMid = (K.size()) / 2;
  Header header(img.header());
  Image sharpImg(img);
  int i, j;
  // Using <= because it would stop one short otherwise
  // indeces start at kMid to skip past the border of the image
  for(i = kMid; i <= header.height() - kMid; i++) {
    for(j = kMid; j <= header.width() - kMid; j++) {
      img(i, j) = apply_kernel(sharpImg, i, j, K);
    }
  }
  return img;
}

Pixel Filter::apply_kernel(Image& img, int x, int y, Matrix& k) {
  int kSize = (k.size());
  int kMid = kSize / 2;
  int red = 0, blue = 0, green = 0;
  for(int i = x - kMid, a = 0; i <= kMid + x; i++, a++) {
    for(int j = y - kMid, b = 0; j <= kMid + y; j++, b++) {
      /* More effective method using the matrix given by k
       * to multiply each pixel by the value defined in k
       * at that point relative to the original pixel
       */
      red += k[a][b] * img(i, j).r();
      green += k[a][b] * img(i, j).g();
      blue += k[a][b] * img(i, j).b();
    }
  }
  red = clamp(0, 255, red);
  green = clamp(0, 255, green);
  blue = clamp(0, 255, blue);
  Pixel pixel(red, green, blue);
  return pixel;
}

//Ensures that edited color values stay between 0 and 255
int Filter::clamp(int lo, int hi, int x) {
  return std::max(lo, std::min(x, hi));
}
