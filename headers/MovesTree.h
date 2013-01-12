#ifndef MOVES_TREE_H
#define MOVES_TREE_H

#include <iostream>
#include <sstream>

#include "Container.h"
#include "Move.h"

class MovesTree : public Container {
public :
    MovesTree(Move p_m={0,0,0,0,0,-2047});
    virtual ~MovesTree();

    void add(const Move& m);

    inline MovesTree* get(int p) {return children[p];};

    virtual void clear();

    virtual inline int getSize() const {return childrenCount;};

    void print(std::string shift, bool everything);

public :
    Move m;
private :
    MovesTree* children[200];
    int childrenCount;
};

#endif // MOVES_TREE_H
