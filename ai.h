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

//Arbitrary value that was experimentally found to be the most efficient for 1000000 nodes. Might need to be modified if the node count is modified
#define MAX_DEPTH 12



/**
 * @brief Returns the best move for a certain position.
 *
 * @return The best move.
 */
Square getBestMove(GameModel &model);

int miniMax(GameModel model, int depth,int alpha, int beta, bool isMax);

#endif
