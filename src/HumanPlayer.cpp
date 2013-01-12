#include "HumanPlayer.h"

#include <iostream>

HumanPlayer::HumanPlayer(Player p, AbstractChessModel& p_boardModel) :
    player(p),
    boardModel(p_boardModel),
    selected(-1)
{

}

void HumanPlayer::select(int x, int y) {
    if(boardModel.getCurrentPlayer() == player)
    {
        if(boardModel.getPiece(x,y)*player > 0)
        {
            int n = x+y*8;
            if(selected == n) selected=-1;
            else selected = x+y*8;
        }
        else if(selected != -1)
        {
            unsigned int dest = x+y*8;
            boardModel.tryMove(selected, dest);
            selected = -1;
        }
    }
}
