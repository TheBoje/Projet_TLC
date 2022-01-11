#include <X11/Xlib.h>
#include <iostream>
#include "parser.tab.hh"
#include "expr.hh"
#include "clurtle.hh"
#include "clurtle_cpp.hh"

#include "CImg.h"

int yyparse(clurtle::sequence**);


int main(int argc, char * argv[]) {
    clurtle::sequence * s = NULL;
    int res = yyparse(&s);
    
    #define DEBUG_L
    #ifdef DEBUG_L
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
