#include "../head/main.h"
#include "../head/Constants.h"

std::vector<Bot> createBots(int botsCount, sf::Vector2f position)
{
    std::vector<Bot> bots;

    for (int i = 0; i < botsCount; ++i) {
        bots.push_back(Bot(BotType::Orange, textures::playerTexture));
    }

    for (int i = 0; i < botsCount; ++i) {
        bots[i].setPosition(position);
        bots[i].setDirection(Direction::LEFT);
    }

    return bots;
}

int main() {
    GameState gameState = GameState::MainMenu;
    textures::setTextures();

    sf::Clock clockForMove, clockForPlrSprt, clockForChBotDir, clockForStartGame;
    sf::Clock clockForAddBot;
    std::vector<sf::Clock> clockForBots;
    std::vector<sf::Clock> clockForStartBots;
    int currentBots = 1;

    int levelNumber = 2;
    int botsCount = 0;

    std::vector<std::vector<Level>> levels;

    Level levelZeroBin(ZERO_LEVEL);
    Level levelZero(ZERO_LEVEL_S);

    Level levelTwoBin(LEVEL_TWO);
    Level levelTwo(LEVEL_TWO_S);
    std::vector<Level> levelZeroVec;
    std::vector<Level> levelOneVec;
    std::vector<Level> levelTwoVec;

    levelZeroVec.push_back(levelZeroBin);
    levelZeroVec.push_back(levelZero);

    levelTwoVec.push_back(levelTwoBin);
    levelTwoVec.push_back(levelTwo);

    levels.push_back(levelZeroVec);
    levels.push_back(levelOneVec);
    levels.push_back(levelTwoVec);

    Map map(levels[2]);
    Player* player = new Player(textures::playerTexture, sf::Vector2f(586, 536));
    Scale scale = getScale(map.getPoints().size());
    std::vector<Bot> bots;

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

    std::string pathToBackgroundImageForMenu    = "../../../../images/background.png";
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

    Window mainWindow   = createMainWindow(backgroundSpriteForMenu, font);
    Window optionWindow = createOptionWindow(backgroundSpriteForMenu, font);
    Window authorWindow = createAuthorsWindow(backgroundSpriteForAuthors, font);
    Window playWindow   = createPlayWindow(backgroundSpriteForMenu, font);
    Window openWindow   = mainWindow;

    while (window.isOpen()) {
        float timeForMove     = clockForMove.getElapsedTime().asMicroseconds();
        float timeForPlrSprt  = clockForPlrSprt.getElapsedTime().asSeconds();
        std::vector<float> timesForChBotDir;

        if (timesForChBotDir.size() == 0)
            for (int i = 0; i < bots.size(); ++i)
                timesForChBotDir.push_back(0);

        for (int i = 0; i < bots.size(); ++i) {
            timesForChBotDir[i] = clockForBots[i].getElapsedTime().asSeconds();
        }

        sf::IntRect lastTextureRect = player->getSprite().getTextureRect();
        std::vector<Direction> lastBotDirections;

        for (int i = 0; i < currentBots && i < bots.size(); ++i) {
            lastBotDirections.push_back(bots[i].getDirection());
        }
     
        actualPointCount           = map.getPoints().size();
        clockForMove.restart();

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
            gameState  = GameState::Play;
            break;

        case GameState::ReduceBot:
            playWindow.reduceCountBots();
            window.draw(playWindow);
            openWindow = playWindow;
            gameState  = GameState::Play;
            break;

        case GameState::StartGame:
            botsCount = TextToInt(openWindow.getButtons()[6].getContent());
            
            if (bots.size() == 0)
                bots = createBots(botsCount, sf::Vector2f(586, 408));

            if (clockForBots.size() == 0)
                for (int i = 0; i < bots.size(); ++i) {
                    clockForBots.push_back(sf::Clock());
                    clockForStartBots.push_back(sf::Clock());
                }

            if (doStartGame) {
                if (pointCount != actualPointCount) {
                    pointCount  = actualPointCount;
                    scale.addCollectedPoint();
                }

                if (!scale.isAllPointCollected() && player->getHP() > 0) {
                    player->Update(map, timeForMove, timeForPlrSprt);

                    for (int i = 0; i < currentBots; ++i)
                        if (clockForStartBots[i].getElapsedTime().asSeconds() > 3)
                            bots[i].Update(map, timeForMove, timesForChBotDir[i]);
                }

                if (lastTextureRect != player->getSprite().getTextureRect())
                    clockForPlrSprt.restart();

                for (int i = 0; i < currentBots; ++i)
                    if (lastBotDirections[i] != bots[i].getDirection())
                        clockForBots[i].restart();
            }
            else {
                if (clockForStartGame.getElapsedTime().asSeconds() > 2) {
                    doStartGame = true;
                    clockForAddBot.restart();
                }
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
            
            for (int i = 0; i < currentBots; ++i) {
                if (bots[i].catchPlayer(player) && player->getHP() != 0) {
                    if (player->getMode()) {
                        bots[i].setPosition(sf::Vector2f(586, 408));
                        bots[i].setDirection(Direction::LEFT);
                        clockForStartBots[i].restart();
                    }
                    else if (player->getHP() > 0) {
                        player->takeDamage(1);
                        player->setPosition(sf::Vector2f(586, 536));
                        player->setDirection(Direction::LEFT);
                        for (int j = 0; j < currentBots; ++j) {
                            bots[j].setPosition(sf::Vector2f(586, 408));
                        }
                        currentBots = 1;
                        healths.pop_back();
                        doStartGame = false;
                        clockForStartGame.restart();
                        clockForAddBot.restart();
                    }
                }
            }
            
            window.draw(player->getSprite());
            for (int i = 0; i < currentBots; ++i)
                window.draw(bots[i].getSprite());
            
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

            if (clockForAddBot.getElapsedTime().asSeconds() > 5 && currentBots != bots.size()) {
                ++currentBots;
                clockForAddBot.restart();
                clockForBots[currentBots - 1].restart();
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
