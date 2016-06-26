#ifndef H_NODE
#define H_NODE

#include "BaseTypes.h"
#include <string>

//In comments: <> enclose vectors, () enclose sequences, {} enclose Combinations, and [] enclose lists.

class Node;
struct arrival{
	Node* fromNode;
	cardValue connector;
	
	arrival(int, Node*);
};
arrival::arrival(int connector, Node* fromNode) : connector(static_cast<cardValue>(connector)), fromNode(fromNode) {}


//A class that stores info about each state in the game of blackjack. There will be 32 of them linked together and they will be placed in an array.
//[0] <-> No cards
//[1-9] <-> Hand Values: 2-10
//[10-19] <-> Hand Values: Soft 11-Soft 20
//[11-29] Hand Values: Hard 11-Hard 20
//[30] <-> Hand Value :21
//[31] <-> Busted
//They are ordered in this way to make initialization easy.
class Node{
  public:
	Node* forward[10];							//An array of pointers to the nodes that can be reached from the current node with a given card. Ace <-> forward[0]. Card Valued i <-> forward[i].
	std::list<arrival> backward;						//arrivals contain both the address of the node that connects to the current node with their forward pointers and which Card Value created that connection.
	cardSequenceList arrivalPaths;				//A list of all sequences of Card Values that will end at this node.
	
	bool isHard;
	bool isBusted;
	int value;									//The blackjack value of the node (0, 2-21, or 0 for busted).
	int position;								//The index of the Node in the array it will be placed in.
	
	Node();
	
	void connect(int, Node*);					//Creates both the forward pointer for the current node to a target node, and the backward pointer in the target node to the current node.
	void disconnect(int);						//Undoes the previous function.
	cardSequenceList getArrivalPaths(void); 	//Reads out the arrivalPaths variable or recursively generates all sequences to this node while memoizing results in the arrivalPaths variable if it hasn't been done yet.
	
	//print functions
	void printValue(std::string);
	void printPosition(std::string);
	void printHardness(std::string, bool);
};

#endif