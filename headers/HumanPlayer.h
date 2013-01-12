#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "AbstractChessModel.h"
#include "AbstractPlayer.h"

class HumanPlayer : public AbstractPlayer
{
public :
    HumanPlayer(Player p, AbstractChessModel& p_boardModel);

    virtual void select(int x, int y);
    virtual inline void run() {};

    virtual inline int getSelected() const {return selected;};
    inline bool selectedCanGo(int x, int y) const {return boardModel.searchMove(selected, x+y*8); };

private :
    Player player;
    AbstractChessModel& boardModel;
    int selected;
};

#endif // HUMAN_PLAYER_H
