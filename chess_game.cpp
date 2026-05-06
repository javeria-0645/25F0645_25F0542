
#define _CRT_SECURE_NO_WARNINGS   //for using cstring function in version 15
#include "chess_game.h"
#include <iostream>
#include<string>
#include <cstring>
using namespace std;

// ============================================================
//
//   Zainab Aslam (25f-0542) ensure complete implementation of game 
//   Contains: Player, Game
//   Depends on: chess_pieces.h / chess_pieces.cpp of javeria's part 
//
// ============================================================

// ============================================================
//  PLAYER
// ============================================================
//constructor definition
Player::Player() {
	strcpy(name, "Player");
	color = 0;
}
Player::Player(const char* n, int c) {
	strcpy(name, n);
	color = c;
}
//getters definition
const char* Player::getName()  const { 
	return name;
}
int Player::getColor() const { 
	return color;
}

// ── getInput ─────────────────────────────────────────────────
//IT EXPLAINS HOW IT WORKS
// Reads input in chess notation format: "e2 e4"
// Converts letter+number into row/col indices (0-7)
// e.g.  "e2" → col=4, row=6
//        a=0  b=1  c=2  d=3  e=4  f=5  g=6  h=7
//        1=7  2=6  3=5  4=4  5=3  6=2  7=1  8=0
void Player::getInput(int& fromRow, int& fromCol,
	int& toRow, int& toCol) const {
	char from[10], to[10];

	while (true) {
		cout << name << " (" << (color == 0 ? "White" : "Black") << ")";
		if (color == 0)
			cout << " enter move (e.g. e2 e4): ";
		else
			cout << " enter move (e.g. e7 e5): ";
		cin >> from >> to;

		// Column must be letter a-h
		if (from[0] < 'a' || from[0] > 'h' ||
			to[0]   < 'a' || to[0]   > 'h') {
			cout << "  Invalid column. Use a letter from a to h.\n";
			continue;
		}

		// Row must be digit 1-8
		if (from[1] < '1' || from[1] > '8' ||
			to[1]   < '1' || to[1]   > '8') {
			cout << "  Invalid row. Use a number from 1 to 8.\n";
			continue;
		}

		// Convert column letter to array index (same for both colors)
		// a=0  b=1  c=2  d=3  e=4  f=5  g=6  h=7
		fromCol = from[0] - 'a';
		toCol = to[0] - 'a';

		// Convert row number to array index (same for both colors)
		// Row 8 = top of board = array index 0
		// Row 1 = bottom of board = array index 7
		fromRow = 8 - (from[1] - '0');
		toRow = 8 - (to[1] - '0');

		break;  // input is valid
	}
}


