#include <iostream>
#include "parser.tab.hh"
#include "clurtle_drawer/include/expr.hh"
#include "clurtle.hh"
#include "clurtle_cpp.hh"

int main() {
    clurtle::sequence * s = nullptr;
    yyparse(&e);
    #define DEBUG_L
    #ifdef DEBUG_L

    clurtle::clurtle_cpp clurtle("out.cpp");    
    if (s != nullptr) {
        s->visit(clurtle);
    }

    #endif 
    #ifndef DEBUG_L
    
    #endif 

    
    return EXIT_SUCCESS;
}