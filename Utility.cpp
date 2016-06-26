#include "Utility.h"

int hashChoose(int n, int k){
	return (k - 1) + ((n-1)*n)/2;
}

std::pair<int,int> unhashChoose(int index){
	int threshhold = 0;
	for(int depth = 1; true; depth++){
		threshhold = (depth*(depth+1))/2;
		if(threshhold > index){
			depth--;
			threshhold = (depth*(depth+1))/2;
			
			return std::pair<int,int>(depth + 1, index - threshhold + 1);
		}
	}
	
}

std::list<int> factorialFactors(int n){
	std::list<int> returnThis;
	for(int i = 1; i <= n; i++){
		std::list<int> copy = factors[i];
		returnThis.merge(copy);
	}
	return returnThis;
}


int product(std::list<int> listOfInts){
	int p = 1;
	for(auto it = listOfInts.begin(); it != listOfInts.end(); ++it){
		p *= *it;
	}
	return p;
}


int combinatorial(std::vector<int> args){//Computes n choose k, and generalizations as long as the 
	std::list<int> numerator = factorialFactors(args[0]);
	std::list<int> denominator;
	for(int i = 1; i < args.size(); i++){
		denominator.merge(factorialFactors(args[i]));
	}
	for(int i: denominator){//Cancelling out common factors in the denominator.
		for(auto it = numerator.begin(); it != numerator.end(); ++it){
			if(i == *it){
				numerator.erase(it);
				break;
			}
		}
	}
	return product(numerator);
}