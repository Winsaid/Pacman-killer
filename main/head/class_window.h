#pragma once

#include "SFML/Graphics.hpp"
#include "class_button.h"
#include "GameState.h"
#include <string>
#include <vector>
#include <iostream>
#include "Player.h"
#include "Bot.h"
#include "Scale.h"
#include "Map.h"

class Window : public sf::Drawable {
public:
	Window() {};
	Window(std::vector<sf::Text> contents, std::vector<Button> buttons, sf::Sprite background);
	Window(const Window& other);
	Window(Window&& other) noexcept;
	~Window() {}

	Window& operator=(const Window& other);
	Window& operator=(Window&& other) noexcept;

	std::vector<sf::Text> getContents() { return this->_contents; }
	std::vector<Button>   getButtons() { return this->_buttons; }
	auto                  getBeginButton() { return this->_buttons.begin(); }
	auto                  getendButton() { return this->_buttons.end(); }
	sf::Sprite            getBackground() { return this->_background; }
	GameState             getGameState() { return this->_state; }

	std::vector<sf::Text> getContents() const { return this->_contents; }
	std::vector<Button>   getButtons() const { return this->_buttons; }
	sf::Sprite            getBackground() const { return this->_background; }
	GameState             getGameState() const { return this->_state; }

	void setBackground(sf::Sprite background) { this->_background = background; }
	void setButtons(std::vector<Button> buttons) { this->_buttons = buttons; }
	void setContents(std::vector<sf::Text> contents) { this->_contents = contents; }
	void setGameState(GameState state) { this->_state = state; }

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	GameState doAction(sf::Vector2f touchPosition);
	void addButton(Button newButton) { this->_buttons.push_back(newButton); }
	void addContent(sf::Text newContent) { this->_contents.push_back(newContent); }
	void addCountRounds();
	void reduceCountRounds();
	void addCountBots();
	void reduceCountBots();

private:
	std::vector<sf::Text> _contents;
	std::vector<Button>   _buttons;
	sf::Sprite            _background;
	GameState             _state;
};

Window createMainWindow(sf::Sprite backgroundSprite, const sf::Font& font);
Window createOptionWindow(sf::Sprite backgroundSprite, const sf::Font& font);
Window createAuthorsWindow(sf::Sprite backgroundSprite, const sf::Font& font);
Window createPlayWindow(sf::Sprite backgroundSprite, const sf::Font& font);
Window createPauseWindow(sf::Sprite backgroundSprite, const sf::Font& font);