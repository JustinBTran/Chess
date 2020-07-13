#include "Piece.h"
#include "GameState.h"
#pragma once

//Filter out all non safe moves. Y and X and the pieces current position
vector<array<int, 2>> fltrMoves(GameState &state, vector<array<int, 2>> moves, int y, int x)
{
	vector<array<int, 2>> fltr;
	for (auto move : moves) {
		bool unSafe = state.safeMove(state,y,x,move[0],move[1]);
		if (!unSafe) {
			fltr.push_back(move);
		}
	}
	return fltr;
}


void Rook::SetHasMoved(bool moved) {
	hasMoved = moved;
}

vector<array <int,2>> Rook::getMoves(GameState &state, int y, int x)
{
	vector<array<int,2>> moves;
	//get all moves vertically downwards(col 0->7)
	for (int col = y + 1; col < 8; col++) {
		if (state.board[col][x] == NULL) {
			std::array<int, 2> temp = { col,x };
			moves.push_back(temp);
		}
		else if (state.board[col][x]->color != color) {
			array<int, 2> temp = { col,x };
			moves.push_back(temp);
			break;
		}
		else {
			break;
		}
	}
	//get all moves horizontally right(row 0->7)
	for (int row = x + 1; row < 8; row++) {
		if (state.board[y][row] == NULL) {
			std::array<int, 2> temp = { y, row };
			moves.push_back(temp);
		}
		else if (state.board[y][row]->color != color) {
			array<int, 2> temp = {y,row};
			moves.push_back(temp);
			break;
		}
		else {
			break;
		}

	}

	//get all moves vertically upwards(col 7->0)
	for (int col = y - 1; col >= 0; col--) {
		if (state.board[col][x] == NULL) {
		std:: array<int, 2>temp = {col,x};
			moves.push_back(temp);
		}
		else if (state.board[col][x]->color != color) {
			array<int, 2> temp = { col,x };
			moves.push_back(temp);
			break;
		}
		else {
			break;
		}
	}

	//get all moves horizontally right(row 7->0)
	for (int row = x - 1; row >= 0; row--) {
		if (state.board[y][row] == NULL) {
			std:: array<int, 2>temp = { y,row };
			moves.push_back(temp);
		}
		else if (state.board[y][row]->color != color) {
			array<int, 2> temp = { y,row };
			moves.push_back(temp);
			break;
		}
		else {
			break;
		}

	}
	vector<array<int, 2>> fltrd = fltrMoves(state,moves,y,x);
	state.board[y][x]->moves = fltrd;
	return fltrd;
}

void Pawn::SetHasMoved(bool moved){
	hasMoved = moved;
}

void Pawn::SetEnPassant(bool enpassant)
{
	enPassant = enpassant;
}

vector<array<int, 2>> Pawn::getMoves(GameState &state, int y, int x)
{
	bool white = true;
	bool black = false;
	vector<array<int, 2>>moves;
	if (color == white) {
		//if pawn hasn't moved, it can move 2 spaces foward
		if (hasMoved == false && y -2  >= 0) {
			if (state.board[y - 2][x] == NULL && state.board[y - 1][x] == NULL) {
				array<int, 2>temp = { y - 2,x };
				moves.push_back(temp);
			}
		}
		//check in front
		if (y - 1 >= 0 && state.board[y-1][x]==NULL) {
			array<int, 2>temp = { y - 1,x };
			moves.push_back(temp);
		}
		//check if there is a black piece to its top left
		if (y - 1 >= 0 && x - 1 >= 0) {
			if (state.board[y - 1][x - 1] != NULL && state.board[y-1][x-1]->color == black) {
			array<int, 2>temp = { y - 1,x-1 };
			moves.push_back(temp);
			}
		}
		//check if there is a black piece to its top right
		if (y - 1 >= 0 && x + 1 <8) {
			if (state.board[y - 1][x + 1] != NULL && state.board[y - 1][x + 1]->color == black) {
				array<int, 2>temp = { y - 1,x + 1 };
				moves.push_back(temp);
			}
		}
		//check enpassant
		if (y == 3) {
			//check left
			if (x - 1 >= 0 && state.board[y][x-1] != nullptr && state.board[y][x-1]->color == black) {
				if (state.board[y][x - 1]->id == 0) {
					Pawn* pawn = dynamic_cast<Pawn*>(state.board[y][x-1]);
					if (pawn->enPassant == true) {
						moves.push_back({y-1,x-1});
					}
				}
			}//chwck right
			if (x + 1 < 8 && state.board[y][x+1] != nullptr && state.board[y][x+1]->color == black) {
				if (state.board[y][x+1]-> id == 0) {
					Pawn* pawn = dynamic_cast<Pawn*>(state.board[y][x + 1]);
					if (pawn->enPassant == true) {
						moves.push_back({y-1,x+1});
					}
				}

			}
		}

	}
	else {
		//if pawn hasn't moved, it can move 2 spaces foward
		if (hasMoved == false && y + 2 < 8) {
			if (state.board[y + 2][x] == NULL && state.board[y + 1][x] == NULL) {
				array<int, 2>temp = { y + 2,x };
				moves.push_back(temp);
			}
		}
		//check in front
		if (y + 1 < 8 && state.board[y + 1][x] == NULL) {
			array<int, 2>temp = { y + 1,x };
			moves.push_back(temp);
		}
		//check if there is a white piece to its bottom left
		if (y + 1 < 8 && x - 1 >= 0) {
			if (state.board[y + 1][x - 1] != NULL && state.board[y + 1][x - 1]->color == white) {
				array<int, 2>temp = { y + 1,x - 1 };
				moves.push_back(temp);
			}
		}
		//check if there is a white piece to its bottom right
		if (y + 1 < 8 && x + 1 < 8) {
			if (state.board[y + 1][x + 1] != NULL && state.board[y + 1][x + 1]->color == white) {
				array<int, 2>temp = { y + 1,x + 1 };
				moves.push_back(temp);
			}
		}
		//check enpassant
		if (y == 4) {
			//check left
			if (x - 1 >= 0 && state.board[y][x - 1] != nullptr && state.board[y][x - 1]->color == white) {
				if (state.board[y][x - 1]->id == 0) {
					Pawn* pawn = dynamic_cast<Pawn*>(state.board[y][x - 1]);
					if (pawn->enPassant == true) {
						moves.push_back({ y + 1,x - 1 });
					}
				}
			}//chwck right
			if (x + 1 < 8 && state.board[y][x + 1] != nullptr && state.board[y][x + 1]->color == white) {
				if (state.board[y][x + 1]->id == 0) {
					Pawn* pawn = dynamic_cast<Pawn*>(state.board[y][x + 1]);
					if (pawn->enPassant == true) {
						moves.push_back({ y + 1,x + 1 });
					}
				}

			}
		}
	}
	vector<array<int, 2>> fltrd = fltrMoves(state, moves, y, x);
	state.board[y][x]->moves = fltrd;
	return fltrd;
}

vector<array<int, 2>> Knight::getMoves(GameState& state, int y, int x)
{
	vector<array<int, 2>>moves;

	if (y - 2 >= 0) {
		if (x - 1 >= 0) { 
			if (state.board[y - 2][x - 1] == NULL || state.board[y - 2][x - 1]->color != color) {
				moves.push_back({ y - 2,x - 1 });
			}
		}
		if (x + 1 < 8) { 
			if (state.board[y - 2][x + 1] == NULL || state.board[y - 2][x + 1]->color != color) {
				moves.push_back({ y - 2,x + 1 });
			}
		}
	}
	if (x - 2 >= 0) {
		if (y - 1 >= 0) { 
			if (state.board[y - 1][x - 2] == nullptr || state.board[y - 1][x - 2]->color != color) {
				moves.push_back({ y - 1,x - 2 });
			}
		}
		if (y + 1 < 8) {
			if (state.board[y + 1][x - 2] == nullptr || state.board[y + 1][x - 2]->color != color) {
				moves.push_back({ y + 1,x - 2 });
			}
		}
	}
	if (y + 2 < 8) {
		if (x - 1 >= 0) { 
			if (state.board[y + 2][x - 1] == NULL || state.board[y + 2][x - 1]->color != color) {
				moves.push_back({ y + 2,x - 1 });
			}
		}
		if (x + 1 < 8) { 
			if (state.board[y + 2][x + 1] == NULL || state.board[y + 2][x + 1]->color != color) {
				moves.push_back({ y + 2,x + 1 });
			}
		}
	}
	if (x + 2 < 8) {
		if (y - 1 >= 0) {
			if (state.board[y - 1][x + 2] == NULL || state.board[y - 1][x + 2]->color != color) {
				moves.push_back({ y - 1,x + 2 });
			}
		}
		if (y + 1 < 8) { 
			if (state.board[y + 1][x + 2] == NULL || state.board[y + 1][x + 2]->color != color) {
				moves.push_back({ y + 1,x + 2 });
			}
			}
	}

	vector<array<int, 2>> fltrd = fltrMoves(state, moves, y, x);
	state.board[y][x]->moves = fltrd;
	return fltrd;
}

vector<array<int, 2>> Bishop::getMoves(GameState &state, int y, int x)
{
	vector<array<int, 2>> moves;
	
	// iterate upward right
	int row = x+1;
	int col = y-1;
	while(row < 8 && col >=0 ) {
		if (state.board[col][row] == NULL) {
			moves.push_back({col,row});
		}
		else if (state.board[col][row]->color != color) {
			moves.push_back({col,row});
			break;
		}
		else {
			break;
		}
		row++;
		col--;

	}

	//iterate upward left
	row = x - 1;
	col = y - 1;
	while (row >= 0 && col >= 0) {
		if (state.board[col][row] == NULL) {
			moves.push_back({ col,row });
		}
		else if (state.board[col][row]->color != color) {
			moves.push_back({col,row});
			break;
		}
		else {
			break;
		}
		row--;
		col--;
	}

	//iterate downward left
	row = x - 1;
	col = y + 1;
	while (row >= 0 && col < 8) {
		if (state.board[col][row] == NULL) {
			moves.push_back({ col,row });
		}
		else if (state.board[col][row]->color != color) {
			moves.push_back({ col,row });
			break;
		}
		else {
			break;
		}
		row--;
		col++;
	}

	//iterate downward right
	row = x + 1;
	col = y + 1;
	while (row < 8 && col < 8) {
		if (state.board[col][row] == NULL) {
			moves.push_back({ col,row });
		}
		else if (state.board[col][row]->color != color) {
			moves.push_back({ col,row });
			break;
		}
		else {
			break;
		}
		row++;
		col++;
	}

	vector<array<int, 2>> fltrd = fltrMoves(state, moves, y, x);
	state.board[y][x]->moves = fltrd;
	return fltrd;
}

vector<array<int, 2>> Queen::getMoves(GameState& state, int y, int x)
{
	vector<array<int, 2>> moves;
	//get all moves vertically downwards(col 0->7)
	for (int col = y + 1; col < 8; col++) {
		if (state.board[col][x] == NULL) {
			std::array<int, 2> temp = { col,x };
			moves.push_back(temp);
		}
		else if (state.board[col][x]->color != color) {
			array<int, 2> temp = { col,x };
			moves.push_back(temp);
			break;
		}
		else {
			break;
		}
	}
	//get all moves horizontally right(row 0->7)
	for (int row = x + 1; row < 8; row++) {
		if (state.board[y][row] == NULL) {
			std::array<int, 2> temp = { y, row };
			moves.push_back(temp);
		}
		else if (state.board[y][row]->color != color) {
			array<int, 2> temp = { y,row };
			moves.push_back(temp);
			break;
		}
		else {
			break;
		}

	}
	//get all moves vertically upwards(col 7->0)
	for (int col = y - 1; col >= 0; col--) {
		if (state.board[col][x] == NULL) {
			std::array<int, 2>temp = { col,x };
			moves.push_back(temp);
		}
		else if (state.board[col][x]->color != color) {
			array<int, 2> temp = { col,x };
			moves.push_back(temp);
			break;
		}
		else {
			break;
		}
	}
	//get all moves horizontally right(row 7->0)
	for (int row = x - 1; row >= 0; row--) {
		if (state.board[y][row] == NULL) {
			std::array<int, 2>temp = { y,row };
			moves.push_back(temp);
		}
		else if (state.board[y][row]->color != color) {
			array<int, 2> temp = { y,row };
			moves.push_back(temp);
			break;
		}
		else {
			break;
		}

	}
	// iterate upward right
	int row = x + 1;
	int col = y - 1;
	while (row < 8 && col >= 0) {
		if (state.board[col][row] == NULL) {
			moves.push_back({ col,row });
		}
		else if (state.board[col][row]->color != color) {
			moves.push_back({ col,row });
			break;
		}
		else {
			break;
		}
		row++;
		col--;

	}
	//iterate upward left
	row = x - 1;
	col = y - 1;
	while (row >= 0 && col >= 0) {
		if (state.board[col][row] == NULL) {
			moves.push_back({ col,row });
		}
		else if (state.board[col][row]->color != color) {
			moves.push_back({ col,row });
			break;
		}
		else {
			break;
		}
		row--;
		col--;
	}
	row = x - 1;
	col = y + 1;
	while (row >= 0 && col < 8) {
		if (state.board[col][row] == NULL) {
			moves.push_back({ col,row });
		}
		else if (state.board[col][row]->color != color) {
			moves.push_back({ col,row });
			break;
		}
		else {
			break;
		}
		row--;
		col++;
	}
	//iterate downward right
	row = x + 1;
	col = y + 1;
	while (row < 8 && col < 8) {
		if (state.board[col][row] == NULL) {
			moves.push_back({ col,row });
		}
		else if (state.board[col][row]->color != color) {
			moves.push_back({ col,row });
			break;
		}
		else {
			break;
		}
		row++;
		col++;
	}


	vector<array<int, 2>> fltrd = fltrMoves(state, moves, y, x);
	state.board[y][x]->moves = fltrd;
	return fltrd;
}

//See if king is in check
bool King::inCheck(GameState &state, int y, int x)
{
	bool white = true;
	bool black = false;
	//get all moves vertically downwards(col 0->7)
	for (int col = y + 1; col < 8; col++) {
		if (state.board[col][x] != nullptr) {
			//printf("\n%d",col);
			if (state.board[col][x]->color == color) {
				break;
			}
			else if(state.board[col][x]->id == 1 || state.board[col][x]->id == 4) {
				return true;
			}
			else {
				break;
			}
		}
	}
	//get all moves vertically upward(col 7->0)
	for (int col = y - 1; col >= 0; col--) {
		if (state.board[col][x] != NULL) {
			if (state.board[col][x]->color == color) {
				break;
			}
			else if (state.board[col][x]->id == 1 || state.board[col][x]->id == 4) {
				return true;
			}
			else {
				break;
			}
		}
	}
	//get all moves horizontally left(row 7->0)
	for (int row = x - 1; row >= 0; row--) {
		if (state.board[y][row] != NULL) {
			if (state.board[y][row]->color == color) {
				break;
			}
			else if (state.board[y][row]->id == 1 || state.board[y][row]->id ==4) {
				return true;
			}
			else {
				break;
			}
		}
	}
	//get all moves horizontally right(row 0->7)
	for (int row = x + 1; row < 8; row++) {
		if (state.board[y][row] != NULL) {
			if (state.board[y][row]->color == color) {
				break;
			}
			else if (state.board[y][row]->id == 1 || state.board[y][row]->id == 4) {
				return true;
			}
			else {
				break;
			}
		}
	}

	// iterate upward right
	int row = x + 1;
	int col = y - 1;
	while (row < 8 && col >= 0) {
		if (state.board[col][row] != NULL) {
			if (state.board[col][row]->color == color) {
				break;
			}
			else if (state.board[col][row]->id == 3 || state.board[col][row]->id == 4) {
				return true;
			}
			else {
				break;
			}
		}
		row++;
		col--;
	}
	// iterate upward left
	row = x - 1;
	col = y - 1;
	while (row >= 0 && col >= 0) {
		if (state.board[col][row] != NULL) {
			if (state.board[col][row]->color == color) {
				break;
			}
			else if (state.board[col][row]->id == 3 || state.board[col][row]->id == 4) {
				return true;
			}
			else {
				break;
			}
		}
		row--;
		col--;
	}
	//iterate downward left
	row = x - 1;
	col = y + 1;
	while (row >= 0 && col < 8) {
		if (state.board[col][row] != NULL) {
			if (state.board[col][row]->color == color) {
				break;
			}
			else if (state.board[col][row]->id == 3 || state.board[col][row]->id == 4) {
				return true;
			}
			else {
				break;
			}
		}
		row--;
		col++;
	}
	//iterate downward right
	row = x + 1;
	col = y + 1;
	while (row < 8 && col < 8) {
		if (state.board[col][row] != NULL) {
			if (state.board[col][row]->color == color) {
				break;
			}
			else if (state.board[col][row]->id == 3 || state.board[col][row]->id == 4) {
				return true;
			}
			else {
				break;
			}
		}
		row++;
		col++;
	}

	if (y - 2 >= 0) {
		if (x - 1 >= 0) {
			if (state.board[y - 2][x - 1] != NULL && state.board[y - 2][x - 1]->color != color) {
				if (state.board[y - 2][x - 1]->id == 2) { return true; }
			}
		}
		if (x + 1 < 8) {
			if (state.board[y - 2][x + 1] != NULL && state.board[y - 2][x + 1]->color != color) {
				if (state.board[y - 2][x + 1]->id == 2) { return true; }
			}
		}
	}
	if (y + 2 < 8) {
		if (x - 1 >= 0) {
			if (state.board[y + 2][x - 1] != NULL && state.board[y + 2][x - 1]->color != color) {
				if (state.board[y + 2][x - 1]->id == 2) { return true; }
			}
		}
		if (x + 1 < 8) {
			if (state.board[y + 2][x + 1] != NULL && state.board[y + 2][x + 1]->color != color) {
				if (state.board[y + 2][x + 1]->id == 2) { return true; }
			}
		}
	}
	if (x - 2 >= 0) {
		if (y - 1 >= 0) {
			if (state.board[y - 1][x - 2] != NULL && state.board[y - 1][x - 2]->color != color) {
				if (state.board[y - 1][x - 2]->id == 2) { return true; }
			}
		}
		if (y + 1 < 8) {
			if (state.board[y + 1][x - 2] != NULL && state.board[y + 1][x - 2]->color != color) {
				if (state.board[y + 1][x - 2]->id == 2) { return true; }
			}
		}
	}
	if (x + 2 < 8) {
		if (y - 1 >= 0) {
			if (state.board[y - 1][x + 2] != NULL && state.board[y - 1][x + 2]->color != color) {
				if (state.board[y - 1][x + 2]->id == 2) { return true; }
			}
		}
		if (y + 1 < 8) {
			if (state.board[y + 1][x + 2] != NULL && state.board[y + 1][x + 2]->color != color) {
				if (state.board[y + 1][x + 2]->id == 2) { return true; }
			}
		}
	}

	if (x - 1 >= 0) {
		if (y - 1 >= 0) {
			if (state.board[y - 1][x - 1] != NULL && state.board[y - 1][x - 1]->color != color) {
				if (state.board[y - 1][x - 1]->id == 5) { return true; }
			}
		}
		if (state.board[y][x - 1] != NULL && state.board[y][x - 1]->color != color) {
			if (state.board[y][x - 1]->id == 5) { return true; }
		}
		if (y + 1 < 8) {
			if (state.board[y + 1][x - 1] != NULL && state.board[y + 1][x - 1]->color != color) {
				if (state.board[y+1][x - 1]->id == 5) { return true; }
			}
		}
	}
	if (x + 1 < 8) {
		if (y - 1 >= 0) {
			if (state.board[y - 1][x + 1] != NULL && state.board[y - 1][x + 1]->color != color) {
				if (state.board[y-1][x + 1]->id == 5) { return true; }
			}
		}
		if (state.board[y][x + 1] != NULL && state.board[y][x + 1]->color != color) {
			if (state.board[y][x + 1]->id == 5) { return true; }
		}
		if (y + 1 < 8) {
			if (state.board[y + 1][x + 1] != NULL && state.board[y + 1][x + 1]->color != color) {
				if (state.board[y + 1][x + 1]->id == 5) { return true; }
			}
		}
	}
	if (y - 1 >= 0) {
		if (state.board[y - 1][x] != NULL && state.board[y - 1][x]->color != color) {
			if (state.board[y -1 ][x ]->id == 5) { return true; }
		}
	}
	if (y + 1 < 8) {
		if (state.board[y + 1][x] != NULL && state.board[y + 1][x]->color != color) {
			if (state.board[y + 1][x]->id == 5) { return true; }
		}
	}

	
	if (color == white) {
		//top left
		if (y - 1 >= 0 && x - 1 >= 0 && state.board[y - 1][x - 1] != NULL) {
			if (state.board[y - 1][x - 1]->color == black) {
				if (state.board[y - 1][x - 1]->id == 0) { return true; }
			}
		}
		//top right
		if (y - 1 >= 0 && x + 1 < 8 && state.board[y - 1][x + 1] != NULL) {
			if (state.board[y - 1][x + 1]->color == black) {
				if (state.board[y - 1][x + 1]->id == 0) { return true; }
			}
		}
	}
	else {
		//bottom left
		if (y + 1 < 8 && x - 1 >= 0 && state.board[y + 1][x - 1] != NULL) {
			if (state.board[y + 1][x - 1]->color == white) {
				if (state.board[y + 1][x - 1]->id == 0) { return true; }
			}
		}
		//bottom right
	}
	
	return false;
}

vector<array<int, 2>> King::getMoves(GameState& state, int y, int x)
{
	bool white = true;
	bool black = false;
	bool unSafe;
	vector<array<int, 2>> moves;
	//check left side
	if (x - 1 >= 0) {
		if (y - 1 >= 0) {
			if (state.board[y - 1][x - 1] == NULL || state.board[y - 1][x - 1]->color != color) {
				moves.push_back({y-1,x-1});
			}
		}
		if (state.board[y][x - 1] == NULL || state.board[y][x - 1]->color != color) {
			moves.push_back({ y,x - 1 });
		}
		if (y + 1 < 8) {
			if (state.board[y + 1][x - 1] == NULL || state.board[y + 1][x - 1]->color != color) {
				moves.push_back({ y + 1,x - 1 });
			}
		}
	}
	//check right side
	if (x + 1 < 8) {
		if (y - 1 >= 0) {
			if (state.board[y - 1][x + 1] == NULL || state.board[y - 1][x + 1]->color != color) {
				moves.push_back({ y - 1,x+1 });
			}
		}
		if (state.board[y][x + 1] == NULL || state.board[y][x + 1]->color != color) {
			moves.push_back({ y,x + 1 });
		}
		if (y + 1 < 8) {
			if (state.board[y + 1][x + 1] == NULL || state.board[y + 1][x + 1]->color != color) {
				moves.push_back({ y + 1,x + 1 });
			}
		}
	}
	//check front and back
	if (y - 1 >= 0) {
		if (state.board[y - 1][x] == NULL || state.board[y - 1][x]->color != color) {
			moves.push_back({y-1,x});
		}
	}
	if (y + 1 < 8) {
		if (state.board[y + 1][x] == NULL || state.board[y + 1][x]->color != color) {
			moves.push_back({ y + 1,x });
		}
	}
	//castling
	King* king = dynamic_cast<King*>(state.board[y][x]);
	bool kingInCheck = king->inCheck(state, y, x);
	if (hasMoved == false && kingInCheck == false) {
		//check white side
		if (color == white) {
			//check there is a white rook at [7][0]
			if (state.board[7][0] != nullptr && state.board[7][0]->color == color && state.board[7][0]->id == 1) {
				Rook* cast = dynamic_cast<Rook*>(state.board[7][0]);
				//see if queen side rook has not moved there is no pieces between the king and the queen side rook
				if (cast->hasMoved == false && state.board[7][1] == nullptr && state.board[7][2] == nullptr && state.board[7][3] == nullptr) {
					//see if king passes through check
					unSafe = state.safeMove(state, y, x, 7, 3);
					if (unSafe == false) {
						moves.push_back({7,2});
					}
				}
			}
			//check there is a white rook at [7][7]
			if (state.board[7][7] != nullptr && state.board[7][7]->color == color && state.board[7][7]->id == 1) {
				Rook* castr = dynamic_cast<Rook*>(state.board[7][7]);
				//see if king side rook has not moved there is no pieces between the king and the queen side rook
				if (castr->hasMoved == false && state.board[7][6] == nullptr && state.board[7][5] == nullptr) {
					//see if king passes through check
					unSafe = state.safeMove(state, y, x, 7, 5);
					if (unSafe == false) {
						moves.push_back({ 7,6 });
					}
				}
			}
		}

		else {
			//check if there is a black rook at [0][0]
			if (state.board[0][0] != nullptr && state.board[0][0]->color == color && state.board[0][0]->id == 1) {
				Rook* cast = dynamic_cast<Rook*>(state.board[0][0]);
				//see if queen side rook has not moved there is no pieces between the king and the queen side rook
				if (cast->hasMoved == false && state.board[0][1] == nullptr && state.board[0][2] == nullptr && state.board[0][3] == nullptr) {
					//see if king passes through check
					unSafe = state.safeMove(state, y, x, 0, 3);
					if (unSafe == false) {
						moves.push_back({ 0,2 });
					}
				}
			}
			//check if there is a black rook at [0][7]
			if (state.board[0][7] != nullptr && state.board[0][7]->color == color && state.board[0][7]->id == 1) {
				Rook* castr = dynamic_cast<Rook*>(state.board[0][7]);
				//see if king side rook has not moved there is no pieces between the king and the queen side rook
				if (castr->hasMoved == false && state.board[0][6] == nullptr && state.board[0][5] == nullptr) {
					//see if king passes through check
					unSafe = state.safeMove(state, y, x, 0, 5);
					if (unSafe == false) {
						moves.push_back({ 0,6 });
					}
				}
			}
		}
	}

	vector<array<int, 2>> fltrd = fltrMoves(state, moves, y, x);
	state.board[y][x]->moves = fltrd;
	return fltrd;
}

vector<array<int, 2>> Piece::getAttackingMoves(GameState &state, int y, int x)
{
	vector<array<int, 2>>moves = {};
	if (state.board[y][x]->id == 0) {
		if (state.board[y][x]->color == true) {
			if (y - 1 >= 0) {
				if (x - 1 >= 0) {
					moves.push_back({ y - 1,x - 1 });
				}
				if (x + 1 < 8 ) {
					moves.push_back({ y - 1, x + 1 });
				}
				if (state.board[y - 1][x] == nullptr) {
					moves.push_back({y-1,x});
				}
			}
		}
		else {
			if (y + 1 < 8) {
				if (x - 1 >= 0) {
					moves.push_back({ y - 1,x - 1 });
				}
				if (x + 1 < 8) {
					moves.push_back({ y - 1, x + 1 });
				}
				if (state.board[y + 1][x] == nullptr) {
					moves.push_back({ y - 1,x });
				}
			}
		}
	}
	else if (state.board[y][x]->id == 2) {
		if (y - 2 >= 0) {
			if (x - 1 >= 0) {
				moves.push_back({ y - 2,x - 1 });
			}
			if (x + 1 < 8) {
				moves.push_back({ y - 2,x + 1 });
			}
		}
		if (x - 2 >= 0) {
			if (y - 1 >= 0) {
				moves.push_back({ y - 1,x - 2 });
			}
			if (y + 1 < 8) {
				moves.push_back({ y + 1,x - 2 });
			}
		}
		if (y + 2 < 8) {
			if (x - 1 >= 0) {
				moves.push_back({ y + 2,x - 1 });
			}
			if (x + 1 < 8) {
				moves.push_back({ y + 2,x + 1 });
			}
		}if (x + 2 < 8) {
			if (y - 1 >= 0) {
				moves.push_back({ y - 1,x + 2 });
			}
			if (y + 1 < 8) {
				moves.push_back({ y + 1,x + 2 });
			}
		}

	}
	return moves;
}
