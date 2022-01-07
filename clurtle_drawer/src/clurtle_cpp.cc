#include "clurtle_cpp.hh"

#include <exception>

#include "change_color.hh"
#include "forward.hh"
#include "rotate.hh"
#include "line.hh"
#include "rectangle.hh"
#include "conditional.hh"
#include "while_loop.hh"
#include "constant.hh"
#include "for_loop.hh"
#include "color.hh"
#include "ope.hh"
#include "variable.hh"
#include "affectation.hh"
#include "seq.hh"

namespace clurtle {
    clurtle_cpp::clurtle_cpp(std::string filename) : _pen_is_up(0), _pos_x(0), _pos_y(0), _rot(0), _indent(0) {
        try
        {
            _file.open(filename);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            exit(EXIT_FAILURE);
        }
        
        // TODO: FREE ME PLEASE !!!
        _color = {new constant(0), new constant(0), new constant(0)};
    }

    void clurtle_cpp::visit_up(const up * u) {
        _pen_is_up = true;
        std::cout << std::string(_indent, '\t') << "PEN_UP();" << std::endl;
    }

    void clurtle_cpp::visit_down(const down * d) {
        _pen_is_up = false;
        std::cout << std::string(_indent, '\t') << "PEN_DOWN();" << std::endl;
    }

    void clurtle_cpp::visit_change_color(const change_color * cc) {
        std::cout << std::string(_indent, '\t') << "CHANGE_COLOR = ";
        cc->get_color()->visit(*this);
        std::cout << ";" << std::endl; 
    }

    void clurtle_cpp::visit_color(const color * c) {
        std::cout << "{";
        c->get_r()->visit(*this);
        std::cout << ", ";
        c->get_g()->visit(*this);
        std::cout << ", ";
        c->get_b()->visit(*this);
        std::cout << "}";
    }


    void clurtle_cpp::visit_forward(const forward * f) {
        std::cout << std::string(_indent, '\t') << "FORWARD(";
        f->get_amount()->visit(*this);
        std::cout << ");" << std::endl;
    }

    void clurtle_cpp::visit_rotate(const rotate * r) {
        std::cout << std::string(_indent, '\t') << "ROTATE(";
        r->get_amount()->visit(*this);
        std::cout << ");" << std::endl;
    }

    void clurtle_cpp::visit_line(const line * l) {
        std::cout << std::string(_indent, '\t') << "LINE(";
        l->get_length()->visit(*this);
        std::cout << ");" << std::endl;
    }

    void clurtle_cpp::visit_rectangle(const rectangle * r) {
        std::cout << std::string(_indent, '\t') << "RECTANGLE(";
        r->get_length()->visit(*this);
        std::cout << ", ";
        r->get_width()->visit(*this);
        std::cout << ");" << std::endl;
    }

    void clurtle_cpp::visit_conditional(const conditional * c) {
        std::cout << std::string(_indent, '\t') << "IF (";
        c->get_cond()->visit(*this);
        std::cout << ") {" << std::endl;
        c->get_cons()->visit(*this);
        std::cout << std::string(_indent, '\t') << "}";
        if (c->get_alt() != nullptr) {
            std::cout << "ELSE {" << std::endl;
            c->get_alt()->visit(*this);
            std::cout << "}";
        }
        std::cout << std::endl;
    }

    void clurtle_cpp::visit_while_loop(const while_loop * wl) {
        std::cout << std::string(_indent, '\t') << "WHILE (";
        _indent++;
        wl->get_cond()->visit(*this);
        std::cout << ") {" << std::endl;;
        wl->get_body()->visit(*this);
        _indent--;
        std::cout << std::string(_indent, '\t') << "}" << std::endl;
    }

    void clurtle_cpp::visit_for_loop(const for_loop * fl) {
        std::cout << std::string(_indent, '\t') << "FOR ( let " << fl->get_var()->get_name() << " = 0; " << fl->get_var()->get_name() << " < ";
        fl->get_to()->visit(*this);
        std::cout << ") {" << std::endl;
        _indent++;
        fl->get_body()->visit(*this);
        _indent--;
        std::cout << std::string(_indent, '\t') << "}" << std::endl;
    }

    void clurtle_cpp::visit_ope(const ope * o) {
        o->get_left()->visit(*this);
        switch (o->get_symbol())
        {
        case OP_PLUS:
            std::cout << "+";
            break;
        case OP_MINUS:
            std::cout << "-";
            break;
        case OP_TIMES:
            std::cout << "*";
            break;
        case OP_GT:
            std::cout << ">";
            break;
        case OP_GEQ:
            std::cout << ">=";
            break;
        case OP_LT:
            std::cout << "<";
            break;
        case OP_LEQ:
            std::cout << "<=";
            break;
        case OP_EQ:
            std::cout << "==";
            break;
        case OP_AND:
            std::cout << "&&";
            break;
        case OP_OR:
            std::cout << "||";
            break;
        case OP_NOT:
            std::cout << "!";
            break;
        default:
            throw std::runtime_error("unknown operator exception");
            break;
        }
        o->get_right()->visit(*this);
    }

    void clurtle_cpp::visit_constant(const constant * c) {
        std::cout << c->get_value();
    }

    void clurtle_cpp::visit_variable(const variable * v) {
        std::cout << v->get_name();
    }

    void clurtle_cpp::visit_affectation(const affectation * a) {
        // if a->var->get_name() not exists ? -> initialisation -> prefix "int"
        std::cout << std::string(_indent, '\t') << "int ";
        a->get_var()->visit(*this);
        std::cout << " = ";
        a->get_expr()->visit(*this);
        std::cout << ";" << std::endl;
    }

    void clurtle_cpp::visit_sequence(const sequence * s) {
        if (s->get_first() != nullptr) {
            s->get_first()->visit(*this);
        }
    }

    void clurtle_cpp::visit_seq_item(const seq_item * si) {
        if (si != NULL) {
            if (si->get_inst() != NULL) {
                si->get_inst()->visit(*this);
                if (si->get_next() != NULL) {
                    si->get_next()->visit(*this);
                } 
            }
        }
    }
}