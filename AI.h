#include "GameState.h"
#include "Piece.h"

#pragma once

GameState CopyGameState(GameState state);
//vector<array<int, 2>> arrangeMoveableUnits(GameState state, vector < array<int, 2>> units);
int TreePromote(GameState& state, int y, int x, string unitChar);
int TreeMove(GameState &state, int y_old, int x_old, int y_new, int x_new);
array<int, 3> minimax(GameState state, int depth, int alpha, int beta, bool player);

void AIMove(GameState &state, int y_old, int x_old, int y_new, int x_new);

