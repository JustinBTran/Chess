#include "GameState.h"
#include <iostream>
#include <string>

#pragma once

void ReverseVector(vector<array<int, 2>>& arr)
{
	int i = 0;
	int j = arr.size() - 1;
	array<int, 2> temp;
	while (i < j) {
		temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
		i++;
		j--;
	}
}


void GameState::PrintBoard()
{
	std::cout << "\n   0  1  2  3  4  5  6  7  \n";
	std::cout << "  ________________________  \n";
	for (int col = 0; col < 8; col++) {
		std::cout << col << "|";
		for (int row = 0; row < 8; row++) {
			string name = "-- ";
			bool check = (board[col][row] == NULL);
			char player;
			//get the piece color if there is one
			if (!check) {
				if (board[col][row]->color == true) {
					player = 'W';
				}
				else {
					player = 'B';
				}
			}
			else {
				player = '-';
			}
			name[0] = player;
			if (check) {
				//do nothing
				NULL;

			}
			else if (board[col][row]->id == 1) {
				name[1] = 'R';
			}
			else if (board[col][row]->id == 0) {
				//std::cout << "P";
				name[1] = 'P';
			}
			else if (board[col][row]->id == 2) {
				name[1] = 'N';
			}
			else if (board[col][row]->id == 3) {
				name[1] = 'B';
			}
			else if (board[col][row]->id == 4) {
				name[1] = 'Q';
			}
			else if (board[col][row]->id == 5) {
				name[1] = 'K';
			}
			else {
				//printf("id:%d",board[col][row]->id);
				name[1] = '-';
			}
			std::cout << name;

		}
		std::cout << "|\n";
	}
	std::cout << "  ________________________ \n";

}

//get the moves for all pieces, and reset enpassant
void GameState::ScanBoard(bool player) {
	bool black = false;
	bool white = true;
	Pawn* pawn;
	whiteMoveableUnits = {};
	blackMoveableUnits = {};
	blackPnts = 0;
	whitePnts = 0;
	//track to see if players lost their king
	bool hasBlackKing = false;
	bool hasWhiteKing = false;
	int movePnts = 15;
	int pwnAdvncmntFctr = 20;
	King* blackKing = dynamic_cast<King*>(board[blackKingY][blackKingX]);
	King* whiteKing = dynamic_cast<King*>(board[whiteKingY][whiteKingX]);
	bool blackKingInCheck = blackKing->inCheck(*this,blackKingY,blackKingX);
	bool whiteKingInCheck = whiteKing->inCheck(*this,whiteKingY,whiteKingX);
	
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			if (board[row][col] != nullptr) {
				Piece* test = board[row][col];
				board[row][col]->moves = board[row][col]->getMoves(*this, row, col);
				//If the piece have moves it can do, add it to (player)MoveableUnites
				if (board[row][col]->color == white) {
					if (board[row][col]->moves.size() > 0) {
						whiteMoveableUnits.push_back({ row,col });
					}
				}
				else if (board[row][col]->color == black) {
					if (board[row][col]->moves.size() > 0) {
						blackMoveableUnits.push_back({ row,col });
					}
				}

				//if it is blacks' turn, pawns on row 3 are no longer enpassant-able
				if (player == black && row == 3) {
					if (board[row][col] != nullptr && board[row][col]->id == 0) {
						pawn = dynamic_cast<Pawn*>(board[row][col]);
						pawn->SetEnPassant(false);
					}
				}
				//if it is whites' turn, pawns on row 4 are no longer enpassant-able
				if (player == white && row == 4) {
					if (board[row][col] != nullptr && board[row][col]->id == 0) {
						pawn = dynamic_cast<Pawn*>(board[row][col]);
						pawn->SetEnPassant(false);
					}
				}

				//Evaluate pnts
				switch (board[row][col]->id) {
				case 0:
					if (board[row][col]->color == white) {
						whitePnts = whitePnts + 100;
						//whitePnts = whitePnts + board[row][col]->moves.size() * movePnts;
						whitePnts = whitePnts + board[row][col]->getAttackingMoves(*this, row, col).size() * movePnts;
						whitePnts = whitePnts + (7 - row) * pwnAdvncmntFctr;
					}
					else if (board[row][col]->color == black) {
						blackPnts += 100;
						//blackPnts += board[row][col]->moves.size() * movePnts;
						blackPnts = blackPnts + board[row][col]->getAttackingMoves(*this, row, col).size() * movePnts;
						blackPnts = blackPnts + row * pwnAdvncmntFctr;
					}
					break;
				case 1:
					if (board[row][col]->color == white) {
						whitePnts = whitePnts + 500;
						whitePnts = whitePnts + board[row][col]->moves.size() * movePnts;
					}
					else if (board[row][col]->color == black) {
						blackPnts += 500;
						blackPnts += board[row][col]->moves.size() * movePnts;
					}
					break;
				case 2:
					if (board[row][col]->color == white) {
						whitePnts = whitePnts + 300;
						//whitePnts = whitePnts + board[row][col]->moves.size() * movePnts;
						whitePnts = whitePnts + board[row][col]->getAttackingMoves(*this, row, col).size() * movePnts;
					}
					else if (board[row][col]->color == black) {
						blackPnts = blackPnts + 300;
						//blackPnts += board[row][col]->moves.size() * movePnts;
						blackPnts += board[row][col]->getAttackingMoves(*this, row, col).size() * movePnts;
					}
					break;
				case 3:
					if (board[row][col]->color == white) {
						whitePnts = whitePnts + 300;
						whitePnts = whitePnts + board[row][col]->moves.size() * movePnts;
					}
					else if (board[row][col]->color == black) {
						blackPnts = blackPnts + 300;
						blackPnts += board[row][col]->moves.size() * movePnts;
					}
					break;
				case 4:
					if (board[row][col]->color == white) {
						whitePnts = whitePnts + 900;
						whitePnts = whitePnts + board[row][col]->moves.size() * movePnts;
					}
					else if (board[row][col]->color == black) {
						blackPnts += 900;
						blackPnts += board[row][col]->moves.size() * movePnts;
					}
					break;
				case 5:
					if(board[row][col]->color == white) {
						if ((row < 3 && board[7][0] == nullptr) || (row>5 && board[7][7] == nullptr)) {
							whitePnts = whitePnts + 200;
						}
						if(col>6){
							whitePnts = whitePnts + 50;
						}
					}else if (board[row][col]->color == black) {
						if ((row < 3 && board[0][0] == nullptr) || (row>5 && board[0][7] == nullptr)) {
							blackPnts = blackPnts + 200;
						}
						if (col < 1) {
							blackPnts = blackPnts + 50;
						}
					}
				}

			}
		}
	}
	//reverse black moves
	if (player == black) {
		ReverseVector(blackMoveableUnits);
	}
	if (whiteKing->hasMoved == true) {
		blackPnts = blackPnts + 20;
	}
	if (blackKing->hasMoved == true) {
		whitePnts = whitePnts + 20;
	}
	if (whiteKingInCheck && whiteMoveableUnits.size() == 0) {
		blackPnts = 10000;
		whitePnts = 0;
	}
	else if (blackKingInCheck && blackMoveableUnits.size() == 0) {
		blackPnts = 0;
		whitePnts = 10000;
	}
	else if ((!whiteKingInCheck) && whiteMoveableUnits.size() == 0) {
		blackPnts = 0;
		whitePnts = 0;
	}
	else if ((!blackKingInCheck) && blackMoveableUnits.size() == 0) {
		blackPnts = 0;
		whitePnts = 0;
	}
	else if (whiteMoveableUnits.size() == 1 && board[whiteMoveableUnits[0][0]][whiteMoveableUnits[0][1]]->id == 5) {
		whitePnts = 0;
	}
	else if (blackMoveableUnits.size() == 1 && board[blackMoveableUnits[0][0]][blackMoveableUnits[0][1]]->id == 5) {
		blackPnts = 0;
	}
}

void GameState::SetWhiteKingPos(int y, int x) {
	whiteKingX = x;
	whiteKingY = y;
}

void GameState::SetBlackKingPos(int y, int x) {
	blackKingX = x;
	blackKingY = y;
}

void GameState::SetBoard(Piece* set[8][8])
{
	for (int col = 0; col < 8; col++) {
		for (int row = 0; row < 8; row++) {
			board[col][row] = set[col][row];
		}
	}

}

//Check to see if the players king will be in check after the move. Return true if unsafe.
bool GameState::safeMove(GameState state, int y_old, int x_old, int y_new, int x_new)
{
	bool color = state.board[y_old][x_old]->color;
	bool white = true;
	bool black = false;
	array<int, 2> kingPos;
	if (color == white) {
		kingPos = { state.whiteKingY,state.whiteKingX };
	}
	else {
		kingPos = { state.blackKingY,state.blackKingX };
	}
	if (y_old == kingPos[0] && x_old == kingPos[1]) {
		kingPos = { y_new,x_new };
	}
	GameState temp;
	temp.SetBoard(state.board);
	//check for enpassant
	if (temp.board[y_old][x_old]->id == 0) {
		if (temp.board[y_new][x_new] == nullptr && x_old != x_new) {
			state.board[y_old][x_new] = nullptr;
		}
	}
	//does the move
	temp.board[y_new][x_new] = temp.board[y_old][x_old];
	temp.board[y_old][x_old] = nullptr;

	King* check = dynamic_cast<King*>(temp.board[kingPos[0]][kingPos[1]]);
	bool notSafe = check->inCheck(temp, kingPos[0], kingPos[1]);
	return notSafe;
}

//Check to see if the move is an EnPassant. If so kill the pawn that moved last turn
int GameState::EnPassant(GameState& state, int y_old, int x_old, int y_new, int x_new)
{
	if (state.board[y_old][x_old] == nullptr || state.board[y_old][x_old]->id != 0) {
		return 0;
	}
	//Enpassant means the pawn is moving to an empty stop, which is not in the same column it was before
	if (state.board[y_new][x_new] == nullptr && x_old != x_new) {
		delete(state.board[y_old][x_new]);
		state.board[y_old][x_new] = nullptr;
		//printf("EN PASSANT KILL");
		return 1;
	}

	return 0;
}

int GameState::promote(int y, int x, string unitChar)
{
	if (board[y][x] == nullptr) {
		return 0;
	}
	if (board[y][x]->id == 0) {
		if (unitChar.compare("Q") == 0) {
			Queen* queen = new Queen(board[y][x]->color);
			delete(board[y][x]);
			board[y][x] = queen;
			return 1;
		}
		else if (unitChar.compare("R") == 0) {
			Rook* rook = new Rook(board[y][x]->color);
			delete(board[y][x]);
			board[y][x] = rook;
			return 1;
		}
		else if (unitChar.compare("N") == 0) {
			Knight* knight = new Knight(board[y][x]->color);
			delete(board[y][x]);
			board[y][x] = knight;
			return 1;
		}
		else if (unitChar.compare("B") == 0) {
			Bishop* bishop = new Bishop(board[y][x]->color);
			delete(board[y][x]);
			board[y][x] = bishop;
			return 1;
		}
	}
	cout << "\ninvalid unit";
	return 0;
}

//String so that program does not crash if user enters more than 1 char
string GameState::choosePromote()
{
	string unitChar;
	printf("\n");
	cout << "Rook: R";
	cout << "\nKnight: N";
	cout << "\nBishop: B";
	cout << "\nQueen: Q";
	cout << "\n------------";
	cout << "\nEnter the desired Unit: ";
	cin >> unitChar;
	return unitChar;



	return "0";
}

//this method will change haMoved properties for Pawns, Rooks, and Kings
int GameState::blackMove(GameState& state)
{
	cout << "\nBlack Move!";
	bool white = true;
	bool black = false;
	bool nonValid;
	int id;
	int y_old;
	int x_old;
	int y_new;
	int x_new;
	bool validPiece = false;
	int prom = 0;

	while (validPiece == false) {
		printf("\n");
		cout << "enter y_old: ";
		cin >> y_old;
		cout << "enter x_old: ";
		cin >> x_old;
		if (y_old > 7 || x_old > 7) {
			printf("location out of bounds");
		}
		else if (state.board[y_old][x_old] == nullptr) {
			printf("there is no piece at that spot");
		}
		else if (state.board[y_old][x_old]->color != black) {
			printf("That piece is not black!");
			//return 0;
		}
		else {
			validPiece = true;

		}
	}
	cout << "enter y_new: ";
	cin >> y_new;
	cout << "enter x_new: ";
	cin >> x_new;

	if (y_old == y_new && x_old == x_new) {
		printf("A piece cannot move to the spot it is already in!");
		return 0;
	}
	else if (y_new > 7 || x_old > 7) {
		printf("location out of bounds");
		return 0;
	}

	else {
		//vector<array<int, 2>>moves = state.board[y_old][x_old]->getMoves(state, y_old, x_old);
		vector<array<int, 2>>moves = state.board[y_old][x_old]->moves;
		nonValid = std::find(moves.begin(), moves.end(), std::array<int, 2>{ y_new, x_new }) == moves.end();
		if (nonValid) {
			printf("That piece can't move there!");
			return 0;
		}
		else {
			//check if there is a piece in the spot we want to move. If so kill it
			if (state.board[y_new][x_new] != nullptr) {
				delete(state.board[y_new][x_new]);
			}
			id = state.board[y_old][x_old]->id;
			if (id == 0) {
				Pawn* cast = dynamic_cast<Pawn*>(board[y_old][x_old]);
				cast->hasMoved = true;
				//If the pawn moved forward 2 spaces, make it enpassant-able
				if (y_new == (y_old + 2)) {
					cast->SetEnPassant(true);
				}
				EnPassant(state, y_old, x_old, y_new, x_new);
				if (y_new == 7) {
					while (prom == 0) {
						string unitChar = choosePromote();
						prom = promote(y_old, x_old, unitChar);
					}
				}
			}
			if (id == 1) {
				Rook* cast = dynamic_cast<Rook*>(board[y_old][x_old]);
				cast->hasMoved = true;

			}
			if (id == 5) {
				King* cast = dynamic_cast<King*>(board[y_old][x_old]);
				cast->hasMoved = true;
				SetBlackKingPos(y_new, x_new);
				//move rook for castle moves
				if (y_old == 0 && x_old == 4 && y_new == y_old && x_new == (x_old - 2)) {
					state.board[0][3] = state.board[0][0];
					state.board[0][0] = nullptr;
					Rook* rook = dynamic_cast<Rook*>(board[0][3]);
					rook->hasMoved = true;
				}
				else if (y_old == 0 && x_old == 4 && y_new == y_old && x_new == (x_old + 2)) {
					state.board[0][5] = state.board[0][7];
					state.board[0][7] = nullptr;
					Rook* rook = dynamic_cast<Rook*>(board[0][5]);
					rook->hasMoved = true;
				}
			}
			state.board[y_new][x_new] = state.board[y_old][x_old];
			state.board[y_old][x_old] = nullptr;
			return 1;
		}
	}
	return 0;
}

/*
int GameState::whiteMove(GameState& state)
{
	cout << "\nWhite Move!";
	bool white = true;
	bool black = false;
	bool nonValid;
	int id;
	int y_old;
	int x_old;
	int y_new;
	int x_new;
	bool validPiece = false;
	int prom = 0;
	while (validPiece == false) {
		printf("\n");
		cout << "enter y_old: ";
		cin >> y_old;
		cout << "enter x_old: ";
		cin >> x_old;
		if (y_old > 7 || x_old > 7) {
			printf("location out of bounds");
		}
		else if (state.board[y_old][x_old] == nullptr) {
			printf("there is no piece at that spot");
		}
		else if (state.board[y_old][x_old]->color != white) {
			printf("That piece is not white!");
			//return 0;
		}
		else {
			validPiece = true;
		}
	}
	cout << "enter y_new: ";
	cin >> y_new;
	cout << "enter x_new: ";
	cin >> x_new;
	if (y_old == y_new && x_old == x_new) {
		printf("A piece cannot move to the spot it is already in!");
		return 0;
	}
	else if (y_new > 7 || x_old > 7) {
		printf("location out of bounds");
		return 0;
	}
	else {
		//vector<array<int, 2>>moves = state.board[y_old][x_old]->getMoves(state, y_old, x_old);
		vector<array<int, 2>>moves = state.board[y_old][x_old]->moves;
		nonValid = std::find(moves.begin(), moves.end(), std::array<int, 2>{ y_new, x_new }) == moves.end();
		if (nonValid) {
			printf("That piece can't move there!");
			return 0;
		}
		else {
			//check if there is a piece in the spot we want to move. If so kill it
			if (state.board[y_new][x_new] != nullptr) {
				delete(state.board[y_new][x_new]);
			}
			id = state.board[y_old][x_old]->id;
			if (id == 0) {
				Pawn* cast = dynamic_cast<Pawn*>(board[y_old][x_old]);
				cast->hasMoved = true;
				//If the pawn moved forward 2 spaces, make it enpassant-able
				if (y_new == (y_old - 2)) {
					cast->SetEnPassant(true);
				}
				EnPassant(state, y_old, x_old, y_new, x_new);
				if (y_new == 0) {
					while (prom == 0) {
						string unitChar = choosePromote();
						prom = promote(y_old, x_old, unitChar);
					}
				}
			}
			if (id == 1) {
				Rook* cast = dynamic_cast<Rook*>(board[y_old][x_old]);
				cast->hasMoved = true;
			}
			if (id == 5) {
				King* cast = dynamic_cast<King*>(board[y_old][x_old]);
				cast->hasMoved = true;
				SetWhiteKingPos(y_new, x_new);
				//move rook for castle moves
				if (y_old == 7 && x_old == 4 && y_new == y_old && x_new == (x_old - 2)) {
					state.board[7][3] = state.board[7][0];
					state.board[7][0] = nullptr;
					Rook* rook = dynamic_cast<Rook*>(board[7][3]);
					rook->hasMoved = true;
				}
				else if (y_old == 7 && x_old == 4 && y_new == y_old && x_new == (x_old + 2)) {
					state.board[7][5] = state.board[7][7];
					state.board[7][7] = nullptr;
					Rook* rook = dynamic_cast<Rook*>(board[7][5]);
					rook->hasMoved = true;
				}
			}
			state.board[y_new][x_new] = state.board[y_old][x_old];
			state.board[y_old][x_old] = nullptr;
			return 1;
		}
	}
	return 0;
}*/

int GameState::whiteMove(GameState& state, int y_old, int x_old, int y_new, int x_new)
{
	int id;
	int prom = 0;
	//check if there is a piece in the spot we want to move. If so kill it
	if (state.board[y_new][x_new] != nullptr) {
		delete(state.board[y_new][x_new]);
	}

	id = state.board[y_old][x_old]->id;
	if (id == 0) {
		Pawn* cast = dynamic_cast<Pawn*>(board[y_old][x_old]);
		cast->hasMoved = true;
		//If the pawn moved forward 2 spaces, make it enpassant-able
		if (y_new == (y_old - 2)) {
			cast->SetEnPassant(true);
		}
		EnPassant(state, y_old, x_old, y_new, x_new);
		if (y_new == 0) {
			while (prom == 0) {
				//string unitChar = choosePromote();
				//prom = promote(y_old, x_old, unitChar);
				prom = promote(y_old, x_old, "Q");
			}
		}
	}
	if (id == 1) {
		Rook* cast = dynamic_cast<Rook*>(board[y_old][x_old]);
		cast->hasMoved = true;
	}
	if (id == 5) {
		King* cast = dynamic_cast<King*>(board[y_old][x_old]);
		cast->hasMoved = true;
		SetWhiteKingPos(y_new, x_new);
		//move rook for castle moves
		if (y_old == 7 && x_old == 4 && y_new == y_old && x_new == (x_old - 2)) {
			state.board[7][3] = state.board[7][0];
			state.board[7][0] = nullptr;
			Rook* rook = dynamic_cast<Rook*>(board[7][3]);
			rook->hasMoved = true;
		}
		else if (y_old == 7 && x_old == 4 && y_new == y_old && x_new == (x_old + 2)) {
			state.board[7][5] = state.board[7][7];
			state.board[7][7] = nullptr;
			Rook* rook = dynamic_cast<Rook*>(board[7][5]);
			rook->hasMoved = true;
		}
	}
	state.board[y_new][x_new] = state.board[y_old][x_old];
	state.board[y_old][x_old] = nullptr;
	return 1;
}