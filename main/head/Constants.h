#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

const int LEVEL_ZERO_BOT_START_X = 886;
const int LEVEL_ZERO_BOT_START_Y = 248;

const int LEVEL_ONE_BOT_START_X = 822;
const int LEVEL_ONE_BOT_START_Y = 312;

const int LEVEL_TWO_BOT_START_X = 886;
const int LEVEL_TWO_BOT_START_Y = 408;

const int LEVEL_ZERO_PLAEYR_START_X = 886;
const int LEVEL_ZERO_PLAEYR_START_Y = 440;
const int LEVEL_ZERO_PLAEYR_SECOND_START_X = 886;
const int LEVEL_ZERO_PLAEYR_SECOND_START_Y = 376;

const int LEVEL_ONE_PLAEYR_START_X = 822;
const int LEVEL_ONE_PLAEYR_START_Y = 472;

const int LEVEL_TWO_PLAEYR_START_X = 886;
const int LEVEL_TWO_PLAEYR_START_Y = 536;
const int LEVEL_TWO_PLAEYR_SECOND_START_X = 886;
const int LEVEL_TWO_PLAEYR_SECOND_START_Y = 280;


const float WINDOW_HEIGHT = 1020.0;
const float WINDOW_WIDTH = 1280.0;

const int MAP_LEVEL_ZERO_HEIGHT = 11;
const int MAP_LEVEL_ZERO_WIDTH = 20;
const int MAP_START_LEVEL_ZERO_X = 598;
const int MAP_START_LEVEL_ZERO_Y = 152;

const int MAP_LEVEL_ONE_HEIGHT = 15;
const int MAP_LEVEL_ONE_WIDTH = 15;
const int MAP_START_LEVEL_ONE_X = 598;
const int MAP_START_LEVEL_ONE_Y = 152;

int MAP_LEVEL_TWO_HEIGHT = 22;
int MAP_LEVEL_TWO_WIDTH = 19;
int MAP_START_LEVEL_TWO_X = 598;
int MAP_START_LEVEL_TWO_Y = 152;

std::vector<sf::String> ZERO_LEVEL = {
	"00000000000000000000",
	"01111011111111011110",
	"01001010000001010010",
	"01011111111111111010",
	"01010010000001001010",
	"01111110000101111110",
	"01010010000001001010",
	"01011111111111111010",
	"01001010000001010010",
	"01111011111111011110",
	"00000000000000000000",
};

std::vector<sf::String> ZERO_LEVEL_S = {
	"2027272727272727272727272727272727272721",
	"250*0*0*0*010*0*0*0*0*0*0*0*010*0*0*0*24",
	"250*05020*010*0202020202020*010*02060*24",
	"250*010*0*0*0*0*0*0*0*0*0*0*0*0*0*010*24",
	"250*010*02020*05020_0_02060*02020*010*24",
	"250*0*0*0*0*0*010_0_0_0_010*0*0*0*0*0*24",
	"250*010*02020*0702020202080*02020*010*24",
	"250*010*0*0*0*0*0*0*0*0*0*0*0*0*0*010*24",
	"250*07020*010*0202020202020*010*02080*24",
	"250*0*0*0*010*0*0*0*0*0*0*0*010*0*0*0*24",
	"2226262626262626262626262626262626262623"
};

std::vector<sf::String> LEVEL_ONE = {
	"000000000000000",
	"011111000111110",
	"010101101101010",
	"010100101001010",
	"010110101011010",
	"010011111110010",
	"011110000011110",
	"010010000010010",
	"010110000011010",
	"011100000001110",
	"010101111101010",
	"010111010111010",
	"010010010010010",
	"011111111111110",
	"000000000000000"
};

std::vector<sf::String> LEVEL_ONE_S = {
	"202727272727272727272727272721",
	"250*0*0*0*0*0702080*0*0*0*0*24",
	"250*010*010*0*010*0*010*010*24",
	"250*010*07060*010*05080*010*24",
	"250*010*0*010*010*010*0*010*24",
	"250*07020*0*0*0*0*0*0*02080*24",
	"250*0*0*0*05020_02060*0*0*0*24",
	"250*05020*01_0_0_0010*02060*24",
	"250*010*0*01_0_0_0010*0*010*24",
	"250*0!0*050202020202060*0!0*24",
	"250*010*010*0*0*0*0*010*010*24",
	"250*010*0*0*010*010*0*0*010*24",
	"250*07020*02080*07020*02080*24",
	"250*0*0*0*0*0*0*0*0*0*0*0*0*24",
	"222626262626262626262626262623"
};

std::vector<sf::String> LEVEL_TWO = {
	"0000000000000000000",
	"0111111110111111110",
	"0100100010100010010",
	"0100100010100010010",
	"0111111111111111110",
	"0100101000002010010",
	"0111101110111011110",
	"0000100010100010000",
	"0000101111111010000",
	"0000101000001010000",
	"0000111000001110000",
	"0000101000001010000",
	"0000101111111010000",
	"0000101000001010000",
	"0111111110111111110",
	"0100100010100010010",
	"0110111111111110110",
	"0010101000001010100",
	"0111101110111011110",
	"0100000010100000010",
	"0111111111111111110",
	"0000000000000000000"
};

std::vector<sf::String> LEVEL_TWO_S = {
	"20272727272727272727272727272727272721",
	"250*0*0*0*0*0*0*0*010*0*0*0*0*0*0!0*24",
	"250!05060*0502060*010*0502060*05060*24",
	"250*07080*0702080*010*0702080*07080*24",
	"250*0*0*0*0*0*0*0*0*0*0*0*0*0*0*0*0*24",
	"250*02020*010*02020202020*010*02020*24",
	"250*0*0*0*010*0*0*010*0*0*010*0*0*0*24",
	"222626060*0102020*010*0202010*05262623",
	"0_0_0_250*010*0*0*0*0*0*0*010*240_0_0_",
	"0_0_0_250*010*05020_02060*010*240_0_0_",
	"0_0_0_250*0*0*010_0_0_010*0*0*240_0_0_",
	"0_0_0_250*010*07020202080*010*240_0_0_",
	"0_0_0_250*010*0*0*0*0*0*0*010*240_0_0_",
	"202727080*010*02020202020*010*07272721",
	"250*0*0*0*0*0*0*0*010*0*0*0*0*0*0*0*24",
	"250!02060*0202020*010*0202020*05020*24",
	"250*0*010*0*0*0*0*0*0*0*0*0*0*010*0*24",
	"25020*010*010*02020202020*010*010*0224",
	"250*0*0*0*010*0*0*010*0*0*010*0*0*0*24",
	"250*0202020202020*010*0202020202020!24",
	"250*0*0*0*0*0*0*0*0*0*0*0*0*0*0*0*0*24",
	"22262626262626262626262626262626262623"
};