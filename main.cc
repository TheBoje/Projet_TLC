#include <iostream>
#include "parser.tab.hh"

int main() {
    int res = yyparse();
    printf("Res: %d\n", res);
    return EXIT_SUCCESS;
}