#ifndef IA_PLAYER_H
#define IA_PLAYER_H

#include "AbstractPlayer.h"

#include "ChessModel.h"
#include "MovesTree.h"


class AIPlayer : public AbstractPlayer
{
public :
    AIPlayer(Player p, ChessModel& p_boardModel, int p_lvl);

    virtual inline void select(int x, int y) {};
    virtual void run();

    void AIRec(int n, MovesTree* p_mt, int alpha=-2047, int beta=2047);

    virtual inline int getSelected() const {return -1;};

private :
    int lvl;
    Player player;
    ChessModel& boardModel;
};

#endif // IA_PLAYER_H
