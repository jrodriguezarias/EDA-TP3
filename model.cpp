/**
 * @brief Implements the Reversi game model
 * @author Marc S. Ressl
 *
 * @copyright Copyright (c) 2023-2024
 */

#include "raylib.h"
#include <cstring>
#include "model.h"

void initModel(GameModel &model)
{
    model.gameOver = true;

    model.playerTime[0] = 0;
    model.playerTime[1] = 0;

    memset(model.board, PIECE_EMPTY, sizeof(model.board));
}

void startModel(GameModel &model)
{
    model.gameOver = false;

    model.currentPlayer = PLAYER_BLACK;

    model.playerTime[0] = 0;
    model.playerTime[1] = 0;
    model.turnTimer = GetTime();

    memset(model.board, PIECE_EMPTY, sizeof(model.board));
    model.board[BOARD_SIZE / 2 - 1][BOARD_SIZE / 2 - 1] = PIECE_WHITE;
    model.board[BOARD_SIZE / 2 - 1][BOARD_SIZE / 2] = PIECE_BLACK;
    model.board[BOARD_SIZE / 2][BOARD_SIZE / 2] = PIECE_WHITE;
    model.board[BOARD_SIZE / 2][BOARD_SIZE / 2 - 1] = PIECE_BLACK;
}

Player getCurrentPlayer(GameModel &model)
{
    return model.currentPlayer;
}

int getScore(GameModel &model, Player player)
{
    int score = 0;

    for (int y = 0; y < BOARD_SIZE; y++)
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            if (((model.board[y][x] == PIECE_WHITE) &&
                 (player == PLAYER_WHITE)) ||
                ((model.board[y][x] == PIECE_BLACK) &&
                 (player == PLAYER_BLACK)))
                score++;
        }

    return score;
}

double getTimer(GameModel &model, Player player)
{
    double turnTime = 0;

    if (!model.gameOver && (player == model.currentPlayer))
        turnTime = GetTime() - model.turnTimer;

    return model.playerTime[player] + turnTime;
}

Piece getBoardPiece(GameModel &model, Square square)
{
    return model.board[square.y][square.x];
}

void setBoardPiece(GameModel &model, Square square, Piece piece)
{
    model.board[square.y][square.x] = piece;
}

bool isSquareValid(Square square)
{
    return (square.x >= 0) &&
           (square.x < BOARD_SIZE) &&
           (square.y >= 0) &&
           (square.y < BOARD_SIZE);
}

void getValidMoves(GameModel &model, Moves &validMoves)
{

    Square borders[8] = { {1,0}, {1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1}, {0,-1}, {1,-1}};
    int currentPlayer = (getCurrentPlayer(model) == PLAYER_WHITE)? PIECE_WHITE : PIECE_BLACK;
    int currentOpponent = (getCurrentPlayer(model) == PLAYER_WHITE)? PIECE_BLACK : PIECE_WHITE;

    for (int y = 0; y < BOARD_SIZE; y++)
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            Square move = {x, y};
           
            if (getBoardPiece(model, move) == PIECE_EMPTY)
            {
                bool pieceFound = false; //flag that tracks if another piece has been found in one of the valid directions order to validate the move

                for (auto &direction: borders) //iterates through adjacent places
                {
                    Square adjacentSpot = {x + direction.x, y + direction.y};

                    if (getBoardPiece(model, adjacentSpot) == currentOpponent 
                                      && isSquareValid(adjacentSpot)) //if an opponent piece is adjacent
                    {


                        while(isSquareValid(adjacentSpot) && (getBoardPiece(model, adjacentSpot) != PIECE_EMPTY)) //search for a player piece in the direction that it was found
                        {
                            adjacentSpot.x += direction.x;
                            adjacentSpot.y += direction.y;

                         
                            if((getBoardPiece(model, adjacentSpot) == currentPlayer))  {
                                validMoves.push_back(move);
                                pieceFound = true;
                            }

                            if(pieceFound)
                                break;

                        }
                    }

                    if(pieceFound)
                        break;
                }
            }
        }
}

bool playMove(GameModel &model, Square move)
{
    // Set game piece
    Piece piece =
        (getCurrentPlayer(model) == PLAYER_WHITE)
            ? PIECE_WHITE
            : PIECE_BLACK;
    
    Piece currentOpponent =
        (getCurrentPlayer(model) == PLAYER_WHITE)
            ? PIECE_BLACK
            : PIECE_WHITE;

    setBoardPiece(model, move, piece);

    // To-do: your code goes here...

    Square borders[8] = {{1,0}, {1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1}, {0,-1}, {1,-1}};
    
    for (auto &direction: borders)
    {
        Square adjacentSpot = {move.x + direction.x, move.y + direction.y};
        if (getBoardPiece(model, adjacentSpot) == currentOpponent 
            && isSquareValid(adjacentSpot)) //if an opponent piece is adjacent
        {

            while(isSquareValid(adjacentSpot) && (getBoardPiece(model, adjacentSpot) != PIECE_EMPTY)) 
            //search for a player piece in the direction that it was found
            {
                adjacentSpot.x += direction.x;
                adjacentSpot.y += direction.y;

                if(getBoardPiece(model, adjacentSpot) == piece)//encontre una pieza de mi tipo)
                {
                    //agarro todas las piezas en el medio y las doy vuelta

                    while(adjacentSpot.x != move.x || adjacentSpot.y != move.y)
                    {
                        adjacentSpot.x -= direction.x;
                        adjacentSpot.y -= direction.y;
                        setBoardPiece(model, adjacentSpot, piece);
                    }
                    break;
                }
            }
        }
        
    }



    
    
    // Update timer
    double currentTime = GetTime();
    model.playerTime[model.currentPlayer] += currentTime - model.turnTimer;
    model.turnTimer = currentTime;

    // Swap player
    model.currentPlayer =
        (model.currentPlayer == PLAYER_WHITE)
            ? PLAYER_BLACK
            : PLAYER_WHITE;

    // Game over?
    Moves validMoves;
    getValidMoves(model, validMoves);

    if (validMoves.size() == 0) {

        //swap player
        model.currentPlayer=
            (model.currentPlayer == PLAYER_WHITE)
                ? PLAYER_BLACK
                : PLAYER_WHITE;

        Moves validMoves;
        getValidMoves(model, validMoves);
        if(validMoves.size() == 0)
            model.gameOver = true;
    }



    return true;
}
