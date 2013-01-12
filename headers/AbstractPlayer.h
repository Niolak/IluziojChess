#ifndef ABSTRACT_PLAYER_H
#define ABSTRACT_PLAYER_H

class AbstractPlayer
{
public :
    virtual void select(int x, int y) = 0;
    virtual void run() = 0;
    virtual inline int getSelected() const = 0;
};

#endif // ABSTRACT_PLAYER_H
