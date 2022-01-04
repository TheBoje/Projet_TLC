#ifndef TERM_HH
#define TERM_HH

#include "visitor.hh"

namespace clurtle {
    class term {
    public:
        virtual ~term() {}

        virtual void visit(visitor * v) const = 0;
    };
}

#endif