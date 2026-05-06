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







#endif 
