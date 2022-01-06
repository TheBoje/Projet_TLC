#include "clurtle_cpp.hh"

#include "change_color.hh"
#include "forward.hh"
#include "rotate.hh"
#include "line.hh"
#include "rectangle.hh"
#include "conditional.hh"
#include "while_loop.hh"

namespace clurtle {
    clurtle_cpp::clurtle_cpp(std::string filename) : _pen_is_up(0), _pos_x(0), _pos_y(0), _rot(0) {
        try
        {
            _file.open(filename);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            exit(EXIT_FAILURE);
        }
        
        _color = {0, 0, 0};
    }

    void clurtle_cpp::visit_up(const up * u) {
        _pen_is_up = true;
        std::cout << "PEN_UP;" << std::endl;
    }

    void clurtle_cpp::visit_down(const down * d) {
        _pen_is_up = false;
        std::cout << "PEN_DOWN;" << std::endl;
    }

    void clurtle_cpp::visit_change_color(const change_color * cc) {
        std::cout << "COLOR = {";
        _color = cc->get_color();
        _color[0]->visit(this);
        std::cout << ", ";
        _color[1]->visit(this);
        std::cout << ", ";
        _color[2]->visit(this);
        std::cout << "};" << std::endl; 
    }

    void clurtle_cpp::visit_forward(const forward * f) {
        std::cout << "FORWARD(";
        f->get_amount()->visit(this);
        std::cout << ");" << std::endl;
    }

    void clurtle_cpp::visit_rotate(const rotate * r) {
        std::cout << "ROTATE(";
        r->get_amount()->visit(this);
        std::cout << ");" << std::endl;
    }

    void clurtle_cpp::visit_line(const line * l) {
        std::cout << "LINE(";
        l->get_length()->visit(this);
        std::cout << ");" << std::endl;
    }

    void clurtle_cpp::visit_rectangle(const rectangle * r) {
        std::cout << "RECTANGLE(";
        r->get_length()->visit(this);
        std::cout << ", ";
        r->get_width()->visit(this);
        std::cout << ");" << std::endl;
    }

    void clurtle_cpp::visit_conditional(const conditional * c) {
        std::cout << "IF (";
        c->get_cond()->visit(this);
        std::cout << ") {" << std::endl;
        c->get_cons()->visit(this);
        std::cout << "}";
        if (c->get_alt() != nullptr) {
            std::cout << "ELSE {" << std::endl;
            c->get_alt()->visit(this);
            std::cout << "}";
        }
        std::cout << std::endl;
    }

    void clurtle_cpp::visit_while_loop(const while_loop * wl) {
        std::cout << "WHILE (";
        wl->get_cond()->visit(this);
        std::cout << ") {" << std::endl;;
        wl->get_cons()->visit(this);
        std::cout << "}" << std::endl;
    }

    void clurtle_cpp::visit_for_loop(const for_loop * fl) {
        std::cout << "FOR ("
    }
}