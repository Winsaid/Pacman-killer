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
    int botsCount = 0;

    Level levelZeroBin(ZERO_LEVEL, sf::Vector2f(MAP_LEVEL_ZERO_HEIGHT, MAP_LEVEL_ZERO_WIDTH), sf::Vector2f(MAP_START_LEVEL_ZERO_X, MAP_START_LEVEL_ZERO_Y));
    Level levelZero(ZERO_LEVEL_S, sf::Vector2f(MAP_LEVEL_ZERO_HEIGHT, MAP_LEVEL_ZERO_WIDTH), sf::Vector2f(MAP_START_LEVEL_ZERO_X, MAP_START_LEVEL_ZERO_Y));

    Level levelTwoBin(LEVEL_TWO, sf::Vector2f(MAP_LEVEL_TWO_HEIGHT, MAP_LEVEL_TWO_WIDTH), sf::Vector2f(MAP_START_LEVEL_TWO_X, MAP_START_LEVEL_TWO_Y));
    Level levelTwo(LEVEL_TWO_S, sf::Vector2f(MAP_LEVEL_TWO_HEIGHT, MAP_LEVEL_TWO_WIDTH), sf::Vector2f(MAP_START_LEVEL_TWO_X, MAP_START_LEVEL_TWO_Y));

    Map map(levelZeroBin, levelZero, sf::Vector2f(LEVEL_ZERO_BOT_START_X, LEVEL_ZERO_BOT_START_Y), sf::Vector2f(LEVEL_ZERO_PLAEYR_START_X, LEVEL_ZERO_PLAEYR_START_Y));
    Player* firstPlayer = new Player(textures::playerTexture, map.getPlayerPosition(), 1);
    Player* secondPlayer = new Player(textures::playerTexture, map.getSecondPlayerPosition(), 2);
    Scale scale = getScale(map.getPoints().size());
    std::vector<Bot> bots;

    sf::Font font;
    if (!font.loadFromFile("../../../../fonts/Joystix.TTF")) {
        throw std::runtime_error("Failed to load font");
    }

    sf::Text end;
    end.setCharacterSize(30);
    end.setFont(font);
    end.setPosition(sf::Vector2f(900.f, 50.f));

    sf::Sprite health;
    health.setTexture(textures::playerTexture);
    health.setTextureRect(sf::IntRect(16, 16, 16, 16));
    health.setScale(2, 2);
    health.setPosition(sf::Vector2f(700.f, 50.f));

    std::vector<sf::Sprite> healths;
    for (int index = 0; index < firstPlayer->getHP(); ++index) {
        healths.push_back(health);
        health.setPosition(sf::Vector2f(health.getPosition().x + 48, health.getPosition().y));
    }

    sf::Sprite secondHealth;
    secondHealth.setTexture(textures::playerTexture);
    secondHealth.setTextureRect(sf::IntRect(144, 96, 16, 16));
    secondHealth.setScale(2, 2);
    secondHealth.setPosition(sf::Vector2f(700.f, 90.f));

    std::vector<sf::Sprite> secondHealths;
    for (int index = 0; index < secondPlayer->getHP(); ++index) {
        secondHealths.push_back(secondHealth);
        secondHealth.setPosition(sf::Vector2f(secondHealth.getPosition().x + 48, secondHealth.getPosition().y));
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
    bool isFirst = true;
    bool haveTwoPlayer;

    while (window.isOpen()) {
        float timeForMove = clockForMove.getElapsedTime().asMicroseconds();
        float timeForPlrSprt = clockForPlrSprt.getElapsedTime().asSeconds();
        std::vector<float> timesForChBotDir;

        if (timesForChBotDir.size() == 0)
            for (int i = 0; i < bots.size(); ++i)
                timesForChBotDir.push_back(0);

        for (int i = 0; i < bots.size(); ++i) {
            timesForChBotDir[i] = clockForBots[i].getElapsedTime().asSeconds();
        }

        sf::IntRect lastTextureRect = firstPlayer->getSprite().getTextureRect();
        std::vector<Direction> lastBotDirections;

        for (int i = 0; i < currentBots && i < bots.size(); ++i) {
            lastBotDirections.push_back(bots[i].getDirection());
        }

        actualPointCount = map.getPoints().size();
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
            gameState = GameState::Play;
            break;

        case GameState::ReduceBot:
            playWindow.reduceCountBots();
            window.draw(playWindow);
            openWindow = playWindow;
            gameState = GameState::Play;
            break;

        case GameState::StartGame:
            haveTwoPlayer = true;
            botsCount = TextToInt(openWindow.getButtons()[6].getContent());            

            if (!haveTwoPlayer) {
                if (isFirst == true) {
                    if (TextToInt(openWindow.getButtons()[2].getContent()) == 0) {
                        Map map(levelZeroBin, levelZero, sf::Vector2f(LEVEL_ZERO_BOT_START_X, LEVEL_ZERO_BOT_START_Y), sf::Vector2f(LEVEL_ZERO_PLAEYR_START_X, LEVEL_ZERO_PLAEYR_START_Y));
                        isFirst = false;
                    }
                    else if (TextToInt(openWindow.getButtons()[2].getContent()) == 1) {
                        Map map(levelZeroBin, levelZero, sf::Vector2f(LEVEL_ZERO_BOT_START_X, LEVEL_ZERO_BOT_START_Y), sf::Vector2f(LEVEL_ZERO_PLAEYR_START_X, LEVEL_ZERO_PLAEYR_START_Y));
                        isFirst = false;
                    }
                    else if (TextToInt(openWindow.getButtons()[2].getContent()) == 2) {
                        Map map2(levelTwoBin, levelTwo, sf::Vector2f(LEVEL_TWO_BOT_START_X, LEVEL_TWO_BOT_START_Y), sf::Vector2f(LEVEL_TWO_PLAEYR_START_X, LEVEL_TWO_PLAEYR_START_Y));
                        map = map2;
                        isFirst = false;
                    }

                    if (bots.size() == 0)
                        bots = createBots(botsCount, map.getBotPosition());

                    for (int i = 0; i < currentBots; ++i) {
                        bots[i].setPosition(map.getBotPosition());
                    }

                    pointCount = map.getPoints().size();
                    scale = getScale(map.getPoints().size());
                    firstPlayer->setPosition(map.getPlayerPosition());
                }

                if (clockForBots.size() == 0)
                    for (int i = 0; i < bots.size(); ++i) {
                        clockForBots.push_back(sf::Clock());
                        clockForStartBots.push_back(sf::Clock());
                    }


                if (doStartGame) {
                    if (pointCount != actualPointCount) {
                        pointCount = actualPointCount;
                        scale.addCollectedPoint();
                    }

                    if (!scale.isAllPointCollected() && firstPlayer->getHP() > 0) {
                        firstPlayer->Update(map, timeForMove, timeForPlrSprt);

                        for (int i = 0; i < currentBots; ++i)
                            if (clockForStartBots[i].getElapsedTime().asSeconds() > 3)
                                bots[i].Update(map, timeForMove, timesForChBotDir[i]);
                    }

                    if (lastTextureRect != firstPlayer->getSprite().getTextureRect())
                        clockForPlrSprt.restart();

                    for (int i = 0; i < currentBots; ++i)
                        if (lastBotDirections[i] != bots[i].getDirection())
                            clockForBots[i].restart();
                }
                else {
                    if (clockForStartGame.getElapsedTime().asSeconds() > 2) {
                        clockForAddBot.restart();
                        doStartGame = true;
                    }
                }

                if (firstPlayer->getMode() && firstPlayer->getTime() > 15)
                    firstPlayer->unsetMadMode();

                window.clear(sf::Color::Black);
                window.draw(map);
                window.draw(scale);

                if (scale.isAllPointCollected()) {
                    end.setString("You win!");
                    end.setFillColor(sf::Color::Cyan);
                    window.draw(end);
                }


                for (int i = 0; i < currentBots; ++i) {
                    if (bots[i].catchPlayer(firstPlayer) && firstPlayer->getHP() != 0) {
                        if (firstPlayer->getMode()) {
                            bots[i].setPosition(map.getBotPosition());
                            bots[i].setDirection(Direction::LEFT);
                            clockForStartBots[i].restart();
                        }
                        else if (firstPlayer->getHP() > 0) {
                            firstPlayer->takeDamage(1);
                            firstPlayer->setPosition(map.getPlayerPosition());
                            firstPlayer->setDirection(Direction::LEFT);
                            for (int j = 0; j < currentBots; ++j) {
                                bots[j].setPosition(map.getBotPosition());
                            }
                            currentBots = 1;
                            healths.pop_back();
                            doStartGame = false;
                            clockForStartGame.restart();
                            clockForAddBot.restart();
                        }
                    }
                }

                window.draw(firstPlayer->getSprite());

                for (int i = 0; i < currentBots; ++i)
                    window.draw(bots[i].getSprite());


                if (firstPlayer->getHP() != 0) {
                    for (const sf::Sprite& currentHealth : healths) {
                        window.draw(currentHealth);
                    }
                }


                if (firstPlayer->getHP() == 0) {
                    end.setString("You lose!");
                    end.setFillColor(sf::Color::Red);
                    window.draw(end);
                }
            }
            else {
                if (isFirst == true) {
                    if (TextToInt(openWindow.getButtons()[2].getContent()) == 0) {
                        Map map1(levelZeroBin, levelZero, sf::Vector2f(LEVEL_ZERO_BOT_START_X, LEVEL_ZERO_BOT_START_Y), sf::Vector2f(LEVEL_ZERO_PLAEYR_START_X, LEVEL_ZERO_PLAEYR_START_Y), sf::Vector2f(LEVEL_ZERO_PLAEYR_SECOND_START_X, LEVEL_ZERO_PLAEYR_SECOND_START_Y));
                        isFirst = false;
                        map = map1;
                    }
                    else if (TextToInt(openWindow.getButtons()[2].getContent()) == 1) {
                        Map map1(levelZeroBin, levelZero, sf::Vector2f(LEVEL_ZERO_BOT_START_X, LEVEL_ZERO_BOT_START_Y), sf::Vector2f(LEVEL_ZERO_PLAEYR_START_X, LEVEL_ZERO_PLAEYR_START_Y), sf::Vector2f(LEVEL_ZERO_PLAEYR_SECOND_START_X, LEVEL_ZERO_PLAEYR_SECOND_START_Y));
                        map = map1;
                        isFirst = false;
                    }
                    else if (TextToInt(openWindow.getButtons()[2].getContent()) == 2) {
                        Map map2(levelTwoBin, levelTwo, sf::Vector2f(LEVEL_TWO_BOT_START_X, LEVEL_TWO_BOT_START_Y), sf::Vector2f(LEVEL_TWO_PLAEYR_START_X, LEVEL_TWO_PLAEYR_START_Y), sf::Vector2f(LEVEL_TWO_PLAEYR_SECOND_START_X, LEVEL_TWO_PLAEYR_SECOND_START_Y));
                        map = map2;
                        isFirst = false;
                    }

                    if (bots.size() == 0)
                        bots = createBots(botsCount, map.getBotPosition());

                    for (int i = 0; i < currentBots; ++i) {
                        bots[i].setPosition(map.getBotPosition());
                    }

                    pointCount = map.getPoints().size();
                    scale = getScale(map.getPoints().size());
                    firstPlayer->setPosition(map.getPlayerPosition());
                    secondPlayer->setPosition(map.getSecondPlayerPosition());
                }

                if (clockForBots.size() == 0)
                    for (int i = 0; i < bots.size(); ++i) {
                        clockForBots.push_back(sf::Clock());
                        clockForStartBots.push_back(sf::Clock());
                    }

                if (doStartGame) {
                    if (pointCount != actualPointCount) {    
                        while (pointCount > actualPointCount) {
                            scale.addCollectedPoint();
                            --pointCount;
                        }
                    }

                    if (!scale.isAllPointCollected() && firstPlayer->getHP() > 0) {
                        firstPlayer->Update(map, timeForMove, timeForPlrSprt);
                        secondPlayer->Update(map, timeForMove, timeForPlrSprt);

                        for (int i = 0; i < currentBots; ++i)
                            if (clockForStartBots[i].getElapsedTime().asSeconds() > 3)
                                bots[i].Update(map, timeForMove, timesForChBotDir[i]);
                    }

                    if (lastTextureRect != firstPlayer->getSprite().getTextureRect())
                        clockForPlrSprt.restart();

                    for (int i = 0; i < currentBots; ++i)
                        if (lastBotDirections[i] != bots[i].getDirection())
                            clockForBots[i].restart();
                }
                else {
                    if (clockForStartGame.getElapsedTime().asSeconds() > 2) {
                        clockForAddBot.restart();
                        doStartGame = true;
                    }
                }

                if (firstPlayer->getMode() && firstPlayer->getTime() > 15)
                    firstPlayer->unsetMadMode();

                if (secondPlayer->getMode() && secondPlayer->getTime() > 15)
                    secondPlayer->unsetMadMode();

                window.clear(sf::Color::Black);
                window.draw(map);
                window.draw(scale);

                if (scale.isAllPointCollected()) {
                    end.setString("You win!");
                    end.setFillColor(sf::Color::Cyan);
                    window.draw(end);
                }

                for (int i = 0; i < currentBots; ++i) {
                    if (bots[i].catchPlayer(firstPlayer) && firstPlayer->getHP() != 0) {
                        if (firstPlayer->getMode()) {
                            bots[i].setPosition(map.getBotPosition());
                            bots[i].setDirection(Direction::LEFT);
                            clockForStartBots[i].restart();
                        }
                        else if (firstPlayer->getHP() > 0) {
                            firstPlayer->takeDamage(1);
                            firstPlayer->setPosition(map.getPlayerPosition());
                            secondPlayer->setPosition(map.getSecondPlayerPosition());
                            firstPlayer->setDirection(Direction::LEFT);
                            secondPlayer->setDirection(Direction::LEFT);
                            for (int j = 0; j < currentBots; ++j) {
                                bots[j].setPosition(map.getBotPosition());
                            }
                            currentBots = 1;
                            healths.pop_back();
                            doStartGame = false;
                            clockForStartGame.restart();
                            clockForAddBot.restart();
                        }
                    }
                    if (bots[i].catchPlayer(secondPlayer) && secondPlayer->getHP() != 0) {
                        if (secondPlayer->getMode()) {
                            bots[i].setPosition(map.getBotPosition());
                            bots[i].setDirection(Direction::LEFT);
                            clockForStartBots[i].restart();
                        }
                        else if (secondPlayer->getHP() > 0) {
                            secondPlayer->takeDamage(1);
                            secondPlayer->setPosition(map.getSecondPlayerPosition());
                            firstPlayer->setPosition(map.getPlayerPosition());
                            firstPlayer->setDirection(Direction::LEFT);
                            secondPlayer->setDirection(Direction::LEFT);
                            for (int j = 0; j < currentBots; ++j) {
                                bots[j].setPosition(map.getBotPosition());
                            }
                            currentBots = 1;
                            secondHealths.pop_back();
                            doStartGame = false;
                            clockForStartGame.restart();
                            clockForAddBot.restart();
                        }
                    }
                }

                for (int i = 0; i < currentBots; ++i)
                    window.draw(bots[i].getSprite());


                if (firstPlayer->getHP() != 0) {
                    window.draw(firstPlayer->getSprite());
                    for (const sf::Sprite& currentHealth : healths) {
                        window.draw(currentHealth);
                    }
                }

                if (secondPlayer->getHP() != 0) {
                    window.draw(secondPlayer->getSprite());
                    for (const sf::Sprite& currentHealth : secondHealths) {
                        window.draw(currentHealth);
                    }
                }

                if (firstPlayer->getHP() == 0 && secondPlayer->getHP() == 0) {
                    end.setString("You lose!");
                    end.setFillColor(sf::Color::Red);
                    window.draw(end);
                }
            }
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                gameState = GameState::MainMenu;
                openWindow = mainWindow; 
                isFirst = true;
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
    delete firstPlayer;
    delete secondPlayer;
    return 0;
}
