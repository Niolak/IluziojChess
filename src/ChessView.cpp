#include "ChessView.h"

ChessView::ChessView(AbstractChessModel& p_model, AbstractPlayer& p_whitePlayer, AbstractPlayer& p_blackPlayer) :
    model(p_model),
    whitePlayer(p_whitePlayer),
    blackPlayer(p_blackPlayer) {

    font.loadFromFile("res/decibel.ttf");

    board.loadFromFile("res/board.png");
    pawn.loadFromFile("res/pawn.png");
    rook.loadFromFile("res/rook.png");
    knight.loadFromFile("res/knight.png");
    bishop.loadFromFile("res/bishop.png");
    queen.loadFromFile("res/queen.png");
    king.loadFromFile("res/king.png");
    spectrum.loadFromFile("res/spectrum.png");
}

void ChessView::draw(sf::RenderTarget& p_window) {
    sf::Sprite sprite;
    sprite.setTexture(board);
    sprite.setScale(75., 75);
    p_window.draw(sprite);

    sf::Sprite pieceSprite;
    pieceSprite.setScale(0.5, 0.5);

    for(int x=0; x<8; ++x) {
        for(int y=0; y<8; ++y) {

            /* To see where the current selected piece can go
            if(whitePlayer.selectedCanGo(x,y) || blackPlayer.selectedCanGo(x,y)) {
                sf::RectangleShape rect(sf::Vector2f(75,75));
                rect.setPosition(x*75, y*75);
                rect.setFillColor(sf::Color(255,0,0,128));
                p_window.draw(rect);
            }
            */

            Piece piece = model.getPiece(x,y);
            if(piece != NONE)
            {
                switch(abs(piece)) {
                case PAWN :
                    pieceSprite.setTexture(pawn);
                    break;

                case ROOK :
                    pieceSprite.setTexture(rook);
                    break;

                case KNIGHT :
                    pieceSprite.setTexture(knight);
                    break;

                case BISHOP :
                    pieceSprite.setTexture(bishop);
                    break;

                case QUEEN :
                    pieceSprite.setTexture(queen);
                    break;

                case KING :
                    pieceSprite.setTexture(king);
                    break;

                case SPECTRUM :
                    pieceSprite.setTexture(spectrum);
                    break;
                }

                if(x+y*8 == whitePlayer.getSelected()+blackPlayer.getSelected()+1) {pieceSprite.setColor(sf::Color(255,128,128));}
                else if(piece<0) pieceSprite.setColor(sf::Color(128,128,255));
                else pieceSprite.setColor(sf::Color::White);

                pieceSprite.setPosition(x*75,y*75);
                p_window.draw(pieceSprite);
            }
        }
    }

    sf::Text text("", font, 50);
    text.setPosition(620, 10);
    text.setColor(sf::Color::Black);

    if(model.isBlackCheck()||model.isWhiteCheck()) {
        text.setString("Echec");
        if(model.isMate()) {
            p_window.draw(text);
            text.move(10, 50);
            text.setString("& mat");
        }
    } else if(model.isMate()) {
        text.setString("Pat");
    }
    p_window.draw(text);
}

sf::Vector2i ChessView::getCoords(sf::Vector2i position) {
    position.x /= 75;
    position.y /= 75;
    return position;
}
