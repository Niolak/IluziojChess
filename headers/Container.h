#ifndef CONTAINER_H
#define CONTAINER_H

#include "Move.h"

class Container {
public :
    virtual inline ~Container() {};
    virtual void clear()=0;
    virtual void add(const Move& move)=0;
    virtual int getSize() const=0;
};

#endif // CONTAINER_H
