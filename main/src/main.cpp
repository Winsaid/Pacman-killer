#include "../head/main.h"
#include "../head/Constants.h"

int main() {
    GameState gameState = GameState::MainMenu;
    textures::setTextures();

    sf::Clock clockForMove, clockForPlrSprt, clockForChBotDir, clockForStartGame;

    Level levelZeroBin(ZERO_LEVEL, sf::Vector2f(MAP_LEVEL_ZERO_HEIGHT, MAP_LEVEL_ZERO_WIDTH), sf::Vector2f(MAP_START_LEVEL_ZERO_X, MAP_START_LEVEL_ZERO_Y));
    Level levelZero(ZERO_LEVEL_S, sf::Vector2f(MAP_LEVEL_ZERO_HEIGHT, MAP_LEVEL_ZERO_WIDTH), sf::Vector2f(MAP_START_LEVEL_ZERO_X, MAP_START_LEVEL_ZERO_Y));

    Level levelTwoBin(LEVEL_TWO, sf::Vector2f(MAP_LEVEL_TWO_HEIGHT, MAP_LEVEL_TWO_WIDTH), sf::Vector2f(MAP_START_LEVEL_TWO_X, MAP_START_LEVEL_TWO_Y));
    Level levelTwo(LEVEL_TWO_S, sf::Vector2f(MAP_LEVEL_TWO_HEIGHT, MAP_LEVEL_TWO_WIDTH), sf::Vector2f(MAP_START_LEVEL_TWO_X, MAP_START_LEVEL_TWO_Y));

    Map map(levelZeroBin, levelZero, sf::Vector2f(LEVEL_ZERO_BOT_START_X, LEVEL_ZERO_BOT_START_Y), sf::Vector2f(LEVEL_ZERO_PLAEYR_START_X, LEVEL_ZERO_PLAEYR_START_Y));
    Player* player = new Player(textures::playerTexture, map.getPlayerPosition());
    Scale scale = getScale(map.getPoints().size());
    Bot bot(Blue, textures::playerTexture);
    bot.setPosition(map.getBotPosition());

    sf::Font font;
    if (!font.loadFromFile("../../../../fonts/Joystix.TTF")) {
        throw std::runtime_error("Failed to load font");
    }
    sf::Font font1;
    if (!font1.loadFromFile("../../../../fonts/graf.ttf")) {
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
    Window authorWindow = createAuthorsWindow(backgroundSpriteForAuthors, font1, font);
    Window playWindow = createPlayWindow(backgroundSpriteForMenu, font);
    Window prompt = createPromptWindow(backgroundSpriteForMenu, font);
    Window openWindow = mainWindow;
    bool isFirst = true;

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
        case GameState::GetColor:
            window.draw(prompt);
            openWindow = prompt;
            break;
        case GameState::SaveColor:
            window.draw(optionWindow);
            openWindow = optionWindow;
            break;

        case GameState::Unselected:
            prompt = selectColors(prompt, mousePos);
            window.draw(prompt);
            openWindow = prompt;
            gameState = GameState::GetColor;
            break;
        case GameState::Hold:
            playWindow = switchMode(playWindow, mousePos);
            window.draw(playWindow);
            openWindow = playWindow;
            break;
        case GameState::Ready:
            window.draw(playWindow);
            openWindow = playWindow;
            break;

        case GameState::Selected:
            window.draw(prompt);
            openWindow = prompt;
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
                if (TextToInt(openWindow.getButtons()[2].getContent()) == 0 && isFirst == true) {
                    Map map(levelZeroBin, levelZero, sf::Vector2f(LEVEL_ZERO_BOT_START_X, LEVEL_ZERO_BOT_START_Y), sf::Vector2f(LEVEL_ZERO_PLAEYR_START_X, LEVEL_ZERO_PLAEYR_START_Y));
                    isFirst = false;
                }
                else if (TextToInt(openWindow.getButtons()[2].getContent()) == 1 && isFirst == true) {
                    Map map(levelZeroBin, levelZero, sf::Vector2f(LEVEL_ZERO_BOT_START_X, LEVEL_ZERO_BOT_START_Y), sf::Vector2f(LEVEL_ZERO_PLAEYR_START_X, LEVEL_ZERO_PLAEYR_START_Y));
                    isFirst = false;
                }
                else if (TextToInt(openWindow.getButtons()[2].getContent()) == 2 && isFirst == true) {
                    Map map2(levelTwoBin, levelTwo, sf::Vector2f(LEVEL_TWO_BOT_START_X, LEVEL_TWO_BOT_START_Y), sf::Vector2f(LEVEL_TWO_PLAEYR_START_X, LEVEL_TWO_PLAEYR_START_Y));
                    map = map2;
                    isFirst = false;
                }
                bot.setPosition(map.getBotPosition());
                player->setPosition(map.getPlayerPosition());
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
                    bot.setPosition(map.getBotPosition());
                    bot.setDirection(Direction::LEFT);
                }
                else if (player->getHP() > 0) {
                    player->takeDamage(1);
                    player->setPosition(sf::Vector2f(map.getPlayerPosition()));
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
                isFirst = true;
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
