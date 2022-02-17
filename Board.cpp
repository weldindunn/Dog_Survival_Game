/*
 * Board.cpp
 *
 *  Created on: Sep 13, 2021
 *  Author: Weldin Dunn
 */

#include "Board.hpp"
#include <iostream>

using namespace std;

Board::Board(char diff, bool d) {
	level = diff;
	debug = d;
	wallStrength = 6;
	InitAll();
}

Board::Board(bool d) {
	level = 'e';
	debug = d;
	wallStrength = 6;
	InitAll();
}

Board::Board(char diff, string name, bool d) {
	level = diff;
	debug = d;
	mydog.name = name;
	wallStrength = 6;
	InitAll();
}

void Board::InitAll() {
	bool keepPlaying = true;
	while (keepPlaying) {
		cout << "What level of difficulty do you want (e, m, or h)?" << endl;
		char c;
		cin >> c;
		level = c;
		startx = rand() % (size - 1) + 1;
		starty = 0;
		endx = rand() % (size - 2) + 1;
		endy = size-1;
		mydog.x = startx;
		mydog.y = starty + 1;
		boardConfig();
		addFood();
		addTraps();
		printBoard();
		mydog.printDog();
		playGame();
		cout << "Play again? (y/n)" << endl;
		string s = "no";
		cin >> s;
		if (s == "yes" || s == "Yes" || s == "Y" || s == "y") {
			keepPlaying = true;
			mydog.reset();
		}
		else {
			cout << "Thanks for playing!" << endl;
			keepPlaying = false;
		}
	}
}

void Board::playGame() {
	bool play = true;
	while (play) {
		cout << "Move (u, d, l, r) " << endl;
		char c;
		cin >> c;
		play = moveDog(c);
		if (play) {
			printBoard();
		}
	}
}

void Board::addFood() {
	// (5 pts) code for the addFood method goes here

	int numFood;
	if (level == 'e') {
		numFood = size;
	} else if (level == 'm') {
		numFood = size-2;
	} else {
		numFood = size-4;
	}

	for (int i = 0; i < numFood;) {
		int foodLoc = rand()%((size-2)*(size-2)) + 20; //Creates a random number less than the size of the area of the board (minus the sides)

		if (board[foodLoc/18][foodLoc%18] == 'T' || board[foodLoc/18][foodLoc%18] == '|' || board[foodLoc/18][foodLoc%18] == '_' || board[foodLoc/18][foodLoc%18] == 'D' || board[foodLoc/18][foodLoc%18] == '>') {
			//Start the loop again
		} else {
			board[foodLoc/18][foodLoc%18] = 'F';
			i++;
		}
	}
}
void Board::addTraps() {
	// (5 pts) code for the addTraps method goes here
	int numTraps;
	if (level == 'e') {
		numTraps = 6;
	} else if (level == 'm') {
		numTraps = 8;
	} else {
		numTraps = 10;
	}

	for (int i = 0; i < numTraps;) {
		int trapLoc = rand()%((size-2)*(size-2)) + 20;

		if (board[trapLoc/18][trapLoc%18] == 'F' || board[trapLoc/18][trapLoc%18] == '|' || board[trapLoc/18][trapLoc%18] == '_') {
			//Start the loop again
		} else {
			board[trapLoc/18][trapLoc%18] = 'T';
			i++;
		}
	}
}
void Board::boardConfig() {
	// (8 pts) code for the boardConfig method goes here

	//Creates blank grid
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			if (y==0 || y==19) { //If at the top or bottom of grid
				board[y][x] = '_';
			} else if (x==0 || x==19) { //If at left or right of grid
				board[y][x] = '|';
			} else {
				board[y][x] = ' ';
			}
		}
	}

	//Determines the wall's length based on difficulty
	int wallLength;
	if (level == 'e') {
		wallLength = 9;
	} else if (level == 'm') {
		wallLength = 13;
	} else {
		wallLength = 16;
	}

	//Adds 10 walls
	for (int i = 0; i < 10; i++) { //Loops through ten walls
		int direction = rand()%2; //Whether going vertical (1) or horizontal (0)
		int row = rand()%8 * 2 + 2; //Chooses a random row or column, even numbers only
		int slabCounter = 0; //How many slabs each wall has

		for (int j = 1; j < size-1; j++) { //Builds each individual slab of wall
			int buildSlab = rand()%3; //Whether should build a slab or not
			if (direction) {
				if (buildSlab) {
					board[j][row] = '|';
					slabCounter++;
				}
			} else {
				if (buildSlab) {
					board[row][j] = '_';
					slabCounter++;
				}
			}
			if (slabCounter >= wallLength) {
				break;
			}
		}
	}

	board[startx][starty] = '>'; //Places entrance
	board[endx][endy] = '>'; //Places exit
	board[mydog.x][mydog.y] = 'D'; //Places doggo
}
void Board::printBoard() {
	// (8 pts) code for the printBoard method goes here
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			cout << board[y][x] << " ";
			if (x==size-1) {
				cout << endl;
			}
		}
	}
}
bool Board::moveDog(char c) {
	// (12 pts) code for the moveDog method goes here

	//Makes the dog move
	if (c == 'u' && mydog.x > 1) {
		//If there is food, add strength
		if (board[mydog.x-1][mydog.y] == 'F') {
			mydog.changeStrength(rand()%16 + 2);

			//Makes the previous space blank
			board[mydog.x][mydog.y] = ' ';

			//Changes location of dog
			mydog.x -= 1;
			board[mydog.x][mydog.y] = 'D';
		} else if (board[mydog.x-1][mydog.y] == 'T') {
			//If there is a trap, subtract strength
			mydog.changeStrength(-1*(rand()%16 + 2));

			//Makes the previous space blank
			board[mydog.x][mydog.y] = ' ';

			//Changes location of dog
			mydog.x -= 1;
			board[mydog.x][mydog.y] = 'D';
		} else if (board[mydog.x-1][mydog.y] == '|' || board[mydog.x-1][mydog.y] == '_') {
			//If there is a wall, ask if it should be broken down, move accordingly
			cout << "Break down wall? (y/n)" << endl;
			char response;
			cin >> response;
			if (response == 'y') {
				//Makes the previous space blank
				board[mydog.x][mydog.y] = ' ';

				//Changes location of dog
				mydog.x -= 1;
				board[mydog.x][mydog.y] = 'D';

				//Subtracts strength for moving
				mydog.changeStrength(-6);
			}
		} else {
			//Makes the previous space blank
			board[mydog.x][mydog.y] = ' ';

			//Changes location of dog
			mydog.x -= 1;
			board[mydog.x][mydog.y] = 'D';

			//Subtracts strength for moving
			mydog.changeStrength(-2);
		}
	} else if (c == 'd' && mydog.x < 18) {
		//If there is food, add strength
		if (board[mydog.x+1][mydog.y] == 'F') {
			mydog.changeStrength(rand()%16 + 2);

			//Makes the previous space blank
			board[mydog.x][mydog.y] = ' ';

			//Changes location of dog
			mydog.x += 1;
			board[mydog.x][mydog.y] = 'D';
		} else if (board[mydog.x+1][mydog.y] == 'T') {
			//If there is a trap, subtract strength
			mydog.changeStrength(-1*(rand()%16 + 2));

			//Makes the previous space blank
			board[mydog.x][mydog.y] = ' ';

			//Changes location of dog
			mydog.x += 1;
			board[mydog.x][mydog.y] = 'D';
		} else if (board[mydog.x+1][mydog.y] == '|' || board[mydog.x+1][mydog.y] == '_') {
			//If there is a wall, ask if it should be broken down, move accordingly
			cout << "Break down wall? (y/n)" << endl;
			char response;
			cin >> response;
			if (response == 'y') {
				//Makes the previous space blank
				board[mydog.x][mydog.y] = ' ';

				//Changes location of dog
				mydog.x += 1;
				board[mydog.x][mydog.y] = 'D';

				//Subtracts strength for moving
				mydog.changeStrength(-6);
			}
		} else {
			//Makes the previous space blank
			board[mydog.x][mydog.y] = ' ';

			//Changes location of dog
			mydog.x += 1;
			board[mydog.x][mydog.y] = 'D';

			//Subtracts strength for moving
			mydog.changeStrength(-2);
		}
	} else if (c == 'l' && mydog.y > 1) {
		//If there is food, add strength
		if (board[mydog.x][mydog.y]-1 == 'F') {
			mydog.changeStrength(rand()%16 + 2);

			//Makes the previous space blank
			board[mydog.x][mydog.y] = ' ';

			//Changes location of dog
			mydog.y -= 1;
			board[mydog.x][mydog.y] = 'D';
		} else if (board[mydog.x][mydog.y-1] == 'T') {
			//If there is a trap, subtract strength
			mydog.changeStrength(-1*(rand()%16 + 2));

			//Makes the previous space blank
			board[mydog.x][mydog.y] = ' ';

			//Changes location of dog
			mydog.y -= 1;
			board[mydog.x][mydog.y] = 'D';
		} else if (board[mydog.x][mydog.y-1] == '|' || board[mydog.x][mydog.y-1] == '_') {
			//If there is a wall, ask if it should be broken down, move accordingly
			cout << "Break down wall? (y/n)" << endl;
			char response;
			cin >> response;
			if (response == 'y') {
				//Makes the previous space blank
				board[mydog.x][mydog.y] = ' ';

				//Changes location of dog
				mydog.y -= 1;
				board[mydog.x][mydog.y] = 'D';

				//Subtracts strength for moving
				mydog.changeStrength(-6);
			}
		} else {
			//Makes the previous space blank
			board[mydog.x][mydog.y] = ' ';

			//Changes location of dog
			mydog.y -= 1;
			board[mydog.x][mydog.y] = 'D';

			//Subtracts strength for moving
			mydog.changeStrength(-2);
		}
	} else if (c == 'r') {
		if (board[mydog.x][mydog.y+1] == '>') {
			//If at the exit, call the won method
			mydog.won();

			return false;
		}

		if (mydog.y < 18) {
			if (board[mydog.x][mydog.y+1] == 'F') {
				//If there is food, add strength
				mydog.changeStrength(rand()%16 + 2);

				//Makes the previous space blank
				board[mydog.x][mydog.y] = ' ';

				//Changes location of dog
				mydog.y += 1;
				board[mydog.x][mydog.y] = 'D';
			} else if (board[mydog.x][mydog.y+1] == 'T') {
				//If there is a trap, subtract strength
				mydog.changeStrength(-1*(rand()%16 + 2));

				//Makes the previous space blank
				board[mydog.x][mydog.y] = ' ';

				//Changes location of dog
				mydog.y += 1;
				board[mydog.x][mydog.y] = 'D';
			} else if (board[mydog.x][mydog.y+1] == '|' || board[mydog.x][mydog.y+1] == '_') {
				//If there is a wall, ask if it should be broken down, move accordingly
				cout << "Break down wall? (y/n)" << endl;
				char response;
				cin >> response;
				if (response == 'y') {
					//Makes the previous space blank
					board[mydog.x][mydog.y] = ' ';

					//Changes location of dog
					mydog.y += 1;
					board[mydog.x][mydog.y] = 'D';

					//Subtracts strength for moving
					mydog.changeStrength(-6);
				}
			} else {
				//Makes the previous space blank
				board[mydog.x][mydog.y] = ' ';

				//Changes location of dog
				mydog.y += 1;
				board[mydog.x][mydog.y] = 'D';

				//Subtracts strength for moving
				mydog.changeStrength(-2);
			}
		}
	}
	return true;
}
