#include "Calculator.h"

int main(){
	Blackjack player;
	Blackjack dealer;
	
	{//Adjusting default Blackjack initialization for the dealer object to match dealer's rules.
		bool soft18orGreater;
		bool hard17orGreater;
		for(int i = 17; i < 30; i++){
			soft18orGreater = (17 <= i && i <= 19);
			hard17orGreater = (26 <= i && i <= 29);
			if(soft18orGreater || hard17orGreater){
				for(int j = 0; j < 10; j++){
					dealer.gamestate[i].disconnect(j);
				}
			}
		}
	}
	
	Choice choice = displayMenu();
	
	switch(choice){
		case Choice::ENUMERATE:
			enumerate(dealer);
			break;
		case Choice::FORWARDTABLE:
			displayForwardTable(dealer);
			break;
		case Choice::BACKWARDTABLE:
			displayBackwardTable(dealer);
			break;
	}
	
	return 0;
}


Choice displayMenu(void){
	std::cout << "What would you like to do?\n";
	std::cout << "1: Enumerate Paths to...\n";
	std::cout << "2: Display Forward Connections.\n";
	std::cout << "3: Display Backward Connections.\n";
	
	Choice choice = static_cast<Choice>(stoi(promptInput("")));
	
	return choice;
}


void displayForwardTable(Blackjack player){
	player.printNextValueTable();
}


void displayBackwardTable(Blackjack player){
	player.printBackValueTable();
}


void enumerate(Blackjack player){
	int x;
	std::string yesNo;
	bool isValid;
	do{
		x = stoi(promptInput("Print to? (1-32): "));
		isValid = (1<=x && x<=32);
	}while(!isValid);
	do{
		yesNo = promptInput("Print full paths? (y/n): ");
		isValid = (yesNo=="y" || yesNo=="n");
	}while(!isValid);
	
	for(int i = 0; i < x; i++){
		player.gamestate[i].getArrivalPaths();
		std::cout << player.gamestate[i].arrivalPaths.size() << " to ";
		player.gamestate[i].printHardness(" ", true);
		player.gamestate[i].printValue(":\n");
		
		if(yesNo == "y"){
			player.printArrivalPaths(i);
		}
	}
}


std::string promptInput(std::string prompt){
	std::string returnValue;
	std::cout << prompt;
	getline (std::cin, returnValue);
	std::cout << "\n\n";
	
	return returnValue;
}
