
#include "Player_O.h"

void Player_O::move(const std::string& coordinates, Board& board) {
	board.incrementTotalMovesOfBothPlayers();
	board.updateBoard(coordinates[0] - '0', coordinates[2] - '0', symbol);
}

char Player_O::getSymbol() const {
	return symbol;
}

int Player_O::getWins() const {
	return wins;
}

void Player_O::incrementWins(bool notTie) {
	if (notTie) { ++wins; }
}