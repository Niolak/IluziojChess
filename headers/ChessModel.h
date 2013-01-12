#ifndef CHESS_MODEL_H
#define CHESS_MODEL_H

#include <vector>
#include <iostream>

#include "AbstractChessModel.h"
#include "bb.h"
#include "Deque.h"

#define KING_CASTLING 1
#define QUEEN_CASTLING 2

class AIPlayer;

class ChessModel : public AbstractChessModel
{
public :
    friend class AIPlayer;
    friend class RandomAIPlayer;

    ChessModel();

    virtual inline Player getCurrentPlayer() {
        return (Player) currentPlayer;
    }

    void createBB();

    void generateMoves(Container& c);
    void checkAllMoves();
    void refreshControlledBB();

    virtual void tryMove(int src, int dest);
    virtual void playMove(Move p_m);

    virtual void validateMove(Move p_m);
    virtual void cancelMove(Move p_m);
    virtual void cancelLastMove();

    inline unsigned int getBlackPiece(bb b) {
        for(int i=1; i<=7; ++i)
        {
            if(pieces[-i]&b) return i;
        }
        return 0;
    };

    inline unsigned int getWhitePiece(bb b) {
        for(int i=1; i<=7; ++i)
        {
            if(pieces[i]&b) return i;
        }
        return 0;
    };

    virtual Piece getPiece(int x, int y);
    virtual Move* searchMove(int src, int dest);

    virtual inline bool isMate() { return possibleMoves.size()==0;};
    virtual inline bool isWhiteCheck() {return whiteKing&blackControlled;};
    virtual inline bool isBlackCheck() {return blackKing&whiteControlled;};

private :
    bb whiteBB;
    bb blackBB;

    bb* pieces;

    // ORDER IS IMPORTANT HERE!!!
    bb blackSpectrum; // for "en passant"
    bb blackKing;
    bb blackQueen;
    bb blackBishop;
    bb blackKnight;
    bb blackRook;
    bb blackPawn;

    bb piecesPtr;

    bb whitePawn;
    bb whiteRook;
    bb whiteKnight;
    bb whiteBishop;
    bb whiteQueen;
    bb whiteKing;
    bb whiteSpectrum; // for "en passant"

    int currentPlayer;

    Deque possibleMoves;
    std::vector<Move> pastMoves;

    // reverse order so it corresponds to bb
    enum {
        A8, B8, C8, D8, E8, F8, G8, H8,
        A7, B7, C7, D7, E7, F7, G7, H7,
        A6, B6, C6, D6, E6, F6, G6, H6,
        A5, B5, C5, D5, E5, F5, G5, H5,
        A4, B4, C4, D4, E4, F4, G4, H4,
        A3, B3, C3, D3, E3, F3, G3, H3,
        A2, B2, C2, D2, E2, F2, G2, H2,
        A1, B1, C1, D1, E1, F1, G1, H1};

    bb cA,cB,cC,cD,cE,cF,cG,cH;
    bb r1,r2,r3,r4,r5,r6,r7,r8;

    bb blackPawnCaptures[64], blackPawnMoves[64], blackPawnMoves2[64], whitePawnMoves2[64], whitePawnMoves[64], whitePawnCaptures[64];
    bb u[64],d[64],l[64],r[64],ul[64],ur[64],dl[64],dr[64];
    bb knightMoves[64];
    bb kingMoves[64];

    bb whiteControlled;
    bb blackControlled;

    unsigned int whiteCastling;
    unsigned int blackCastling;
};

#endif // CHESS_MODEL_H
