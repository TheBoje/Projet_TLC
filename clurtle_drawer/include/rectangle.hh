#ifndef RECTANGLE_HH
#define RECTANGLE_HH

#include "instr.hh"

namespace clurtle {
    class rectangle : public instr {
        int _length;
        int _width;
    public:
        rectangle(int length, int width);
        ~rectangle();

        inline int get_length() const { return _length; }
        inline int get_width() const { return _width; }

        void visit(visitor & v) const;    
    
    };
}

#endif