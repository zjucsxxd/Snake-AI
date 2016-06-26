#include "Map.h"
#include "GameCtrl.h"
#include <new>
#include <cstdlib>

Map::Map(const unsigned &rowCnt_, const unsigned &colCnt_) : rowCnt(rowCnt_), colCnt(colCnt_) {
    content = new(std::nothrow) Grid*[rowCnt_];
    if (!content) {
        GameCtrl::getInstance()->exitWithException("Not enough memory.\n");
    }
    for (unsigned i = 0; i < rowCnt_; ++i) {
        content[i] = new(std::nothrow) Grid[colCnt_];
        if (!content) {
            GameCtrl::getInstance()->exitWithException("Not enough memory.\n");
        }

        // Initial map content
        if (i == 0 || i == rowCnt - 1) {
            for (unsigned j = 0; j < colCnt; ++j) {
                content[i][j].setType(Grid::GridType::WALL);
            }
        }
        content[i][0].setType(Grid::GridType::WALL);
        content[i][colCnt - 1].setType(Grid::GridType::WALL);
    }
}

Map::~Map() {
    for (unsigned i = 0; i < GameCtrl::MAP_ROW; ++i) {
        delete[] content[i];
        content[i] = nullptr;
    }
    delete[] content;
    content = nullptr;
    delete foodPos;
    foodPos = nullptr;
}

Grid& Map::at(const unsigned &x, const unsigned &y) {
    return content[x][y];
}

const Grid& Map::at(const unsigned &x, const unsigned &y) const {
    return content[x][y];
}

void Map::createFood() {
    int row = random(1, rowCnt - 2), col = random(1, colCnt - 2);
    if (!foodPos) {
        foodPos = new(std::nothrow) Point(row, col);
        if (!foodPos) {
            GameCtrl::getInstance()->exitWithException("Not enough memory.\n");
        }
    } else {
        foodPos->x = row;
        foodPos->y = col;
    }
    content[row][col].setType(Grid::GridType::FOOD);
}

void Map::clearFood() {
    if (foodPos) {
        content[foodPos->x][foodPos->y].setType(Grid::GridType::BLANK);
        delete foodPos;
        foodPos = nullptr;
    }
}

bool Map::hasFood() const {
    return foodPos != nullptr;
}

unsigned Map::getRowCount() const {
    return rowCnt;
}

unsigned Map::getColCount() const {
    return colCnt;
}

const Point* Map::getFoodPos() const {
    return foodPos;
}

int Map::random(const int min, const int max) {
    static bool set_seed = true;
    if (set_seed) srand(static_cast<unsigned>(time(NULL)));
    set_seed = false;
    return rand() % (max - min + 1) + min;
}