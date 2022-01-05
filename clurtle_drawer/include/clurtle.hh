#ifndef CLURTLE_HH
#define CLURTLE_HH

#include <array>
#include "visitor.hh"

namespace clurtle {
    class clurtle : public visitor {
        bool                _pen_is_up;
        std::array<char, 3> _color;
        std::array<int, 2>  _pos;
        int                 _rotation;
        
    public:
        clurtle();

        void visit_up(const up * u);
        void visit_down(const down * d);
        void visit_change_color(const change_color * cc);
        void visit_forward(const forward * f);
        void visit_rotate(const rotate * r);
        void visit_line(const line * l);
        void visit_rectangle(const rectangle * r);
        void visit_conditional(const conditional * c);
        void visit_while_loop(const while_loop * wl);
        void visit_for_loop(const for_loop * fl);
        void visit_ope(const ope * o);
    };
}

#endif