#include "CImg.h"

int main() {
    int sizeX = 320, sizeY = 240;
    cimg_library::CImg<unsigned char> img(sizeX, sizeY, 1, 3);

    cimg_library::CImgDisplay disp;

    while (!disp.is_closed()) 
    {
        // boucle des evenements
        if (disp.key() == cimg_library::cimg::keyQ)
        disp.close();
        disp.wait();
    }
}
