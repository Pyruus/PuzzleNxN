/*!
 * @file GameState.h
 * @brief Definition of the `GameState` class used for saving and loading game state.
 *
 * Contains the definition of the `GameState` class, which provides static
 * methods for persisting and restoring the state of the puzzle game,
 * including the board configuration, elapsed time, and move count.
 */

#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "Board.h"
#include <string>

/*!
 * @brief Class providing static methods for saving and loading the game state.
 *
 * This class offers functionality to save the current state of the puzzle game
 * to a file and load a previously saved game state from a file.de.
 */
class GameState {
public:
    /*!
     * @brief Saves the current state of the game to the specified file.
     * @param filename The name of the file to save the game state to.
     * @param size The size of the puzzle board.
     * @param board A constant reference to the `Board` object representing the
     * current configuration of the puzzle.
     * @param elapsedTime The elapsed time of the game in seconds.
     * @param moveCount The number of moves made by the player.
     */
    static void save(const std::string& filename, int size, const Board& board, int elapsedTime, int moveCount);

    /*!
     * @brief Loads a previously saved game state from the specified file.
     * @param filename The name of the file to load the game state from.
     * @param size [out] A reference to an integer where the loaded board size will be stored.
     * @param board [out] A reference to a `Board` object where the loaded board
     * configuration will be stored.
     * @param elapsedTime [out] A reference to an integer where the loaded elapsed
     * time (in seconds) will be stored.
     * @param moveCount [out] A reference to an integer where the loaded move count
     * will be stored.
     * @return true if the game state was successfully loaded from the file, false otherwise
     */
    static bool load(const std::string& filename, int& size, Board& board, int& elapsedTime, int& moveCount);
};
#endif // GAMESTATE_H
