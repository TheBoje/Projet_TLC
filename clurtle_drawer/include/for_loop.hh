#ifndef FOR_LOOP_HH
#define FOR_LOOP_HH

#include <string>

#include "instr.hh"
#include "expr.hh"

namespace clurtle {
    class for_loop : public instr {
        std::string _var;
        expr *      _to;
        instr *     _body;

    public:
        for_loop(std::string var, expr * to, instr * body);
        ~for_loop();

        inline std::string get_var() const { return _var; }
        inline instr * get_body() const { return _body; }

        void visit(visitor & v) const;    
    };
}

#endif