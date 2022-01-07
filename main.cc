#include <iostream>
#include "parser.tab.hh"
#include "clurtle_drawer/include/expr.hh"
#include "clurtle.hh"
#include "clurtle_cpp.hh"

// extern "C" int yyparse(Context* context);


int main() {
    clurtle::sequence * s = NULL;
    int res = yyparse(&s);
    #define DEBUG_L
    #ifdef DEBUG_L

    clurtle::clurtle_cpp clurtle("out.cpp");  
    if (s != nullptr) {
        s->visit(clurtle);
    } else {
        std::cout << "res not found" << std::endl;
    }

    #endif 
    #ifndef DEBUG_L
    
    #endif 

    
    return EXIT_SUCCESS;
}