#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;
bool inGame = true;
int startPieceCount = 4;
int board[14];
bool turn = true, extraTurn = false, inRound = true;

void populate(int piece) {
	for (int i = 0; i < 14; i++) {
		board[i] = piece;
		if (i == 6 || i == 13) {
			board[i] = 0;
		}
	}
}
int getChoice() {
	bool validIn = false;
	int playerPick = 0;
	std::cout << "\nSelect your hole (0-5): \n";
	std::cin >> playerPick;
	while (!validIn) {
		if (std::cin.fail() || playerPick < 0 || playerPick > 5 || board[playerPick] == 0) {
			std::cout << "Please enter a valid choice: \n";
			std::cin.clear();
			std::cin.ignore();
			std::cin >> playerPick;
		}
		else {
			validIn = true;
		}
	}
	return playerPick;
}

bool isCapture(int choice) {
	if (turn) {
		if (board[choice]==0 && choice >= 0 && choice <6) {
			return true;
		}
	}
	else {
		if (board[choice] == 0 && choice >= 7 && choice < 13) {
			return true;
		}
	}
	return false;
}
void capture(int choice) {
	int clearedHole = 12 - choice;
	if (turn) {
		board[6] += board[clearedHole]+1;
		board[clearedHole] = 0;
		board[choice] = -1;
	}
	else {
		board[13] += board[clearedHole]+1;
		board[clearedHole] = 0;
		board[choice] = -1;
	}
}
bool onSide(int choice) {
	if (turn) {
		if (choice == 6) {
			return true;
		}
	}
	else {
		if (choice == 13) {
			return true;
		}
	}
	return false;
}
void drawBoard() {
	/*
	/ \[4][4][4][4][4][4]/ \
	|0|                  |0|
	\ /[4][4][4][4][4][4]\ /
	*/
	std::cout << "\n/ \\";
	for (int j = 12; j > 6; j--) {
		std::cout << "[" << board[j] << "]";
	}
	std::cout << "/ \\";
	std::cout << "\n|" << board[13] << "|                  |" << board[6] << "|\n";
	std::cout << "\\ /";
	for (int i = 0; i < 6; i++) {
		std::cout << "[" << board[i] << "]";
	}
	std::cout << "\\ /\n";

}
bool isDone() {
	bool doneCheck = true;
	if (turn) {
		for (int i = 0; i < 6; i++) {
			if (board[i] != 0) {
				doneCheck = false;
			}
		}
	}
	else {
		for (int j = 12; j > 6; j--) {
			if (board[j] != 0) {
				doneCheck = false;
			}
		}
	}
	return doneCheck;
}
void dropIn(int choice) {
	int pieceCount = board[choice];
	board[choice] = 0;
	choice++;
	for (int i = 0; i < pieceCount; i++) {
		if (i == pieceCount - 1) {
			if (isCapture(choice)) {
				capture(choice);
			}
			if (onSide(choice)) {
				extraTurn = true;
			}
		}
		board[choice]++;
		choice++;
		if (choice >= 14) {
			choice = 0;
		}
	}
}
void cleanBoard() {
	for (int i = 0; i < 6; i++) {
		board[6] += board[i];
		board[i] = 0;
	}
	for (int j = 12; j > 6; j--) {
		board[13] += board[j];
		board[j] = 0;
	}
}
bool isWin() {
	if (board[6] > board[13]) {
		return true;
	}
	else {
		return false;
	}
}
int main() {
	srand(time(0));
	string cont = "nope";
	while (inGame) {
		int playerChoice = 0, botChoice = 7;
		bool valChoice = false;
		populate(startPieceCount);
		inRound = true;
		while (inRound) {
			drawBoard();
			if (turn) {
				playerChoice = getChoice();
				dropIn(playerChoice);
			}
			else {
				while (!valChoice) {
					botChoice = rand() % 6 + 7;
					if (board[botChoice] != 0) {
						valChoice = true;
					}
				}
				valChoice = false;
				std::cout << "\nThe bot picks hole " << botChoice << ".\n";
				dropIn(botChoice);
			}

			if (extraTurn) {
				extraTurn = false;
			}
			else {
				turn = !turn;
			}
			if (isDone()) {
				inRound = false;
				cleanBoard();
				drawBoard();
				if (isWin()) {
					std::cout << "\nYOU WIN!!!!";
				}
				else {
					std::cout << "\nlmao rip";
				}
			}
		}
		std::cout << "\nWould you like to continue? (y/n): \n";
		std::cin >> cont;
		if (cont.at(0) == 'n' || cont.at(0) == 'N') {
			inGame = false;
		}
	}
	return 0;
}