#include "clurtle_cpp.hh"

#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

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
    clurtle_cpp::clurtle_cpp(std::string filename) :_file_out(filename), _file_header("clurtle_drawer/clurtle_cpp.header"), _file_footer("clurtle_drawer/clurtle_cpp.footer"), _indent(1) {
        try
        {
            if (!_file_header.is_open() || !_file_out.is_open() || !_file_footer.is_open()) {
                throw new std::runtime_error("cant open file " + filename + " or clurtle_cpp.header or clurtle_cpp.footer");
            }

            std::string line;
            while ( getline(_file_header, line) )
            {
                _file_out << line << '\n';
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            exit(EXIT_FAILURE);
        }
    }

    clurtle_cpp::~clurtle_cpp() {
        _file_out.close();
        _file_header.close();
        _file_footer.close();
    }

    void clurtle_cpp::visit_up(const up * u) {
        _file_out << std::string(_indent, '\t') << "is_up = true;" << std::endl;
        (void)u; // Suppress unused-parameter warning
    }

    void clurtle_cpp::visit_down(const down * d) {
        _file_out << std::string(_indent, '\t') << "is_up = false;" << std::endl;
        (void)d; // Suppress unused-parameter warning
    }

    void clurtle_cpp::visit_change_color(const change_color * cc) {
        cc->get_color()->visit(*this);
    }

    void clurtle_cpp::visit_color(const color * c) {
        // Au lieu de donner la couleur, on change la valeur de la 
        // couleur actuelle (au lieu de le faire dans `visit_change_color`)
        // car on utilise un tableau pour le stocker localement,
        // il faudrait changer ca parce que si la syntaxe évolue, 
        // (eg. RECTANGLE l w color), le code ne fonctionnera plus.
        // Pour le moment, color est forcément un enfant de change_color,
        // donc cela ne pose pas de problèmes.
        // TODO(Louis): Fix me ! 
        _file_out << std::string(_indent, '\t') << "color[0] = ";
        c->get_r()->visit(*this);
        _file_out << ";" << std::endl << std::string(_indent, '\t') << "color[1] = ";
        c->get_g()->visit(*this);
        _file_out << ";" << std::endl << std::string(_indent, '\t') << "color[2] = ";
        c->get_b()->visit(*this);
        _file_out << ";" << std::endl;
    }


    void clurtle_cpp::visit_forward(const forward * f) {
        _file_out << std::string(_indent, '\t') << "forward(";
        f->get_amount()->visit(*this);
        _file_out << ");" << std::endl;
    }

    void clurtle_cpp::visit_rotate(const rotate * r) {
        _file_out << std::string(_indent, '\t') << "curr_rot = std::fmod((";
        r->get_amount()->visit(*this);
        _file_out << " + curr_rot ), 360);" << std::endl;
    }

    void clurtle_cpp::visit_line(const line * l) {
        _file_out << std::string(_indent, '\t') << "line(";
        l->get_length()->visit(*this);
        _file_out << ");" << std::endl;
    }

    void clurtle_cpp::visit_rectangle(const rectangle * r) {
        _file_out << std::string(_indent, '\t') << "rectangle(";
        r->get_length()->visit(*this);
        _file_out << ", ";
        r->get_width()->visit(*this);        
        _file_out << ");" << std::endl;
    }

    void clurtle_cpp::visit_conditional(const conditional * c) {
        _file_out << std::string(_indent, '\t') << "if (";
        c->get_cond()->visit(*this);
        _file_out << ") {" << std::endl;
        c->get_cons()->visit(*this);
        _file_out << std::string(_indent, '\t') << "}";
        if (c->get_alt() != nullptr) {
            _file_out << "else {" << std::endl;
            c->get_alt()->visit(*this);
            _file_out << "}";
        }
        _file_out << std::endl;
    }

    void clurtle_cpp::visit_while_loop(const while_loop * wl) {
        _file_out << std::string(_indent, '\t') << "while (";
        _indent++;
        wl->get_cond()->visit(*this);
        _file_out << ") {" << std::endl;;
        wl->get_body()->visit(*this);
        _indent--;
        _file_out << std::string(_indent, '\t') << "}" << std::endl;
    }

    void clurtle_cpp::visit_for_loop(const for_loop * fl) {
        _file_out << std::string(_indent, '\t') << "for ( int " << fl->get_var()->get_name() << " = ";
        fl->get_from()->visit(*this);
        _file_out << "; " << fl->get_var()->get_name() << " < ";
        fl->get_to()->visit(*this);
        _file_out << "; " << fl->get_var()->get_name() << "++) {" << std::endl;
        _indent++;
        fl->get_body()->visit(*this);
        _indent--;
        _file_out << std::string(_indent, '\t') << "}" << std::endl;
    }

    void clurtle_cpp::visit_ope(const ope * o) {
        _file_out << "(";
        o->get_left()->visit(*this);
        _file_out << ")";
        switch (o->get_symbol())
        {
        case OP_PLUS:
            _file_out << "+";
            break;
        case OP_MINUS:
            _file_out << "-";
            break;
        case OP_TIMES:
            _file_out << "*";
            break;
        case OP_GT:
            _file_out << ">";
            break;
        case OP_GEQ:
            _file_out << ">=";
            break;
        case OP_LT:
            _file_out << "<";
            break;
        case OP_LEQ:
            _file_out << "<=";
            break;
        case OP_EQ:
            _file_out << "==";
            break;
        case OP_AND:
            _file_out << "&&";
            break;
        case OP_OR:
            _file_out << "||";
            break;
        case OP_NOT:
            _file_out << "!";
            break;
        default:
            throw std::runtime_error("unknown operator exception");
            break;
        }
        _file_out << "(";
        o->get_right()->visit(*this);
        _file_out << ")";
    }

    void clurtle_cpp::visit_constant(const constant * c) {
        _file_out << c->get_value();
    }

    void clurtle_cpp::visit_variable(const variable * v) {
        _file_out << v->get_name();
    }

    void clurtle_cpp::visit_affectation(const affectation * a) {
        _file_out << std::string(_indent, '\t');
        if (std::find(_initialized.begin(), _initialized.end(), a->get_var()->get_name()) == _initialized.end()) {
            // if la variable n'est pas dans _initialized aka n'est initialisée
            _file_out << "double ";
            _initialized.push_back(a->get_var()->get_name());
        }
        a->get_var()->visit(*this);
        _file_out << " = ";
        a->get_expr()->visit(*this);
        _file_out << ";" << std::endl;
    }

    void clurtle_cpp::visit_sequence(const sequence * s) {
        if (s->get_first() != nullptr) {
            s->get_first()->visit(*this);
        }
        // Add file footer
        std::string line;
        while (getline(_file_footer, line))
        {
            _file_out << line << '\n';
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