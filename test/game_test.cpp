#include <gtest/gtest.h>
#include "../src/game.h"

TEST(game_test, construct_game)
{
    size_t size = 10;
    Game game(size);
    EXPECT_EQ(game.getBoardSize(), size);
}

TEST(game_test, place_player)
{
    size_t size = 10;
    Game game(size);
    game.placePlayer(2, 3);
    EXPECT_EQ(game.getCellType(2, 3), Board::CellType::PLAYER);
}

TEST(game_test, place_player_twice)
{
    size_t size = 10;
    Game game(size);
    game.placePlayer(8, 7);
    game.placePlayer(1, 0);
    EXPECT_EQ(game.getCellType(1, 0), Board::CellType::PLAYER);
    EXPECT_EQ(game.getCellType(8, 7), Board::CellType::EMPTY);
}

TEST(game_test, place_wall)
{
    size_t size = 10;
    Game game(size);
    game.placeWall(2, 3);
    EXPECT_EQ(game.getCellType(2, 3), Board::CellType::WALL);
}

TEST(game_test, place_wall_on_player)
{
    size_t size = 10;
    Game game(size);
    game.placePlayer(5, 6);
    EXPECT_THROW(game.placeWall(5, 6), std::invalid_argument);
    EXPECT_EQ(game.getCellType(5, 6), Board::CellType::PLAYER);
}

TEST(game_test, place_exit)
{
    size_t size = 10;
    Game game(size);
    game.placeExit(2, 3);
    EXPECT_EQ(game.getCellType(2, 3), Board::CellType::EXIT);
}

TEST(game_test, place_exit_on_player)
{
    size_t size = 10;
    Game game(size);
    game.placePlayer(5, 6);
    EXPECT_THROW(game.placeExit(5, 6), std::invalid_argument);
    EXPECT_EQ(game.getCellType(5, 6), Board::CellType::PLAYER);
}

TEST(game_test, move_up)
{
    size_t size = 10;
    Game game(size);
    game.placePlayer(2, 3);
    game.moveUp();
    EXPECT_EQ(game.getCellType(1, 3), Board::CellType::PLAYER);
    EXPECT_EQ(game.getCellType(2, 3), Board::CellType::EMPTY);
}

TEST(game_test, move_up_wallhit)
{
    size_t size = 10;
    Game game(size);
    game.placePlayer(2, 3);
    game.placeWall(1, 3);
    EXPECT_THROW(game.moveUp(), Game::wallhit_exception);
    EXPECT_EQ(game.getCellType(2, 3), Board::CellType::PLAYER);
}

TEST(game_test, move_up_exitreach)
{
    size_t size = 10;
    Game game(size);
    game.placePlayer(2, 3);
    game.placeExit(1, 3);
    EXPECT_THROW(game.moveUp(), Game::exitreach_exception);
    EXPECT_EQ(game.getCellType(2, 3), Board::CellType::PLAYER);
}

TEST(game_test, move_up_out_of_range)
{
    size_t size = 10;
    Game game(size);
    game.placePlayer(0, 2);
    EXPECT_THROW(game.moveUp(), std::out_of_range);
    EXPECT_EQ(game.getCellType(0, 2), Board::CellType::PLAYER);
}

TEST(game_test, move_down)
{
    size_t size = 10;
    Game game(size);
    game.placePlayer(5, 5);
    game.moveDown();
    EXPECT_EQ(game.getCellType(6, 5), Board::CellType::PLAYER);
    EXPECT_EQ(game.getCellType(5, 5), Board::CellType::EMPTY);
}

TEST(game_test, move_down_wallhit)
{
    size_t size = 10;
    Game game(size);
    game.placePlayer(5, 5);
    game.placeWall(6, 5);
    EXPECT_THROW(game.moveDown(), Game::wallhit_exception);
    EXPECT_EQ(game.getCellType(5, 5), Board::CellType::PLAYER);
}

TEST(game_test, move_down_exitreach)
{
    size_t size = 10;
    Game game(size);
    game.placePlayer(5, 5);
    game.placeExit(6, 5);
    EXPECT_THROW(game.moveDown(), Game::exitreach_exception);
    EXPECT_EQ(game.getCellType(5, 5), Board::CellType::PLAYER);
}

TEST(game_test, move_down_out_of_range)
{
    size_t size = 10;
    Game game(size);
    game.placePlayer(9, 5);
    EXPECT_THROW(game.moveDown(), std::out_of_range);
    EXPECT_EQ(game.getCellType(9, 5), Board::CellType::PLAYER);
}

TEST(game_test, move_left)
{
    size_t size = 10;
    Game game(size);
    game.placePlayer(7, 3);
    game.moveLeft();
    EXPECT_EQ(game.getCellType(7, 2), Board::CellType::PLAYER);
    EXPECT_EQ(game.getCellType(7, 3), Board::CellType::EMPTY);
}

TEST(game_test, move_left_wallhit)
{
    size_t size = 10;
    Game game(size);
    game.placePlayer(7, 3);
    game.placeWall(7, 2);
    EXPECT_THROW(game.moveLeft(), Game::wallhit_exception);
    EXPECT_EQ(game.getCellType(7, 3), Board::CellType::PLAYER);
}

TEST(game_test, move_left_exitreach)
{
    size_t size = 10;
    Game game(size);
    game.placePlayer(7, 3);
    game.placeExit(7, 2);
    EXPECT_THROW(game.moveLeft(), Game::exitreach_exception);
    EXPECT_EQ(game.getCellType(7, 3), Board::CellType::PLAYER);
}

TEST(game_test, move_left_out_of_range)
{
    size_t size = 10;
    Game game(size);
    game.placePlayer(3, 0);
    EXPECT_THROW(game.moveLeft(), std::out_of_range);
    EXPECT_EQ(game.getCellType(3, 0), Board::CellType::PLAYER);
}

TEST(game_test, move_right)
{
    size_t size = 10;
    Game game(size);
    game.placePlayer(4, 2);
    game.moveRight();
    EXPECT_EQ(game.getCellType(4, 3), Board::CellType::PLAYER);
    EXPECT_EQ(game.getCellType(4, 2), Board::CellType::EMPTY);
}

TEST(game_test, move_right_wallhit)
{
    size_t size = 10;
    Game game(size);
    game.placePlayer(4, 2);
    game.placeWall(4, 3);
    EXPECT_THROW(game.moveRight(), Game::wallhit_exception);
    EXPECT_EQ(game.getCellType(4, 2), Board::CellType::PLAYER);
}

TEST(game_test, move_right_exitreach)
{
    size_t size = 10;
    Game game(size);
    game.placePlayer(4, 2);
    game.placeExit(4, 3);
    EXPECT_THROW(game.moveRight(), Game::exitreach_exception);
    EXPECT_EQ(game.getCellType(4, 2), Board::CellType::PLAYER);
}

TEST(game_test, move_right_out_of_range)
{
    size_t size = 10;
    Game game(size);
    game.placePlayer(2, 9);
    EXPECT_THROW(game.moveRight(), std::out_of_range);
    EXPECT_EQ(game.getCellType(2, 9), Board::CellType::PLAYER);
}