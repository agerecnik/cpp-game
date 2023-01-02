#include <stdexcept>
#include <iostream>
#include "board.h"

using std::cout;
using std::endl;

Board::Board(const size_t s)
{
    for (size_t y = 0; y < s; ++y) {
        vector<CellType> line;
        for (size_t x = 0; x < s; ++x) {
            line.push_back(CellType::EMPTY);
        }
        v.push_back(line);
    }
}

Board::~Board() = default;

const Board::CellType Board::getCellType(const size_t y, const size_t x)
{
    return v.at(y).at(x);
}

void Board::setCellType(const size_t y, const size_t x, const CellType cellType)
{
    v.at(y).at(x) = cellType;
}

const size_t Board::size()
{
    return v.size();
}

void Board::print()
{
    for (size_t y = 0; y < v.size(); ++y) {
        for (size_t x = 0; x < v[y].size(); ++x) {
            cout << static_cast<char>(v[y][x]) << " ";
        }
        cout << endl;
    }
}