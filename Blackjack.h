#include "Node.cpp"

//A class that contains all the nodes and performs computations with them.
class Blackjack{
  public:
	Node gamestate[32];
	
	Blackjack();
	
	//print functions
	void printTableHeader(int);
	void printNextValueTable(void);
	void printBackValueTable(void);
	void printArrivalPaths(int);
};