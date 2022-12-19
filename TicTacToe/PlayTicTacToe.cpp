
#include "PlayTicTacToe.h"

void PlayTicTacToe::start() {
	
	board.displayBoard();
	player->incrementRoundsPlayed();

	while (true) {

		std::cout << "Player " << player->getSymbol() << " enter coordinates! Format: digit:digit\n";
		std::string coordinates = player->enterCoordinates(board);

		player->move(coordinates, board);
		board.displayBoard();

		std::optional<std::string> checkForEndOfRound = board.checkForEndOfRoundConditions(player->getSymbol());

		if (checkForEndOfRound.has_value()) {

			player->incrementWins(!checkForEndOfRound.value().ends_with("tie!"));
			player->incrementTies(checkForEndOfRound.value().ends_with("tie!"));

			std::cout << checkForEndOfRound.value() << '\n' << '\n';
			displayStatistics();

			std::cout << "Press 'enter' to start a new round.\n";
			std::cout << "Press any other key to exit.\n";
			if (int ascii = _getch(); ascii != ASCII_CARRIAGE_RETURN) { std::cout << "Game exited.\n"; break; }

			board = Board();
			board.displayBoard();
			player->incrementRoundsPlayed();
			std::cout << "A new round is started.\n\n";
		}

		indexPlayers = (indexPlayers + 1) % 2;
		player = players[indexPlayers];
	}
}

void PlayTicTacToe::displayStatistics() const {
	std::cout << std::format("---- Total Rounds Played: {} ----\n", player->getRoundsPlayed());
	std::cout << "Player " << players[0]->getSymbol() << " wins: " << players[0]->getWins() << '\n';
	std::cout << "Player " << players[1]->getSymbol() << " wins: " << players[1]->getWins() << '\n';
	std::cout << "Ties: " << player->getTies() << '\n' << '\n';
}