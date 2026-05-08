#pragma once
#ifndef CHESS_GAME_H
#define CHESS_GAME_H
#include "chess_pieces.h"
#include<iostream>
#include<string>

using namespace std;
// ============================================================
//  PLAYER
// ============================================================
class Player {
private:
	char name[50];
	int  color;      // 0 = White,  1 = Black

public:
	//constructor
	Player();
	//parameterized constructor 
	Player(const char* name, int color);

	// Getters
	const char* getName()  const;
	int         getColor() const;

	// Ask the player to type a move to fills fromRow/Col and toRow/Col
	void getInput(int& fromRow, int& fromCol,int& toRow, int& toCol) const;
};
// ============================================================
//  GAME
// ============================================================
class Game {
private:
	Board       board;
	Player      players[2];
	MoveHistory history;
	int         currentTurn;   // 0 = White's turn,  1 = Black's turn
	bool isInCheck(int color) const;
	// Simulates a move, checks if it leaves own king in check, undoes it
	bool wouldLeaveKingInCheck(int fromRow, int fromCol,int toRow, int toCol,int color);
	// Returns true if 'color' has zero legal moves left
	bool hasNoLegalMoves(int color);
	// Checks if the game is over — checkmate or stalemate
	int  checkGameOver();
	// Special move handlers
	void executeCastling(int fromRow, int fromCol,int toRow, int toCol);
	bool isCastlingMove(int fromRow, int fromCol,int toRow, int toCol) const;

	void executeEnPassant(int fromRow, int fromCol,int toRow, int toCol);
	bool isEnPassantMove(int fromRow, int fromCol,int toRow, int toCol) const;

	void handlePawnPromotion(int row, int col);
// Clears en passant flags for all pawns of a color
	void clearEnPassantFlags(int color);

	// Validates input and checks full legality of a move
	bool isLegalMove(int fromRow, int fromCol,
		int toRow, int toCol,
		int color);

	// Switches turn from 0 to 1 or 1 to 0
	void switchTurn();

	// Prints a simple status line showing whose turn it is
	void printStatus() const;

public:
	Game();

	// Sets  names for both players
	void setup();

	//  runs until checkmate or stalemate
	void run();

};



#endif 
