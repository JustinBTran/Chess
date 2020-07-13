#pragma once
#include <stdlib.h>  
#include "GameState.h"

class Transposition {
public:
	Transposition(unsigned int key, int d, int eval, bool color) {
		zobristKey = key;
		if (color == true) {
			whiteEval = eval;
			blackEval = 100000; //invalid int
			depthW = d;

		}
		else {
			blackEval = eval;
			whiteEval = 100000;
			depthB = d;
		}
	}
	unsigned int zobristKey;
	int depthW;
	int depthB;
	int whiteEval;
	int blackEval;
};


class TranspositionTable {
public:
	TranspositionTable(){
		for (int i = 0; i < 64; i++) {
			for (int j = 0; j < 13; j++) {
				keys[i][j] = (unsigned int) rand() % 4294967295;
			}
			//enpassant
			if ((i > 23 && i < 32) || (i <= 39 && i>=32)) {// enpassant
				keys[i][13] = (unsigned int)rand() % 4294967295;
			}
			else if (i == 0) {
				keys[i][13] = (unsigned int)rand() % 4294967295;
			}
			else if (i == 4) {
				keys[i][13] = (unsigned int)rand() % 4294967295;
			}
			else if (i == 7) {
				keys[i][13] = (unsigned int)rand() % 4294967295;
			}
			else if (i == 56) {
				keys[i][13] = (unsigned int)rand() % 4294967295;
			}
			else if (i == 60) {
				keys[i][13] = (unsigned int)rand() % 4294967295;
			}
			else if (i == 63) {
				keys[i][13] = (unsigned int)rand() % 4294967295;
			}	
		}
		for (int i = 0; i < 1000; i++) {
			transposeList[i] = nullptr;
		}
	}
	unsigned int keys[64][14];
	unsigned int getKey(int rol, int col, int id, bool booln, bool color);
	Transposition* transposeList[1000];
	unsigned int getKobristKey(GameState state);
	unsigned int updateKobristKey(GameState state, unsigned int kobristKey, int y_old, int x_old, int y_new, int x_new);
	int hashFunction(unsigned int kobristKey);
	unsigned int updateKobristEnpassant(Piece* board[8][8], unsigned int key, bool player);
};

