#include <iostream>
#include "parser.tab.hh"
#include "clurtle_drawer/include/expr.hh"
#include "clurtle.hh"
#include "clurtle_cpp.hh"

// extern "C" int yyparse(Context* context);


int main() {
    clurtle::sequence * s = NULL;
    std::cout << "s before parse : " << s << std::endl;
    int res = yyparse(&s);
    std::cout << "s after parse : " << s << std::endl;
    std::cout << "parsing code : " << res << std::endl;
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