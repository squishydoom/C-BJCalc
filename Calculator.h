#include "Blackjack.cpp"

#include <iostream>
#include <string>

enum class Choice{
	ENUMERATE = 1,
	FORWARDTABLE,
	BACKWARDTABLE,
};

Choice displayMenu(void);
void displayForwardTable(Blackjack);
void displayBackwardTable(Blackjack);
void enumerate(Blackjack);
std::string promptInput(std::string);