#pragma once
#include "Piece.h"
#include <unordered_map>
#include <vector>

void ReverseVector(vector<array<int, 2>>& arr);
void swap(array<int, 2> &x, array<int, 2> &y);
void quicksort(vector<array<int, 2>>& arr, int low, int high);
int partition(vector<array<int, 2>>& arr, int low, int high);

class GameState {


public:
	GameState() {}
	Piece* board[8][8];
	int whiteKingX;
	int whiteKingY;
	int blackKingX;
	int blackKingY;
	vector<array<int, 2>> blackMoveableUnits = {};
	vector<array<int, 2>> whiteMoveableUnits = {};
	int blackPnts;
	int whitePnts;


	void PrintBoard();
	void subScan(bool player, int y_lowLim, int y_upLim, int x_lowLim, int x_upLim);
	void ScanBoard(bool player);
	void SetWhiteKingPos(int y, int x);
	void SetBlackKingPos(int y, int x);
	void SetBoard(Piece* set[8][8]);


	//Idk why I passed state as an argument, but rn its too much trouble to change it
	bool safeMove(GameState &state, int y_old, int x_old, int y_new, int x_new);
	int EnPassant(GameState& state, int y_old, int x_old, int y_new, int x_new);
	int promote(int y, int x, string unitChar);
	string choosePromote();

	int blackMove(GameState& state);
	int whiteMove(GameState& state, int y_old, int x_old, int y_new, int x_new);


};