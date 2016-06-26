#include "Node.h"

Node::Node(void):
	forward{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
	isHard(true),
	isBusted(false),
	value(0),
	position(0) {}


//Creates the both the forward pointer for the current node to a target node, and the arrival in the target node from the current node.	
void Node::connect(int index, Node* next){
	forward[index] = next;
	next->backward.push_back(arrival(index + 1, this));
}

void Node::disconnect(int index){
	Node* nodeToCheck = forward[index];
	if(nodeToCheck != nullptr){
		forward[index] = nullptr;
		for(auto it = nodeToCheck->backward.begin(); it != nodeToCheck->backward.end(); ++it){
			if (it->fromNode == this){
				nodeToCheck->backward.erase(it);
				return;
			}
		}
	}
}


//Recursively generates all sequences to this node while memoizing results.
cardSequenceList Node::getArrivalPaths(){
	cardSequenceList returnList;
	if(!arrivalPaths.empty()){
		returnList = arrivalPaths;
	}else{
		for(auto it = backward.begin(); it != backward.end(); ++it){
			cardSequenceList pathsToPrevious = it->fromNode->getArrivalPaths();
			cardValue addedToAllPreviousPaths = it->connector;
			
			if(!pathsToPrevious.empty()){
				for(auto jt = pathsToPrevious.begin(); jt != pathsToPrevious.end(); ++jt){
					cardSequence addThisToReturnList(*jt);
					addThisToReturnList.push_back(addedToAllPreviousPaths);
					returnList.push_back(addThisToReturnList);
				}
			}else{
				cardSequence addThisToReturnList;
				addThisToReturnList.push_back(addedToAllPreviousPaths);
				returnList.push_back(addThisToReturnList);
			}
		}
		arrivalPaths = returnList;
	}
	return returnList;
}


//print functions
void Node::printValue(std::string after){
	if(!isBusted){
		std::cout << value;
	}else{
		std::cout << "Busted";
	}
	std::cout << after;
}


void Node::printPosition(std::string after){
	std::cout << position << after;
}


void Node::printHardness(std::string after, bool SHORT = false){
	std::string s;
	if(!SHORT){
		if (isHard){
			s = "Hard";
		}else{
			s = "Soft";
		}
	}else{
		if (isHard){
			s = "h";
		}else{
			s = "s";
		}
	}
	
	if (isBusted){
		s = "";
	}
	std::cout << s << after;
}