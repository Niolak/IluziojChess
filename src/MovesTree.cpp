#include <iostream>
#include <cassert>
#include "bb.h"

#include "MovesTree.h"

MovesTree::MovesTree(Move p_m) :
    m(p_m),
    childrenCount(0)
{

}

MovesTree::~MovesTree() {
    clear();
}

void MovesTree::add(const Move& m) {
    children[childrenCount++] = new MovesTree(m);

    assert(childrenCount <= 200);
}

void MovesTree::clear() {
    for(int i=0; i<childrenCount; ++i)
    {
        delete children[i];
    }
    childrenCount=0;
}

void MovesTree::print(std::string shift, bool everything) {
    if(m.score<0)
        std::cerr << shift << " * -" << std::dec << (-m.score) << " ( " << std::hex << bbFrom(m.src) << " to " << std::hex << bbFrom(m.dest) << " with " << m.piece << " )" << std::endl;
    else
        std::cerr << shift << " * " << std::dec << (m.score) << " ( " << std::hex << bbFrom(m.src) << " to " << std::hex << bbFrom(m.dest) << " with " << m.piece << " )" << std::endl;
    for(int i=0; i<childrenCount; ++i) {
        if(everything || (children[i]->m.score == -m.score)) children[i]->print(shift+"     ", everything);
    }
}
