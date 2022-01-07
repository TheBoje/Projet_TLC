#ifndef OPE_HH
#define OPE_HH

#include "expr.hh"

namespace clurtle {

    enum ope_symbol {
        OP_PLUS,
        OP_MINUS,
        OP_TIMES,
        OP_DIVIDE,
        OP_GT,
        OP_GEQ,
        OP_LT,
        OP_LEQ,
        OP_EQ,
        OP_AND,
        OP_OR,
        OP_NOT
    };

    class ope : public expr {
        expr * _left;
        ope_symbol _symbol;
        expr * _right;

    public:
        ope(ope_symbol o, expr * left, expr * right);
        ~ope();

        inline expr * get_left() const { return _left; }
        inline ope_symbol get_symbol() const { return _symbol; } 
        inline expr * get_right() const { return _right; }

        void visit(visitor & v) const;
    };

}

#endif