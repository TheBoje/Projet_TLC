#ifndef CLURTLE_CPP_HH
#define CLURTLE_CPP_HH

#include <array>
#include <iostream>
#include <fstream>
#include <vector>
#include "visitor.hh"
#include "expr.hh"

namespace clurtle {
    class clurtle_cpp : public visitor {
        std::ofstream _file_out;
        std::ifstream _file_header;
        std::ifstream _file_footer;
        std::vector<std::string> _initialized;
        std::vector<std::string> _dont_use;
        int _indent;
        
    public:
        clurtle_cpp(std::string filename);
        ~clurtle_cpp();

        void visit_up(const up * u);
        void visit_down(const down * d);
        void visit_change_color(const change_color * cc);
        void visit_color(const color * c);
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
        void visit_seq_item(const seq_item * si);
    };
}

#endif