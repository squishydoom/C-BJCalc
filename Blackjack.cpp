#include <iostream>

#include "Blackjack.h"

Blackjack::Blackjack(){ //Initializes everything except the arrivalPaths and arrivalPacks variables.
	//The 32 states that can occur in a game of black jack.
	//[0] <-> No cards
	//[1-9] <-> Hand Values: 2-10
	//[10-19] <-> Hand Values: Soft 11-Soft 20
	//[20-29] Hand Values: Hard 11-Hard 20
	//[30] <-> Hand Value :21
	//[31] <-> Busted
	//They are ordered in this way to produce a DAG when the connecting pointers are created between them.
	for(int i = 0; i < 32; i++){
		gamestate[i].position = i;
	}

	for(int i = 10; i <= 19; i++){
		gamestate[i].isHard = false;
	}
	gamestate[31].isBusted = true;

	for (int i = 0; i < 10; i++){
		gamestate[i].value = i+1;
		gamestate[i+10].value = gamestate[i+20].value = i+11;
	}

	gamestate[0].value = gamestate[31].value = 0;
	gamestate[30].value = 21;
	
	gamestate[0].connect(0, &gamestate[10]);
	gamestate[0].connect(1, &gamestate[1]);
	gamestate[0].connect(2, &gamestate[2]);
	gamestate[0].connect(3, &gamestate[3]);
	gamestate[0].connect(4, &gamestate[4]);
	gamestate[0].connect(5, &gamestate[5]);
	gamestate[0].connect(6, &gamestate[6]);
	gamestate[0].connect(7, &gamestate[7]);
	gamestate[0].connect(8, &gamestate[8]);
	gamestate[0].connect(9, &gamestate[9]);

	Node* next = nullptr;
	bool under11;
	bool soft;
	for(int i = 0; i < 10; i++){
		for(int j = 1; j < 30; j++){
			under11 = (1 <= j && j <= 9);
			soft = (10 <= j && j <= 19);
			if(i != 0){
				if(under11){
					if(i+j+2 <= 10){
						next = &gamestate[i+j+1];
					}else{
						next = &gamestate[i+j+11];
					}
				}else if(soft){
					if(i+j+2 != 21){
						next = &gamestate[i+j+1];
					}else{
						next = &gamestate[30];
					}
				}else{
					if(i+j-8 > 21){
						next = &gamestate[31];
					}else{
						next = &gamestate[i+j+1];
					}
				}
			}else{ // i == 0
				if(j%10 == 9){
					next = &gamestate[30];
				}else if(under11){
					next = &gamestate[j+11];
				}else{
					next = &gamestate[j+1];
				}
			}
			
			gamestate[j].connect(i, next);
		}
	}
}


//print functions
void Blackjack::printTableHeader(int offset = 1){
	for(int i = 0; i < offset + 1; i++){
		std::cout << "\t";
	}
	
	std::cout << "A\t";
	for(int i = 2; i <= 9; i++){
		std::cout << i << "\t";
	}
	std::cout << "T\n";
	
	int amount = (offset + 10)*8 + 2;
	for(int i = 0; i < amount; i++){
		std::cout << "=";
	}
	std::cout << "\n";
}


void Blackjack::printNextValueTable(){
	printTableHeader();
	for(int i = 0; i < 30; i++){
		gamestate[i].printHardness(" ", true);
		gamestate[i].printValue("\t||\t");
		
		for(int j = 0; j < 10; j++){
			if(gamestate[i].forward[j] != nullptr){
				std::cout << (gamestate[i].forward[j]) -> value << "\t";
			}else{
				std::cout << "NULL\t";
			}
			
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}


void Blackjack::printBackValueTable(){
	for(int i = 0; i < 32; i++){
		gamestate[i].printHardness(" ", true);
		gamestate[i].printValue("\t||\t");
		
		for(auto jt = gamestate[i].backward.begin(); jt != gamestate[i].backward.end(); ++jt){
			std::cout << "(";
			(*jt->fromNode).printHardness("", true);
			(*jt->fromNode).printValue(",");
			std::cout << static_cast<int>(jt->connector) << ")\t";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}


void Blackjack::printArrivalPaths(int index){
	cardSequenceList printThisCardSequenceList = gamestate[index].getArrivalPaths();
	for(auto it = printThisCardSequenceList.begin(); it != printThisCardSequenceList.end(); ++it){
		cardSequence printThisCardSequence = *it;
		std::cout << "(";
		for(auto jt = printThisCardSequence.begin(); jt != printThisCardSequence.end();){
			std::cout << static_cast<int>(*jt);
			if(++jt != printThisCardSequence.end()){
				std::cout << ",";
			}
		}
		std::cout << ") ";
	}
	std::cout << "\n\n";
}