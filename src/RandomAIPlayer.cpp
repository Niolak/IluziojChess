
#include <cstdlib>
#include <ctime>

#include "RandomAIPlayer.h"

RandomAIPlayer::RandomAIPlayer(Player p, ChessModel& p_boardModel) :
    player(p),
    boardModel(p_boardModel)
{
    std::srand(std::time(0));
}

void RandomAIPlayer::run() {
    if(boardModel.getCurrentPlayer() == player)
    {
        std::cout << std::endl << "random player" << std::endl;
        boardModel.checkAllMoves();
        std::cout << boardModel.possibleMoves.getSize() << std::endl;
        for(int i=0; i<boardModel.possibleMoves.getSize(); ++i) {
            std::cout << boardModel.possibleMoves[i].src << " to " << boardModel.possibleMoves[i].dest << std::endl;
        }
        if(boardModel.possibleMoves.getSize()) {int k = std::rand()%boardModel.possibleMoves.getSize();
        std::cout << "choix : " << k << std::endl;
        Move m = boardModel.possibleMoves[k];
        boardModel.validateMove(m);
        }
    }
}

