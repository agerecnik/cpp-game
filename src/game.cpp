#include "game.h"

using std::array;

Game::Game(size_t s) : board(s), playerOnBoard(false) {}

Game::~Game() = default;

const Board::CellType Game::getCellType(const size_t y, const size_t x)
{
    return board.getCellType(y, x);
}

const size_t Game::getBoardSize()
{
    return board.size();
}

void Game::placeWall(const size_t y, const size_t x)
{
    if (board.getCellType(y, x) == Board::CellType::PLAYER) {
        throw std::invalid_argument("Cannot place a wall on the player.");
    }
    board.setCellType(y, x, Board::CellType::WALL);
}

void Game::placePlayer(const size_t y, const size_t x)
{
    if (playerOnBoard) {
        updatePlayerPosition(y, x);
    } else {
        board.setCellType(y, x, Board::CellType::PLAYER);
        playerPosition.y = y;
        playerPosition.x = x;
        playerOnBoard = true;
    }
}

void Game::placeExit(const size_t y, const size_t x)
{
    if (board.getCellType(y, x) == Board::CellType::PLAYER) {
        throw std::invalid_argument("Cannot place an exit on the player.");
    }
    board.setCellType(y, x, Board::CellType::EXIT);
}

void Game::printBoard()
{
    board.print();
}

void Game::moveUp()
{
    if (playerPosition.y > 0) {
        if (hitWall(playerPosition.y - 1, playerPosition.x)) {
            throw wallhit_exception("Player has hit a wall.");
        }
        if (reachedExit(playerPosition.y - 1, playerPosition.x)) {
            throw exitreach_exception("Player has reached the exit.");
        }
        updatePlayerPosition(playerPosition.y - 1, playerPosition.x);
    } else {
        throw std::out_of_range("Cannot move out of the board.");
    }
}

void Game::moveDown()
{
    if (playerPosition.y + 1 < board.size()) {
        if (hitWall(playerPosition.y + 1, playerPosition.x)) {
            throw wallhit_exception("Player has hit a wall.");
        }
        if (reachedExit(playerPosition.y + 1, playerPosition.x)) {
            throw exitreach_exception("Player has reached the exit.");
        }
        updatePlayerPosition(playerPosition.y + 1, playerPosition.x);
    } else {
        throw std::out_of_range("Cannot move out of the board.");
    }
}

void Game::moveLeft()
{
    if (playerPosition.x > 0) {
        if (hitWall(playerPosition.y, playerPosition.x - 1)) {
            throw wallhit_exception("Player has hit a wall.");
        }
        if (reachedExit(playerPosition.y, playerPosition.x - 1)) {
            throw exitreach_exception("Player has reached the exit.");
        }
        updatePlayerPosition(playerPosition.y, playerPosition.x - 1);
    } else {
        throw std::out_of_range("Cannot move out of the board.");
    }
}

void Game::moveRight()
{
    if (playerPosition.x + 1 < board.size()) {
        if (hitWall(playerPosition.y, playerPosition.x + 1)) {
            throw wallhit_exception("Player has hit a wall.");
        }
        if (reachedExit(playerPosition.y, playerPosition.x + 1)) {
            throw exitreach_exception("Player has reached the exit.");
        }
        updatePlayerPosition(playerPosition.y, playerPosition.x + 1);
    } else {
        throw std::out_of_range("Cannot move out of the board.");
    }
}

bool Game::hitWall(const size_t y, const size_t x)
{
    if (board.getCellType(y, x) == Board::CellType::WALL) {
        return true;
    }
    return false;
}

bool Game::reachedExit(const size_t y, const size_t x)
{
    if (board.getCellType(y, x) == Board::CellType::EXIT) {
        return true;
    }
    return false;
}

void Game::updatePlayerPosition(const size_t newY, const size_t newX)
{
    board.setCellType(playerPosition.y, playerPosition.x, Board::CellType::EMPTY);
    playerPosition.y = newY;
    playerPosition.x = newX;
    board.setCellType(playerPosition.y, playerPosition.x, Board::CellType::PLAYER);
}