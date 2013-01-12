#include "AIPlayer.h"
#include "MovesTree.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

AIPlayer::AIPlayer(Player p, ChessModel& p_boardModel, int p_lvl) :
    lvl(p_lvl),
    player(p),
    boardModel(p_boardModel) {

    std::srand(std::time(0));
}

void AIPlayer::run() {
    if(boardModel.getCurrentPlayer() == player)
    {
        MovesTree mt;
        AIRec(lvl, &mt);

        std::deque<Move> goodMoves;

        for(int i=0; i<mt.getSize(); ++i) {
            if(mt.get(i)->m.score == -mt.m.score)
            {
                goodMoves.push_back(mt.get(i)->m);
            }
        }

        if(goodMoves.size())
        {
            int k = std::rand()%goodMoves.size();
            boardModel.validateMove(goodMoves[k]);
        }
    }
}

void AIPlayer::AIRec(int n, MovesTree* p_mt, int alpha, int beta) {
    if(n==0)
    {
        p_mt->m.score = (countBits(boardModel.whitePawn)-countBits(boardModel.blackPawn))*10
                            +(countBits(boardModel.whiteKnight)-countBits(boardModel.blackKnight))*30
                            +(countBits(boardModel.whiteBishop)-countBits(boardModel.blackBishop))*30
                            +(countBits(boardModel.whiteRook)-countBits(boardModel.blackRook))*50
                            +(countBits(boardModel.whiteQueen)-countBits(boardModel.blackQueen))*90;

        if(boardModel.getCurrentPlayer()==BLACK) p_mt->m.score = -p_mt->m.score;
    }
    else
    {
        int i;
        int impossibleMoves=0;

        boardModel.generateMoves(*p_mt);
        for(i=0; i<p_mt->getSize(); ++i) {
            boardModel.playMove(p_mt->get(i)->m);
            boardModel.refreshControlledBB();

            if((boardModel.currentPlayer == BLACK && (boardModel.whiteKing & ~boardModel.blackControlled)) ||
               (boardModel.currentPlayer == WHITE && (boardModel.blackKing & ~boardModel.whiteControlled)))
            {
                AIRec(n-1, p_mt->get(i), -beta, -alpha);
            }
            else
            {
                ++impossibleMoves;
            }

            boardModel.cancelMove(p_mt->get(i)->m);
            boardModel.refreshControlledBB();

            if(((int)p_mt->get(i)->m.score) != 2047 && (int)p_mt->get(i)->m.score != -2047) {
                int val = - ((int)p_mt->get(i)->m.score);
                if(val > p_mt->m.score) {
                    p_mt->m.score = val;
                    if(p_mt->m.score > alpha) {
                        alpha = p_mt->m.score;
                        if(alpha >= beta) {
                            break;
                        }
                    }
                }
            }
        }
        if(p_mt->getSize()-impossibleMoves == 0 && (boardModel.isWhiteCheck()||boardModel.isBlackCheck())) {
            p_mt->m.score = player*boardModel.getCurrentPlayer() * (2000+n);
        }

        //if(n!=lvl) p_mt->clear();
    }
}
