#include "class_button.h"

int main()
{
	sf::RenderWindow win(sf::VideoMode(1920, 1080), "Pacman");
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("C:\\dev\\Pacman-killer\\images\\background.png"))
		return 1;

	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);

	sf::Font font;
	if (!font.loadFromFile("C:\\dev\\Pacman-killer\\fonts\\Joystix.TTF"))
		return 1;

	auto yellow = sf::Color{ 0xFFFF00FF };
	auto black = sf::Color{ 0x00000099 };
	int textSize = 75;

	Button playButton(
		setText(std::string("Play"), 75, &font, yellow),
		setRectangle(sf::Vector2f(250, 100), black, sf::Vector2f(100, 250))
	);

	Button optionButton(
		setText(std::string("Option"), 75, &font, yellow),
		setRectangle(sf::Vector2f(355, 100), black, sf::Vector2f(100, 370))
	);

	Button authorsButton(
		setText(std::string("Authors"), 75, &font, yellow),
		setRectangle(sf::Vector2f(432, 100), black, sf::Vector2f(100, 490))
	);

	Button exitButton(
		setText(std::string("Exit"), 75, &font, yellow),
		setRectangle(sf::Vector2f(250, 100), black, sf::Vector2f(100, 610))
	);


	playButton.setPosition(sf::Vector2f(200, 250));

	while (win.isOpen()) {
		sf::Event event;

		while (win.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				win.close();
			}
		}

		win.clear();
		win.draw(backgroundSprite);
		win.draw(playButton);
		win.draw(optionButton);
		win.draw(authorsButton);
		win.draw(exitButton);
		win.display();
	}

	return 0;
}