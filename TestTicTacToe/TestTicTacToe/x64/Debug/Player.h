
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

	/*
	Method 'std::string enterCoordinates(const Board& board, const std::string& input) const'
	overloads the original method 'std::string enterCoordinates(const Board& board) const'
	only in folder 'TestTicTacToe' in order to facilitate testing without interactive input
	during the tests.

	Actually, for demonstration purposes, file 'test.cpp' contains tests with 
	both methods: one test group requiring interactive input during the test and 
	another test group taking a predefined input. Optionally, one of these groups of tests
    can be disabled. 
	*/
	std::string enterCoordinates(const Board& board, const std::string& input) const;

	void incrementTies(bool) const;
	int getTies() const;
	void incrementRoundsPlayed() const;
	int getRoundsPlayed() const;
};

