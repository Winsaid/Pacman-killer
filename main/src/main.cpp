#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Textures.h"
#include "Player.h"
#include "Map.h"
#include "Scale.h"
#include "Bot.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Title");
    textures::setTextures();

    sf::Clock clockForMove;
    sf::Clock clockForPlrSprt;
    sf::Clock clockForChBotDir;
    sf::Clock clockForStartGame;

    //Level zero_level(ZERO_LEVEL);
    //Level level_s(ZERO_LEVEL_S);
    
    Level zero_level(LEVEL_TWO);
    Level level_s(LEVEL_TWO_S);
    
    std::vector<Level> levels;
    levels.push_back(zero_level);
    levels.push_back(level_s);
   
    Map map(levels);
    Player* player = new Player(textures::playerTexture, sf::Vector2f(586, 536));
    Scale scale    = getScale(map.getPoints().size());
    Bot bot(Blue, textures::playerTexture);
    bot.setPosition(sf::Vector2f(586, 408));

    sf::Font font;
    font.loadFromFile("./fonts/Joystix.TTF");

    sf::Text end;
    end.setCharacterSize(30);
    end.setFont(font);
    end.setPosition(sf::Vector2f(600.f, 50.f));
    
    sf::Sprite health;
    health.setTexture(textures::playerTexture);
    health.setTextureRect(sf::IntRect(16, 16, 16, 16));
    health.setScale(2, 2);
    health.setPosition(sf::Vector2f(400.f, 50.f));

    std::vector<sf::Sprite> healths;
    for (int index = 0; index < player->getHP(); ++index)
    {
        healths.push_back(health);
        health.setPosition(sf::Vector2f(health.getPosition().x + 48, health.getPosition().y));
    }
    
    int actualPointCount;
    int pointCount = map.getPoints().size();
    bool doStartGame = false;

    while (window.isOpen()) {
        float timeForMove           = clockForMove.getElapsedTime().asMicroseconds();  
        float timeForPlrSprt        = clockForPlrSprt.getElapsedTime().asSeconds();
        float timeForChBotDir       = clockForChBotDir.getElapsedTime().asSeconds();
        sf::IntRect lastTextureRect = player->getSprite().getTextureRect();
        Direction lastBotDirection  = bot.getDirection();
        clockForMove.restart();
        actualPointCount = map.getPoints().size();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();  
            }
        }
    
        if (doStartGame) {
            if (pointCount != actualPointCount) {
                pointCount = actualPointCount;
                scale.addCollectedPoint();
            }

            if (!scale.isAllPointCollected() && player->getHP() > 0) {
                player->Update(map, timeForMove, timeForPlrSprt);
                bot.Update(map, timeForMove, timeForChBotDir);
            }

            if (lastTextureRect != player->getSprite().getTextureRect())
                clockForPlrSprt.restart();

            if (lastBotDirection != bot.getDirection())
                clockForChBotDir.restart();
        }
        else {
            float time = clockForStartGame.getElapsedTime().asSeconds();
            if (time > 2)
                doStartGame = true;
        }

        if (player->getMode() == true && player->getTime() > 15)
            player->unsetMadMode();

        window.clear(sf::Color::Black);
        window.draw(map);
        
        if (scale.isAllPointCollected()) {
            end.setString("You win!");
            end.setFillColor(sf::Color::Cyan);
            window.draw(end);
        }

        if (bot.catchPlayer(player) && player->getHP() != 0) {
            if (player->getMode()) {
                bot.setPosition(sf::Vector2f(586, 408));
                bot.setDirection(Direction::LEFT);
            }
            else if (player->getHP() > 0) {
                player->takeDamage(1);
                player->setPosition(sf::Vector2f(586, 536));
                player->setDirection(Direction::LEFT);
                player->getController()->setPressedButton(PressedButton::A);
                player->getSprite().setTextureRect(sf::IntRect(48, 0, -16, 16));
                bot.setPosition(sf::Vector2f(586, 408));
                bot.setDirection(Direction::LEFT);
                healths.pop_back();
                doStartGame = false;
                clockForStartGame.restart();
            }
        }

        window.draw(player->getSprite());
        window.draw(bot.getSprite());
        if (player->getHP() != 0)
            for (sf::Sprite currentHealth : healths) {
                window.draw(currentHealth);
            }

        if (player->getHP() == 0) {
            end.setString("You lose!");
            end.setFillColor(sf::Color::Red);
            window.draw(end);
        }
        window.draw(scale);
        window.display();
    }

    delete player;
    return 0;
}
