#include "AI.h"


GameState CopyGameState(GameState state)
{
	GameState retState;
	retState.SetBoard(state.board);
	retState.whiteKingY = state.whiteKingY;
	retState.whiteKingX = state.whiteKingX;
	retState.blackKingY = state.blackKingY;
	retState.blackKingX = state.blackKingX;
	return retState;
}

int TreePromote(GameState& state, int y, int x, string unitChar)
{
	if (state.board[y][x] == nullptr) {
		return 0;
	}
	if (state.board[y][x]->id == 0) {
		if (unitChar.compare("Q") == 0) {
			Queen* queen = new Queen(state.board[y][x]->color);
			//delete(board[y][x]);
			state.board[y][x] = queen;
			return 1;
		}
		/*else if (unitChar.compare("R") == 0) {
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
		}*/
	}
	//cout << "\ninvalid unit";
	return 0;
}



//returns 2 if there has been a promotion, 1 if a unit had made its first move, 3 for a castle
int TreeMove(GameState& state, int y_old, int x_old, int y_new, int x_new)
{
	bool color = state.board[y_old][x_old]->color;
	int id = state.board[y_old][x_old]->id;
	bool white = true;
	bool black = false;
	int ret = 0;
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

	//check for enpassant and promotion and move 2 spaces
	if (state.board[y_old][x_old]->id == 0) {
		Pawn* pawn = dynamic_cast<Pawn*>(state.board[y_old][x_old]);
		if (pawn->hasMoved == false) {
			pawn->SetHasMoved(true);
			ret = 1;
		}
		if (state.board[y_new][x_new] == nullptr && x_old != x_new) {
			state.board[y_old][x_new] = nullptr;
		}
		else if (color == white && y_new == 0) {//en passant can't lead to a promote
			TreePromote(state, y_old, x_old, "Q");
			ret = 2;
		}
		else if (color == black && y_new == 7) {
			TreePromote(state, y_old, x_old, "Q");
			ret = 2;
		}
		else if (color == white) {
			//If the pawn moved forward 2 spaces, make it enpassant-able
			if (y_new == (y_old - 2)) {
				pawn->SetEnPassant(true);
			}
		}
		else if (color == black) {
			//If the pawn moved forward 2 spaces, make it enpassant-able
			if (y_new == (y_old + 2)) {
				pawn->SetEnPassant(true);
			}
		}
	}

	//check for castle
	if (color == white) {
		if (id == 5) {
			King* cast = dynamic_cast<King*>(state.board[y_old][x_old]);
			if (cast->hasMoved == false) {
				cast->hasMoved = true;
				ret = 1;
			}
			state.SetWhiteKingPos(y_new, x_new);
			//move rook for castle moves
			if (y_old == 7 && x_old == 4 && y_new == y_old && x_new == (x_old - 2)) {
				state.board[7][3] = state.board[7][0];
				state.board[7][0] = nullptr;
				Rook* rook = dynamic_cast<Rook*>(state.board[7][3]);
				rook->hasMoved = true;
				ret = 3;
			}
			else if (y_old == 7 && x_old == 4 && y_new == y_old && x_new == (x_old + 2)) {
				state.board[7][5] = state.board[7][7];
				state.board[7][7] = nullptr;
				Rook* rook = dynamic_cast<Rook*>(state.board[7][5]);
				rook->hasMoved = true;
				ret = 3;
			}
		}
	}
	else {
		if (id == 5) {
			King* cast = dynamic_cast<King*>(state.board[y_old][x_old]);
			if (cast->hasMoved == false) {
				cast->hasMoved = true;
				ret = 1;
			}
			state.SetBlackKingPos(y_new, x_new);
			//move rook for castle moves
			if (y_old == 0 && x_old == 4 && y_new == y_old && x_new == (x_old - 2)) {
				state.board[0][3] = state.board[0][0];
				state.board[0][0] = nullptr;
				Rook* rook = dynamic_cast<Rook*>(state.board[0][3]);
				rook->hasMoved = true;
				ret = 3;
			}
			else if (y_old == 0 && x_old == 4 && y_new == y_old && x_new == (x_old + 2)) {
				state.board[0][5] = state.board[0][7];
				state.board[0][7] = nullptr;
				Rook* rook = dynamic_cast<Rook*>(state.board[0][5]);
				rook->hasMoved = true;
				ret = 3;
			}
		}
	}
	//if rook, set hasMoved to true
	if (id == 1) {
		Rook* rook = dynamic_cast<Rook*>(state.board[y_old][x_old]);
		if (rook->hasMoved == false) {
			rook->SetHasMoved(true);
			ret = 1;
		}
		
	}
	//printf("\n 2. y_new:%d   x_new:%d ", y_new,x_new);
	state.board[y_new][x_new] = state.board[y_old][x_old];
	state.board[y_old][x_old] = nullptr;

	return ret;
}

//index 0 is the board value, index 1 is the move, index 2 is the piece to mvoe
array<int, 3> minimax(GameState state, int depth, int alpha, int beta, bool player, unsigned int kobristKey, TranspositionTable &table)
{
	bool white = true;
	bool black = false;
	Piece* blkKingPntr = state.board[state.blackKingY][state.blackKingX];
	Piece* whtKingPntr = state.board[state.whiteKingY][state.whiteKingX];
	Pawn* pawn;
	Rook* rook;
	King* king;
	unsigned int key = kobristKey;

	//if king is dead return worst value for player, need to do before board is scanned
	if (blkKingPntr == nullptr || blkKingPntr->color == white || blkKingPntr->id != 5) {
		return{ 99999,-1,-1 };
	}
	else if (whtKingPntr == nullptr || whtKingPntr->color == black || whtKingPntr->id != 5) {
		return { -99999,-1,-1 };
	}
	unsigned int stateKey = table.updateKobristEnpassant(state.board, kobristKey, player);
	state.ScanBoard(player);
	//return worst value if player is checkmated
	if (state.blackMoveableUnits.size() == 0) {
		return{ 99999,-1,-1 };
	}
	else if (state.whiteMoveableUnits.size()==0) {
		return { -99999,-1,-1 };
	}
	int value = (state.whitePnts - state.blackPnts);
	int tempMove = 0;
	int nextMove = 0;
	int currPiece = 0;
	int selectPiece = 0;
	array<int, 3> data;
	int enpass = 0;
	vector<array<int, 2>> unitMoves;
	int hash;

	if (depth == 0) {
		//the move returned here shouldnt matter
		//printf("\n Depth reached");
		return { value,-1,-1 };
	}

	//maximizing player
	if (player == white) {
		int maxEval = -99999;
		//so that the collection being iterated through does not change
		vector<array<int, 2>> units = state.whiteMoveableUnits;
		selectPiece = units[0][0]*10 + units[0][1];
		array<int,2>baseWhiteMove = (state.board[units[0][0]][units[0][1]]->moves)[0];
		nextMove = baseWhiteMove[0] * 10 + baseWhiteMove[1];
		 
		for (array<int, 2> unit : units) {
			currPiece = unit[0] * 10 + unit[1];
			state.ScanBoard(white);//reset the piece moves
			unitMoves = state.board[unit[0]][unit[1]]->moves;
			for (array <int, 2> move : unitMoves) {
				tempMove = move[0] * 10 + move[1];
				key = kobristKey; // resetKey
				key = stateKey;
				key = table.updateKobristKey(state, key, unit[0], unit[1], move[0], move[1]);
				hash = table.hashFunction(key);
				bool test = (table.transposeList[hash] != nullptr && table.transposeList[hash]->depthW >= depth && table.transposeList[hash]->zobristKey == key && table.transposeList[hash]->whiteEval != 10000);
				if (table.transposeList[hash] != nullptr && table.transposeList[hash]->depthW >= depth && table.transposeList[hash]->zobristKey == key && table.transposeList[hash]->whiteEval != 10000) {
					data = { table.transposeList[hash]->whiteEval, -1,-1};
				}
				else {
					GameState tempState = CopyGameState(state);
					enpass = TreeMove(tempState, unit[0], unit[1], move[0], move[1]);
					data = minimax(tempState, depth - 1, alpha, beta, black, key, table);
					if (table.transposeList[hash] == nullptr || table.transposeList[hash]->depthW < depth) {//replace the kobristKey if the depth is better
						delete(table.transposeList[hash]);
						table.transposeList[hash] = new Transposition(key, depth, data[0], white);
					}
					//else if(whiteEval == 10000)
					else {
						table.transposeList[hash]->whiteEval = data[0];
						table.transposeList[hash]->depthW = depth;
					}
					//have to delete new pointers from promotions to avoid stack overflow, and others
					if (enpass == 2) {
						if (tempState.board[move[0]][move[1]] != nullptr && tempState.board[move[0]][move[1]]->id == 5) {
							delete(tempState.board[move[0]][move[1]]);
							tempState.board[move[0]][move[1]] = nullptr;
						}
					}
					else if (enpass == 1) { //reset hasMoved
						if (tempState.board[move[0]][move[1]] != nullptr) {
							switch (tempState.board[move[0]][move[1]]->id) {
							case 0:
								pawn = dynamic_cast<Pawn*>(tempState.board[move[0]][move[1]]);
								pawn->SetHasMoved(false);
								pawn->enPassant = false;
								break;
							case 1:
								rook = dynamic_cast<Rook*>(tempState.board[move[0]][move[1]]);
								rook->SetHasMoved(false);
								break;
							case 5:
								king = dynamic_cast<King*>(tempState.board[move[0]][move[1]]);
								king->hasMoved = false;
								break;
							}

						}
					}
					else if (enpass == 3) {// reset hasMoved for castling
						king = dynamic_cast<King*>(tempState.board[move[0]][move[1]]);
						king->hasMoved = false;
						if (move[1] == 2) {
							rook = dynamic_cast<Rook*>(tempState.board[move[0]][move[1] + 1]);
							rook->hasMoved = false;
						}
						else if (move[1] == 6) {
							rook = dynamic_cast<Rook*>(tempState.board[move[0]][move[1] - 1]);
							rook->hasMoved = false;
						}
					}
				}
				if (data[0] > maxEval) {
					maxEval = data[0];
					nextMove = tempMove;
					selectPiece = currPiece;
				}
				if (data[0] > alpha) {
					alpha = data[0];
				}
				if (alpha >= beta) {
					break;
				}
			}
			if (alpha >= beta) {
				break;
			}
		}
		return { maxEval, nextMove,selectPiece };
	}
	else {
		int minEval = 99999;
		vector<array<int, 2>> units = state.blackMoveableUnits;
		selectPiece = units[0][0] * 10 + units[0][1];
		array<int, 2>baseBlackMove = (state.board[units[0][0]][units[0][1]]->moves)[0];
		nextMove = baseBlackMove[0] * 10 + baseBlackMove[1];
		for (array<int, 2>unit : units) {
			currPiece = unit[0] * 10 + unit[1];
			state.ScanBoard(black);//reset the piece moves
			unitMoves = state.board[unit[0]][unit[1]]->moves;
			for (array<int, 2> move : unitMoves) {
				tempMove = move[0] * 10 + move[1];
				key = kobristKey; // resetKey
				key = stateKey;
				key = table.updateKobristKey(state, key, unit[0], unit[1], move[0], move[1]);
				hash = table.hashFunction(key);
				//bool test = (table.transposeList[hash] != nullptr && table.transposeList[hash]->depth >= depth && table.transposeList[hash]->zobristKey == key && table.transposeList[hash]->blackEval != 10000);
				if (table.transposeList[hash] != nullptr && table.transposeList[hash]->depthB >= depth && table.transposeList[hash]->zobristKey == key && table.transposeList[hash]->blackEval != 10000) {
					data = { table.transposeList[hash]->blackEval, -1,-1 };
				}
				else {
					GameState tempState = CopyGameState(state);
					enpass = TreeMove(tempState, unit[0], unit[1], move[0], move[1]);
					data = minimax(tempState, depth - 1, alpha, beta, white, key, table);
					if (table.transposeList[hash] == nullptr || table.transposeList[hash]->depthB < depth) {//replace the kobristKey if the depth is better
						delete(table.transposeList[hash]);
						table.transposeList[hash] = new Transposition(key, depth, data[0], black);
					}
					//else if(blackEval == 10000)
					else {
						table.transposeList[hash]->blackEval = data[0];
						table.transposeList[hash]->depthB = depth;
					}
					//have to delete new pointers from promotions to avoid stack overflow
					if (enpass == 2) {
						if (tempState.board[move[0]][move[1]] != nullptr && tempState.board[move[0]][move[1]]->id == 5) {
							delete(tempState.board[move[0]][move[1]]);
							tempState.board[move[0]][move[1]] = nullptr;
						}
					}
					else if (enpass == 1) { //reset hasMoved
						if (tempState.board[move[0]][move[1]] != nullptr) {
							switch (tempState.board[move[0]][move[1]]->id) {
							case 0:
								pawn = dynamic_cast<Pawn*>(tempState.board[move[0]][move[1]]);
								pawn->SetHasMoved(false);
								pawn->enPassant = false;
								break;
							case 1:
								rook = dynamic_cast<Rook*>(tempState.board[move[0]][move[1]]);
								rook->SetHasMoved(false);
								break;
							case 5:
								king = dynamic_cast<King*>(tempState.board[move[0]][move[1]]);
								king->hasMoved = false;
								break;
							}

						}
					}
					else if (enpass == 3) {// reset hasMoved for castling
						king = dynamic_cast<King*>(tempState.board[move[0]][move[1]]);
						king->hasMoved = false;
						if (move[1] == 2) {
							rook = dynamic_cast<Rook*>(tempState.board[move[0]][move[1] + 1]);
							rook->hasMoved = false;
						}
						else if (move[1] == 6) {
							rook = dynamic_cast<Rook*>(tempState.board[move[0]][move[1] - 1]);
							rook->hasMoved = false;
						}

					}
				}
				if (data[0] < minEval) {
					minEval = data[0];
					nextMove = tempMove;
					selectPiece = currPiece;
				}
				if (data[0] < beta) {
					beta = data[0];
				}
				if (beta <= alpha) {
					break;
				}
			}
			if (beta <= alpha) {
				break;
			}
		}
		return {minEval, nextMove, selectPiece };

	}

	//return array<int, 2>();
}

void AIMove(GameState& state, int y_old, int x_old, int y_new, int x_new)
{
	bool white = true;
	bool black = false;
	bool color;
	bool nonValid;
	int id;
	bool validPiece = false;
	int prom = 0;

	color = state.board[y_old][x_old]->color;
	//check if there is a piece in the spot we want to move. If so kill it
	if (state.board[y_new][x_new] != nullptr) {
		delete(state.board[y_new][x_new]);
	}
	id = state.board[y_old][x_old]->id;
	if (color == black) {
		if (id == 0) {
			Pawn* cast = dynamic_cast<Pawn*>(state.board[y_old][x_old]);
			cast->hasMoved = true;
			//If the pawn moved forward 2 spaces, make it enpassant-able
			if (y_new == (y_old + 2)) {
				cast->SetEnPassant(true);
			}
			state.EnPassant(state, y_old, x_old, y_new, x_new);
			if (y_new == 7) {
				prom = state.promote(y_old, x_old, "Q");
			}
		}
		if (id == 1) {
			Rook* cast = dynamic_cast<Rook*>(state.board[y_old][x_old]);
			cast->hasMoved = true;
		}
		if (id == 5) {
			King* cast = dynamic_cast<King*>(state.board[y_old][x_old]);
			cast->hasMoved = true;
			state.SetBlackKingPos(y_new, x_new);
			//move rook for castle moves
			if (y_old == 0 && x_old == 4 && y_new == y_old && x_new == (x_old - 2)) {
				state.board[0][3] = state.board[0][0];
				state.board[0][0] = nullptr;
				Rook* rook = dynamic_cast<Rook*>(state.board[0][3]);
				rook->hasMoved = true;
			}
			else if (y_old == 0 && x_old == 4 && y_new == y_old && x_new == (x_old + 2)) {
				state.board[0][5] = state.board[0][7];
				state.board[0][7] = nullptr;
				Rook* rook = dynamic_cast<Rook*>(state.board[0][5]);
				rook->hasMoved = true;
			}
		}
	}
	else {
		if (id == 0) {
			Pawn* cast = dynamic_cast<Pawn*>(state.board[y_old][x_old]);
			cast->hasMoved = true;
			//If the pawn moved forward 2 spaces, make it enpassant-able
			if (y_new == (y_old - 2)) {
				cast->SetEnPassant(true);
			}
			state.EnPassant(state, y_old, x_old, y_new, x_new);
			if (y_new == 0) {
				prom = state.promote(y_old, x_old, "Q");
			}
		}
		if (id == 1) {
			Rook* cast = dynamic_cast<Rook*>(state.board[y_old][x_old]);
			cast->hasMoved = true;
		}
		if (id == 5) {
			King* cast = dynamic_cast<King*>(state.board[y_old][x_old]);
			cast->hasMoved = true;
			state.SetWhiteKingPos(y_new, x_new);
			//move rook for castle moves
			if (y_old == 7 && x_old == 4 && y_new == y_old && x_new == (x_old - 2)) {
				state.board[7][3] = state.board[7][0];
				state.board[7][0] = nullptr;
				Rook* rook = dynamic_cast<Rook*>(state.board[7][3]);
				rook->hasMoved = true;
			}
			else if (y_old == 7 && x_old == 4 && y_new == y_old && x_new == (x_old + 2)) {
				state.board[7][5] = state.board[7][7];
				state.board[7][7] = nullptr;
				Rook* rook = dynamic_cast<Rook*>(state.board[7][5]);
				rook->hasMoved = true;
			}
		}
	}

	state.board[y_new][x_new] = state.board[y_old][x_old];
	state.board[y_old][x_old] = nullptr;
}


