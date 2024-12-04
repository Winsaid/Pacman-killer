#include "../head/class_window.h"

Window::Window(std::vector<sf::Text> contents, std::vector<Button> buttons, sf::Sprite background)
	: _contents(contents), _buttons(buttons), _background(background), _state(GameState::MainMenu)
{}

Window::Window(const Window& other)
{
	this->_background = other.getBackground();
	this->_buttons = other.getButtons();
	this->_contents = other.getContents();
}

Window::Window(Window&& other) noexcept
{
	this->_contents = other.getContents();
	this->_buttons = other.getButtons();
	this->_background.setTexture(*other.getBackground().getTexture());
}

Window& Window::operator=(const Window& other)
{
	if (this == &other)
		return *this;

	this->_background = other.getBackground();
	this->_buttons = other.getButtons();
	this->_contents = other.getContents();

	return *this;
}

Window& Window::operator=(Window&& other) noexcept
{
	if (this == &other)
		return *this;

	this->_background = other.getBackground();
	this->_buttons = other.getButtons();
	this->_contents = other.getContents();

	return *this;
}

GameState Window::doAction(sf::Vector2f touchPosition)
{
	for (auto& button : this->_buttons) {
		if (button.getGlobalBounds().contains(touchPosition))
			return button.getGameState();
	}

	return this->_state;
}

void Window::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_background, states);

	for (auto button : this->_buttons) {
		target.draw(button);
	}

	for (auto content : this->_contents) {
		target.draw(content);
	}
}

void Window::addCountRounds() {
	for (auto begin = this->getBeginButton(), end = this->getendButton(); begin != end; ++begin) {
		if (begin->getGameState() == GameState::CountRound) {
			int countRounds = TextToInt(begin->getContent()) + 1;
			if (countRounds > 9) {
				begin->setContent(IntToText(0));
				break;
			}
			begin->setContent(IntToText(countRounds));
			break;
		}
	}
}

void Window::reduceCountRounds() {
	for (auto begin = this->getBeginButton(), end = this->getendButton(); begin != end; ++begin) {
		if (begin->getGameState() == GameState::CountRound) {
			int countRounds = TextToInt(begin->getContent()) - 1;
			if (countRounds < 0) {
				begin->setContent(IntToText(9));
				break;
			}
			begin->setContent(IntToText(countRounds));
			break;
		}
	}
}

void Window::addCountBots() {
	for (auto begin = this->getBeginButton(), end = this->getendButton(); begin != end; ++begin) {
		if (begin->getGameState() == GameState::CountBot) {
			int countRounds = TextToInt(begin->getContent()) + 1;
			if (countRounds > 4) {
				begin->setContent(IntToText(0));
				break;
			}
			begin->setContent(IntToText(countRounds));
			break;
		}
	}
}
void Window::reduceCountBots() {
	for (auto begin = this->getBeginButton(), end = this->getendButton(); begin != end; ++begin) {
		if (begin->getGameState() == GameState::CountBot) {
			int countRounds = TextToInt(begin->getContent()) - 1;
			if (countRounds < 0) {
				begin->setContent(IntToText(9));
				break;
			}
			begin->setContent(IntToText(countRounds));
			break;
		}
	}
}

Window createMainWindow(sf::Sprite backgroundSprite, const sf::Font& font) {
	const auto yellow = sf::Color{ 0xFFFF00FF };
	const auto black = sf::Color{ 0x00000099 };
	const int textSize = 75;

	Window window;

	Button playButton(
		setText(std::string("Play"), 75, &font, yellow),
		setRectangle(sf::Vector2f(250, 100), black, sf::Vector2f(100, 250)),
		"Play",
		GameState::Play
	);

	Button optionButton(
		setText(std::string("Options"), 75, &font, yellow),
		setRectangle(sf::Vector2f(355, 100), black, sf::Vector2f(100, 370)),
		"Options",
		GameState::OptionsMenu
	);

	Button authorsButton(
		setText(std::string("Authors"), 75, &font, yellow),
		setRectangle(sf::Vector2f(432, 100), black, sf::Vector2f(100, 490)),
		"Authors",
		GameState::Authors
	);

	Button exitButton(
		setText(std::string("Exit"), 75, &font, yellow),
		setRectangle(sf::Vector2f(250, 100), black, sf::Vector2f(100, 610)),
		"Exit",
		GameState::Exit
	);

	playButton.setPosition(sf::Vector2f(100, 250));
	optionButton.setPosition(sf::Vector2f(100, 370));
	authorsButton.setPosition(sf::Vector2f(100, 490));
	exitButton.setPosition(sf::Vector2f(100, 610));

	std::vector<Button> buttons;
	buttons.push_back(playButton);
	buttons.push_back(optionButton);
	buttons.push_back(authorsButton);
	buttons.push_back(exitButton);

	window.setButtons(buttons);
	window.setBackground(backgroundSprite);

	return window;
}

Window createOptionWindow(sf::Sprite backgroundSprite, const sf::Font& font) {
	const auto yellow = sf::Color{ 0xFFFF00FF };
	const auto black = sf::Color{ 0x00000099 };
	const int textSize = 75;

	Window window;

	Button SelectNameButton(
		setText(std::string("Select Name"), 75, &font, yellow),
		setRectangle(sf::Vector2f(250, 100), black, sf::Vector2f(100, 250)),
		"SelectName",
		GameState::Exit
	);

	Button SelectColorButton(
		setText(std::string("Select Color"), 75, &font, yellow),
		setRectangle(sf::Vector2f(355, 100), black, sf::Vector2f(100, 370)),
		"Select Color",
		GameState::Exit
	);

	Button SelectMazeButton(
		setText(std::string("Select Maze"), 75, &font, yellow),
		setRectangle(sf::Vector2f(432, 100), black, sf::Vector2f(100, 490)),
		"Select Maze",
		GameState::Exit
	);

	Button SelectLifesButton(
		setText(std::string("Select Lifes"), 75, &font, yellow),
		setRectangle(sf::Vector2f(250, 100), black, sf::Vector2f(100, 610)),
		"Select Lifes",
		GameState::Exit
	);

	Button BackButton(
		setText(std::string("Back"), 75, &font, yellow),
		setRectangle(sf::Vector2f(250, 100), black, sf::Vector2f(100, 730)),
		"Back To Menu",
		GameState::Back
	);

	std::vector<Button> buttons;
	buttons.push_back(SelectNameButton);
	buttons.push_back(SelectColorButton);
	buttons.push_back(SelectMazeButton);
	buttons.push_back(SelectLifesButton);
	buttons.push_back(BackButton);

	window.setButtons(buttons);
	window.setBackground(backgroundSprite);
	return window;
}

Window createAuthorsWindow(sf::Sprite backgroundSprite, const sf::Font& font) {
	const auto yellow = sf::Color{ 0xFFFF00FF };
	const auto black = sf::Color{ 0x00000099 };
	const int textSize = 75;

	Window window;

	std::vector<sf::Text> contents;
	sf::Text header = setText("Created by Legend Trio:", 50, &font, yellow);
	sf::Text firstAdmin = setText("Winsaid", 30, &font, yellow);
	sf::Text secondAdmin = setText("Sonador", 30, &font, yellow);
	sf::Text thirdAdmin = setText("Wave78", 30, &font, yellow);


	Button BackButton(
		setText(std::string("Back"), 75, &font, yellow),
		setRectangle(sf::Vector2f(250, 100), black, sf::Vector2f(100, 730)),
		"Back To Menu",
		GameState::Back
	);
	std::vector<Button> buttons;

	header.setPosition(550, 20);
	firstAdmin.setPosition(900, 120);
	secondAdmin.setPosition(900, 220);
	thirdAdmin.setPosition(900, 320);
	contents.push_back(header);
	contents.push_back(firstAdmin);
	contents.push_back(secondAdmin);
	contents.push_back(thirdAdmin);
	buttons.push_back(BackButton);

	window.setContents(contents);
	window.setButtons(buttons);
	window.setBackground(backgroundSprite);

	return window;
}

Window createPlayWindow(sf::Sprite backgroundSprite, const sf::Font& font) {
	const auto yellow = sf::Color{ 0xFFFF00FF };
	const auto black = sf::Color{ 0x00000099 };
	const int textSize = 75;

	Window window;

	Button StartGameButton(
		setText(std::string("Start Game"), 75, &font, yellow),
		setRectangle(sf::Vector2f(900, 100), black, sf::Vector2f(500, 150)),
		"Start Game",
		GameState::StartGame
	);

	Button Rounds(
		setText(std::string("Count of rounds"), 75, &font, yellow),
		setRectangle(sf::Vector2f(900, 100), black, sf::Vector2f(500, 270)),
		"Count of rounds",
		GameState::Empty
	);

	Button ReduceRounds(
		setText(std::string("<"), 75, &font, yellow),
		setRectangle(sf::Vector2f(100, 100), black, sf::Vector2f(500, 390)),
		"Delete Rounds",
		GameState::ReduceRound
	);

	Button CountRound(
		setText(std::string("0"), 75, &font, yellow),
		setRectangle(sf::Vector2f(650, 100), black, sf::Vector2f(625, 390)),
		"Count Round",
		GameState::CountRound
	);

	Button AddRounds(
		setText(std::string(">"), 75, &font, yellow),
		setRectangle(sf::Vector2f(100, 100), black, sf::Vector2f(1300, 390)),
		"Adding Rounds",
		GameState::AddRound
	);


	Button Bots(
		setText(std::string("Count of bots"), 75, &font, yellow),
		setRectangle(sf::Vector2f(900, 100), black, sf::Vector2f(500, 510)),
		"Count of bots",
		GameState::Empty
	);

	Button ReduceBots(
		setText(std::string("<"), 75, &font, yellow),
		setRectangle(sf::Vector2f(100, 100), black, sf::Vector2f(500, 630)),
		"Delete Bots",
		GameState::ReduceBot
	);

	Button CountBots(
		setText(std::string("0"), 75, &font, yellow),
		setRectangle(sf::Vector2f(650, 100), black, sf::Vector2f(625, 630)),
		"Count Bots",
		GameState::CountBot
	);

	Button AddingBots(
		setText(std::string(">"), 75, &font, yellow),
		setRectangle(sf::Vector2f(100, 100), black, sf::Vector2f(1300, 630)),
		"Adding Bots",
		GameState::AddBot
	);

	Button BackButton(
		setText(std::string("Back"), 75, &font, yellow),
		setRectangle(sf::Vector2f(900, 100), black, sf::Vector2f(500, 750)),
		"Back To Menu",
		GameState::Back
	);

	std::vector<Button> buttons;
	buttons.push_back(StartGameButton);
	buttons.push_back(AddRounds);
	buttons.push_back(CountRound);
	buttons.push_back(ReduceRounds);
	buttons.push_back(AddingBots);
	buttons.push_back(ReduceBots);
	buttons.push_back(CountBots);
	buttons.push_back(BackButton);
	buttons.push_back(Rounds);
	buttons.push_back(Bots);

	window.setButtons(buttons);
	window.setBackground(backgroundSprite);

	return window;
}
