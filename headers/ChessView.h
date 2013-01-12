#ifndef CHESS_VIEW_H
#define CHESS_VIEW_H

#include <SFML/Graphics.hpp>

#include "AbstractChessModel.h"
#include "AbstractPlayer.h"

class ChessView {
public :
    ChessView(AbstractChessModel& p_model, AbstractPlayer& p_whitePlayer, AbstractPlayer& p_blackPlayer);

    void draw(sf::RenderTarget& p_window);

    sf::Vector2i getCoords(sf::Vector2i position);

private :
    AbstractChessModel& model;
    AbstractPlayer& whitePlayer;
    AbstractPlayer& blackPlayer;
    sf::Texture board;
    sf::Texture pawn;
    sf::Texture rook;
    sf::Texture knight;
    sf::Texture bishop;
    sf::Texture queen;
    sf::Texture king;
    sf::Texture spectrum;
    sf::Font font;
};


#endif // CHESS_VIEW_H
