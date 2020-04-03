#include <iostream>
#include "Board.h"
#include "Computer.h"
#include "time.h"
#include <chrono>


using namespace std;
using namespace chrono;

double inputTimeSeconds;
int inputDepth;
high_resolution_clock::time_point startTime;

Board board;

void playConsole();
char getCurrentSymbol(int current);
void run();



int main(int argc, const char* argv[]) {

	cout << "Time: ";
	cin >> inputTimeSeconds;

	cout << "Depth: ";
	cin >> inputDepth;

	board.clear();
	run();
	return 0;
}


void playConsole() {
	board.clear();
	Computer computer;
	bool flag = true;
	int current = 1;
	int x = -1, y = -1;
	vector<int> v;
	int playerChoice;

	cout << "Please choose 'X' or 'O' to play.\nEnter 1 to choose 'X', 2 to choose 'O': " << endl;
	cin >> playerChoice;
	while (playerChoice != 1 && playerChoice != 2) {
		cout << "Incorrect choice! Enter your choice again. " << endl;
		cout << "Enter 1 to choose 'X', 2 to choose 'O': " << endl;
		cin >> playerChoice;
		if (playerChoice == 1 || playerChoice == 2) break;
	}

	if (playerChoice == 1) {
		board.setPlayerSymbol('X');
		board.setComputerSymbol('O');
	}
	else {
		board.setPlayerSymbol('O');
		board.setComputerSymbol('X');
	}
	//option for player to go first
	cout << "You play as " << board.getPlayerSymbol() << ". Let's start!" << endl;
	cout << "Do you want to go first? y/n" << endl;
	char playerGoFirst;
	cin >> playerGoFirst;

	if (playerGoFirst == 'Y' || playerGoFirst == 'y') {
		current = 1;
		cout << "OK. You go first!" << endl;
	}
	else {
		cout << "OK. I go first!" << endl;
		current = 2;
	}

	board.print();
	while (flag) {
		cout << endl;
		if (current == 1) {
			cout << "Your turn. (" << getCurrentSymbol(current) << " )" << endl;
			cout << "Enter X coordinate of your move: ";
			cin >> x;
			cout << "Enter Y coordinate of your move: ";
			cin >> y;
		}
		else {
			startTime = high_resolution_clock::now();
			v = computer.nextMoveAlphaBeta(board, inputDepth, startTime, inputTimeSeconds);
			x = v[0];
			y = v[1];
		}

		if (!board.checkEmpty(x, y)) {
			cout << endl << "Not a legal move. Try again!" << endl;
			continue;
		}
		else {

			board.setValue(x, y, getCurrentSymbol(current));
			board.print();
			if (current == 1) {
				cout << "Your move is : (" << x << ", " << y << ") " << endl;
			}
			else {
				cout << "My move is : (" << x << ", " << y << ") " << endl;
			}
		}

		if (board.win(x, y)) {
			board.print();
			if (current == 1) {
				cout << "CONGRATULATIONS! YOU WON!" << endl;
			}
			else {
				cout << "I WON!!!" << endl;
			}
			break;
		}
		else if (board.draw()) {
			board.print();
			cout << "Draw game!" << endl;
			break;
		}
		else {
			current = 3 - current;
		}
	}
}


char getCurrentSymbol(int current) {
	if (current == 1) {
		return board.getPlayerSymbol();
	}
	else {
		return board.getComputerSymbol();
	}
}


void run() {
	bool flag = true;
	char x;
	while (flag) {
		playConsole();
		cout << "Do you want to play another game? y/n" << endl;
		cin >> x;
		if (x == 'N' || x == 'n') {
			flag = false;
		}
		else {
			cout << "------------------------------------------------------" << endl;
		}
	}
}

