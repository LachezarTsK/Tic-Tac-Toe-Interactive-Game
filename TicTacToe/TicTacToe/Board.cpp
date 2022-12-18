
#include "Board.h"
#include "Player.h"

#include <format>
#include <string>
#include <memory>
#include <iostream>
#include <optional>

Board::Board(size_t rows, size_t columns) :rows{ rows }, columns{ columns } {
	board.assign(rows, std::vector<char>(columns, ' '));
	sumRows.resize(rows);
	sumColumns.resize(columns);
}

void Board::displayBoard() const {
	system("cls");
	for (size_t row = 0; row < rows; ++row) {
		for (size_t column = 0; column < columns; ++column) {
			char separator = column < columns - 1 ? '|' : '\u0000';
			std::cout << std::format(" {} {}", board[row][column], separator);
		}
		std::cout << "\n-----------\n";
	}
	std::cout << std::endl;
}

/*
Operations '--row' and '--column' are being done since
valid user input for rows/columns is not 0-indexed but starts from 1.
*/
void Board::updateBoard(size_t row, size_t column, char symbol) {
	--row;
	--column;
	board[row][column] = symbol;

	int asciiCodeSymbol = static_cast<int>(symbol);
	sumRows[row] += asciiCodeSymbol;
	sumColumns[column] += asciiCodeSymbol;
	if (row == column) { sumDiagonal_UpLeft_DownRight += asciiCodeSymbol; }
	if (row == getTotalColumns() - 1 - column) { sumDiagonal_UpRight_DownLeft += asciiCodeSymbol; }
}

/*
The check is for 'input[0] - 1' and 'input[2] - 1' since
valid user input for rows/columns is not 0-indexed but starts from 1.
*/
bool Board::isValidInput(const std::string& input) const {
	return input.size() == 3
		&& isdigit(input[0]) && input[0] - 1 - '0' < getTotalRows()
		&& input[1] == ':'
		&& isdigit(input[2]) && input[2] - 1 - '0' < getTotalColumns()
		&& pointIsEmpty(input[0] - 1 - '0', input[2] - 1 - '0');
}

size_t Board::getTotalRows()const {
	return rows;
}

size_t Board::getTotalColumns()const {
	return columns;
}

int Board::getTotalMovesOfBothPlayers() const {
	return totalMovesOfBothPlayers;
}

void Board::incrementTotalMovesOfBothPlayers() {
	++totalMovesOfBothPlayers;
}

bool Board::pointIsEmpty(size_t row, size_t column) const {
	return board[row][column] == ' ';
}

std::optional<std::string> Board::checkForEndOfRoundConditions(char symbol) const {
	int asciiCodeSymbol = static_cast<int>(symbol);

	for (const auto& sum : sumRows) {
		if (sum == asciiCodeSymbol * getTotalRows()) {
			return std::format("Player {} won this round!", symbol);
		}
	}

	for (const auto& sum : sumColumns) {
		if (sum == asciiCodeSymbol * getTotalColumns()) {
			return std::format("Player {} won this round!", symbol);
		}
	}

	if (sumDiagonal_UpLeft_DownRight == asciiCodeSymbol * getTotalRows()) {
		return std::format("Player {} won this round!", symbol);
	}

	if (sumDiagonal_UpRight_DownLeft == asciiCodeSymbol * getTotalRows()) {
		return std::format("Player {} won this round!", symbol);
	}

	if (totalMovesOfBothPlayers == getTotalRows() * getTotalColumns()) {
		return std::format("This round ends in a tie!");
	}
	return std::optional<std::string>{};
}