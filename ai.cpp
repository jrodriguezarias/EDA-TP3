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

    int index = miniMax(model, MAX_NODES,  -INF, INF, true);
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


int miniMax(GameModel model, int nodeLimit, int alpha, int beta, bool isMax) {
    static int nodes = 0;
    Moves validMoves;
    getValidMoves(model, validMoves);
    Player currentPlayer = (getCurrentPlayer(model) == PLAYER_WHITE)? PLAYER_WHITE : PLAYER_BLACK;
    int index; // index of the best move according to the algorithm
    GameModel tempModel = model;
    if(nodes == nodeLimit){
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
            nodes++;
            int value = miniMax(model, nodeLimit, alpha, beta, !isMax);
            max = ((max <  value) ? value : max);
            alpha = (alpha < max) ? max : alpha;
            if(beta <= alpha) {
                break; // alpha pruning
            }

        }

        if( nodes == nodeLimit) { // inmmediate next move
            return i - 1;
        }
        return max;

    }
    else {
        long int min = INF;
        for(int i = 0; i < validMoves.size(); i++) {
            tempModel = model;
            playMove(tempModel, validMoves[i]);
            nodes++;
            int value = miniMax(tempModel, nodeLimit, alpha, beta, !isMax);
            min = ((min >  value) ? value : min);
            beta = (beta > min) ? min : beta;
            if(beta <= alpha) {
                break; // beta pruning
            }
        }
        return min;
    }
}