#ifndef CHANGE_COLOR_HH
#define CHANGE_COLOR_HH

#include <array>
#include "instr.hh"
#include "expr.hh"

namespace clurtle {
    class change_color : public instr {
        std::array<expr *, 3> _color;

    public: 
        change_color(std::array<expr *, 3> color);
        ~change_color();

        inline std::array<expr *, 3> get_color() const { return _color; };

        void visit(visitor & v) const;
    };
}

#endif