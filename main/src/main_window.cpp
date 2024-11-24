#include "../head/class_button.h"
#include "../head/options.h"
#include "../head/authors.h"
#include "SFML/Audio.hpp"
#include <iostream>

enum class GameState { MainMenu, OptionsMenu, Authors };

int main()
{
	GameState gameState = GameState::MainMenu;
	sf::RenderWindow win(sf::VideoMode(1920, 1080), "Pacman");
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("../../../../images/background.png"));

	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);

	sf::Font font;
	if (!font.loadFromFile("../../../../fonts/Joystix.TTF"))
		return 1;


	auto yellow = sf::Color{ 0xFFFF00FF };
	auto black = sf::Color{ 0x00000099 };
	int textSize = 75;

	Button playButton(
		setText(std::string("Play"), 75, &font, yellow),
		setRectangle(sf::Vector2f(250, 100), black, sf::Vector2f(100, 250)),
		"Play"
	);

	Button optionButton(
		setText(std::string("Options"), 75, &font, yellow),
		setRectangle(sf::Vector2f(355, 100), black, sf::Vector2f(100, 370)),
		"Options"
	);

	Button authorsButton(
		setText(std::string("Authors"), 75, &font, yellow),
		setRectangle(sf::Vector2f(432, 100), black, sf::Vector2f(100, 490)),
		"Authors"
	);

	Button exitButton(
		setText(std::string("Exit"), 75, &font, yellow),
		setRectangle(sf::Vector2f(250, 100), black, sf::Vector2f(100, 610)),
		"Exit"
	);


	playButton.setPosition(sf::Vector2f(200, 250));
	std::vector<Button> menu;
	menu.push_back(playButton);
	menu.push_back(optionButton);
	menu.push_back(authorsButton);
	menu.push_back(exitButton);

	options options(font, yellow, black);
	Authors add(font, yellow, black);

	while (win.isOpen()) {
		sf::Event event;

		while (win.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				win.close();
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2i mousePos = sf::Mouse::getPosition(win);
					if (gameState == GameState::MainMenu) {
						for (size_t i = 0; i < menu.size(); ++i) {
							if (menu[i].getShape().getGlobalBounds().contains(sf::Vector2f(mousePos))) {
								std::string but = menu[i].getText();
								if (menu[i].getText() == "Options") {
									gameState = GameState::OptionsMenu;
								}
								else if (menu[i].getText() == "Exit") {
									win.close();
								}
								else if (menu[i].getText() == "Authors") {
									gameState = GameState::Authors;
								}
							}
						}
					}
					else if (gameState == GameState::OptionsMenu) {
						for (size_t i = 0; i < options.buttons.size(); ++i) {
							if (options.buttons[i].getShape().getGlobalBounds().contains(sf::Vector2f(mousePos))) {
								if (options.buttons[i].getText() == "Back To Menu") {
									gameState = GameState::MainMenu;
								}
							}
						}
					}
				else if (gameState == GameState::Authors) {
					for (size_t i = 0; i < add.buttons.size(); ++i) {
						if (add.buttons[i].getShape().getGlobalBounds().contains(sf::Vector2f(mousePos))) {
							if (add.buttons[i].getText() == "Back To Menu") {
								gameState = GameState::MainMenu;
							}
						}
					}
				}
			}
				break;
			}
		}


		win.clear();
		if (gameState == GameState::MainMenu) {
			win.draw(backgroundSprite);
			for (const auto& button : menu)
				win.draw(button);
		}
		else if(gameState == GameState::OptionsMenu) {
			win.draw(backgroundSprite);
			for (const auto& button : options.buttons)
				win.draw(button);
		}
		else if (gameState == GameState::Authors) {
			add.setBack();
			win.draw(add.backSprite);
			std::vector<sf::Text>textArr = add.setDevText();
			for (const auto& text : textArr) {
				win.draw(text);
			}
			for (const auto& button : add.buttons) {
				win.draw(button);
			}
		}
		win.display();
	}

	return 0;
}