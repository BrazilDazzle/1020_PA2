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

Image& Filter::sharpen(Image& img, Matrix& K){
    cout << "inside sharpen" << endl;
    int kMid = (K.size()) / 2;
    cout << kMid << endl;
    Header header(img.header());
    cout << img.header().height() << endl;
    //vector<Pixel> pixels = img.pixels();
    //Image* sharpImage(&img);
    int i = 0, j = 0;
    for(i = kMid; i + kMid < header.height(); i++){
        //cout << i << "i" << endl;
        for(j = kMid; j + kMid < header.width(); j++){
            //cout << j << "j" << endl;
            apply_kernel(img, i, j, K);
        }
    }
    return img;
}

Pixel Filter::apply_kernel(Image& img, int x, int y, Matrix& k){
    int kSize = (k.size());
    int kMid = kSize / 2;
    //cout << "inside appy_kernel" << endl;
    uint8_t red = 0, blue = 0, green = 0;
    for(int i = x - kMid; i <= kMid + x; i++){
        for(int j = y - kMid; j < kMid + y; j++){
            /* Checks to see if either the column or 
             * row lines up with the center pixel
             */
            if(i == x || j == y){
                /* This case occurs when at the center pixel
                 * ((kSize * 2) - 1) will be either 5 or 9,
                 * depending on size of the matrix
                 */
                if(i == x && j == y){
                    Pixel tempPix = img(i, j);
                    red += tempPix.r() * ((kSize * 2) - 1);
                    green += tempPix.g() * ((kSize * 2) - 1);
                    blue += tempPix.b() * ((kSize * 2) - 1);
                }
                    /* This case occurs when either the row or
                     * the column are in line with the center
                     * pixel. Subtracts because of -1
                     */
                    else{
                        Pixel tempPix = img(i, j);
                        red -= tempPix.r();
                        green -= tempPix.g();
                        blue -= tempPix.b();
                    }
                
            }
            /* No need for else statement, don't need
             * to do anything with other pixels
             */
        }
    }
    clamp(0, 255, red);
    clamp(0, 255, green);
    clamp(0, 255, blue);
    Pixel pixel(red, green, blue);
    return pixel;
}

int Filter::clamp(int lo, int hi, int x){
    return std::max(lo, std::min(x, hi));
}