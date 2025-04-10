/*!
 * @file Tile.h
 * @brief Definition of the `Tile` class representing a single tile on the puzzle board.
 *
 * Contains the definition of the `Tile` class, which stores the value and
 * coordinates of a single tile within the sliding puzzle.
 */

#include <Coordinates.h>

#ifndef TILE_H
#define TILE_H

/*!
 * @brief Class representing a single tile on the sliding puzzle board.
 *
 * This class holds the value displayed on the tile and its current position
 * on the board. The value 0 represents the empty tile.
 */
class Tile {

public:
    /*!
     * @brief Default constructor for the Tile class.
     *
     * Initializes a tile with a default value and default coordinates.
     */
    Tile();

    /*!
     * @brief Constructor for the Tile class.
     * @param value The initial value of the tile.
     * @param x The initial row (X-coordinate) of the tile.
     * @param y The initial column (Y-coordinate) of the tile.
     */
    Tile(int value, int x, int y);

    /*!
     * @brief Returns the value of the tile.
     * @return The integer value displayed on the tile.
     */
    int getValue() const;

    /*!
     * @brief Returns the current row (X-coordinate) of the tile.
     * @return The row index of the tile on the board.
     */
    int getX() const;

    /*!
     * @brief Returns the current column (Y-coordinate) of the tile.
     * @return The column index of the tile on the board.
     */
    int getY() const;

    /*!
     * @brief Sets the value of the tile.
     * @param value The new integer value to set for the tile.
     */
    void setValue(int value);

    /*!
     * @brief Sets the row (X-coordinate) of the tile.
     * @param x The new row index for the tile.
     */
    void setX(int x);

    /*!
     * @brief Sets the column (Y-coordinate) of the tile.
     * @param y The new column index for the tile.
     */
    void setY(int y);

private:
    /*!
     * @brief The value displayed on the tile. 0 indicates the empty tile.
     */
    int value;

    /*!
     * @brief The current position of the tile on the board.
     */
    Coordinates<int> position;
};

#endif // TILE_H
