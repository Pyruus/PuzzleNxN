/*!
 * @file Board.h
 * @brief Definition of the class representing the puzzle board.
 *
 * Contains the definition of the `Board` class, which manages the state of the
 * tiles on the board, allows for making moves, shuffling, checking the solution,
 * and other operations related to the logic of the sliding puzzle board.
 */

#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "MoveDirection.h"
#include "Tile.h"

/*!
 * @brief Class representing the sliding puzzle board.
 *
 * Stores a two-dimensional structure of tiles and implements the logic
 * related to operations on the board, such as getting tiles, making moves,
 * shuffling, and checking the solution state.
 */
class Board {

public:
    /*!
     * @brief Constructor for the Board class.
     * @param size The size of the board (number of rows and columns). Creates a board of dimensions size x size.
     */
    Board(int size);

    /*!
     * @brief Returns the tile located at the specified position.
     * @param x The X-coordinate (row) of the tile to get.
     * @param y The Y-coordinate (column) of the tile to get.
     * @return The `Tile` object located at the (x, y) position.
     */
    Tile getTile(int x, int y) const;

    /*!
     * @brief Attempts to move the empty tile (value 0) in the specified direction.
     * @param direction The direction of the move (Up, Down, Left, Right).
     * @return true if the move was successful, false otherwise.
     */
    bool moveTile(MoveDirection direction);

    /*!
     * @brief Shuffles the tiles on the board.
     */
    void shuffle();

    /*!
     * @brief Returns the size of the board.
     * @return The number of rows or columns of the board.
     */
    int getSize() const;

    /*!
     * @brief Checks if the current arrangement of tiles on the board is solved.
     * @return true if the board is in the solved state, false otherwise.
     */
    bool isSolved() const;

    /*!
     * @brief Checks if the current arrangement of tiles on the board is solvable.
     * @return true if the puzzle has a solution, false otherwise.
     */
    bool isSolvable() const;

    /*!
     * @brief Returns a copy of the entire tile structure of the board.
     * @return A two-dimensional vector of `Tile` objects representing the current state of the board.
     */

    std::vector<std::vector<Tile>> getTiles() const;
    bool operator<(const Board& other) const;
    /*!
     * @brief Sets the value of the tile at the specified position.
     * @param row The row coordinate of the tile to set.
     * @param col The column coordinate of the tile to set.
     * @param value The new value of the tile.
     */
    void setTileValue(int row, int col, int value);

private:
    /*!
     * @brief The size of the board (number of rows and columns).
     */
    int size;

    /*!
     * @brief A two-dimensional vector structure storing the tiles of the board.
     */
    std::vector<std::vector<Tile>> tiles;
};

#endif // BOARD_H
