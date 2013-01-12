#ifndef RANDOM_AIPLAYER_H
#define RANDOM_AIPLAYER_H

#include "AbstractPlayer.h"

#include "ChessModel.h"

class RandomAIPlayer : public AbstractPlayer
{
public :
    RandomAIPlayer(Player p, ChessModel& p_boardModel);

    virtual inline void select(int x, int y) {};
    virtual void run();

    virtual inline int getSelected() const {return -1;};

private :
    Player player;
    ChessModel& boardModel;
};

#endif

