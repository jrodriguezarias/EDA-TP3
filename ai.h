/**
 * @brief Implements the Reversi game AI
 * @author Marc S. Ressl
 *
 * @copyright Copyright (c) 2023-2024
 */

#ifndef AI_H
#define AI_H

#include "model.h"

#define INF 1000000
#define MAX_NODES 1000000

#define MAX_DEPTH 12
// Arbitrary value that allows for the decision tree to be approximately 1000000 nodes in size. 
// Estimated as 2 * base 6 (the average amount of validMoves for any given moment) logarithm of the node count rounded up to the nearest integer.
// This value was experimentally calculated to be a good estimate.


/**
 * @brief Returns the best move for a certain position.
 *
 * @return The best move.
 */
Square getBestMove(GameModel &model);

int miniMax(GameModel model, int depth,int alpha, int beta, bool isMax);

#endif
