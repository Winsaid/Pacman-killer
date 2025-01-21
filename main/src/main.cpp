#include "../head/main.h"

int main() {
    GameState gameState = GameState::MainMenu;
    textures::setTextures();

    sf::Clock clockForMove, clockForPlrSprt, clockForChBotDir, clockForStartGame;
    
    Level level(1, 0);
    
    Map map(level);
    Player* player = new Player(textures::playerTexture, sf::Vector2f(586, 536));
    Scale scale = getScale(map.getPoints().size());
    Bot bot(Blue, textures::playerTexture);
    bot.setPosition(sf::Vector2f(586, 408));

    sf::Font font;
    if (!font.loadFromFile("../../../../fonts/Joystix.TTF")) {
        throw std::runtime_error("Failed to load font");
    }

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
    for (int index = 0; index < player->getHP(); ++index) {
        healths.push_back(health);
        health.setPosition(sf::Vector2f(health.getPosition().x + 48, health.getPosition().y));
    }

    int actualPointCount;
    int pointCount = map.getPoints().size();
    bool doStartGame = false;

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Pacman");

    std::string pathToBackgroundImageForMenu = "../../../../images/background.png";
    std::string pathToBackgroundImageForAuthors = "../../../../images/authors.png";

    sf::Texture backgroundTextureForMenu;
    if (!backgroundTextureForMenu.loadFromFile(pathToBackgroundImageForMenu)) {
        throw std::runtime_error("Failed to load background texture");
    }
    sf::Sprite backgroundSpriteForMenu;
    backgroundSpriteForMenu.setTexture(backgroundTextureForMenu);

    sf::Texture backgroundTextureForAuthors;
    if (!backgroundTextureForAuthors.loadFromFile(pathToBackgroundImageForAuthors)) {
        throw std::runtime_error("Failed to load background texture");
    }
    sf::Sprite backgroundSpriteForAuthors;
    backgroundSpriteForAuthors.setTexture(backgroundTextureForAuthors);

    Window mainWindow = createMainWindow(backgroundSpriteForMenu, font);
    Window optionWindow = createOptionWindow(backgroundSpriteForMenu, font);
    Window authorWindow = createAuthorsWindow(backgroundSpriteForAuthors, font);
    Window playWindow = createPlayWindow(backgroundSpriteForMenu, font);
    Window openWindow = mainWindow;

    while (window.isOpen()) {
        float timeForMove = clockForMove.getElapsedTime().asMicroseconds();
        float timeForPlrSprt = clockForPlrSprt.getElapsedTime().asSeconds();
        float timeForChBotDir = clockForChBotDir.getElapsedTime().asSeconds();

        sf::IntRect lastTextureRect = player->getSprite().getTextureRect();
        Direction lastBotDirection = bot.getDirection();
        clockForMove.restart();
        actualPointCount = map.getPoints().size();

        sf::Event event;
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && gameState != GameState::StartGame) {
                gameState = openWindow.doAction(mousePos);
            }
        }

        switch (gameState) {
        case GameState::Back:
            window.draw(mainWindow);
            openWindow = mainWindow;
            break;

        case GameState::OptionsMenu:
            window.draw(optionWindow);
            openWindow = optionWindow;
            break;

        case GameState::Authors:
            window.draw(authorWindow);
            openWindow = authorWindow;
            break;

        case GameState::Exit:
            window.close();
            break;

        case GameState::Play:
            window.draw(playWindow);
            openWindow = playWindow;
            break;

        case GameState::AddRound:
            playWindow.addCountRounds();
            window.draw(playWindow);
            openWindow = playWindow;
            gameState = GameState::Play;
            break;

        case GameState::ReduceRound:
            playWindow.reduceCountRounds();
            window.draw(playWindow);
            openWindow = playWindow;
            gameState = GameState::Play;
            break;

        case GameState::AddBot:
            playWindow.addCountBots();
            window.draw(playWindow);
            openWindow = playWindow;
            gameState = GameState::Play;
            break;

        case GameState::ReduceBot:
            playWindow.reduceCountBots();
            window.draw(playWindow);
            openWindow = playWindow;
            gameState = GameState::Play;
            break;

        case GameState::StartGame:
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
                if (clockForStartGame.getElapsedTime().asSeconds() > 2)
                    doStartGame = true;
            }

            if (player->getMode() && player->getTime() > 15)
                player->unsetMadMode();

            window.clear(sf::Color::Black);
            window.draw(map);
            window.draw(scale);

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
                    healths.pop_back();
                    doStartGame = false;
                    clockForStartGame.restart();
                }
            }

            
            window.draw(player->getSprite());
            window.draw(bot.getSprite());

            
            if (player->getHP() != 0) {
                for (const sf::Sprite& currentHealth : healths) {
                    window.draw(currentHealth);
                }
            }

            
            if (player->getHP() == 0) {
                end.setString("You lose!");
                end.setFillColor(sf::Color::Red);
                window.draw(end);
            }

            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                gameState = GameState::MainMenu;
                openWindow = mainWindow; 
            }

            break;

        case GameState::MainMenu:
                window.draw(openWindow);
            break;
        }
        window.display();
    }
    delete player;
    return 0;
}
