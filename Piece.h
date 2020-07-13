#pragma once
#include <vector>
#include <array>
using namespace std;
class GameState;

vector<array<int, 2>> fltrMoves(GameState &state, vector<array<int, 2>> moves, int y, int x);

class Piece {
public:
	Piece(bool col) {
		color = col;
		moves = {};
	}
	bool color;
	int id;
	virtual vector<array<int,2>> getMoves(GameState &state, int x, int y) = 0;
	vector<array<int, 2>> moves;
	vector<array<int, 2>> getAttackingMoves(GameState &state, int y, int x);
	
};

class Pawn : public Piece {
public:
	Pawn(bool col) : Piece(col) {
		hasMoved = false;
		id = 0;
		enPassant = false;
	}
	bool hasMoved;
	bool enPassant;
	void SetHasMoved(bool moved);
	void SetEnPassant(bool enpassant);
	vector<array<int, 2> > getMoves(GameState &state, int y, int x);
};

class Rook : public Piece {
public:
	Rook(bool col) :Piece(col) { 
		hasMoved = false; 
		id = 1;
	}
	bool hasMoved;
	void SetHasMoved(bool moved);
	//std::vector<int[2]> getMoves(GameState);
	vector<array<int,2> > getMoves(GameState &state, int y, int x);
};

class Knight : public Piece {
public:
	Knight(bool col) :Piece(col) {
		id = 2;
	}
	vector<array<int, 2> > getMoves(GameState &state, int y, int x);
};

class Bishop : public Piece {
public:
	Bishop(bool col) : Piece(col) {
		id = 3;
	}
	vector<array<int, 2> > getMoves(GameState& state, int y, int x);
};

class Queen : public Piece {
public:
	Queen(bool col) : Piece(col) {
		id = 4;
	}
	vector<array<int,2>> getMoves(GameState &state, int y, int x);
};

class King : public Piece {
public:
	King(bool col) : Piece(col) {
		id = 5;
		hasMoved = false;
	}
	bool hasMoved;
	bool inCheck(GameState &state, int y, int x);
	vector<array<int, 2>> getMoves(GameState &state, int y, int x);
};

