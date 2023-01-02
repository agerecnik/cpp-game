#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/board.h"

TEST(board_test, initialize_board_size_10)
{
    size_t size = 10;
    Board board(size);
    EXPECT_EQ(board.size(), size);
    for (size_t y = 0; y < size; ++y) {
        for (size_t x = 0; x < size; ++x) {
            EXPECT_EQ(board.getCellType(y, x), Board::CellType::EMPTY);
        }
    }
}

TEST(board_test, set_cell_type)
{
    size_t size = 10;
    Board board(size);
    board.setCellType(5, 3, Board::CellType::WALL);
    EXPECT_EQ(board.getCellType(5, 3), Board::CellType::WALL);
    board.setCellType(5, 3, Board::CellType::PLAYER);
    EXPECT_EQ(board.getCellType(5, 3), Board::CellType::PLAYER);
    board.setCellType(5, 3, Board::CellType::EXIT);
    EXPECT_EQ(board.getCellType(5, 3), Board::CellType::EXIT);
    board.setCellType(5, 3, Board::CellType::EMPTY);
    EXPECT_EQ(board.getCellType(5, 3), Board::CellType::EMPTY);
}

TEST(board_test, set_cell_type_out_of_range)
{
    size_t size = 10;
    Board board(size);
    EXPECT_THROW(board.setCellType(10, 0, Board::CellType::WALL), std::out_of_range);
    EXPECT_THROW(board.setCellType(11, 0, Board::CellType::WALL), std::out_of_range);
    EXPECT_THROW(board.setCellType(0, 10, Board::CellType::WALL), std::out_of_range);
    EXPECT_THROW(board.setCellType(0, 11, Board::CellType::WALL), std::out_of_range);
}

TEST(board_test, get_cell_type_out_of_range)
{
    size_t size = 10;
    Board board(size);
    EXPECT_THROW(board.getCellType(10, 0), std::out_of_range);
    EXPECT_THROW(board.getCellType(11, 0), std::out_of_range);
    EXPECT_THROW(board.getCellType(0, 10), std::out_of_range);
    EXPECT_THROW(board.getCellType(0, 11), std::out_of_range);
}

TEST(board_test, print_mixed_board)
{
    size_t size = 3;
    Board board(size);

    board.setCellType(0, 0, Board::CellType::PLAYER);
    board.setCellType(0, 1, Board::CellType::EMPTY);
    board.setCellType(0, 2, Board::CellType::EMPTY);
    board.setCellType(1, 0, Board::CellType::WALL);
    board.setCellType(1, 1, Board::CellType::EMPTY);
    board.setCellType(1, 2, Board::CellType::EMPTY);
    board.setCellType(2, 0, Board::CellType::EMPTY);
    board.setCellType(2, 1, Board::CellType::EMPTY);
    board.setCellType(2, 2, Board::CellType::EXIT);

    testing::internal::CaptureStdout();
    board.print();
    std::string output = testing::internal::GetCapturedStdout();
    output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());

    ASSERT_TRUE(output.length() == (board.size() * board.size() * 2));

    int i = 0;
    for (size_t y = 0; y < board.size(); ++y) {
        for (size_t x = 0; x < board.size(); ++x) {
            EXPECT_TRUE(board.getCellType(y, x) == output[i]);
            i += 2;
        }
    }
}

TEST(board_test, print_empty_board)
{
    size_t size = 5;
    Board board(size);

    testing::internal::CaptureStdout();
    board.print();
    std::string output = testing::internal::GetCapturedStdout();
    output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());

    ASSERT_TRUE(output.length() == (board.size() * board.size() * 2));

    int i = 0;
    for (size_t y = 0; y < board.size(); ++y) {
        for (size_t x = 0; x < board.size(); ++x) {
            EXPECT_TRUE(board.getCellType(y, x) == output[i]);
            i += 2;
        }
    }
}