#ifndef FOR_LOOP_HH
#define FOR_LOOP_HH

#include <string>

#include "variable.hh"
#include "instr.hh"
#include "expr.hh"
#include "seq.hh"

namespace clurtle {
    class for_loop : public instr {
        variable * _var;
        expr *     _from;
        expr *     _to;
        seq_item * _body;

    public:
        for_loop(variable * var, expr * from, expr * to, seq_item * body);
        ~for_loop();

        inline variable * get_var() const { return _var; }
        inline expr * get_from() const { return _from; }
        inline expr * get_to() const {return _to; }
        inline seq_item * get_body() const { return _body; }

        void visit(visitor & v) const;    
    };
}

#endif