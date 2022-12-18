
#pragma once

#include <vector>
#include <string>
#include <optional>

class Board
{
public://made public only in folder 'TestTicTacToe' in order to facilitate testing
	size_t  rows;
	size_t columns;
	std::vector<std::vector<char>>board;
	std::vector<int>sumRows;
	std::vector<int>sumColumns;
	int sumDiagonal_UpLeft_DownRight = 0;
	int sumDiagonal_UpRight_DownLeft = 0;
	int totalMovesOfBothPlayers = 0;

public:
	Board(size_t rows = 3, size_t columns = 3);

	void displayBoard() const;
	void updateBoard(size_t row, size_t column, char symbol);
	void incrementTotalMovesOfBothPlayers();

	bool isValidInput(const std::string& input) const;
	std::optional<std::string> checkForEndOfRoundConditions(char symbol) const;

	size_t getTotalRows() const;
	size_t getTotalColumns() const;
	int getTotalMovesOfBothPlayers() const;
	bool pointIsEmpty(size_t row, size_t column) const;

};


