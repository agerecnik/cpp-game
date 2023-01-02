#ifndef BOARD_H
#define BOARD_H

#include <vector>

using std::vector;

class Board
{
public:
    enum CellType { EMPTY = '.', PLAYER = 'P', WALL = 'W', EXIT = 'E' };

    Board(size_t size);
    ~Board();

    const CellType getCellType(const size_t y, const size_t x);
    void setCellType(const size_t y, const size_t x, const CellType cellType);
    const size_t size();
    void print();

private:
    vector<vector<CellType>> v;
};

#endif