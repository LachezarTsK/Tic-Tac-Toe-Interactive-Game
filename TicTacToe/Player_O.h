
#pragma once

#include "Player.h"

class Player_O : public Player
{
	inline static const char symbol = 'O';
	int wins = 0;

public:
	void move(const std::string& coordinates, Board& board) override;
	char getSymbol() const override;
	int getWins() const override;
	void incrementWins(bool) override;
};

