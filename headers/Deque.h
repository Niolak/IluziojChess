#ifndef DEQUE_H
#define DEQUE_H

#include <deque>
#include "Container.h"
#include "Move.h"

class Deque : public std::deque<Move>, public Container
{
public :
    virtual inline void clear() {std::deque<Move>::clear();};
    virtual inline void add(const Move& p_move) {std::deque<Move>::push_back(p_move);};
    virtual inline int getSize() const {return size();};
};

#endif // DEQUE_H
