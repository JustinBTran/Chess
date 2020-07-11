#pragma once
#include "TranspositionTable.h"

//booln is hasMoved/Enpassant
unsigned int TranspositionTable::getKey(int row, int col, int id, bool booln, bool color)
{
	int idx1 = row * 8 + col;
	int idx2;
	switch (id) {
	case -1:
		idx2 = 12;//empty
		break;
	case 0:
		if (color == true) {
			idx2 = 0;
		}
		else {
			idx2 = 6;
		}
		if(color == true && row == 4 && booln){
			idx2 = 13;//special case
		}
		else if (color == false && row == 3 && booln) {

		}
		break;
	case 1:
		if (color == true) {
			idx2 = 1;
		}
		else {
			idx2 = 7;
		}
		if (color == true && row == 7 && (col == 0 || col == 7 && !booln)) {
			idx2 = 13;
		}
		else if (color == false && row == 0 && (col == 0 || col == 7 && !booln)) {
			idx2 = 13;
		}
		break;
	case 2:
		if (color == true) {
			idx2 = 2;
		}
		else {
			idx2 = 8;
		}
		break;
		break;
	case 3:
		if (color == true) {
			idx2 = 3;
		}
		else {
			idx2 = 9;
		}
		break;
	case 4:
		if (color == true) {
			idx2 = 4;
		}
		else {
			idx2 = 10;
		}
		break;

	case 5:
		if (color == true) {
			idx2 = 5;
		}
		else {
			idx2 = 11;
		}
		if (color == true && row == 7 && col == 4 && !booln ) {
			idx2 = 13;
		}
		else if (color == false && row == 0 && col==4 && !booln) {
			idx2 = 13;
		}
		break;
	}
	return keys[idx1][idx2];
}

unsigned int TranspositionTable::getKobristKey(GameState state)
{
	unsigned int key = 0;
	unsigned int tempKey;
	bool color;
	int id;
	bool booln;
	Piece* piece;
	Pawn* pawn;
	Rook* rook;
	King* king;
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			piece = state.board[row][col];
			if (piece == nullptr) {
				tempKey = getKey(row, col, -1, false, false);
				key = key^tempKey;
			}
			else {
				color = piece->color;
				id = piece->id;
				if (id == 0) {
					pawn = dynamic_cast<Pawn*>(piece);
					booln = pawn->enPassant;
				}
				else if (id == 1) {
					rook = dynamic_cast<Rook*>(piece);
					booln = rook->hasMoved;
				}
				else if (id == 5) {
					king = dynamic_cast<King*>(piece);
					booln - king->hasMoved;
				}
				tempKey = getKey(row, col, id, booln, color);
				key = key^ tempKey;
			}
		}
	}
	return key;
}

unsigned int TranspositionTable::updateKobristKey(GameState state, unsigned int kobristKey, int y_old, int x_old, int y_new, int x_new)
{
	unsigned int key = kobristKey;
	Piece* newPos = state.board[y_new][x_new];
	Piece* oldPos = state.board[y_old][x_old];
	Rook* rook;
	Pawn* pawn;
	King* king;
	bool booln = false;
	//xor out the piece from oldPos
	switch (oldPos->id) {
	case 0:
		pawn = dynamic_cast<Pawn*>(oldPos);
		booln = pawn->enPassant;
		break;
	case 1:
		rook = dynamic_cast<Rook*>(oldPos);
		booln = rook->hasMoved;
		break;
	case 5:
		king = dynamic_cast<King*>(oldPos);
		booln = king->hasMoved;
		break;
	}
	bool oldPosBooln = booln;
	//xor out what used to be in oldPos
	key = key ^ (getKey(y_old, x_old,oldPos->id,oldPosBooln,oldPos->color));
	//xor in null in the oldPos
	key = key ^ (getKey(y_old, x_old, -1, false, false));
	//xor out what used to be in newPos
	if (newPos == nullptr) {
		key = key ^ (getKey(y_new, x_new, -1, false, false));
	}
	else {
		switch (newPos->id) {
		case 0:
			pawn = dynamic_cast<Pawn*>(newPos);
			booln = pawn->enPassant;
			break;
		case 1:
			rook = dynamic_cast<Rook*>(newPos);
			booln = rook->hasMoved;
			break;
		case 5:
			king = dynamic_cast<King*>(newPos);
			booln = king->hasMoved;
			break;
		}
		key = key ^ (getKey(y_new, x_new, newPos->id, booln, newPos->color));
	}
	// xor in  the old piece in the new position
	bool newPosBooln = true;
	if (oldPos->id == 0) {
		if (abs(y_new - y_old) == 2) {
			key = key ^ (getKey(y_new, x_new, oldPos->id, true, oldPos->color));//check if the piece is now enpassantable
		}
		//check promotes
		else if (oldPos->color == true && y_new == 0) {
			key = key ^ (getKey(y_new, x_new, 4, false, oldPos->color));
		}
		else if (oldPos->color == false && y_new == 7) {
			key = key ^ (getKey(y_new, x_new, 4, false, oldPos->color));
		}
		else {
			key = key ^ (getKey(y_new, x_new, oldPos->id, false, oldPos->color));
		}
		//check for enpassant
		if (newPos == nullptr && x_old != x_new) {
			Pawn* deadPawn = dynamic_cast<Pawn*>(state.board[y_old][x_new]);
			key = key ^ getKey(y_old,x_new, 0, deadPawn->hasMoved, deadPawn->color);
			key = key ^ getKey(y_old,x_new, -1, false, false);
		}
	}
	else {
		key = key ^ (getKey(y_new, x_new, oldPos->id, true, oldPos->color));
	}

	
	//check for castle, xor in and out rooks
	if (oldPos->id == 5 && abs(x_new - x_old) == 2) {
		if (y_new == 7 && x_new == 6) {
			key = key ^ getKey(7,7, 1, false, true);
			key = key ^ getKey(7,7,-1,false,true);
			key = key ^ getKey(7,5, -1, false, true);
			key = key ^ getKey(7,5, 1, true, true);
		}
		else if (y_new == 7 && x_new == 2) {
			key = key ^ getKey(7, 0, 1, false, true);
			key = key ^ getKey(7, 0, -1, false, true);
			key = key ^ getKey(7, 3, -1, false, true);
			key = key ^ getKey(7, 3, 1, true, true);
		}
		else if (y_new ==  0) {
			if (x_new == 5) {
				key = key ^ getKey(0, 7, 1, false, false);
				key = key ^ getKey(0, 7, -1, false, false);
				key = key ^ getKey(0, 5, -1, false, false);
				key = key ^ getKey(0, 5, 1, true, false);
			}
			else if (x_new == 2) {
				key = key ^ getKey(0, 0, 1, false, false);
				key = key ^ getKey(0, 0, -1, false, false);
				key = key ^ getKey(0, 3, -1, false, false);
				key = key ^ getKey(0, 3, 1, true, false);
			}

		}
	}


	return key;

}

int TranspositionTable::hashFunction(unsigned int kobristKey)
{
	return ((unsigned int) kobristKey)%1000;
}
