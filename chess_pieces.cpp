#include "chess_pieces.h"
#include<iostream>
#include<string>
#include <windows.h>
using namespace std;

// =======================================
//   chess_pieces.cpp
//   this file contains Piece, King, Queen, Rook, Bishop, Knight, Pawn,
//  Move, MoveHistory, Board
// ===============================================


// ============================================================
//  Helper
// ================================
static int absVal(int x) {
	return (x < 0) ? -x : x;
}


// =========================================
//  PIECE  (Base class)
// ===================================================

Piece::Piece(int color, int row, int col) {
	this->color = color;
	this->row = row;
	this->col = col;
	this->isAlive = true;
}

Piece::~Piece() {
}

int  Piece::getColor() const { 
  return color; }
int  Piece::getRow() const { 
  return row; }
int  Piece::getCol() const {
  return col; }
bool Piece::getIsAlive() const { 
  return isAlive; }

void Piece::setRow(int r) { 
  row = r; }
void Piece::setCol(int c) { 
  col = c; }
void Piece::setIsAlive(bool val) { 
  isAlive = val; }
// ============================================================
//  KING
// =======================================================

King::King(int color, int row, int col)
	: Piece(color, row, col)
{
	hasMoved = false;
}

const char* King::getSymbol() {
	return (color == 0) ? "\u2654" : "\u265A"; 
}

bool King::isValidMove(int toRow, int toCol, Piece* grid[8][8]) {
	int rowDiff = absVal(toRow - row);
	int colDiff = absVal(toCol - col);

	// to move exactly 1 square in any direction
	if (rowDiff > 1 || colDiff > 1)      
    return false;
	if (rowDiff == 0 && colDiff == 0)   
    return false;  // means didn't move

	// making sure own color piece isnt being captured
	Piece* dest = grid[toRow][toCol];
	if (dest != nullptr && dest->getColor() == color) return false;

	return true;
}

bool King::getHasMoved() const {
  return hasMoved; }
void King::setHasMoved(bool v) { 
  hasMoved = v; }


// ============================================================
//  QUEEN
// ===============================================

Queen::Queen(int color, int row, int col)
	: Piece(color, row, col) {
}

const char* Queen::getSymbol() {
	return (color == 0) ? "\u2655" : "\u265B"; 
}

bool Queen::isValidMove(int toRow, int toCol, Piece* grid[8][8]) {
	if (toRow == row && toCol == col) return false;

	// Queen moves like both rook and bishop
	bool straightLine = (toRow == row || toCol == col);
	bool diagonal = (absVal(toRow - row) == absVal(toCol - col));

	if (!straightLine && !diagonal) return false;

	// Can't capture own piece
	Piece* dest = grid[toRow][toCol];
	if (dest != nullptr && dest->getColor() == color) return false;

	// making sure path is clear
	int rowStep = 0, colStep = 0;
	if (toRow > row) rowStep = 1;
	if (toRow < row) rowStep = -1;
	if (toCol > col) colStep = 1;
	if (toCol < col) colStep = -1;

	int r = row + rowStep;
	int c = col + colStep;
	while (r != toRow || c != toCol) {
		if (grid[r][c] != nullptr) return false; 
		r += rowStep;
		c += colStep;
	}
	return true;
}


// ============================================================
//  ROOK
// ================================================

Rook::Rook(int color, int row, int col)
	: Piece(color, row, col)
{
	hasMoved = false;
}

const char* Rook::getSymbol() {
	return (color == 0) ? "\u2656" : "\u265C";
}

bool Rook::isValidMove(int toRow, int toCol, Piece* grid[8][8]) {
	if (toRow == row && toCol == col) return false;

	// moving in a straight line 
	if (toRow != row && toCol != col) return false;

	// Can't capture own piece
	Piece* dest = grid[toRow][toCol];
	if (dest != nullptr && dest->getColor() == color) return false;

	int rowStep = 0, colStep = 0;
	if (toRow > row) rowStep = 1;
	if (toRow < row) rowStep = -1;
	if (toCol > col) colStep = 1;
	if (toCol < col) colStep = -1;

	int r = row + rowStep;
	int c = col + colStep;
	while (r != toRow || c != toCol) {
		if (grid[r][c] != nullptr) return false;
		r += rowStep;
		c += colStep;
	}
	return true;
}

bool Rook::getHasMoved()       const { return hasMoved; }
void Rook::setHasMoved(bool v) { hasMoved = v; }


// ==========================================================
//  BISHOP
// ============================================================

Bishop::Bishop(int color, int row, int col)
	: Piece(color, row, col) {
}

const char* Bishop::getSymbol() {
	return (color == 0) ? "\u2657" : "\u265D";  
}

bool Bishop::isValidMove(int toRow, int toCol, Piece* grid[8][8]) {
	if (toRow == row && toCol == col) return false;

	// Must move diagonally
	if (absVal(toRow - row) != absVal(toCol - col)) return false;

	Piece* dest = grid[toRow][toCol];
	if (dest != nullptr && dest->getColor() == color) return false;

	int rowStep = (toRow > row) ? 1 : -1;
	int colStep = (toCol > col) ? 1 : -1;

	int r = row + rowStep;
	int c = col + colStep;
	while (r != toRow || c != toCol) {
		if (grid[r][c] != nullptr) return false;
		r += rowStep;
		c += colStep;
	}
	return true;
}


// ========================================================
//  KNIGHT
// ============================================================

Knight::Knight(int color, int row, int col)
	: Piece(color, row, col) {
}

const char* Knight::getSymbol() {
	return (color == 0) ? "\u2658" : "\u265E";  
}

bool Knight::isValidMove(int toRow, int toCol, Piece* grid[8][8]) {
	int rowDiff = absVal(toRow - row);
	int colDiff = absVal(toCol - col);

	// Knight moves in an L shape
	bool validShape = (rowDiff == 2 && colDiff == 1) ||
		(rowDiff == 1 && colDiff == 2);
	if (!validShape) return false;


	// no capturing own piece
	Piece* dest = grid[toRow][toCol];
	if (dest != nullptr && dest->getColor() == color) return false;

	return true;
}


// ======================================================
//  PAWN
// ============================================================

Pawn::Pawn(int color, int row, int col)
	: Piece(color, row, col)
{
	hasMoved = false;
	enPassantVulnerable = false;
}

const char* Pawn::getSymbol() {
	return (color == 0) ? "\u2659" : "\u265F"; 
}

bool Pawn::isValidMove(int toRow, int toCol, Piece* grid[8][8]) {
	// White moves up  so row decreases , Black moves DOWN so row increases
	int direction = (color == 0) ? -1 : 1;

	int rowDiff = toRow - row;   // sign direction for pawns
	int colDiff = absVal(toCol - col);

	//  forward move (no capture) 
	if (colDiff == 0) {
		// 0ne step forward
		if (rowDiff == direction) {
			if (grid[toRow][toCol] != nullptr) return false;  // blocked
			return true;
		}
		// Two steps forward from start
		if (rowDiff == 2 * direction && !hasMoved) {
			int midRow = row + direction;
			if (grid[midRow][col] != nullptr) 
        return false;  // path blocked
			if (grid[toRow][toCol] != nullptr)
        return false;  // destination blocked
			return true;
		}
		return false;
	}

	// Diagonal capture (including en passant) 
	if (colDiff == 1 && rowDiff == direction) {
		Piece* dest = grid[toRow][toCol];

		// Normal diagonal capture
		if (dest != nullptr && dest->getColor() != color) return true;

		// En passant(means destination is empty but adjacent pawn is vulnerable)
		if (dest == nullptr) {
			Piece* adjacent = grid[row][toCol];  // pawn beside this one
			if (adjacent != nullptr &&
				adjacent->getColor() != color) {
				// checking if it's a pawn that just moved 2 squares
				Pawn* adjPawn = dynamic_cast<Pawn*>(adjacent);
				if (adjPawn != nullptr && adjPawn->getEnPassantVulnerable())
					return true;
			}
		}
		return false;
	}

	return false;  // any other move illegal
}

bool Pawn::getHasMoved() const { return hasMoved; }
bool Pawn::getEnPassantVulnerable() const { return enPassantVulnerable; }
void Pawn::setHasMoved(bool v) { hasMoved = v; }
void Pawn::setEnPassantVulnerable(bool v) { enPassantVulnerable = v; }
