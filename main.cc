#include <iostream>
#include "parser.tab.hh"
#include "clurtle_drawer/include/expr.hh"
#include "clurtle.hh"
#include "clurtle_cpp.hh"

#include "CImg.h"

// extern "C" int yyparse(Context* context);


int main() {
    clurtle::sequence * s = NULL;
    int res = yyparse(&s);
    
    // #define DEBUG_L
    #ifdef DEBUG_L

    clurtle::clurtle_cpp clurtle("out.cpp");  
    if (s != nullptr) {
        s->visit(clurtle);
    } else {
        std::cout << "res not found" << std::endl;
    }

    #endif 
    #ifndef DEBUG_L
    int sizeX = 320, sizeY = 240;
    cimg_library::CImg<unsigned char> img(sizeX, sizeY, 1, 3);

    clurtle::clurtle clurtle(img);

    cimg_library::CImgDisplay disp;

    if (s != nullptr) {
        s->visit(clurtle);
    } else {
        std::cout << "res not found" << std::endl;
    }

    while (!disp.is_closed()) 
    {
        // boucle des evenements
        if (disp.key() == cimg_library::cimg::keyQ)
        disp.close();
        disp.wait();
    }
    #endif 

    
    return EXIT_SUCCESS;
}