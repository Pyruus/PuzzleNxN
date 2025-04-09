#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "Board.h"
#include <fstream>
#include <string>

class GameState {
public:
    static void save(const std::string& filename, int size, const Board& board, int elapsedTime, int moveCount);
    static bool load(const std::string& filename, int& size, Board& board, int& elapsedTime, int& moveCount);
};
#endif // GAMESTATE_H
