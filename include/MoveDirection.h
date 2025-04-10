/*!
 * @file MoveDirection.h
 * @brief Definition of the `MoveDirection` enumeration.
 *
 * Contains the definition of the `MoveDirection` enum class, which represents
 * the possible directions for moving a tile on the puzzle board.
 */

#ifndef MOVEDIRECTION_H
#define MOVEDIRECTION_H

/*!
 * @brief Enumeration class representing the possible directions for moving a tile.
 *
 * This enum class defines the four cardinal directions in which a tile can be
 * moved on the sliding puzzle board. These directions correspond to
 * the movement of the empty space.
 */
enum class MoveDirection {
    /*!
     * @brief Represents the upward movement of a tile.
     */
    UP,
    /*!
     * @brief Represents the downward movement of a tile.
     */
    DOWN,
    /*!
     * @brief Represents the leftward movement of a tile.
     */
    LEFT,
    /*!
     * @brief Represents the rightward movement of a tile.
     */
    RIGHT
};

#endif // MOVEDIRECTION_H
