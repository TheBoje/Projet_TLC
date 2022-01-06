#include "seq.hh"

clurtle::seq_item::seq_item(instr * i, seq_item * next = nullptr) :
    _instr(i),
    _next(next)
{}

clurtle::seq_item::~seq_item() {
    delete _instr;
    if(_next != nullptr)
        delete _next;
}

void clurtle::seq_item::add(instr * i) {
    if(_next == nullptr)
        _next = new seq_item(i);
    else
        _next->add(i);
}

clurtle::sequence::sequence(instr * i) :
    _first(nullptr)
{
    if(i != nullptr)
        _first = new seq_item(i);
}

clurtle::sequence::~sequence() {
    if(_first != nullptr)
        delete _first;
}

void clurtle::sequence::visit(visitor & v) const {
    v.visit_sequence(this);
}

void clurtle::sequence::add(instr * i) {
    if(_first == nullptr)
        _first = new seq_item(i, _first);
    else
        _first->add(i);
}