#include "../include/Board.h"
#include <iostream>
#include <algorithm>
#include <random>

Board::Board(int n) : gridSize(n), tiles() {
    initialize();
}

void Board::initialize() {
  for (int i = 0; i < gridSize * gridSize - 1; i++) {
    auto tile = new Tile();
    if (i < gridSize * gridSize - 1) {
        tile->setValue( i + 1);
    }

    tiles.push_back(tile);
  }
}

void Board::shuffle() {
  std::vector<int> values;
  for (int i = 0; i < gridSize * gridSize - 1; ++i) {
    values.push_back(i + 1);
  }
  values.push_back(0);

  std::random_device rd;
  std::mt19937 g(rd());

  do {
    std::shuffle(values.begin(), values.end(), g);
  } while (!isSolvable(values));

  for (int i = 0; i < gridSize * gridSize; ++i) {
    tiles[i]->setValue( values[i] );
  }
}

bool Board::isSolvable(const std::vector<int>& puzzle){
  int invCount = getInversionCount(puzzle);
  if (gridSize % 2 == 0){
    return invCount % 2 == 0;
  } else {
    int emptyRow = 0;
    for (int i = 0; i < puzzle.size(); i++) {
      if (puzzle[i] == 0){
        emptyRow = i / gridSize;
        break;
      }
    }

    int rowFromBottom = gridSize - emptyRow;
    return (invCount + rowFromBottom) % 2 == 1;
  }
}

int Board::getInversionCount(const std::vector<int>& puzzle){
  int invCount = 0;
  for (int i = 0; i < puzzle.size() - 1; i++) {
    if (puzzle[i] == 0) continue;

    for (int j = i + 1; j < puzzle.size(); j++) {
      if (puzzle[j] == 0) continue;

      if (puzzle[i] > puzzle[j]) {
        invCount++;
      }
    }
  }
  return invCount;
}
