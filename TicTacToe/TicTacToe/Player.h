
#pragma once

#include "Board.h"

#include <string>
#include <iostream>

class Player
{
public:
	Player()=default;
	virtual ~Player() = default;
	
	virtual void move(const std::string&, Board& board) = 0;
	virtual char getSymbol() const = 0;
	virtual int getWins() const = 0;
	virtual void incrementWins(bool) = 0;

	inline static int ties = 0;
	inline static int roundsPlayed = 0;

	std::string enterCoordinates(const Board& board) const;
	void incrementTies(bool) const;
	int getTies() const;
	void incrementRoundsPlayed() const;
	int getRoundsPlayed() const;
};

