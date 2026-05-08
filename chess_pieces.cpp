#include "chess_pieces.h"
#include<iostream>
#include<string>
#include <windows.h>
using namespace std;

// =======================================
//   chess_pieces.cpp
//   this file contains Piece, King, Queen, Rook, Bishop, Knight, Pawn,
//  Move, MoveHistory, Board
// =========================================


// ================================
//  Helper
// ================================
static int absVal(int x) {
	return (x < 0) ? -x : x;
}


// =========================================
//  PIECE  (Base class)
// ==========================================

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
// =======================================================
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


// =================================================
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


// =================================================
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


// ==============================
//  MOVE  
// ==============================

Move::Move() {
	fromRow = 0;
	fromCol = 0;
	toRow = 0;
	toCol = 0;
	pieceMoved = nullptr;
	pieceCaptured = nullptr;
	isCastling = false;
	isEnPassant = false;
	isPromotion = false;
}


// ===============================================
//  MOVE HISTORY
// ===============================================


MoveHistory::MoveHistory() {
	count = 0;
}

void MoveHistory::addMove(Move m) {
	if (count < 300)
		moves[count++] = m;
}

Move MoveHistory::getLastMove() const {
	// caller must check isEmpty() before calling this
	return moves[count - 1];
}

int  MoveHistory::getCount() const {
	return count;
}
bool MoveHistory::isEmpty() const { 
	return count == 0;
}

void MoveHistory::printHistory() const {
	cout << "\n=== Move History ===\n";
	for (int i = 0; i < count; i++) {
		// Convert 0-7 col to a-h letter
		char fromColLetter = 'a' + moves[i].fromCol;
		char toColLetter = 'a' + moves[i].toCol;
		int  fromRowNum = 8 - moves[i].fromRow;
		int  toRowNum = 8 - moves[i].toRow;

		cout << (i + 1) << ". "
			<< fromColLetter << fromRowNum
			<< " -> "
			<< toColLetter << toRowNum;

		if (moves[i].isCastling) cout << "  (castling)";
		if (moves[i].isEnPassant) cout << "  (en passant)";
		if (moves[i].isPromotion) cout << "  (promotion)";
		cout << "\n";
	}
	cout << "====================\n\n";
}


// =====================================================
//  BOARD
// ======================================================

Board::Board() {
	for (int r = 0; r < 8; r++)
		for (int c = 0; c < 8; c++)
			grid[r][c] = nullptr;
}

// Destructor deleteing every piece to avoid memory leak
Board::~Board() {
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			if (grid[r][c] != nullptr) {
				delete grid[r][c];
				grid[r][c] = nullptr;
			}
		}
	}
}

// initBoard =================
// Creates all 32 pieces with 'new' and places them on starting squares.
// White is at the bottom (rows 6 & 7), Black at the top (rows 0 & 1).
void Board::initBoard() {
	//  White back rank (row 7)==================
	grid[7][0] = new Rook(0, 7, 0);
	grid[7][1] = new Knight(0, 7, 1);
	grid[7][2] = new Bishop(0, 7, 2);
	grid[7][3] = new Queen(0, 7, 3);
	grid[7][4] = new King(0, 7, 4);
	grid[7][5] = new Bishop(0, 7, 5);
	grid[7][6] = new Knight(0, 7, 6);
	grid[7][7] = new Rook(0, 7, 7);

	// White pawns (row 6)==================
	for (int c = 0; c < 8; c++)
		grid[6][c] = new Pawn(0, 6, c);

	// Black back rank (row 0) ==================
	grid[0][0] = new Rook(1, 0, 0);
	grid[0][1] = new Knight(1, 0, 1);
	grid[0][2] = new Bishop(1, 0, 2);
	grid[0][3] = new Queen(1, 0, 3);
	grid[0][4] = new King(1, 0, 4);
	grid[0][5] = new Bishop(1, 0, 5);
	grid[0][6] = new Knight(1, 0, 6);
	grid[0][7] = new Rook(1, 0, 7);

	// ================== Black pawns (row 1) ==================
	for (int c = 0; c < 8; c++)
		grid[1][c] = new Pawn(1, 1, c);

}

//  ================== getPiece ==================
Piece* Board::getPiece(int row, int col) const {
	if (row < 0 || row > 7 || col < 0 || col > 7)
		return nullptr;
	return grid[row][col];
}

// ================== setPiece ==================
void Board::setPiece(int row, int col, Piece* p) {
	if (row < 0 || row > 7 || col < 0 || col > 7) return;
	grid[row][col] = p;
}

/* ================== movePiece ==================
 moves a piece pointer from one cell to another.
 deletes any captured piece automatically.
 Game class will handles the validity.*/

void Board::movePiece(int fromRow, int fromCol, int toRow, int toCol) {
	// If there is a piece at destination it is captured
	if (grid[toRow][toCol] != nullptr) {
		delete grid[toRow][toCol];
		grid[toRow][toCol] = nullptr;
	}

	// moves the pointer
	grid[toRow][toCol] = grid[fromRow][fromCol];
	grid[fromRow][fromCol] = nullptr;

	// updating piece's own position fields
	if (grid[toRow][toCol] != nullptr) {
		grid[toRow][toCol]->setRow(toRow);
		grid[toRow][toCol]->setCol(toCol);
	}
}

/* ================== isPathClear ==================
checks every square BETWEEN source and destination.
used by Rook, Bishop, and Queen isValidMove().
knights jump so they wont call this function.*/

bool Board::isPathClear(int fromRow, int fromCol,
	int toRow, int toCol) const {
	int rowStep = 0, colStep = 0;

	if (toRow > fromRow) rowStep = 1;
	if (toRow < fromRow) rowStep = -1;
	if (toCol > fromCol) colStep = 1;
	if (toCol < fromCol) colStep = -1;

	int r = fromRow + rowStep;
	int c = fromCol + colStep;

	while (r != toRow || c != toCol) {
		if (grid[r][c] != nullptr) return false;  // something blocking
		r += rowStep;
		c += colStep;
	}
	return true;
}

/* ================== display ==================
   using ANSI escape codes for checkerboard
   Unicode for chess piece symbols 
 */


void Board::display() const { // ANSI background colors 
	const char* DARK_SQ = "\033[48;2;101;67;33m";   // deep brown
	const char* LIGHT_SQ = "\033[48;2;210;180;140m";  // warm tan
	const char* WHITE_PC = "\033[1;38;2;255;255;255m"; // pure white text
	const char* BLACK_PC = "\033[1;38;2;0;0;0m";       // pure black text
	const char* RESET = "\033[0m";
	cout << "      a    b    c    d    e    f    g    h\n";
	cout << "    +----+----+----+----+----+----+----+----+\n";
//--------------------------------------

	for (int r = 0; r < 8; r++) {
		cout << "  " << (8 - r) << " |";

		for (int c = 0; c < 8; c++) {
			bool isDark = (r + c) % 2 != 0;
			cout << (isDark ? DARK_SQ : LIGHT_SQ);

			if (grid[r][c] == nullptr) {
				cout << "    ";   // empty ,using 4 spaces
			}
			else {
				cout << (grid[r][c]->getColor() == 0 ? WHITE_PC : BLACK_PC);
				cout << " " << grid[r][c]->getSymbol() << "  ";
			}
			cout << RESET << "|";
		}

		cout << " " << (8 - r) << "\n";
		cout << "    +----+----+----+----+----+----+----+----+\n";
	}

	cout << "      a    b    c    d    e    f    g    h\n\n";
}

// ================== isUnderAttack ==================
// Returns true if any piece of 'byColor' can legally move to (row, col).
// Used by Game to detect check: isUnderAttack(kingRow, kingCol, opponentColor)

bool Board::isUnderAttack(int row, int col, int byColor) const {
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			Piece* p = grid[r][c];
			if (p == nullptr)             
				continue;
			if (p->getColor() != byColor) 
				continue;

			// Polymorphism sso it calls the correct isValidMove for each piece type
			if (p->isValidMove(row, col, (Piece * (*)[8])grid))
				return true;
		}
	}
	return false;
}

/* ================== findKing ==================
this cans the board and stores the King's position in outRow/outCol.
will be used before every isUnderAttack check. */
void Board::findKing(int color, int& outRow, int& outCol) const {
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			Piece* p = grid[r][c];
			if (p == nullptr)       
				continue;
			if (p->getColor() != color)
				continue;

			// dynamic cast returns non null only if p really is king
			King* k = dynamic_cast<King*>(p);
			if (k != nullptr) {
				outRow = r;
				outCol = c;
				return;
			}
		}
	}
}
