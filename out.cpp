#include <iostream>
#include <math.h>

#include "CImg.h"

int curr_x = 100;
int curr_y = 100;
int curr_rot = 0;
bool is_up = false;
int color[3] = {100, 100, 100};
cimg_library::CImg<unsigned char> *img;

void rectangle(int length, int width) {
    for(int _i = 0; _i < 4; _i++) 
    {
        int x = curr_x + ((_i % 2 == 0 ? length : width) * cos(curr_rot * (M_1_PI / 180)));
        int y = curr_y + ((_i % 2 == 0 ? length : width) * sin(curr_rot * (M_1_PI / 180)));
        

        std::cout << "x " << x << " y " << y << " rot " << curr_rot << std::endl;
        img->draw_line(curr_x, curr_y, x, y, color);

        curr_x = x;
        curr_y = y;

        curr_rot = (curr_rot + 90) % 360;
    }   
}

void line(int length) {
    
}

void forward(int length) {
    int x = curr_x + length * cos(curr_rot * (M_1_PI / 180));
    int y = curr_y + length * sin(curr_rot * (M_1_PI / 180));

    if(!is_up)
        img->draw_line(curr_x, curr_y, x, y, color);

    curr_x = x;
    curr_y = y;
}

int main() {
    int sizeX = 320, sizeY = 240;
    
    img = new cimg_library::CImg<unsigned char>(sizeX, sizeY, 1, 3);
    img->fill(255); // on remplit en blanc
	is_up = false;
	rectangle(10, 6);
	is_up = true;
	forward(5);
	color[0] = 0;
	color[1] = 255;
	color[2] = 0;
	curr_rot += (90 + curr_rot )% 360;
	line(6);
	is_up = true;
	curr_rot += (90 + curr_rot )% 360;
	forward(5);
	curr_rot += (-90 + curr_rot )% 360;
	forward(3);
	color[0] = 255;
	color[1] = 0;
	color[2] = 0;
	curr_rot += (-90 + curr_rot )% 360;
	line(10);
    cimg_library::CImgDisplay disp;
    disp.display(*img);
    while (!disp.is_closed()) 
    {
        // boucle des evenements
        if (disp.key() == cimg_library::cimg::keyQ)
        disp.close();
        disp.wait();
    }
}
