#include "clurtle.hh"

#include <math.h>
#include <iostream>

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
#include "seq.hh"
#include "color.hh"


clurtle::clurtle::clurtle(int sizex, int sizey) : 
    _pen_is_up(true), 
    _color{0, 0, 0},
    _pos({sizex / 2, sizey / 2}),
    _rotation(0),
    _img(cimg_library::CImg<unsigned char>(sizex, sizey, 1, 3))
{
    _img.fill(255);
}

clurtle::clurtle::~clurtle() {
    cimg_library::CImgDisplay disp;
    disp.display(_img);
    _img.save_bmp("toto.bmp");
    while (!disp.is_closed()) 
    {
        // boucle des evenements
        if (disp.key() == cimg_library::cimg::keyQ)
        disp.close();
        disp.wait();
    }
}

void clurtle::clurtle::visit_up(const up * u) {
    _pen_is_up = true;
    (void)u; // Suppress unused-parameter warning
}

void clurtle::clurtle::visit_down(const down * d) {
    _pen_is_up = false;
    (void)d; // Suppress unused-parameter warning
}

void clurtle::clurtle::visit_change_color(const change_color * cc) {
    cc->get_color()->visit(*this);
}

void clurtle::clurtle::visit_color(const color * c) {
    c->get_r()->visit(*this);
    c->get_g()->visit(*this);
    c->get_b()->visit(*this);

    char r = get_last_int();
    char g = get_last_int();
    char b = get_last_int();

    _color[2] = r;
    _color[1] = g;
    _color[0] = b;
}

void clurtle::clurtle::visit_forward(const forward * f) {
    f->get_amount()->visit(*this);
    int hyp = get_last_int();

    int x = _pos[0] + hyp * cos(_rotation * (M_PI / 180));
    int y = _pos[1] + hyp * sin(_rotation * (M_PI / 180));

    if(!_pen_is_up)
    {
        _img.draw_line(_pos[0], _pos[1], x, y, _color);

    }

    _pos[0] = x;
    _pos[1] = y;
}

void clurtle::clurtle::visit_rotate(const rotate * r) {
    r->get_amount()->visit(*this);
    
    int rot = get_last_int();

    _rotation = (_rotation + rot) % 360;
}

void clurtle::clurtle::visit_line(const line * l) {
    l->get_length()->visit(*this);
    int length = get_last_int();

    int x = _pos[0] + length * cos(_rotation * (M_PI / 180));
    int y = _pos[1] + length * sin(_rotation * (M_PI / 180));

    _img.draw_line(_pos[0], _pos[1], x, y, _color);
}

void clurtle::clurtle::visit_rectangle(const rectangle * r) {
    r->get_length()->visit(*this);
    int length = get_last_int();
    r->get_width()->visit(*this);
    int width = get_last_int();

    for(int i = 0; i < 4; i++) 
    {
        int x = _pos[0] + (i % 2 == 0 ? length : width) * cos(_rotation * (M_PI / 180));
        int y = _pos[1] + (i % 2 == 0 ? length : width) * sin(_rotation * (M_PI / 180));

        _img.draw_line(_pos[0], _pos[1], x, y, _color);

        _pos[0] = x;
        _pos[1] = y;

        _rotation = (_rotation + 90) % 360;        
    }
}


void clurtle::clurtle::visit_ope(const ope * o) {
    ope_symbol ope = o->get_symbol();
    
    o->get_left()->visit(*this); // not **this ?
    o->get_right()->visit(*this);
    
    int size = _stack.size();
    int sb_size = _stack_bool.size();

    if(ope != OP_AND && ope != OP_OR && size >= 2)
    {
        int a = _stack[size - 1];
        int b = _stack[size - 2];

        _stack.pop_back();
        _stack.pop_back();

        switch (ope)
        {
        case OP_PLUS:
            _stack.push_back(a + b);
            break;

        case OP_MINUS:
            _stack.push_back(a - b);
            break;

        case OP_TIMES:
            _stack.push_back(a * b);
            break;

        case OP_DIVIDE:
            _stack.push_back(a / b);
            break;

        case OP_GT:
            _stack_bool.push_back(a > b);
            break;
        
        case OP_GEQ:
            _stack_bool.push_back(a >= b);
            break;

        case OP_LT:
            _stack_bool.push_back(a < b);
            break;
        
        case OP_LEQ:
            _stack_bool.push_back(a <= b);
            break;
        
        case OP_EQ:
            _stack_bool.push_back(a == b);
            break;

        default:
            break;
        }
    }
    else if((ope == OP_AND || ope == OP_OR) && sb_size >= 2)
    {
        bool a = _stack_bool[sb_size - 1];
        bool b = _stack_bool[sb_size - 2];

        _stack_bool.pop_back();
        _stack_bool.pop_back();

        switch (ope)
        {
        case OP_AND:
            _stack_bool.push_back(a && b);
            break;
        
        case OP_OR:
            _stack_bool.push_back(a || b);
            break;

        default:
            break;
        }
    }
    else if(ope == OP_NOT && sb_size >= 1)
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
    std::string incr = fl->get_var()->get_name();
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
    _variables[a->get_var()->get_name()] = get_last_int();
}


void clurtle::clurtle::visit_sequence(const sequence * s) {
    seq_item * t = s->get_first();
    while(t != nullptr) 
    {
        t->get_inst()->visit(*this);
        t = t->get_next();
    }
}

void clurtle::clurtle::visit_seq_item(const seq_item * si) {
    if (si != NULL) 
    {
        if (si->get_inst() != NULL) 
        {
            si->get_inst()->visit(*this);
            if (si->get_next() != NULL) 
            {
                si->get_next()->visit(*this);
            } 
        }
    }
}

