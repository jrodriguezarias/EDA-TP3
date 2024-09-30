/**
 * @brief Implements the Reversi game AI
 * @author Marc S. Ressl
 *
 * @copyright Copyright (c) 2023-2024
 */

#include <cstdlib>

#include "ai.h"

#include <iostream>
#include <ostream>

#include "controller.h"

Square getBestMove(GameModel &model)
{

    // To-do: your code goes here...

    Moves validMoves;
    getValidMoves(model, validMoves);

    int index = miniMax(model, MAX_DEPTH, -INF, INF, true);
    std::cout << index << std::endl;
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


int miniMax(GameModel model, int depth, int alpha, int beta, bool isMax) {
    // Node count. Increased every time the function is called to keep count of nodes evaluated
    static int nodes;
    nodes++;


    Moves validMoves;
    getValidMoves(model, validMoves);
    
    Player currentPlayer = (getCurrentPlayer(model) == PLAYER_WHITE)? PLAYER_WHITE : PLAYER_BLACK;
    int index; // index of the best move according to the algorithm
    GameModel tempModel = model; // model used for looking into future moves without disrupting the ongoing game

    if(depth == 0 || model.gameOver || nodes == MAX_NODES){ // Heuristic evaluation 
        return getScore(model, currentPlayer);
    }


    int i;
    if(isMax) {// maximizing player
        long int max = -INF;


        for(i = 0; i < (validMoves.size() - 1) && nodes < MAX_NODES; i++) {
            tempModel = model;
            playMove(tempModel, validMoves[i]);

            int value = miniMax(model, depth - 1, alpha, beta, !isMax);//recursive call
            max = ((max <  value) ? value : max);

            /******************************
             * Alpha pruning module *
             ******************************/
            alpha = (alpha < max) ? max : alpha;
            if(beta <= alpha) {
                std::cout << "alpha prune" << std::endl;
                break; // alpha pruning
            }


        }

        if(depth == MAX_DEPTH) { // FINAL RETURN. Returns inmmediate next move's index
            nodes = 0; // reset nodes to evaluate for the next turn
            return i;
        }
        return max;

    }
    else { // minmizing player
        long int min = INF;
        for(int i = 0; i < (validMoves.size() - 1) && nodes < MAX_NODES; i++) {
            tempModel = model;
            playMove(tempModel, validMoves[i]);

            int value = miniMax(tempModel, depth - 1, alpha, beta, !isMax);//recursive call
            min = ((min >  value) ? value : min);

             /******************************
             * Beta pruning module *
             ******************************/
            beta = (beta > min) ? min : beta;
            if(alpha >= beta) {
                std::cout << "beta prune" << std::endl;
                break; // beta pruning
            }

        }
        return min;
    }
}