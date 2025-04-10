#include "GameState.h"
#include <qDebug>
#include <vector>
#include <fstream>

void GameState::save(const std::string& filename, int size, const Board& board, int elapsedTime, int moveCount) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << size << std::endl;
        const auto& tiles = board.getTiles();
        for (const auto& row : tiles) {
            for (const auto& tile : row) {
                file << tile.getValue() << " ";
            }
        }
        file << std::endl;
        file << moveCount << std::endl;
        file << elapsedTime << std::endl;
        file.close();
    } else {
        qDebug() << "Nie można otworzyć pliku do zapisu: " << filename.c_str();
    }
}

bool GameState::load(const std::string& filename, int& size, Board& board, int& elapsedTime, int& moveCount) {
    std::ifstream file(filename);
    if (file.is_open()) {
        if (!(file >> size)) return false;
        std::vector<std::vector<int>> tiles(size, std::vector<int>(size));
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (!(file >> tiles[i][j])) return false;
            }
        }

        if (!(file >> moveCount)) return false;
        if (!(file >> elapsedTime)) return false;
        file.close();

        Board loadedBoard(size);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                loadedBoard.setTileValue(i, j, tiles[i][j]);
            }
        }
        board = loadedBoard;
        return true;
    } else {
        qDebug() << "Nie można otworzyć pliku do odczytu: " << filename.c_str();
        return false;
    }
}
