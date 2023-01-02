#ifndef GAME_H
#define GAME_H

#include <array>
#include "board.h"

class Game
{
public:
    class wallhit_exception : public std::runtime_error
    {
        using runtime_error::runtime_error;
    };

    class exitreach_exception : public std::runtime_error
    {
        using runtime_error::runtime_error;
    };

    struct Position {
        size_t y;
        size_t x;
    };

    Game(size_t size);
    ~Game();

    const Board::CellType getCellType(const size_t y, const size_t x);
    const size_t getBoardSize();

    /**
     * @brief Places a wall on the board based on the input parameters. The wall cannot be
     * placed on the player; in this case an error is thrown. The wall can be placed on an
     * exit; in this case the wall overwrites the exit.
     *
     * @param y
     * @param x
     */
    void placeWall(const size_t y, const size_t x);

    /**
     * @brief Places the player on the board based on the input parameters. The player can be
     * placed on a wall or an exit; in this case the player overwrites the wall/exit.
     *
     * @param y
     * @param x
     */
    void placePlayer(const size_t y, const size_t x);

    /**
     * @brief Places an exit on the board based on the input parameters. The exit cannot be
     * placed on the player; in this case an error is thrown. The exit can be placed on a wall,
     * in this case the exit overwrites the wall.
     *
     * @param y
     * @param x
     */
    void placeExit(const size_t y, const size_t x);
    void printBoard();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

private:
    Board board;
    Position playerPosition;
    bool playerOnBoard;

    bool hitWall(const size_t y, const size_t x);
    bool reachedExit(const size_t y, const size_t x);
    void updatePlayerPosition(const size_t y, const size_t x);
};

#endif