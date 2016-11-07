#include "Blackjack.cpp"

#include <iostream>
#include <string>
#include <utility>

enum class menuChoice{
	ENUMERATE = 1,
	FORWARDTABLE,
	BACKWARDTABLE
};

enum class playerChoice{
	DEALER = 1,
	PLAYER
};

std::pair<playerChoice, menuChoice> displayMenu(void);
void displayForwardTable(Blackjack);
void displayBackwardTable(Blackjack);
void enumerate(Blackjack);
std::string promptInput(std::string);