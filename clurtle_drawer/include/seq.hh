#ifndef SEQ_HH
#define SEQ_HH


#include "instr.hh"

namespace clurtle {

    class seq_item {
        instr * _instr;
        seq_item * _next;
    public:
        seq_item(instr * i, seq_item * next);
        ~seq_item();

        inline const instr * get_inst() const { return _instr; }
        inline bool has_next() const { return (_next != nullptr); }
        inline seq_item * get_next() const { return _next; }

        void add(instr * i);
    };


    class sequence : public instr {
        seq_item * _first;
    public:
        sequence(instr * first);
        ~sequence();
        
        inline seq_item * get_first() const { return _first; }

        void visit(visitor & v) const;

        void add(instr * i);
    };
}
#endif
