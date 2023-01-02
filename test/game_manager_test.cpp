#include <gtest/gtest.h>
#include "../src/game_manager.h"

TEST(game_manager_test, new_game)
{
    size_t size1 = 10;
    size_t size2 = 6;
    GameManager manager;

    EXPECT_FALSE(manager.isGameLoaded());
    manager.newGame("game", size1);
    EXPECT_TRUE(manager.isGameLoaded());
    EXPECT_THROW(manager.newGame("game", size1), std::invalid_argument);
    EXPECT_THROW(manager.newGame("game", size2), std::invalid_argument);
    EXPECT_EQ(manager.getCurrentGame().getBoardSize(), size1);

    manager.newGame("", size2);
    EXPECT_THROW(manager.newGame("", size2), std::invalid_argument);
    EXPECT_EQ(manager.getCurrentGame().getBoardSize(), size2);
}

TEST(game_manager_test, get_game_exception)
{
    size_t size1 = 10;
    GameManager manager;

    EXPECT_THROW(manager.getCurrentGame(), std::logic_error);
    manager.newGame("game", size1);
    manager.gameCompleted();
    EXPECT_THROW(manager.getCurrentGame(), std::logic_error);
}

TEST(game_manager_test, switch_game)
{
    size_t size1 = 5;
    size_t size2 = 6;
    size_t size3 = 9;
    GameManager manager;
    manager.newGame("game1", size1);
    manager.newGame("game2", size2);
    manager.newGame("game3", size3);

    manager.switchGame("game1");
    EXPECT_EQ(manager.getCurrentGame().getBoardSize(), size1);

    manager.switchGame("game3");
    EXPECT_EQ(manager.getCurrentGame().getBoardSize(), size3);

    manager.switchGame("game2");
    EXPECT_EQ(manager.getCurrentGame().getBoardSize(), size2);

    EXPECT_THROW(manager.switchGame("game4"), std::invalid_argument);
}

TEST(game_manager_test, restart_game)
{
    size_t size1 = 12;
    size_t size2 = 14;
    GameManager manager;

    EXPECT_THROW(manager.restartGame(), std::logic_error);

    manager.newGame("game1", size1);
    manager.newGame("game2", size2);

    manager.switchGame("game1");
    manager.getCurrentGame().moveDown();

    manager.switchGame("game2");
    manager.getCurrentGame().moveRight();

    manager.switchGame("game1");
    manager.restartGame();
    EXPECT_EQ(manager.getCurrentGame().getCellType(0, 0), Board::CellType::PLAYER);
    EXPECT_EQ(manager.getCurrentGame().getCellType(1, 0), Board::CellType::EMPTY);

    manager.switchGame("game2");
    EXPECT_EQ(manager.getCurrentGame().getCellType(0, 1), Board::CellType::PLAYER);
    EXPECT_EQ(manager.getCurrentGame().getCellType(0, 0), Board::CellType::EMPTY);
}

TEST(game_manager_test, game_completed)
{
    size_t size = 5;
    GameManager manager;
    manager.newGame("game", size);

    EXPECT_TRUE(manager.isGameLoaded());
    manager.gameCompleted();
    EXPECT_FALSE(manager.isGameLoaded());
    EXPECT_THROW(manager.gameCompleted(), std::logic_error);
}

TEST(game_manager_test, board)
{
    size_t size = 8;
    GameManager manager;
    manager.newGame("game", size);

    EXPECT_EQ(manager.getCurrentGame().getCellType(0, 0), Board::CellType::PLAYER);
    EXPECT_EQ(manager.getCurrentGame().getCellType(size - 1, size - 1), Board::CellType::EXIT);

    int wallCounter = 0;
    int playerCounter = 0;
    int exitCounter = 0;
    int emptyCoutner = 0;

    for (size_t y = 0; y < size; ++y) {
        for (size_t x = 0; x < size; ++x) {
            if (manager.getCurrentGame().getCellType(y, x) == Board::CellType::WALL) {
                ++wallCounter;
            } else if (manager.getCurrentGame().getCellType(y, x) == Board::CellType::PLAYER) {
                ++playerCounter;
            } else if (manager.getCurrentGame().getCellType(y, x) == Board::CellType::EXIT) {
                ++exitCounter;
            } else if (manager.getCurrentGame().getCellType(y, x) == Board::CellType::EMPTY) {
                ++emptyCoutner;
            }
        }
    }

    EXPECT_EQ(wallCounter, 6);
    EXPECT_EQ(playerCounter, 1);
    EXPECT_EQ(exitCounter, 1);
    EXPECT_EQ(emptyCoutner, size * size - 8);

    manager.newGame("game2", 4);
    EXPECT_EQ(manager.getCurrentGame().getBoardSize(), 5);

    manager.newGame("game3", 16);
    EXPECT_EQ(manager.getCurrentGame().getBoardSize(), 15);
}