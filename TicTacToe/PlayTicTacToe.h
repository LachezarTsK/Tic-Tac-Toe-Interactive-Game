#pragma once

#include <iostream>
#include <array>
#include <string>
#include <optional>
#include <format>
#include <conio.h>


#include "Board.h"
#include "Player.h"
#include "Player_X.h"
#include "Player_O.h"

class PlayTicTacToe
{
	inline static const int ASCII_CARRIAGE_RETURN = 13;

	std::shared_ptr<Player> player_X = std::make_shared<Player_X>();
	std::shared_ptr<Player> player_O = std::make_shared<Player_O>();
	std::array<std::shared_ptr<Player>, 2> players{ player_X, player_O };

	size_t indexPlayers = 0;
	std::shared_ptr<Player> player = players[indexPlayers];
	
	Board board;

public:
	void start();
	void displayStatistics() const;
};

