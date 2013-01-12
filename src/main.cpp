#include <SFML/Graphics.hpp>
#include <iostream>

#include "ChessModel.h"
#include "ChessView.h"
#include "AIPlayer.h"
#include "HumanPlayer.h"
#include "RandomAIPlayer.h"

int main(int argc, char** argv)
{
    sf::RenderWindow window(sf::VideoMode(800,600), "Chess", sf::Style::Close);

    ChessModel chessModel;

    HumanPlayer player(WHITE, chessModel);
    AIPlayer player2(BLACK, chessModel, 4);

    ChessView chessView(chessModel, player, player2);

    while(window.isOpen()) {
        sf::Event event;

        if(chessModel.getCurrentPlayer()==WHITE) player.run();
        else player2.run();

        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }

            if(event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i position = sf::Mouse::getPosition(window);
                sf::Vector2i coords = chessView.getCoords(position);
                player.select(coords.x, coords.y);
                player2.select(coords.x, coords.y);
            }

            if(event.type == sf::Event::KeyPressed && event.key.code==sf::Keyboard::Z) {
                chessModel.cancelLastMove();
                chessModel.cancelLastMove();
            }
        }

        window.clear(sf::Color(255,255,128));
        chessView.draw(window);
        window.display();
    }
}
