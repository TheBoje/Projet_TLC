#include "clurtle.hh"

#include <math.h>

#include "change_color.hh"
#include "forward.hh"
#include "rotate.hh"
#include "line.hh"
#include "rectangle.hh"
#include "conditional.hh"
#include "while_loop.hh"
#include "for_loop.hh"
#include "ope.hh"
#include "constant.hh"
#include "variable.hh"
#include "affectation.hh"

clurtle::clurtle::clurtle() : 
    _pen_is_up(true), 
    _color({0, 0, 0}),
    _pos({0, 0}),
    _rotation(0)
{} 

void clurtle::clurtle::visit_up(const up * u) {
    _pen_is_up = true;
}

void clurtle::clurtle::visit_down(const down * d) {
    _pen_is_up = false;
}

void clurtle::clurtle::visit_change_color(const change_color * cc) {
    //_color = cc->get_color();
}

void clurtle::clurtle::visit_forward(const forward * f) {
    f->get_amount()->visit(*this);
    
    int hyp = get_last_int();

    int x = _pos[0] + hyp * cos(_rotation * (M_1_PI / 180));
    int y = _pos[1] + hyp * sin(_rotation * (M_1_PI / 180));

    // TODO: Déplacer de "amount"
}

void clurtle::clurtle::visit_rotate(const rotate * r) {
    r->get_amount()->visit(*this);
    
    int rot = get_last_int();

    _rotation = (_rotation + rot) % 360;
    // TODO: tourne la tortue de amount degré
}

void clurtle::clurtle::visit_line(const line * l) {
    l->get_length()->visit(*this);
    int length = get_last_int();
    // TODO: dessine une ligne sans bouger la tortue
}

void clurtle::clurtle::visit_rectangle(const rectangle * r) {
    r->get_length()->visit(*this);
    int length = get_last_int();
    r->get_width()->visit(*this);
    int width = get_last_int();
    // TODO: dessine un rectangle
}


void clurtle::clurtle::visit_ope(const ope * o) {
    ope_symbol ope = o->get_symbol();
    
    o->get_left()->visit(*this); // not **this ?
    o->get_right()->visit(*this);
    
    int size = _stack.size();
    int sb_size = _stack_bool.size();

    if(ope != AND && ope != OR && size >= 2)
    {
        int a = _stack[size - 1];
        int b = _stack[size - 2];

        _stack.pop_back();
        _stack.pop_back();

        switch (ope)
        {
        case PLUS:
            _stack.push_back(a + b);
            break;

        case MINUS:
            _stack.push_back(a - b);
            break;

        case TIMES:
            _stack.push_back(a * b);
            break;

        case DIVIDE:
            _stack.push_back(a / b);
            break;

        case GT:
            _stack_bool.push_back(a > b);
            break;
        
        case GEQ:
            _stack_bool.push_back(a >= b);
            break;

        case LT:
            _stack_bool.push_back(a < b);
            break;
        
        case LEQ:
            _stack_bool.push_back(a <= b);
            break;
        
        case EQ:
            _stack_bool.push_back(a == b);
            break;

        default:
            break;
        }
    }
    else if(ope == AND || ope == OR && sb_size >= 2)
    {
        bool a = _stack_bool[sb_size - 1];
        bool b = _stack_bool[sb_size - 2];

        _stack_bool.pop_back();
        _stack_bool.pop_back();

        switch (ope)
        {
        case AND:
            _stack_bool.push_back(a && b);
            break;
        
        case OR:
            _stack_bool.push_back(a || b);
            break;

        default:
            break;
        }
    }
    else if(ope == NOT && sb_size >= 1)
    {
        _stack_bool[sb_size - 1] = !_stack_bool[sb_size - 1];
    }
    
}

void clurtle::clurtle::visit_conditional(const conditional * c) {
    c->get_cond()->visit(*this);
    
    bool cond = get_last_bool();

    if(cond) 
    {
        c->get_cons()->visit(*this);
    }
    else
    {
        c->get_alt()->visit(*this);
    }
}

void clurtle::clurtle::visit_while_loop(const while_loop * wl) {
    wl->get_cond()->visit(*this);
    bool res = get_last_bool();

    while(res) {
        wl->get_body()->visit(*this);
        wl->get_cond()->visit(*this);
        res = get_last_bool();
    }
}

void clurtle::clurtle::visit_for_loop(const for_loop * fl) {
    std::string incr = fl->get_var();
    _variables[incr] = 0;

    fl->get_to()->visit(*this);
    int to = get_last_int();

    for(int i = 0; i < to; i++)
    {
        fl->get_body()->visit(*this);
    }

    _variables.erase(incr);
}

void clurtle::clurtle::visit_constant(const constant * c) {
    _stack.push_back(c->get_value());
}

void clurtle::clurtle::visit_variable(const variable * v) {
    _stack.push_back(_variables[v->get_name()]);
}

void clurtle::clurtle::visit_affectation(const affectation * a) {
    a->get_expr()->visit(*this);
    _variables[a->get_var()] = get_last_int();
}