#ifndef CLURTLE_HH
#define CLURTLE_HH

#include <map>
#include <array>
#include <vector>

#include "visitor.hh"
#include "CImg.h"


namespace clurtle {
    class clurtle : public visitor {
        bool                        _pen_is_up;
        unsigned char               _color[3];
        std::array<int, 2>          _pos;
        int                         _rotation;
        std::vector<int>            _stack;
        std::vector<bool>           _stack_bool;
        std::map<std::string, int>  _variables;
        cimg_library::CImg<unsigned char> _img;

        inline int get_last_int() { 
            int a = _stack[_stack.size() - 1]; 
            _stack.pop_back(); 
            return a;
        }
        
        inline bool get_last_bool() {
            bool a = _stack_bool[_stack_bool.size() - 1]; 
            _stack_bool.pop_back(); 
            return a;
        }

    public:
        clurtle(cimg_library::CImg<unsigned char> & img);

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
        void visit_constant(const constant * c);
        void visit_variable(const variable * v);
        void visit_affectation(const affectation * a);
        void visit_sequence(const sequence * s);
    };
}

#endif