
#include "Player.h"
#include "Board.h"

std::string Player::enterCoordinates(const Board& board) const {
	std::string coordinates;
	while (true) {
		std::cin >> coordinates;
		if (!board.isValidInput(coordinates)) { std::cout << "Invalid Input\n"; }
		else { break; }
	}
	return coordinates;
}

std::string Player::enterCoordinates(const Board& board, const std::string& input) const {
	std::stringstream stream(input);
	std::string coordinates;
	while (true) {
		std::getline(stream, coordinates, '\n');
		if (!board.isValidInput(coordinates)) { std::cout << "Invalid Input\n"; }
		else { break; }
	}
	return coordinates;
}

void Player::incrementTies(bool isTie) const {
	if (isTie) { ++ties; }
}

int Player::getTies() const {
	return ties;
}

void Player::incrementRoundsPlayed() const {
	++roundsPlayed;
}

int Player::getRoundsPlayed() const {
	return roundsPlayed;
}