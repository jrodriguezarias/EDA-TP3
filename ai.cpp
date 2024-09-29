/**
 * @brief Implements the Reversi game AI
 * @author Marc S. Ressl
 *
 * @copyright Copyright (c) 2023-2024
 */

#include <cstdlib>

#include "ai.h"
#include "controller.h"

Square getBestMove(GameModel &model)
{

    // To-do: your code goes here...

    Moves validMoves;
    getValidMoves(model, validMoves);

    int index = miniMax(model, MAX_DEPTH,  -INF, INF, true);
    return validMoves[index];

    /*
    // +++ TEST
    // Returns a random valid move...

    Moves validMoves;
    getValidMoves(model, validMoves);

    int index = rand() % validMoves.size();
    return validMoves[index];
    // --- TEST
    */
}


int miniMax(GameModel model, int depth,int alpha, int beta, bool isMax) {

    Moves validMoves;
    getValidMoves(model, validMoves);
    Player currentPlayer = (getCurrentPlayer(model) == PLAYER_WHITE)? PLAYER_WHITE : PLAYER_BLACK;
    int index; // index of the best move according to the algorithm
    GameModel tempModel = model;
    if(depth == 0){
        return getScore(model, currentPlayer);
    }


    int i;
    if(isMax) {
        long int max = -INF;


        for(i = 0; i < validMoves.size(); i++) {
            tempModel = model;
            playMove(tempModel, validMoves[i]);
            if(tempModel.gameOver) {
                return getScore(model, currentPlayer);
            }
            int value = miniMax(model, depth - 1, alpha, beta, !isMax);
            max = ((max <  value) ? value : max);
            alpha = (alpha < max) ? max : alpha;
            if(beta <= alpha) {
                break; // alpha pruning
            }

        }

        if(depth == MAX_DEPTH) { // inmmediate next move
            return i - 1;
        }
        return max;

    }
    else {
        long int min = INF;
        for(int i = 0; i < validMoves.size(); i++) {
            tempModel = model;
            playMove(tempModel, validMoves[i]);
            int value = miniMax(tempModel, depth - 1, alpha, beta, !isMax);
            min = ((min >  value) ? value : min);
            beta = (beta > min) ? min : beta;
            if(beta <= alpha) {
                break; // beta pruning
            }
        }
        return min;
    }
}