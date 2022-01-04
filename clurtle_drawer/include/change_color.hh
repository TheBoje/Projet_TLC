#ifndef CHANGE_COLOR_HH
#define CHANGE_COLOR_HH

#include <array>
#include "instr.hh"

namespace clurtle {
    class change_color : public instr {
        std::array<char, 3> _color;

    public: 
        change_color(std::array<int, 3> color);
        ~change_color();

        inline std::array<char, 3> get_color() const { return _color; };

        void visit(visitor & v) const;
    };
}

#endif