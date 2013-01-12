#ifndef MOVE_H
#define MOVE_H

struct Move {
    unsigned int src : 6;
    unsigned int dest   : 6;
    unsigned int piece   : 3;
    unsigned int capturedPiece : 3;
    unsigned int special  : 2; // Castlings
    int score : 12;
};

#endif // MOVE_H
