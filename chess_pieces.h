#ifndef CHESS_PIECES_H
#define CHESS_PIECES_H
#include <windows.h>
#include <iostream>
using namespace std;

// ============================================================
//  PIECE 
// ============================================================
class Piece {
protected:
	int  color;    // 0 = White,  1 = Black
	int  row;
	int  col;
	bool isAlive;

public:
	Piece(int color, int row, int col);
	virtual ~Piece();

	// Pure virtual func
	virtual bool isValidMove(int toRow, int toCol, Piece* grid[8][8]) = 0;
	virtual const char* getSymbol() = 0;   // gives symbol of piece

	// Getters
	int  getColor() const;
	int  getRow() const;
	int  getCol() const;
	bool getIsAlive() const;

	// setters 
	void setRow(int r);
	void setCol(int c);
	void setIsAlive(bool val);
};


// ============================================================
//  KING
// ============================================================
class King : public Piece {
private:
	bool hasMoved;   

public:
	King(int color, int row, int col);

	bool isValidMove(int toRow, int toCol, Piece* grid[8][8]) override;
	const char* getSymbol() override;

	bool getHasMoved() const;
	void setHasMoved(bool val);
};

// ============================================================
//  QUEEN
// ============================================================
class Queen : public Piece {
public:
	Queen(int color, int row, int col);

	bool isValidMove(int toRow, int toCol, Piece* grid[8][8]) override;
	const char* getSymbol() override;
};
// ============================================================
//  ROOK
// ============================================================
class Rook : public Piece {
private:
	bool hasMoved; 

public:
	Rook(int color, int row, int col);

	bool isValidMove(int toRow, int toCol, Piece* grid[8][8]) override;
	const char* getSymbol() override;

	bool getHasMoved() const;
	void setHasMoved(bool val);
};


// ============================================================
//  BISHOP
// ============================================================
class Bishop : public Piece {
public:
	Bishop(int color, int row, int col);

	bool isValidMove(int toRow, int toCol, Piece* grid[8][8]) override;
	const char* getSymbol() override;
};


// ============================================================
//  KNIGHT
// ============================================================
class Knight : public Piece {
public:
	Knight(int color, int row, int col);

	bool isValidMove(int toRow, int toCol, Piece* grid[8][8]) override;
	const char* getSymbol() override;
};


// ============================================================
//  PAWN
// ============================================================
class Pawn : public Piece {
private:
	bool hasMoved;            // false = can move 2 squares on first move
	bool enPassantVulnerable;   // true for one turn after a 2-square advance

public:
	Pawn(int color, int row, int col);

	bool isValidMove(int toRow, int toCol, Piece* grid[8][8]) override;
	const char* getSymbol() override;

	bool getHasMoved() const;
	bool getEnPassantVulnerable()  const;
	void setHasMoved(bool val);
	void setEnPassantVulnerable(bool val);
};

