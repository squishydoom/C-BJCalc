#ifndef H_UTILITY
#define H_UTILITY

#include <list>
#include <utility>
#include <vector>

const std::list<int> factors[22] = {
	{},
	{},
	{2},
	{3},
	{2,2},
	{5},
	{2,3},
	{7},
	{2,2,2},
	{3,3},
	{2,5},
	{11},
	{2,2,3},
	{13},
	{2,7},
	{3,5},
	{2,2,2,2},
	{17},
	{2,3,3},
	{19},
	{2,2,5},
	{3,7}
};

//Useful math functions.
int hashChoose(int, int);		//Generates the index of the array where Choose data be stored.
std::pair<int, int> unhashChoose(int); //Gets the n and k that generated the input index.
std::list<int> factorialFactors(int); 		//List of prime factors in the product n!.
int product(std::list<int>);			//Multiplies out a list of integers.
int combinatorial(std::vector<int>);	//Calculates factorial ratios of the form n! / (i!j!...k!) when input is <n,i,j,...,k>. Defined for when i+j+...+k <= n.

#endif