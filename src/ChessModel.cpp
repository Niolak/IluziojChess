#include "ChessModel.h"

#include <iostream>

ChessModel::ChessModel() :

    blackKing(0x0800000000000000),
    blackQueen(0x1000000000000000),
    blackBishop(0x2400000000000000),
    blackKnight(0x4200000000000000),
    blackRook(0x8100000000000000),
    blackPawn(0x00FF000000000000),
    whitePawn(0x000000000000FF00),
    whiteRook(0x0000000000000081),
    whiteKnight(0x0000000000000042),
    whiteBishop(0x0000000000000024),
    whiteQueen(0x0000000000000010),
    whiteKing(0x0000000000000008),

/* Uncomment to test a simple situation
    blackKing(0x0800000000000000),
    blackQueen(0x0000000000000000),
    blackBishop(0x00000000000000),
    blackKnight(0x00000000000000),
    blackRook(0x8100000000000000),
    blackPawn(0x00000000000000),
    whitePawn(0x00000000000000),
    whiteRook(0x0000000000000081),
    whiteKnight(0x00000000000000),
    whiteBishop(0x00000000000000),
    whiteQueen(0x00000000000000),
    whiteKing(0x0000000000000008),
// */
    currentPlayer(WHITE),

    whiteCastling(KING_CASTLING|QUEEN_CASTLING),
    blackCastling(KING_CASTLING|QUEEN_CASTLING)
{
    pieces = &piecesPtr;

    cA = bbFrom(A1) | bbFrom(A2) | bbFrom(A3) | bbFrom(A4) | bbFrom(A5) | bbFrom(A6) | bbFrom(A7) | bbFrom(A8);
    cB = bbFrom(B1) | bbFrom(B2) | bbFrom(B3) | bbFrom(B4) | bbFrom(B5) | bbFrom(B6) | bbFrom(B7) | bbFrom(B8);
    cC = bbFrom(C1) | bbFrom(C2) | bbFrom(C3) | bbFrom(C4) | bbFrom(C5) | bbFrom(C6) | bbFrom(C7) | bbFrom(C8);
    cD = bbFrom(D1) | bbFrom(D2) | bbFrom(D3) | bbFrom(D4) | bbFrom(D5) | bbFrom(D6) | bbFrom(D7) | bbFrom(D8);
    cE = bbFrom(E1) | bbFrom(E2) | bbFrom(E3) | bbFrom(E4) | bbFrom(E5) | bbFrom(E6) | bbFrom(E7) | bbFrom(E8);
    cF = bbFrom(F1) | bbFrom(F2) | bbFrom(F3) | bbFrom(F4) | bbFrom(F5) | bbFrom(F6) | bbFrom(F7) | bbFrom(F8);
    cG = bbFrom(G1) | bbFrom(G2) | bbFrom(G3) | bbFrom(G4) | bbFrom(G5) | bbFrom(G6) | bbFrom(G7) | bbFrom(G8);
    cH = bbFrom(H1) | bbFrom(H2) | bbFrom(H3) | bbFrom(H4) | bbFrom(H5) | bbFrom(H6) | bbFrom(H7) | bbFrom(H8);

    r1 = bbFrom(A1) | bbFrom(B1) | bbFrom(C1) | bbFrom(D1) | bbFrom(E1) | bbFrom(F1) | bbFrom(G1) | bbFrom(H1);
    r2 = bbFrom(A2) | bbFrom(B2) | bbFrom(C2) | bbFrom(D2) | bbFrom(E2) | bbFrom(F2) | bbFrom(G2) | bbFrom(H2);
    r3 = bbFrom(A3) | bbFrom(B3) | bbFrom(C3) | bbFrom(D3) | bbFrom(E3) | bbFrom(F3) | bbFrom(G3) | bbFrom(H3);
    r4 = bbFrom(A4) | bbFrom(B4) | bbFrom(C4) | bbFrom(D4) | bbFrom(E4) | bbFrom(F4) | bbFrom(G4) | bbFrom(H4);
    r5 = bbFrom(A5) | bbFrom(B5) | bbFrom(C5) | bbFrom(D5) | bbFrom(E5) | bbFrom(F5) | bbFrom(G5) | bbFrom(H5);
    r6 = bbFrom(A6) | bbFrom(B6) | bbFrom(C6) | bbFrom(D6) | bbFrom(E6) | bbFrom(F6) | bbFrom(G6) | bbFrom(H6);
    r7 = bbFrom(A7) | bbFrom(B7) | bbFrom(C7) | bbFrom(D7) | bbFrom(E7) | bbFrom(F7) | bbFrom(G7) | bbFrom(H7);
    r8 = bbFrom(A8) | bbFrom(B8) | bbFrom(C8) | bbFrom(D8) | bbFrom(E8) | bbFrom(F8) | bbFrom(G8) | bbFrom(H8);

    whiteBB = whiteBishop | whiteKing | whiteKnight | whitePawn | whiteQueen | whiteRook;
    blackBB = blackBishop | blackKing | blackKnight | blackPawn | blackQueen | blackRook;

    createBB();
    refreshControlledBB();
    generateMoves(possibleMoves);
}

void ChessModel::createBB() {
    for(unsigned int i=0; i<64; ++i)
    {
        bb bbi = bbFrom(i);

        whitePawnMoves[i] = 0;
        blackPawnMoves[i] = 0;
        whitePawnCaptures[i] = 0;
        blackPawnCaptures[i] = 0;
        whitePawnMoves2[i] = 0;
        blackPawnMoves2[i] = 0;
        if(i>=8 && i<56)
        {
            whitePawnMoves[i] = bbi << 8;
            if(bbi & ~cH) whitePawnCaptures[i] |= bbi << 7;
            if(bbi & ~cA) whitePawnCaptures[i] |= bbi << 9;

            blackPawnMoves[i] = bbi >> 8;
            if(bbi & ~cH) blackPawnCaptures[i] |= bbi >> 9;
            if(bbi & ~cA) blackPawnCaptures[i] |= bbi >> 7;

            if(bbi & r2) whitePawnMoves2[i] |= bbi << 16;
            if(bbi & r7) blackPawnMoves2[i] |= bbi >> 16;
        }

        knightMoves[i] = 0;
        if(bbi & (~(cA | r7 | r8))) knightMoves[i] |= bbi << 17;
        if(bbi & (~(cH | r7 | r8))) knightMoves[i] |= bbi << 15;
        if(bbi & (~(cA | r1 | r2))) knightMoves[i] |= bbi >> 15;
        if(bbi & (~(cH | r1 | r2))) knightMoves[i] |= bbi >> 17;
        if(bbi & (~(cA | cB | r8))) knightMoves[i] |= bbi << 10;
        if(bbi & (~(cG | cH | r8))) knightMoves[i] |= bbi << 6;
        if(bbi & (~(cA | cB | r1))) knightMoves[i] |= bbi >> 6;
        if(bbi & (~(cG | cH | r1))) knightMoves[i] |= bbi >> 10;

        u[i] = 0;
        d[i] = 0;
        l[i] = 0;
        r[i] = 0;
        ul[i] = 0;
        ur[i] = 0;
        dl[i] = 0;
        dr[i] = 0;
        for(int j = i-8; j>=0; j-=8) u[i] |= bbFrom(j);
        for(int j = i+8; j<64; j+=8) d[i] |= bbFrom(j);
        for(int j = i-1; j>=0 && !(bbFrom(j)&cH); --j) l[i] |= bbFrom(j);
        for(int j = i+1; j<64 && !(bbFrom(j)&cA); ++j) r[i] |= bbFrom(j);
        for(int j = i-9; j>=0 && !(bbFrom(j)&cH); j-=9) ul[i] |= bbFrom(j);
        for(int j = i-7; j>=0 && !(bbFrom(j)&cA); j-=7) ur[i] |= bbFrom(j);
        for(int j = i+7; j<64 && !(bbFrom(j)&cH); j+=7) dl[i] |= bbFrom(j);
        for(int j = i+9; j<64 && !(bbFrom(j)&cA); j+=9) dr[i] |= bbFrom(j);

        kingMoves[i] = 0;
        if(bbi & ~cA) kingMoves[i] |= bbi << 1;
        if(bbi & ~cH) kingMoves[i] |= bbi >> 1;
        if(bbi & ~r8) kingMoves[i] |= bbi << 8;
        if(bbi & ~r1) kingMoves[i] |= bbi >> 8;
        if(bbi & ~(cA | r1)) kingMoves[i] |= bbi >> 7;
        if(bbi & ~(cH | r1)) kingMoves[i] |= bbi >> 9;
        if(bbi & ~(cH | r8)) kingMoves[i] |= bbi << 7;
        if(bbi & ~(cA | r8)) kingMoves[i] |= bbi << 9;
    }
}

void ChessModel::generateMoves(Container& c) {
    bb tmp;
    unsigned int src;
    unsigned int dest;
    bb moves;
    bb tmp_moves;
    register bb blocking;

    bb somebody = blackBB | whiteBB;
    bb nobody = ~somebody;

    c.clear();

    if(currentPlayer==WHITE)
    {
        tmp = whitePawn;
        while(tmp) {
            src = firstBit(tmp);
            tmp &= ~bbFrom(src);
            moves = whitePawnMoves[src]&nobody;
            while(moves)
            {
                dest = firstBit(moves);
                moves &= ~bbFrom(dest);
                c.add({src, dest, PAWN, 0, 0, -2047});
            }

            moves = whitePawnCaptures[src]&(blackBB|blackSpectrum);
            while(moves)
            {
                dest = firstBit(moves);
                moves &= ~bbFrom(dest);
                c.add({src, dest, PAWN, getBlackPiece(bbFrom(dest)), 0, -2047});
            }

            moves = whitePawnMoves2[src]&nobody&(nobody<<8);
            while(moves)
            {
                dest = firstBit(moves);
                moves &= ~bbFrom(dest);
                c.add({src, dest, PAWN, 0, 1, -2047});
            }
        }

        tmp = whiteKnight;
        while(tmp) {
            src = firstBit(tmp);
            tmp &= ~bbFrom(src);
            moves = knightMoves[src]&~whiteBB;
            while(moves)
            {
                dest = firstBit(moves);
                moves &= ~bbFrom(dest);
                c.add({src, dest, KNIGHT, getBlackPiece(bbFrom(dest)), 0, -2047});
            }
        }

        tmp = whiteRook | whiteQueen;
        while(tmp) {
            src = firstBit(tmp);
            tmp &= ~bbFrom(src);

            moves = 0;

            tmp_moves = u[src];
            blocking = u[src]&whiteBB;
            if(blocking) tmp_moves &= d[lastBit(blocking)];
            blocking = tmp_moves&blackBB;
            if(blocking) tmp_moves &= ~u[lastBit(blocking)];
            moves |= tmp_moves;

            tmp_moves = d[src];
            blocking = d[src]&whiteBB;
            if(blocking) tmp_moves &= u[firstBit(blocking)];
            blocking = tmp_moves&blackBB;
            if(blocking) tmp_moves &= ~d[firstBit(blocking)];
            moves |= tmp_moves;

            tmp_moves = l[src];
            blocking = l[src]&whiteBB;
            if(blocking) tmp_moves &= r[lastBit(blocking)];
            blocking = tmp_moves&blackBB;
            if(blocking) tmp_moves &= ~l[lastBit(blocking)];
            moves |= tmp_moves;

            tmp_moves = r[src];
            blocking = r[src]&whiteBB;
            if(blocking) tmp_moves &= l[firstBit(blocking)];
            blocking = tmp_moves&blackBB;
            if(blocking) tmp_moves &= ~r[firstBit(blocking)];
            moves |= tmp_moves;

            while(moves) {
                dest = firstBit(moves);
                c.add({src, dest, getWhitePiece(bbFrom(src)), (bbFrom(dest)&blackBB)?getBlackPiece(bbFrom(dest)):0, whiteCastling, -2047});
                moves &= ~bbFrom(dest);
            }
        }

        tmp = whiteBishop | whiteQueen;
        while(tmp) {
            src = firstBit(tmp);
            tmp &= ~bbFrom(src);

            moves = 0;

            tmp_moves = ul[src];
            blocking = ul[src]&whiteBB;
            if(blocking) tmp_moves &= dr[lastBit(blocking)];
            blocking = tmp_moves&blackBB;
            if(blocking) tmp_moves &= ~ul[lastBit(blocking)];
            moves |= tmp_moves;

            tmp_moves = dl[src];
            blocking = dl[src]&whiteBB;
            if(blocking) tmp_moves &= ur[firstBit(blocking)];
            blocking = tmp_moves&blackBB;
            if(blocking) tmp_moves &= ~dl[firstBit(blocking)];
            moves |= tmp_moves;

            tmp_moves = ur[src];
            blocking = ur[src]&whiteBB;
            if(blocking) tmp_moves &= dl[lastBit(blocking)];
            blocking = tmp_moves&blackBB;
            if(blocking) tmp_moves &= ~ur[lastBit(blocking)];
            moves |= tmp_moves;

            tmp_moves = dr[src];
            blocking = dr[src]&whiteBB;
            if(blocking) tmp_moves &= ul[firstBit(blocking)];
            blocking = tmp_moves&blackBB;
            if(blocking) tmp_moves &= ~dr[firstBit(blocking)];
            moves |= tmp_moves;

            while(moves) {
                dest = firstBit(moves);
                c.add({src, dest, getWhitePiece(bbFrom(src)), (bbFrom(dest)&blackBB)?getBlackPiece(bbFrom(dest)):0, 0, -2047});
                moves &= ~bbFrom(dest);
            }
        }

        src = firstBit(whiteKing);
        moves = kingMoves[src]&~whiteBB;
        while(moves) {
            dest = firstBit(moves);
            moves &= ~bbFrom(dest);
            c.add({src, dest, KING, getBlackPiece(bbFrom(dest)), whiteCastling, -2047});
        }
        if(whiteCastling) {
            if((whiteCastling&QUEEN_CASTLING)&&(whiteRook&0x0000000000000080)&&!((0x0000000000000070&somebody)|(0x0000000000000038&blackControlled))) {
                c.add({E1, C1, KING, 0, whiteCastling, -2047});
            }
            if((whiteCastling&KING_CASTLING)&&(whiteRook&0x0000000000000001)&&!((0x0000000000000006&somebody)|(0x000000000000000E&blackControlled))) {
                c.add({E1, G1, KING, 0, whiteCastling, -2047});
            }
        }
    }
    else
    {
        tmp = blackPawn;
        while(tmp) {
            src = firstBit(tmp);
            tmp &= ~bbFrom(src);
            moves = blackPawnMoves[src]&nobody;
            while(moves)
            {
                dest = firstBit(moves);
                moves &= ~bbFrom(dest);
                c.add({src, dest, PAWN, 0, 0, -2047});
            }
            moves = blackPawnCaptures[src]&(whiteBB|whiteSpectrum);
            while(moves)
            {
                dest = firstBit(moves);
                moves &= ~bbFrom(dest);
                c.add({src, dest, PAWN, getWhitePiece(bbFrom(dest)), 0, -2047});
            }
            moves = blackPawnMoves2[src]&nobody&(nobody>>8);
            while(moves)
            {
                dest = firstBit(moves);
                moves &= ~bbFrom(dest);
                c.add({src, dest, PAWN, 0, 1, -2047});
            }
        }

        tmp = blackKnight;
        while(tmp) {
            src = firstBit(tmp);
            tmp &= ~bbFrom(src);
            moves = knightMoves[src]&~blackBB;
            while(moves)
            {
                dest = firstBit(moves);
                c.add({src, dest, KNIGHT, getWhitePiece(bbFrom(dest)), 0, -2047});
                moves &= ~bbFrom(dest);
            }
        }

        tmp = blackRook | blackQueen;
        while(tmp) {
            src = firstBit(tmp);
            tmp &= ~bbFrom(src);

            moves = 0;

            tmp_moves = u[src];
            blocking = u[src]&blackBB;
            if(blocking) tmp_moves &= d[lastBit(blocking)];
            blocking = tmp_moves&whiteBB;
            if(blocking) tmp_moves &= ~u[lastBit(blocking)];
            moves |= tmp_moves;

            tmp_moves = d[src];
            blocking = d[src]&blackBB;
            if(blocking) tmp_moves &= u[firstBit(blocking)];
            blocking = tmp_moves&whiteBB;
            if(blocking) tmp_moves &= ~d[firstBit(blocking)];
            moves |= tmp_moves;

            tmp_moves = l[src];
            blocking = l[src]&blackBB;
            if(blocking) tmp_moves &= r[lastBit(blocking)];
            blocking = tmp_moves&whiteBB;
            if(blocking) tmp_moves &= ~l[lastBit(blocking)];
            moves |= tmp_moves;

            tmp_moves = r[src];
            blocking = r[src]&blackBB;
            if(blocking) tmp_moves &= l[firstBit(blocking)];
            blocking = tmp_moves&whiteBB;
            if(blocking) tmp_moves &= ~r[firstBit(blocking)];
            moves |= tmp_moves;

            while(moves) {
                dest = firstBit(moves);
                c.add({src, dest, getBlackPiece(bbFrom(src)), (bbFrom(dest)&whiteBB)?getWhitePiece(bbFrom(dest)):0, blackCastling, -2047});
                moves &= ~bbFrom(dest);
            }
        }

        tmp = blackBishop | blackQueen;
        while(tmp) {
            src = firstBit(tmp);
            tmp &= ~bbFrom(src);

            moves = 0;

            tmp_moves = ul[src];
            blocking = ul[src]&blackBB;
            if(blocking) tmp_moves &= dr[lastBit(blocking)];
            blocking = tmp_moves&whiteBB;
            if(blocking) tmp_moves &= ~ul[lastBit(blocking)];
            moves |= tmp_moves;

            tmp_moves = dl[src];
            blocking = dl[src]&blackBB;
            if(blocking) tmp_moves &= ur[firstBit(blocking)];
            blocking = tmp_moves&whiteBB;
            if(blocking) tmp_moves &= ~dl[firstBit(blocking)];
            moves |= tmp_moves;

            tmp_moves = ur[src];
            blocking = ur[src]&blackBB;
            if(blocking) tmp_moves &= dl[lastBit(blocking)];
            blocking = tmp_moves&whiteBB;
            if(blocking) tmp_moves &= ~ur[lastBit(blocking)];
            moves |= tmp_moves;

            tmp_moves = dr[src];
            blocking = dr[src]&blackBB;
            if(blocking) tmp_moves &= ul[firstBit(blocking)];
            blocking = tmp_moves&whiteBB;
            if(blocking) tmp_moves &= ~dr[firstBit(blocking)];
            moves |= tmp_moves;

            while(moves) {
                dest = firstBit(moves);
                moves &= ~bbFrom(dest);
                c.add({src, dest, getBlackPiece(bbFrom(src)), (bbFrom(dest)&whiteBB)?getWhitePiece(bbFrom(dest)):0, 0, -2047});
            }
        }

        src = firstBit(blackKing);
        moves = kingMoves[src]&~blackBB;
        while(moves) {
            dest = firstBit(moves);
            moves &= ~bbFrom(dest);
            c.add({src, dest, KING, getWhitePiece(bbFrom(dest)), blackCastling, -2047});
        }

        if(blackCastling) {
            if((blackCastling&QUEEN_CASTLING)&&(blackRook&0x8000000000000000)&&!((0x7000000000000000&somebody)|(0x3800000000000000&whiteControlled))) {
                c.add({E8, C8, KING, 0, blackCastling, -2047});
            }
            if((blackCastling&KING_CASTLING)&&(blackRook&0x0100000000000000)&&!((0x0600000000000000&somebody)|(0x0E00000000000000&whiteControlled))) {
                c.add({E8, G8, KING, 0, blackCastling, -2047});
            }
        }
    }
}

void ChessModel::refreshControlledBB() {
    bb tmpBB;
    unsigned int tmp;
    register bb tmpMoves;
    register bb blocking;

    whiteControlled = 0;
    blackControlled = 0;

    register bb someone = whiteBB | blackBB;


    tmpBB = whitePawn;
    while(tmpBB) {
        tmp = firstBit(tmpBB);
        tmpBB &= ~bbFrom(tmp);

        whiteControlled |= whitePawnCaptures[tmp];
    }

    tmpBB = whiteKnight;
    while(tmpBB) {
        tmp = firstBit(tmpBB);
        tmpBB &= ~bbFrom(tmp);

        whiteControlled |= knightMoves[tmp];
    }


    tmpBB = whiteKing;
    tmp = firstBit(tmpBB);
    whiteControlled |= kingMoves[tmp];

    tmpBB = whiteRook | whiteQueen;
    while(tmpBB) {
        tmp = firstBit(tmpBB);
        tmpBB &= ~bbFrom(tmp);

        tmpMoves = u[tmp];
        blocking = tmpMoves&someone;
        if(blocking) tmpMoves &= ~u[lastBit(blocking)];
        whiteControlled |= tmpMoves;

        tmpMoves = d[tmp];
        blocking = tmpMoves&someone;
        if(blocking) tmpMoves &= ~d[firstBit(blocking)];
        whiteControlled |= tmpMoves;

        tmpMoves = l[tmp];
        blocking = tmpMoves&someone;
        if(blocking) tmpMoves &= ~l[lastBit(blocking)];
        whiteControlled |= tmpMoves;

        tmpMoves = r[tmp];
        blocking = tmpMoves&someone;
        if(blocking) tmpMoves &= ~r[firstBit(blocking)];
        whiteControlled |= tmpMoves;
    }

    tmpBB = whiteBishop | whiteQueen;
    while(tmpBB) {
        tmp = firstBit(tmpBB);
        tmpBB &= ~bbFrom(tmp);

        tmpMoves = ul[tmp];
        blocking = tmpMoves&someone;
        if(blocking) tmpMoves &= ~ul[lastBit(blocking)];
        whiteControlled |= tmpMoves;

        tmpMoves = dr[tmp];
        blocking = tmpMoves&someone;
        if(blocking) tmpMoves &= ~dr[firstBit(blocking)];
        whiteControlled |= tmpMoves;

        tmpMoves = dl[tmp];
        blocking = tmpMoves&someone;
        if(blocking) tmpMoves &= ~dl[firstBit(blocking)];
        whiteControlled |= tmpMoves;

        tmpMoves = ur[tmp];
        blocking = tmpMoves&someone;
        if(blocking) tmpMoves &= ~ur[lastBit(blocking)];
        whiteControlled |= tmpMoves;
    }






    tmpBB = blackPawn;
    while(tmpBB) {
        tmp = firstBit(tmpBB);
        tmpBB &= ~bbFrom(tmp);

        blackControlled |= blackPawnCaptures[tmp];
    }

    tmpBB = blackKnight;
    while(tmpBB) {
        tmp = firstBit(tmpBB);
        tmpBB &= ~bbFrom(tmp);

        blackControlled |= knightMoves[tmp];
    }

    tmpBB = blackKing;
    tmp = firstBit(tmpBB);
    blackControlled |= kingMoves[tmp];

    tmpBB = blackRook | blackQueen;
    while(tmpBB) {
        tmp = firstBit(tmpBB);
        tmpBB &= ~bbFrom(tmp);

        tmpMoves = u[tmp];
        blocking = tmpMoves&someone;
        if(blocking) tmpMoves &= ~u[lastBit(blocking)];
        blackControlled |= tmpMoves;

        tmpMoves = d[tmp];
        blocking = tmpMoves&someone;
        if(blocking) tmpMoves &= ~d[firstBit(blocking)];
        blackControlled |= tmpMoves;

        tmpMoves = l[tmp];
        blocking = tmpMoves&someone;
        if(blocking) tmpMoves &= ~l[lastBit(blocking)];
        blackControlled |= tmpMoves;

        tmpMoves = r[tmp];
        blocking = tmpMoves&someone;
        if(blocking) tmpMoves &= ~r[firstBit(blocking)];
        blackControlled |= tmpMoves;
    }

    tmpBB = blackBishop | blackQueen;
    while(tmpBB) {
        tmp = firstBit(tmpBB);
        tmpBB &= ~bbFrom(tmp);

        tmpMoves = ul[tmp];
        blocking = tmpMoves&someone;
        if(blocking) tmpMoves &= ~ul[lastBit(blocking)];
        blackControlled |= tmpMoves;

        tmpMoves = dr[tmp];
        blocking = tmpMoves&someone;
        if(blocking) tmpMoves &= ~dr[firstBit(blocking)];
        blackControlled |= tmpMoves;

        tmpMoves = dl[tmp];
        blocking = tmpMoves&someone;
        if(blocking) tmpMoves &= ~dl[firstBit(blocking)];
        blackControlled |= tmpMoves;

        tmpMoves = ur[tmp];
        blocking = tmpMoves&someone;
        if(blocking) tmpMoves &= ~ur[lastBit(blocking)];
        blackControlled |= tmpMoves;
    }
}

void ChessModel::tryMove(int src, int dest) {
    Move* move = searchMove(src, dest);
    if(move!=NULL) validateMove(*move);
}

void ChessModel::playMove(Move p_m) {
    pieces[(int)-currentPlayer*p_m.capturedPiece] &= ~bbFrom(p_m.dest);
    pieces[(int)currentPlayer*p_m.piece] ^= bbFrom(p_m.src)|bbFrom(p_m.dest);
    pieces[SPECTRUM] = 0;
    pieces[B_SPECTRUM] = 0;

    if(p_m.piece == PAWN) {
        if(p_m.special) {
            pieces[(int)currentPlayer*SPECTRUM] = bbFrom((p_m.dest+p_m.src)/2);
        }
        else {
            if(bbFrom(p_m.dest)&(r1|r8)) {
                pieces[(int)currentPlayer*PAWN] ^= bbFrom(p_m.dest);
                pieces[(int)currentPlayer*QUEEN] ^= bbFrom(p_m.dest);
            }
            else if(p_m.capturedPiece == SPECTRUM) {
                if(currentPlayer == WHITE) {
                    pieces[B_PAWN] &= ~(bbFrom(p_m.dest) >> 8);
                }
                else {
                    pieces[PAWN] &= ~(bbFrom(p_m.dest) << 8);
                }
            }
        }
    }

    if(currentPlayer==WHITE)
    {
        if(p_m.piece == KING) {
            if(p_m.src == E1 && p_m.dest == G1) {
                whiteRook ^= 0x0000000000000005;
            } else if(p_m.src == E1 && p_m.dest == C1) {
                whiteRook ^= 0x0000000000000090;
            }
            whiteCastling = 0;
        } else if(p_m.piece == ROOK) {
            if(p_m.src == A1 || p_m.dest == A1) whiteCastling &= ~QUEEN_CASTLING;
            else if(p_m.src == H1 || p_m.dest == H1) whiteCastling &= ~KING_CASTLING;
        }
    }
    else
    {
        if(p_m.piece == KING) {
            if(p_m.src == E8 && p_m.dest == G8) {
                blackRook ^= 0x0500000000000000;
            } else if(p_m.src == E8 && p_m.dest == C8) {
                blackRook ^= 0x9000000000000000;
            }
            blackCastling = 0;
        } else if(p_m.piece == ROOK) {
            if(p_m.src == A8 || p_m.dest == A8) blackCastling &= ~QUEEN_CASTLING;
            else if(p_m.src == H8 || p_m.dest == H8) blackCastling &= ~KING_CASTLING;
        }
    }

    whiteBB = whiteBishop | whiteKing | whiteKnight | whitePawn | whiteQueen | whiteRook;
    blackBB = blackBishop | blackKing | blackKnight | blackPawn | blackQueen | blackRook;

    currentPlayer = -currentPlayer;
}

void ChessModel::validateMove(Move p_m)
{
    playMove(p_m);
    pastMoves.push_back(p_m);

    refreshControlledBB();
    generateMoves(possibleMoves);
    checkAllMoves();
}

void ChessModel::checkAllMoves()
{
    std::deque< std::deque<Move>::iterator > toBeRemoved;

    for(std::deque<Move>::iterator it=possibleMoves.begin(); it!= possibleMoves.end(); ++it)
    {
        playMove(*it);
        refreshControlledBB();

        if(currentPlayer == WHITE) {
            if(blackKing & whiteControlled) {
                toBeRemoved.push_back(it);
            }
        } else {
            if(whiteKing & blackControlled) {
                toBeRemoved.push_back(it);
            }
        }

        cancelMove(*it);
        refreshControlledBB();
    }

    for(std::deque< std::deque<Move>::iterator >::iterator it = toBeRemoved.begin(); it!=toBeRemoved.end(); ++it) {
        possibleMoves.erase(*it);
    }
}

void ChessModel::cancelMove(Move p_m) {
    currentPlayer = -currentPlayer;

    pieces[(int)-currentPlayer*p_m.capturedPiece] |= bbFrom(p_m.dest);
    pieces[(int)currentPlayer*p_m.piece] ^= bbFrom(p_m.src)|bbFrom(p_m.dest);
    pieces[SPECTRUM] = 0;
    pieces[B_SPECTRUM] = 0;

    if(!pastMoves.empty()) {
        if(pastMoves.back().piece == PAWN && pastMoves.back().special) {
            pieces[(int)-currentPlayer*SPECTRUM] = bbFrom((pastMoves.back().src+pastMoves.back().dest)/2);
        }
    }

    if(p_m.piece == PAWN) {
        if(bbFrom(p_m.dest)&(r1|r8)) {
            pieces[(int)currentPlayer*PAWN] ^= bbFrom(p_m.dest);
            pieces[(int)currentPlayer*QUEEN] ^= bbFrom(p_m.dest);
        }
        else if(p_m.capturedPiece == SPECTRUM) {
            if(currentPlayer == WHITE) {
                pieces[B_PAWN] |= bbFrom(p_m.dest) >> 8;
            }
            else {
                pieces[PAWN] |= bbFrom(p_m.dest) << 8;
            }
        }
    }
    else if(p_m.piece == KING) {
        if(currentPlayer == WHITE) {
            if(p_m.src == E1 && p_m.dest == G1) {
                whiteRook ^= 0x0000000000000005;
            } else if(p_m.src == E1 && p_m.dest == C1) {
                whiteRook ^= 0x0000000000000090;
            }
            whiteCastling = p_m.special;
        } else {
            if(p_m.src == E8 && p_m.dest == G8) {
                blackRook ^= 0x0500000000000000;
            } else if(p_m.src == E8 && p_m.dest == C8) {
                blackRook ^= 0x9000000000000000;
            }
            blackCastling = p_m.special;
        }
    } else if(p_m.piece == ROOK) {
        if(currentPlayer == WHITE) {
            whiteCastling = p_m.special;
        } else {
            blackCastling = p_m.special;
        }
    }

    whiteBB = whiteBishop | whiteKing | whiteKnight | whitePawn | whiteQueen | whiteRook;
    blackBB = blackBishop | blackKing | blackKnight | blackPawn | blackQueen | blackRook;
}

void ChessModel::cancelLastMove() {

    if(!pastMoves.empty())
    {
        Move p_m = pastMoves.back();
        pastMoves.pop_back();

        cancelMove(p_m);

        refreshControlledBB();
        generateMoves(possibleMoves);
        checkAllMoves();
    }
}

Piece ChessModel::getPiece(int x, int y) {
    bb b = bbFrom(x+y*8);
    if(b & whiteBB) {
        if(b&whitePawn) return PAWN;
        if(b&whiteBishop) return BISHOP;
        if(b&whiteKnight) return KNIGHT;
        if(b&whiteRook) return ROOK;
        if(b&whiteQueen) return QUEEN;
        if(b&whiteKing) return KING;

    }
    else if(b & blackBB) {
        if(b&blackPawn) return B_PAWN;
        if(b&blackBishop) return B_BISHOP;
        if(b&blackKnight) return B_KNIGHT;
        if(b&blackRook) return B_ROOK;
        if(b&blackQueen) return B_QUEEN;
        if(b&blackKing) return B_KING;
    }

    if(b&whiteSpectrum) return SPECTRUM;
    if(b&blackSpectrum) return B_SPECTRUM;
    return NONE;
}

Move* ChessModel::searchMove(int src, int dest)
{
    for(std::deque<Move>::iterator it=possibleMoves.begin(); it!= possibleMoves.end(); ++it)
    {
        if(it->src == src && it->dest == dest) {
            return &(*it);
        }
    }
    return NULL;
}
