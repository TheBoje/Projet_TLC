#include <iostream>
#include <math.h>

#include "CImg.h"

double curr_x = 200;
double curr_y = 200;
double curr_rot = 0;
bool is_up = false;
int color[3] = {0, 0, 0};
cimg_library::CImg<unsigned char> *img;

void rectangle(double length, double width) {
    if (!is_up){
        for(int _i = 0; _i < 4; _i++) 
        {
            double x = curr_x + (_i % 2 == 0 ? length : width) * cos(curr_rot * (M_PI / 180));
            double y = curr_y + (_i % 2 == 0 ? length : width) * sin(curr_rot * (M_PI / 180));
            
            img->draw_line(curr_x, curr_y, x, y, color);

            curr_x = x;
            curr_y = y;

            curr_rot = std::fmod((curr_rot + 90), 360);
        }
    }
}

void line(double length) {
    if(!is_up) {
        double x = curr_x + length * cos(curr_rot * (M_PI / 180));
        double y = curr_y + length * sin(curr_rot * (M_PI / 180));
        img->draw_line(curr_x, curr_y, x, y, color);
    }
}


void forward(double length) {
    double x = curr_x + length * cos(curr_rot * (M_PI / 180));
    double y = curr_y + length * sin(curr_rot * (M_PI / 180));

    if(!is_up)
        img->draw_line(curr_x, curr_y, x, y, color);

    curr_x = x;
    curr_y = y;
}

int main() {
    int sizeX = 400, sizeY = 400;
    
    img = new cimg_library::CImg<unsigned char>(sizeX, sizeY, 1, 3);
    img->fill(255); // on remplit en blanc
	is_up = false;
	double distance = 150;
	double angle = 123;
	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
	for ( int x = 0; x < 100; x++) {
		forward(distance);
		curr_rot = std::fmod((angle + curr_rot ), 360);
	}
    img->save("clurtle_cpp_result.png");
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
