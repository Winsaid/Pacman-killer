#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Textures.h"
#include "Player.h"
#include "Map.h"
#include "Scale.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Title");
    textures::setTextures();

    sf::Clock clockForMove;
    sf::Clock clockForPlrSprt;
    
    //Level zero_level(ZERO_LEVEL);
    //Level level_s(ZERO_LEVEL_S);
    
    Level zero_level(LEVEL_TWO);
    Level level_s(LEVEL_TWO_S);
    
    std::vector<Level> levels;
    levels.push_back(zero_level);
    levels.push_back(level_s);
    
    Map map(levels);
    Player* player = new Player(textures::playerTexture, sf::Vector2f(360, 184), 100);
    Scale scale = getScale(map.getPoints().size());

    sf::Font font;
    font.loadFromFile("./fonts/Joystix.TTF");

    sf::Text end;
    end.setCharacterSize(30);
    end.setFont(font);
    end.setString("You win!");
    end.setFillColor(sf::Color::Green);
    end.setPosition(sf::Vector2f(600.f, 50.f));
    
    int actualPointCount;
    int pointCount = map.getPoints().size();

    while (window.isOpen()) {
        float timeForMove = clockForMove.getElapsedTime().asMicroseconds();
        clockForMove.restart();       
        float timeForPlrSprt = clockForPlrSprt.getElapsedTime().asSeconds();
        sf::IntRect lastTextureRect = player->getSprite().getTextureRect();
        actualPointCount = map.getPoints().size();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();  
            }
        }
    
        if (pointCount != actualPointCount) {
            pointCount = actualPointCount;
            scale.addCollectedPoint();
        }

        if (!scale.isAllPointCollected()) player->Update(map, timeForMove, timeForPlrSprt);

        if (lastTextureRect != player->getSprite().getTextureRect())
            clockForPlrSprt.restart();

        window.clear(sf::Color::Black);
        window.draw(map);
        window.draw(player->getSprite());
        window.draw(scale);
        if (scale.isAllPointCollected()) window.draw(end);
        window.display();
    }

    delete player;
    return 0;
}