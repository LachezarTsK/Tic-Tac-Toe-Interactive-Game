
#include "pch.h"

#include "Board.cpp"
#include "Player.cpp"
#include "Player_X.cpp"
#include "Player_O.cpp"
#include "PlayTicTacToe.cpp"

/*
TEST 5, 6, 7, 11 which do not require interactive input during these tests,
have also their equvalents in TEST 8, 9, 10, 12 which do require
interactive input during the test. Optionally, one of these groups of tests
could be disabled. Both test groups are enabled by default for demonstration purposes.
*/


//==================== TEST 1 =============================
TEST(EndOfRound, WinPlayer_X) {

	PlayTicTacToe play;
	play.player = play.player_X;
	std::string expected("Player X won this round!");

	//---- Horizontal ----
	for (size_t r = 0; r < play.board.getTotalRows(); ++r) {

		play.board = Board();
		for (size_t c = 0; c < play.board.getTotalColumns(); ++c) {
			std::string coordinates = std::to_string(r + 1) + ":" + std::to_string(c + 1);
			play.player->move(coordinates, play.board);
		}
		EXPECT_EQ(expected, play.board.checkForEndOfRoundConditions(play.player->getSymbol()).value());
	}

	//---- Vertical ----
	for (size_t c = 0; c < play.board.getTotalColumns(); ++c) {

		play.board = Board();
		for (size_t r = 0; r < play.board.getTotalRows(); ++r) {
			std::string coordinates = std::to_string(r + 1) + ":" + std::to_string(c + 1);
			play.player->move(coordinates, play.board);
		}
		EXPECT_EQ(expected, play.board.checkForEndOfRoundConditions(play.player->getSymbol()).value());
	}

	//---- Diagonal UpLeft DownRight ----
	//assuming square board
	play.board = Board();
	for (size_t r = 0; r < play.board.getTotalRows(); ++r) {
		std::string coordinates = std::to_string(r + 1) + ":" + std::to_string(r + 1);
		play.player->move(coordinates, play.board);
	}
	EXPECT_EQ(expected, play.board.checkForEndOfRoundConditions(play.player->getSymbol()).value());

	//---- UpRight DownLeft ----
	//assuming square board
	play.board = Board();
	size_t c = play.board.getTotalColumns() - 1;
	for (size_t r = 0; r < play.board.getTotalRows(); ++r) {
		std::string coordinates = std::to_string(r + 1) + ":" + std::to_string(c + 1);
		play.player->move(coordinates, play.board);
		--c;
	}
	EXPECT_EQ(expected, play.board.checkForEndOfRoundConditions(play.player->getSymbol()).value());
}


//==================== TEST 2 =============================
TEST(EndOfRound, WinPlayer_O) {

	PlayTicTacToe play;
	play.player = play.player_O;
	std::string expected("Player O won this round!");

	//---- Horizontal ----
	for (size_t r = 0; r < play.board.getTotalRows(); ++r) {

		play.board = Board();
		for (size_t c = 0; c < play.board.getTotalColumns(); ++c) {
			std::string coordinates = std::to_string(r + 1) + ":" + std::to_string(c + 1);
			play.player->move(coordinates, play.board);
		}
		EXPECT_EQ(expected, play.board.checkForEndOfRoundConditions(play.player->getSymbol()).value());
	}

	//---- Vertical ----
	for (size_t c = 0; c < play.board.getTotalColumns(); ++c) {

		play.board = Board();
		for (size_t r = 0; r < play.board.getTotalRows(); ++r) {
			std::string coordinates = std::to_string(r + 1) + ":" + std::to_string(c + 1);
			play.player->move(coordinates, play.board);
		}
		EXPECT_EQ(expected, play.board.checkForEndOfRoundConditions(play.player->getSymbol()).value());
	}

	//---- Diagonal UpLeft DownRight ----
	//assuming square board
	play.board = Board();
	for (size_t r = 0; r < play.board.getTotalRows(); ++r) {
		std::string coordinates = std::to_string(r + 1) + ":" + std::to_string(r + 1);
		play.player->move(coordinates, play.board);
	}
	EXPECT_EQ(expected, play.board.checkForEndOfRoundConditions(play.player->getSymbol()).value());

	//---- UpRight DownLeft ----
	//assuming square board
	play.board = Board();
	size_t c = play.board.getTotalColumns() - 1;
	for (size_t r = 0; r < play.board.getTotalRows(); ++r) {
		std::string coordinates = std::to_string(r + 1) + ":" + std::to_string(c + 1);
		play.player->move(coordinates, play.board);
		--c;
	}
	EXPECT_EQ(expected, play.board.checkForEndOfRoundConditions(play.player->getSymbol()).value());
}


//==================== TEST 3 =============================
TEST(EndOfRound, Tie) {

	PlayTicTacToe play;
	size_t indexPlayers = 0;
	play.player = play.players[indexPlayers];
	std::string expected("This round ends in a tie!");

	for (size_t r = 0; r < play.board.getTotalRows(); ++r) {

		for (size_t c = 0; c < play.board.getTotalColumns(); ++c) {
			std::string coordinates = std::to_string(r + 1) + ":" + std::to_string(c + 1);
			play.player->move(coordinates, play.board);
			indexPlayers = (indexPlayers + 1) % 2;
			play.player = play.players[indexPlayers];
		}

		if (r == play.board.getTotalRows() - 2) {
			indexPlayers = (indexPlayers + 1) % 2;
			play.player = play.players[indexPlayers];
		}
	}

	EXPECT_EQ(expected, play.board.checkForEndOfRoundConditions(play.player->getSymbol()).value());
}


//==================== TEST 4 =============================
TEST(EndOfRound, NoConditionsForEndOfRound) {

	PlayTicTacToe play;
	size_t indexPlayers = 0;
	play.player = play.players[indexPlayers];

	//Empty board
	EXPECT_FALSE(play.board.checkForEndOfRoundConditions(play.player->getSymbol()).has_value());

	for (size_t r = 0; r < play.board.getTotalRows() - 1; ++r) {
		for (size_t c = 0; c < play.board.getTotalColumns(); ++c) {
			std::string coordinates = std::to_string(r + 1) + ":" + std::to_string(c + 1);
			play.player->move(coordinates, play.board);
			indexPlayers = (indexPlayers + 1) % 2;
			play.player = play.players[indexPlayers];
		}
	}

	//Partially filled board, without a winning combination
	EXPECT_FALSE(play.board.checkForEndOfRoundConditions(play.player->getSymbol()).has_value());
}


//==================== TEST 5 =============================
//Interactive Input Test Equivalent: TEST 8
TEST(TestInvalidMove, InvalidInputFormat_PredefinedInput/* not in the format: digit:digit */) {

	testing::internal::CaptureStdout();
	PlayTicTacToe play;
	play.player = play.player_X;

	std::string randomInvalidInput("qxek1:2");
	std::string randomValidInput("1:2");
	std::string input(randomInvalidInput + '\n' + randomValidInput);
	std::string coordinates = play.player->enterCoordinates(play.board, input);
	std::string output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(output, "Invalid Input\n");

	//the input loop can be exited only with valid coordinates
	EXPECT_TRUE(play.board.isValidInput(coordinates));
}


//==================== TEST 6 =============================
//Interactive Input Test Equivalent: TEST 9
TEST(TestInvalidMove, MoveOusideTheBoard_PredefinedInput) {

	testing::internal::CaptureStdout();
	PlayTicTacToe play;
	play.player = play.player_X;

	std::string randomInvalidInput("8:9");
	std::string randomValidInput("1:2");
	std::string input(randomInvalidInput + '\n' + randomValidInput);
	std::string coordinates = play.player->enterCoordinates(play.board, input);
	std::string output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(output, "Invalid Input\n");

	//the input loop can be exited only with valid coordinates
	EXPECT_TRUE(play.board.isValidInput(coordinates));
}


//==================== TEST 7 =============================
//Interactive Input Test Equivalent: TEST 10
TEST(TestInvalidMove, MoveToAlreadyOccupiedPoint_PredefinedInput) {

	testing::internal::CaptureStdout();
	PlayTicTacToe play;
	play.player = play.player_X;

	std::string inputFirst("1:2");
	std::string coordinatesFirst = play.player->enterCoordinates(play.board, inputFirst);

	//the method is called to record the move on the board for the first player
	play.player->move(coordinatesFirst, play.board);

	std::string inputToAlreadyMarkedPoint(inputFirst);
	std::string inputToPointNotMarked("2:2");
	std::string input(inputToAlreadyMarkedPoint + '\n' + inputToPointNotMarked);

	play.player = play.player_O;
	std::string coordinatesSecond = play.player->enterCoordinates(play.board, input);
	std::string output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(output, "Invalid Input\n");

	//coordinatesFirst already recorded on the board, therefore 'false'
	EXPECT_FALSE(play.board.isValidInput(coordinatesFirst));

	//the input loop can be exited only with valid coordinates
	//coordinatesSecond not recorded on the board for this test, therefore 'true'
	EXPECT_TRUE(play.board.isValidInput(coordinatesSecond));
}


//==================== TEST 8 =============================
//Interactive Test: requires user input during the test
//Predefined Input Test Equivalent: TEST 5
TEST(TestInvalidMove, InvalidInputFormat_InteractiveInput/* not in the format: digit:digit */) {

	std::cout << "\n----- Interactive Test: requires input during the test. -----\n";
	std::cout << "Enter some arbitrary coordinates not in the format: digit:digit. Example: dghwj1289\n";
	std::cout << "Then enter other coordinates within the speficied input format, in order to escape the infinite loop. Example: 2:3\n";

	testing::internal::CaptureStdout();
	PlayTicTacToe play;
	play.player = play.player_X;
	std::string coordinates = play.player->enterCoordinates(play.board);
	std::string output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(output, "Invalid Input\n");

	//the input loop can be exited only with valid coordinates
	EXPECT_TRUE(play.board.isValidInput(coordinates));
}


//==================== TEST 9 =============================
//Interactive Test: requires user input during the test
//Predefined Input Test Equivalent: TEST 6
TEST(TestInvalidMove, MoveOusideTheBoard_InteractiveInput) {

	std::cout << "\n----- Interactive Test: requires input during the test. -----\n";
	std::cout << "Enter some arbitrary coordinates outside the board limits. Example: 8:9\n";
	std::cout << "Then enter other coordinates within the board limits in order to escape the infinite loop. Example: 2:2\n";

	testing::internal::CaptureStdout();
	PlayTicTacToe play;
	play.player = play.player_X;
	std::string coordinates = play.player->enterCoordinates(play.board);
	std::string output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(output, "Invalid Input\n");

	//the input loop can be exited only with valid coordinates
	EXPECT_TRUE(play.board.isValidInput(coordinates));
}


//==================== TEST 10 =============================
//Interactive Test: requires user input during the test
//Predefined Input Test Equivalent: TEST 7
TEST(TestInvalidMove, MoveToAlreadyOccupiedPoint_InteractiveInput) {

	std::cout << "\n----- Interactive Test: requires input during the test. -----\n";
	std::cout << "First Player: Enter some arbitrary coordinates within the board limits. Example: 1:1\n";
	std::cout << "Second Player: Then enter the same coordinates as for the previous player. Example: 1:1\n";
	std::cout << "Then enter different coordinates within the board limits in order to escape the infinite loop. Example: 1:2\n";

	testing::internal::CaptureStdout();
	PlayTicTacToe play;
	play.player = play.player_X;
	std::string coordinatesFirst = play.player->enterCoordinates(play.board);

	//the method is called to record the move on the board for the first player
	play.player->move(coordinatesFirst, play.board);

	play.player = play.player_O;
	std::string coordinatesSecond = play.player->enterCoordinates(play.board);
	std::string output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(output, "Invalid Input\n");

	//coordinatesFirst already recorded on the board, therefore 'false'
	EXPECT_FALSE(play.board.isValidInput(coordinatesFirst));

	//the input loop can be exited only with valid coordinates
	//coordinatesSecond not recorded on the board for this test, therefore 'true'
	EXPECT_TRUE(play.board.isValidInput(coordinatesSecond));
}


//==================== TEST 11 =============================
//Interactive Input Test Equivalent: TEST 12
TEST(TestValidMove, ValidInputFormat_PredefinedInput/*format: digit:digit */) {

	testing::internal::CaptureStdout();
	PlayTicTacToe play;
	play.player = play.player_X;

	std::string randomValidInput("1:2");
	std::string input(randomValidInput);
	std::string coordinates = play.player->enterCoordinates(play.board, input);
	std::string output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(output, "");//there must be no alert "Invalid Input\n"

	//the input loop can be exited only with valid coordinates
	EXPECT_TRUE(play.board.isValidInput(coordinates));
}


//==================== TEST 12 =============================
//Interactive Test: requires user input during the test
//Predefined Input Test Equivalent: TEST 11
TEST(TestValidMove, ValidInputFormat_InteractiveInput/*format: digit:digit*/) {

	std::cout << "\n----- Interactive Test: requires input during the test. -----\n";
	std::cout << "Enter some arbitrary coordinates in the format: digit:digit. Example: 2:3\n";

	testing::internal::CaptureStdout();
	PlayTicTacToe play;
	play.player = play.player_X;
	std::string coordinates = play.player->enterCoordinates(play.board);
	std::string output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(output, "");//there must be no alert "Invalid Input\n"

	//the input loop can be exited only with valid coordinates
	EXPECT_TRUE(play.board.isValidInput(coordinates));
}


//==================== TEST 13 =============================
TEST(CheckForCorrectnessOfSymbolsOnBoard, SymbolPlayer_X) {

	PlayTicTacToe play;
	play.player = play.player_X;

	for (size_t r = 0; r < play.board.getTotalRows(); ++r) {
		for (size_t c = 0; c < play.board.getTotalColumns(); ++c) {
			std::string coordinates = std::to_string(r + 1) + ":" + std::to_string(c + 1);
			play.player->move(coordinates, play.board);
			EXPECT_EQ('X', play.board.board[r][c]);
		}
	}
}


//==================== TEST 14 =============================
TEST(CheckForCorrectnessOfSymbolsOnBoard, SymbolPlayer_O) {

	PlayTicTacToe play;
	play.player = play.player_O;

	for (size_t r = 0; r < play.board.getTotalRows(); ++r) {
		for (size_t c = 0; c < play.board.getTotalColumns(); ++c) {
			std::string coordinates = std::to_string(r + 1) + ":" + std::to_string(c + 1);
			play.player->move(coordinates, play.board);
			EXPECT_EQ('O', play.board.board[r][c]);
		}
	}
}


//==================== TEST 15 =============================
TEST(CheckForCorrectnessOfSymbolsOnBoard, EmptyPoint) {

	PlayTicTacToe play;
	play.player = play.player_O;

	for (size_t r = 0; r < play.board.getTotalRows(); ++r) {
		for (size_t c = 0; c < play.board.getTotalColumns(); ++c) {
			EXPECT_EQ(' ', play.board.board[r][c]);
		}
	}
}