#ifndef ABSTRACT_CHESS_MODEL_H
#define ABSTRACT_CHESS_MODEL_H

#include "Move.h"

enum Player {BLACK=-1, WHITE=1};
enum Piece {B_PAWN=-1, B_ROOK=-2, B_KNIGHT=-3, B_BISHOP=-4, B_QUEEN=-5, B_KING=-6, B_SPECTRUM=-7, NONE=0, PAWN=1, ROOK=2, KNIGHT=3, BISHOP=4, QUEEN=5, KING=6, SPECTRUM=7};

class AbstractChessModel
{
public :
    virtual Player getCurrentPlayer() = 0;
    virtual void tryMove(int src, int dest)=0;
    virtual void validateMove(Move m)=0;
    virtual void cancelLastMove()=0;

    virtual Piece getPiece(int x, int y) = 0;
    virtual Move* searchMove(int src, int dest)=0;

    virtual bool isMate() = 0;
    virtual bool isWhiteCheck() = 0;
    virtual bool isBlackCheck() = 0;
};

#endif // ABSTRACT_CHESS_MODEL_H
