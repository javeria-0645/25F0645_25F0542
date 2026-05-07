
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
// =======================================
//  GAME 
// =======================================

//  isInCheck [FUNCTION]
// Returns true if the king of specifiq color is currently under attack
bool Game::isInCheck(int color) const {
int kingRow, kingCol;
board.findKing(color, kingRow, kingCol);
int opponent = (color == 0) ? 1 : 0;
return board.isUnderAttack(kingRow, kingCol, opponent);
}

// wouldLeaveKingInCheck [FUNCTION]
// Temporarily makes a move, checks if own king is in check,if yes then undoes the move
// just safety check before any move is confirmed.
bool Game::wouldLeaveKingInCheck(int fromRow, int fromCol,int toRow, int toCol,int color) {
// Save pieces at squares
Piece* movingPiece = board.getPiece(fromRow, fromCol);
Piece* capturedPiece = board.getPiece(toRow, toCol);

// Simulate the move 
board.setPiece(toRow, toCol, movingPiece);
board.setPiece(fromRow, fromCol, nullptr);

// Temporarily update piece position
if (movingPiece != nullptr) {
movingPiece->setRow(toRow);
movingPiece->setCol(toCol);
}

// Check if own king is in check after the move
bool inCheck = isInCheck(color);

// then Undo the move 
board.setPiece(fromRow, fromCol, movingPiece);
board.setPiece(toRow, toCol, capturedPiece);

// Restore piece position
if (movingPiece != nullptr) {
movingPiece->setRow(fromRow);
movingPiece->setCol(fromCol);
}

return inCheck;
}
// hasNoLegalMoves [FUNCTION]
// Tries every possible move for every piece of 'color'.
bool Game::hasNoLegalMoves(int color) {
for (int fr = 0; fr < 8; fr++) {
    for (int fc = 0; fc < 8; fc++) {
      Piece* p = board.getPiece(fr, fc);
      if (p == nullptr || p->getColor() != color) 
          continue;

// Try every possible destination
for (int tr = 0; tr < 8; tr++) {
     for (int tc = 0; tc < 8; tc++) {
       if (fr == tr && fc == tc) 
		   continue;

Piece* grid[8][8];
for (int r = 0; r < 8; r++)
for (int c = 0; c < 8; c++)
grid[r][c] = board.getPiece(r, c);

bool moves = p->isValidMove(tr, tc, grid);
bool castl = isCastlingMove(fr, fc, tr, tc);
bool enPas = isEnPassantMove(fr, fc, tr, tc);

if ((moves || castl || enPas) &&!wouldLeaveKingInCheck(fr, fc, tr, tc, color)) {
return false;  // found at least one legal move
       }
     }
   }
 }
}
return true;  // no legal moves found
}

// checkGameOver [FUNCTION]
// Returns: 0 = game continues, 1 = checkmate, 2 = stalemate
int Game::checkGameOver() {
int opponent = (currentTurn == 0) ? 1 : 0;

if (hasNoLegalMoves(opponent)) {
    if (isInCheck(opponent))
       return 1;  // checkmate(king is in chk ,and no l.move)
    else
       return 2;  // stalemate(king is not in chk)
}
return 0;
}
//  executeCastling [FUNCTION]
// Moves both the king and the rook to their castling squares
void Game::executeCastling(int fromRow, int fromCol,int toRow, int toCol) {
int colDiff = toCol - fromCol;
int rookFromCol = (colDiff == 2) ? 7 : 0;
int rookToCol = (colDiff == 2) ? 5 : 3;

// Move king
board.movePiece(fromRow, fromCol, toRow, toCol);
King* king = dynamic_cast<King*>(board.getPiece(toRow, toCol));
if (king) king->setHasMoved(true);

// Move rook
board.movePiece(fromRow, rookFromCol, fromRow, rookToCol);
Rook* rook = dynamic_cast<Rook*>(board.getPiece(fromRow, rookToCol));
if (rook) rook->setHasMoved(true);

cout << "  Castling!\n";
}
//  isCastlingMove [FUNCTION]

bool Game::isCastlingMove(int fromRow, int fromCol,int toRow, int toCol) const {
Piece* p = board.getPiece(fromRow, fromCol);
if (p == nullptr) 
   return false;

King* king = dynamic_cast<King*>(p);
if (king == nullptr)  
    return false;  // not a king
if (king->getHasMoved()) 
    return false; // king already moved
if (fromRow != toRow)  
    return false;  // must stay on same row

int colDiff = toCol - fromCol;
// King must move exactly 2 squares left or right
if (colDiff != 2 && colDiff != -2)
    return false;

int rookCol = (colDiff == 2) ? 7 : 0;
Piece* rook = board.getPiece(fromRow, rookCol);
if (rook == nullptr)
    return false;

Rook* r = dynamic_cast<Rook*>(rook);
if (r == nullptr || r->getHasMoved()) 
    return false;

// Path between king and rook must be clear
int step = (colDiff == 2) ? 1 : -1;
int c = fromCol + step;
while (c != rookCol) {
    if (board.getPiece(fromRow, c) != nullptr) 
       return false;
    c += step;
}
if (isInCheck(p->getColor())) 
return false;

int opponent = (p->getColor() == 0) ? 1 : 0;
if (board.isUnderAttack(fromRow, fromCol + step, opponent)) 
    return false;
if (board.isUnderAttack(fromRow, fromCol + step * 2, opponent))
    return false;

return true;
}
//  isEnPassantMove [FUNCTION]
bool Game::isEnPassantMove(int fromRow, int fromCol,int toRow, int toCol) const {
Piece* p = board.getPiece(fromRow, fromCol);
  if (p == nullptr) 
	  return false;

Pawn* pawn = dynamic_cast<Pawn*>(p);
 if (pawn == nullptr) 
	 return false;

int direction = (p->getColor() == 0) ? -1 : 1;
int rowDiff = toRow - fromRow;
int colDiff = toCol - fromCol;
 if (colDiff < 0) 
	 colDiff = -colDiff;

// Must be diagonal move of 1
  if (rowDiff != direction || colDiff != 1)
    return false;

// Destination must be empty (otherwise it's a normal capture)
 if (board.getPiece(toRow, toCol) != nullptr) 
	 return false;

// Adjacent pawn must be en passant vulnerable
Piece* adjacent = board.getPiece(fromRow, toCol);
 if (adjacent == nullptr)  
	 return false;

Pawn* adjPawn = dynamic_cast<Pawn*>(adjacent);
 if (adjPawn == nullptr) 
	 return false;
 if (adjPawn->getColor() == p->getColor())
	 return false;

return adjPawn->getEnPassantVulnerable();
}

//  executeEnPassant [FUNCTION]
void Game::executeEnPassant(int fromRow, int fromCol,int toRow, int toCol) {

board.movePiece(fromRow, fromCol, toRow, toCol);

Piece* captured = board.getPiece(fromRow, toCol);
  if (captured != nullptr) {
     delete captured;
     board.setPiece(fromRow, toCol, nullptr);
}

cout << "  En passant capture!\n";
}
