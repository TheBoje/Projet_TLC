#ifndef VISITOR_HH
#define VISITOR_HH

namespace clurtle {

    class up; 
    class down;
    class change_color;
    class forward;
    class rotate;
    class line;
    class rectangle;
    class conditional;
    class while_loop;
    class for_loop;
    class ope;
    class ope_bool;
    class constant;

    class visitor  {
    public:
        virtual void visit_up(const up * u) = 0;
        virtual void visit_down(const down * d) = 0;
        virtual void visit_change_color(const change_color * cc) = 0;
        virtual void visit_forward(const forward * f) = 0;
        virtual void visit_rotate(const rotate * r) = 0;
        virtual void visit_line(const line * l) = 0;
        virtual void visit_rectangle(const rectangle * r) = 0;
        virtual void visit_conditional(const conditional * c) = 0;
        virtual void visit_while_loop(const while_loop * wl) = 0;
        virtual void visit_for_loop(const for_loop * fl) = 0;
        virtual void visit_ope(const ope * o) = 0;
        virtual void visit_constant(const constant * c) = 0;
        virtual void visit_ope_bool(const ope_bool * o) = 0;
    };

}

#endif