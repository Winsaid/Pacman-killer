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
			if (countRounds > 2) {
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
				begin->setContent(IntToText(2));
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
			int countBots = TextToInt(begin->getContent()) + 1;
			begin->setContent(IntToText(1));
			begin->setContent(IntToText(countBots));
			break;
		}
	}
}



void Window::reduceCountBots() {
	for (auto begin = this->getBeginButton(), end = this->getendButton(); begin != end; ++begin) {
		if (begin->getGameState() == GameState::CountBot) {
			int countBots = TextToInt(begin->getContent()) - 1;
			if (countBots < 1) {
				begin->setContent(IntToText(1));
				break;
			}
			begin->setContent(IntToText(countBots));
			break;
		}
	}
}

void Window::addCountLifes() {
	for (auto begin = this->getBeginButton(), end = this->getendButton(); begin != end; ++begin) {
		if (begin->getGameState() == GameState::CountLife) {
			int countLife = TextToInt(begin->getContent()) + 1;
			if (countLife > 3) {
				begin->setContent(IntToText(1));
				break;
			}
			begin->setContent(IntToText(countLife));
			break;
		}
	}
}

void Window::reduceCountLifes() {
	for (auto begin = this->getBeginButton(), end = this->getendButton(); begin != end; ++begin) {
		if (begin->getGameState() == GameState::CountLife) {
			int countLife = TextToInt(begin->getContent()) - 1;
			if (countLife < 1) {
				begin->setContent(IntToText(3));
				break;
			}
			begin->setContent(IntToText(countLife));
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
		setRectangle(sf::Vector2f(400, 100), black, sf::Vector2f(740, 250)),
		"Play",
		GameState::Play
	);

	Button optionButton(
		setText(std::string("Options"), 75, &font, yellow),
		setRectangle(sf::Vector2f(400, 100), black, sf::Vector2f(740, 370)),
		"Options",
		GameState::OptionsMenu
	);

	Button authorsButton(
		setText(std::string("Authors"), 75, &font, yellow),
		setRectangle(sf::Vector2f(400, 100), black, sf::Vector2f(740, 490)),
		"Authors",
		GameState::Authors
	);

	Button exitButton(
		setText(std::string("Exit"), 75, &font, yellow),
		setRectangle(sf::Vector2f(400, 100), black, sf::Vector2f(740, 610)),
		"Exit",
		GameState::Exit
	);

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
		setText(std::string("Options:"), 75, &font, yellow),
		setRectangle(sf::Vector2f(550, 100), black, sf::Vector2f(100, 150)),
		"SelectName",
		GameState::Empty
	);

	Button SelectColorButton(
		setText(std::string("Select Color"), 75, &font, yellow),
		setRectangle(sf::Vector2f(355, 100), black, sf::Vector2f(100, 370)),
		"Select Color",
		GameState::GetColor
	);

	Button SelectMazeButton(
		setText(std::string("Select Control"), 75, &font, yellow),
		setRectangle(sf::Vector2f(432, 100), black, sf::Vector2f(100, 490)),
		"Select Control",
		GameState::Control
	);

	Button SelectLifesButton(
		setText(std::string("Select Lifes"), 75, &font, yellow),
		setRectangle(sf::Vector2f(250, 100), black, sf::Vector2f(100, 610)),
		"Select Lifes",
		GameState::SelectLife
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

Window createAuthorsWindow(sf::Sprite backgroundSprite, const sf::Font& font, const sf::Font& font1) {
	const auto yellow = sf::Color{ 0xFFFF00FF };
	const auto white = sf::Color::White;
	const auto blue = sf::Color::Blue;
	const auto red = sf::Color::Red;
	const auto black = sf::Color{ 0x00000099 };
	const int textSize = 75;

	Window window;

	std::vector<sf::Text> contents;
	sf::Text header = setText("Created by Legend Trio:", 100, &font, yellow);
	sf::Text firstAdmin = setText("Winsaid", 80, &font, white);
	sf::Text secondAdmin = setText("Sonador", 80, &font, blue);
	sf::Text thirdAdmin = setText("Wave78", 80, &font, red);

	header.setPosition(520, 20);
	firstAdmin.setPosition(900, 120);
	secondAdmin.setPosition(900, 220);
	thirdAdmin.setPosition(900, 320);
	contents.push_back(header);
	contents.push_back(firstAdmin);
	contents.push_back(secondAdmin);
	contents.push_back(thirdAdmin);

	window.setContents(contents);
	window.setBackground(backgroundSprite);

	return window;
}

Window createPlayWindow(sf::Sprite backgroundSprite, const sf::Font& font) {
	const auto yellow = sf::Color{ 0xFFFF00FF };
	const auto black = sf::Color{ 0x00000099 };
	const int textSize = 75;
	const auto red = sf::Color::Red;
	const auto green = sf::Color(0, 70, 0);
	Window window;

	Button StartGameButton(
		setText(std::string("Start Game"), 75, &font, yellow),
		setRectangle(sf::Vector2f(900, 100), black, sf::Vector2f(500, 150)),
		"Start Game",
		GameState::StartGame
	);

	Button Rounds(
		setText(std::string("Number of level"), 75, &font, yellow),
		setRectangle(sf::Vector2f(900, 100), black, sf::Vector2f(500, 270)),
		"Number of level",
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
		setText(std::string("1"), 75, &font, yellow),
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
	Button multiplay(
		setText(std::string("multiplay"), 73, &font, yellow),
		setRectangle(sf::Vector2f(900, 100), black, sf::Vector2f(500, 750)),
		"nonActive",
		GameState::Hold
	);

	Button BackButton(
		setText(std::string("Back"), 75, &font, yellow),
		setRectangle(sf::Vector2f(900, 100), black, sf::Vector2f(500, 870)),
		"Back To Menu",
		GameState::Back
	);
	multiplay.setOutline(3, red);
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
	buttons.push_back(multiplay);
	buttons.push_back(Bots);

	window.setButtons(buttons);
	window.setBackground(backgroundSprite);

	return window;
}

Window createPromptWindow(sf::Sprite backgroundSprite, const sf::Font& font) {
	const auto yellow = sf::Color(255, 255, 0);
	const auto pink = sf::Color::Magenta;
	const auto blue = sf::Color(0, 0, 70);
	const auto red = sf::Color(70, 0, 0);
	const auto orange = sf::Color(255,127,39);
	const auto blackP = sf::Color(0, 0, 0);
	const auto black = sf::Color(0, 0, 0, 200);
	Window window;

	sf::Text header = setText("Select Color:", 70, &font, yellow);
	Button back(
		setText(std::string(""), 75, &font, yellow),
		setRectangle(sf::Vector2f(1920, 1080), black),
		"",
		GameState::Nothing
	);

	Button rect(
		setText(std::string(""), 75, &font, yellow),
		setRectangle(sf::Vector2f(800, 400), blackP, sf::Vector2f(560, 140)),
		"",
		GameState::Nothing
	);

	Button redColor(
		setText(std::string(""), 75, &font, red),
		setRectangle(sf::Vector2f(50, 50), red, sf::Vector2f(690, 150)),
		"Red",
		GameState::Unselected
	);
	Button blueColor(
		setText(std::string(""), 75, &font, blue),
		setRectangle(sf::Vector2f(50, 50), blue, sf::Vector2f(630, 150)),
		"Blue",
		GameState::Unselected
	);
	Button PinkColor(
		setText(std::string(""), 75, &font, pink),
		setRectangle(sf::Vector2f(50, 50), pink, sf::Vector2f(570, 150)),
		"Pink",
		GameState::Selected
	);

	Button OrangeColor(
		setText(std::string(""), 75, &font, orange),
		setRectangle(sf::Vector2f(50, 50), orange, sf::Vector2f(750, 150)),
		"Orange",
		GameState::Unselected
	);

	Button BackButton(
		setText(std::string("Back"), 75, &font, yellow),
		setRectangle(sf::Vector2f(250, 100), black, sf::Vector2f(100, 730)),
		"Back To Menu",
		GameState::OptionsMenu
	);

	PinkColor.setOutline(3, sf::Color::Yellow);
	std::vector<Button> buttons;
	buttons.push_back(BackButton);
	buttons.push_back(PinkColor);
	buttons.push_back(redColor);
	buttons.push_back(blueColor);
	buttons.push_back(OrangeColor);

	window.setBackground(backgroundSprite);
	window.setButtons(buttons);
	return window;
}

Window selectColors(Window window, sf::Vector2f mousePos) {
	for (auto begin = window.getBeginButton(), end = window.getendButton(); begin != end; ++begin) {
		if (begin->getGameState() == GameState::Selected) {
			begin->setGameState(GameState::Unselected);
			begin->setOutline(3, sf::Color::Yellow);
		}
		if (begin->getGlobalBounds().contains(mousePos)) {
			begin->setGameState(GameState::Selected);
			begin->setOutline(3, sf::Color::Cyan);
		}
	}

	return window;
}

Window switchMode(Window window, sf::Vector2f mousePos) {
	for (auto begin = window.getBeginButton(), end = window.getendButton(); begin != end; ++begin) {
		if (begin->getGameState() == GameState::Hold) {
			begin->setGameState(GameState::Ready);
			begin->setOutline(3, sf::Color::Green);
			break;
		}
		else if (begin->getGameState() == GameState::Ready) {
			begin->setGameState(GameState::Hold);
			begin->setOutline(3, sf::Color::Red);
			break;
		}
	}
	return window;
}
	
	
	Window createPauseWindow(sf::Sprite backgroundSprite, const sf::Font & font) {
	const auto yellow = sf::Color{ 0xFFFF00FF };
	const auto black = sf::Color{ 0x00000099 };
	const int textSize = 75;

	Window window;

	Button ContinuePlayButton(
		setText(std::string("Continue"), 75, &font, yellow),
		setRectangle(sf::Vector2f(900, 100), black, sf::Vector2f(500, 300)),
		"Continue",
		GameState::Continue
	);

	Button Restart(
		setText(std::string("Restart game"), 75, &font, yellow),
		setRectangle(sf::Vector2f(900, 100), black, sf::Vector2f(500, 450)),
		"Restart game",
		GameState::Restart
	);

	Button BackButton(
		setText(std::string("Back"), 75, &font, yellow),
		setRectangle(sf::Vector2f(900, 100), black, sf::Vector2f(500, 600)),
		"Back To Menu",
		GameState::Back
	);

	std::vector<Button> buttons;
	buttons.push_back(ContinuePlayButton);
	buttons.push_back(Restart);
	buttons.push_back(BackButton);
	window.setButtons(buttons);
	window.setBackground(backgroundSprite);

	return window;
}

Window createOptionLifeWindow(sf::Sprite backgroundSprite, const sf::Font& font) {
	const auto yellow = sf::Color{ 0xFFFF00FF };
	const auto black = sf::Color{ 0x00000099 };
	const int textSize = 75;
	Window window;

	Button SaveButton(
		setText(std::string("Save"), 75, &font, yellow),
		setRectangle(sf::Vector2f(900, 100), black, sf::Vector2f(500, 600)),
		"Save",
		GameState::SaveLife
	);

	Button Life(
		setText(std::string("Count of lifes"), 75, &font, yellow),
		setRectangle(sf::Vector2f(900, 100), black, sf::Vector2f(500, 300)),
		"Count of lifes",
		GameState::Empty
	);

	Button ReduceLifes(
		setText(std::string("<"), 75, &font, yellow),
		setRectangle(sf::Vector2f(100, 100), black, sf::Vector2f(500, 450)),
		"Reduce Life",
		GameState::ReduceLife
	);

	Button CountLifes(
		setText(std::string("3"), 75, &font, yellow),
		setRectangle(sf::Vector2f(650, 100), black, sf::Vector2f(625, 450)),
		"Count Life",
		GameState::CountLife
	);

	Button AddingLifes(
		setText(std::string(">"), 75, &font, yellow),
		setRectangle(sf::Vector2f(100, 100), black, sf::Vector2f(1300, 450)),
		"Adding Lifes",
		GameState::AddLife
	);

	std::vector<Button> buttons;
	buttons.push_back(ReduceLifes);
	buttons.push_back(CountLifes);
	buttons.push_back(AddingLifes);
	buttons.push_back(SaveButton);
	buttons.push_back(Life);
	window.setButtons(buttons); 
	window.setBackground(backgroundSprite);

	return window;
}

Window createWinWindow(sf::Sprite backgroundSprite, const sf::Font& font, const sf::Font& font1) {
	const auto yellow = sf::Color{ 0xFFFF00FF };
	const auto black = sf::Color{ 0x00000099 };
	const auto Green = sf::Color(23, 69, 31);
	const int textSize = 75;

	Window window;

	std::vector<sf::Text> contents;
	sf::Text header = setText("Okey, You Win, but it was so easy...", 70, &font1, Green);

	Button restartButton(
		setText(std::string("restart Game"), 75, &font1, yellow),
		setRectangle(sf::Vector2f(750, 100), black, sf::Vector2f(580, 420)),
		"Back To Menu",
		GameState::Restart
	);
	Button BackButton(
		setText(std::string("Back"), 75, &font1, yellow),
		setRectangle(sf::Vector2f(250, 100), black, sf::Vector2f(820, 540)),
		"Back To Menu",
		GameState::Back
	);
	std::vector<Button> buttons;

	header.setPosition(310, 150);
	header.setOutlineColor(yellow);
	header.setOutlineThickness(5);
	contents.push_back(header);
	buttons.push_back(BackButton);
	buttons.push_back(restartButton);
	window.setContents(contents);
	window.setButtons(buttons);
	window.setBackground(backgroundSprite);

	return window;
}

Window createLoseWindow(sf::Sprite backgroundSprite, const sf::Font& font, const sf::Font& font1) {
	const auto yellow = sf::Color{ 0xFFFF00FF };
	const auto black = sf::Color{ 0x00000099 };
	const auto red = sf::Color::Red;
	const int textSize = 75;

	Window window;

	std::vector<sf::Text> contents;
	sf::Text header = setText("LOL, You Died, LOOOOOSER!!!", 70, &font1, red);
	Button restartButton(
		setText(std::string("restart Game"), 75, &font1, yellow),
		setRectangle(sf::Vector2f(750, 100), black, sf::Vector2f(580, 420)),
		"Back To Menu",
		GameState::Restart
	);

	Button BackButton(
		setText(std::string("Back"), 75, &font1, yellow),
		setRectangle(sf::Vector2f(250, 100), black, sf::Vector2f(820, 540)),
		"Back To Menu",
		GameState::Back
	);
	std::vector<Button> buttons;

	header.setPosition(370, 100);
	header.setOutlineColor(yellow);
	header.setOutlineThickness(5);
	contents.push_back(header);
	buttons.push_back(BackButton);
	buttons.push_back(restartButton);
	window.setContents(contents);
	window.setButtons(buttons);
	window.setBackground(backgroundSprite);

	return window;
}

Window createControlWindow(sf::Sprite backgroundSprite, const sf::Font& font) {
	const auto yellow = sf::Color{ 0xFFFF00FF };
	const auto black = sf::Color{ 0x00000099 };
	const int textSize = 75;
	Window window;

	Button SaveButton(
		setText(std::string("Save"), 75, &font, yellow),
		setRectangle(sf::Vector2f(900, 100), black, sf::Vector2f(500, 600)),
		"Save",
		GameState::Back
	);

	Button Life(
		setText(std::string("Switch Manip"), 75, &font, yellow),
		setRectangle(sf::Vector2f(900, 100), black, sf::Vector2f(500, 300)),
		"Count of lifes",
		GameState::Empty
	);

	Button wasd(
		setText(std::string("WASD"), 75, &font, yellow),
		setRectangle(sf::Vector2f(420, 100), black, sf::Vector2f(500, 450)),
		"WASD",
		GameState::WASDch
	);

	Button arrows(
		setText(std::string("arrows"), 75, &font, yellow),
		setRectangle(sf::Vector2f(420, 100), black, sf::Vector2f(978, 450)),
		"Arrows",
		GameState::WASD
	);

	std::vector<Button> buttons;
	buttons.push_back(wasd);
	buttons.push_back(arrows);
	buttons.push_back(SaveButton);
	buttons.push_back(Life);
	window.setButtons(buttons);
	window.setBackground(backgroundSprite);

	return window;
}

Window saveCtrl(Window window, sf::Vector2f mousePos) {
	for (auto begin = window.getBeginButton(), end = window.getendButton(); begin != end; ++begin) {
		if (begin->getGameState() == GameState::WASDch) {
			begin->setGameState(GameState::WASD);
			begin->setOutline(3, sf::Color::Yellow);
		}
		if (begin->getGlobalBounds().contains(mousePos) && begin->getGameState() == GameState::WASD) {
			begin->setGameState(GameState::WASDch);
			begin->setOutline(3, sf::Color::Cyan);
		}
	}
	return window;
}

std::string getControlFromBut(Window window) {
	for (auto begin = window.getBeginButton(), end = window.getendButton(); begin != end; ++begin) {
		if (begin->getGameState() == GameState::WASDch) {
			return begin->getContent().getString();
		}
	}
	return "WASD";
}

BotType GetColorSettings(Window window) {
	for (auto begin = window.getBeginButton(), end = window.getendButton(); begin != end; ++begin) {
		if (begin->getGameState() == GameState::Selected) {
			if (begin->getString() == "Red") {
				return BotType::Red;
			}
			if (begin->getString() == "Blue") {
				return BotType::Blue;
			}
			if (begin->getString() == "Pink") {
				return BotType::Pink;
			}
			if (begin->getString() == "Orange") {
				return BotType::Orange;
			}
		}
	}
}