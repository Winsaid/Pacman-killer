#include "../head/main.h"

int main()
{
	GameState gameState = GameState::MainMenu;

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Pacman");
	std::string pathToBackgroundImageForMenu = "../../../../images/background.png";
	std::string pathToFontFile = "../../../../fonts/Joystix.TTF";
	std::string pathToBackgroundImageForAuthors = "../../../../images/authors.png";

	sf::Texture backgroundTextureForAuthors;
	if (!backgroundTextureForAuthors.loadFromFile(pathToBackgroundImageForAuthors)) {
		throw std::runtime_error("Failed to load background texture");
	}


	sf::Sprite backgroundSpriteForAuthors;
	backgroundSpriteForAuthors.setTexture(backgroundTextureForAuthors);

	sf::Texture backgroundTextureForMenu;
	if (!backgroundTextureForMenu.loadFromFile(pathToBackgroundImageForMenu)) {
		throw std::runtime_error("Failed to load background texture");
	}

	sf::Sprite backgroundSpriteForMenu;
	backgroundSpriteForMenu.setTexture(backgroundTextureForMenu);

	sf::Font font;
	if (!font.loadFromFile(pathToFontFile)) {
		throw std::runtime_error("Failed to load font");
	}

	Window mainWindow   = createMainWindow(backgroundSpriteForMenu, font);
	Window optionWindow = createOptionWindow(backgroundSpriteForMenu, font);
	Window authorWindow = createAuthorsWindow(backgroundSpriteForAuthors, font);
	Window playWindow   = createPlayWindow(backgroundSpriteForMenu, font);
	Window openWindow   = mainWindow;
	while (window.isOpen()) {
		sf::Event event; 
		sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					gameState = openWindow.doAction(mousePos);
				}
			}
		}

		window.clear();

		if (gameState == GameState::MainMenu || gameState == GameState::Back) {
			window.draw(mainWindow);
			openWindow = mainWindow;
		}
		else if (gameState == GameState::OptionsMenu) {
			window.draw(optionWindow);
			openWindow = optionWindow;
		}
		else if (gameState == GameState::Authors) {
			window.draw(authorWindow);
			openWindow = authorWindow;
		}
		else if (gameState == GameState::Exit) {
			window.close();
		}
		else if (gameState == GameState::Play) {
			window.draw(playWindow);
			openWindow = playWindow;
		}
		else if (gameState == GameState::AddRound) {
			playWindow.addCountRounds();
			window.draw(playWindow);
			openWindow = playWindow;
			gameState = GameState::Play;
		}
		else if (gameState == GameState::ReduceRound) {
			playWindow.reduceCountRounds();
			window.draw(playWindow);
			openWindow = playWindow;
			gameState = GameState::Play;
		}
		else if (gameState == GameState::AddBot) {
			playWindow.addCountBots();
			window.draw(playWindow);
			openWindow = playWindow;
			gameState = GameState::Play;
		}
		else if (gameState == GameState::ReduceBot) {
			playWindow.reduceCountBots();
			window.draw(playWindow);
			openWindow = playWindow;
			gameState = GameState::Play;
		}
		else {
			window.draw(openWindow);
		}

		window.display();
	}

	return 0;
}
