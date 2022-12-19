
#include "Player_X.h"

void Player_X::move(const std::string& coordinates, Board& board) {
	board.incrementTotalMovesOfBothPlayers();
	board.updateBoard(coordinates[0]-'0', coordinates[2]-'0', symbol);
}

char Player_X::getSymbol() const {
	return symbol;
}

int Player_X::getWins() const {
	return wins;
}

void Player_X::incrementWins(bool notTie) {
	if (notTie) { ++wins; }
}