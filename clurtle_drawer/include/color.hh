#ifndef COLOR_H
#define COLOR_H

namespace clurtle {
    class color {
        std::array<expr *, 3> _val;
    public: 
        color(expr * val1, expr * val2, expr * val3);
        ~color();

        inline std::array<expr *, 3> get_val() const;

        void visit(visitor & v) const;
    };
}

#endif