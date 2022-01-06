#ifndef FOR_LOOP_HH
#define FOR_LOOP_HH

#include <string>

#include "instr.hh"

namespace clurtle {
    class for_loop : public instr {
        std::string _var;
        instr *     _body;

    public:
        for_loop(std::string var, instr * body);
        ~for_loop();

        inline std::string get_var() const { return _var; }
        inline instr * get_body() const { return _body; }

        void visit(visitor & v) const;    
    };
}

#endif