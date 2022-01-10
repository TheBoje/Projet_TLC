#include <X11/Xlib.h>
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
    
    #define DEBUG_L
    #ifdef DEBUG_L

    clurtle::clurtle_cpp clurtle("clurtle_cpp.cpp");  
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
    #ifndef DEBUG_L

    int sizeX = 1000, sizeY = 1000;

    clurtle::clurtle clurtle(sizeX, sizeY);

    if (s != nullptr) {
        s->visit(clurtle);
    } else {
        std::cout << "res not found" << std::endl;
    }


    #endif 

    
    return res;
}
