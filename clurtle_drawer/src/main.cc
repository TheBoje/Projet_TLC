#include <X11/Xlib.h>
#include <iostream>
#include "parser.tab.hh"
#include "expr.hh"
#include "clurtle.hh"
#include "clurtle_cpp.hh"

#include "CImg.h"

int yyparse(clurtle::sequence**);


void clurtle_usage() {
    std::cout << "clurtle take 0, 1 are 3 args" << std::endl;
    std::cout << "0 : the file will be named \"result.bmp\" and the resolution (1920x1080)" << std::endl;
    std::cout << "1 : the file will be named \"$1.bmp\" and the resolution (1920x1080)" << std::endl;
    std::cout << "3 : the file will be named \"$1.bmp\" and the resolution ($2x$3)" << std::endl;
    std::cout << "./clurtle {imgname} {sizex} {sizey} < {clurtlefile}.cl" << std::endl;
}

int main(int argc, char * argv[]) {
    clurtle::sequence * s = NULL;
    int res = yyparse(&s);
    
    #ifdef CLURTLE_CPP
    std::string out_name;
    if (argc >= 2) {
        out_name = argv[1];
    } else {
        out_name = "result";
    }
    clurtle::clurtle_cpp clurtle(out_name);  
    if (s != nullptr) {
        try {
            s->visit(clurtle);
        } catch (std::runtime_error* re) {
            std::cout << re->what() << std::endl;
            return EXIT_FAILURE;
        }
    } else {
        return res;
    }

    #endif 
    #ifndef CLURTLE_CPP

    std::string img_name = "result";
    int sizeX = 1920, sizeY = 1080;

    if(argc == 2) 
    {
        img_name = argv[1];
    }
    else if(argc == 4) 
    {
        sizeX = atoi(argv[2]);
        sizeY = atoi(argv[3]);
    }
    else if(argc != 1)
    {
        std::cout << argc << std::endl;
        clurtle_usage();
        return EXIT_FAILURE;
    }
    
    clurtle::clurtle clurtle(sizeX, sizeY, img_name);

    if (s != nullptr) {
        try {
            s->visit(clurtle);
        } catch (std::runtime_error * re) { 
            std::cerr << re->what() << std::endl;
            return EXIT_FAILURE; 
        }
    } else {
        std::cout << "res not found" << std::endl;
    }


    #endif 

    
    return res;
}
