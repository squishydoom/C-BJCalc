#pragma once

#include <list>

enum class cardValue{
	NONE = 0,
	ACE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN
};

typedef std::list<cardValue> cardSequence;
typedef std::list<cardSequence> cardSequenceList;