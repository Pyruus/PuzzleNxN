/*!
 * @file PuzzleModel.h
 * @brief Definition of the `PuzzleModel` class, which manages the game logic.
 *
 * Contains the definition of the `PuzzleModel` class, responsible for handling
 * the game state, including the puzzle board, move count, and game completion
 * logic. It also provides methods for interacting with the game, such as
 * moving tiles and shuffling the board.
 */

#ifndef PUZZLEMODEL_H
#define PUZZLEMODEL_H

#include "Board.h"
#include "MoveDirection.h"
#include <QObject>

/*!
 * @brief Class managing the logic and state of the sliding puzzle game.
 *
 * This class manages the logic and state of the sliding puzzle game. It holds the `Board` object,
 * tracks the number of moves made, and determines if the puzzle is solved or solvable.
 * It provides methods to move tiles, shuffle the board, and access the current game state.
 * It inherits from `QObject` to utilize Qt's signals and slots mechanism for
 * communicating changes in the game state to other parts of the application.
 */
class PuzzleModel : public QObject {
    Q_OBJECT

public:
    /*!
     * @brief Constructor for the PuzzleModel class.
     * @param size The initial size of the puzzle board (e.g., 3 for a 3x3 board).
     * @param parent The parent object for this model (defaults to nullptr).
     */
    PuzzleModel(int size, QObject *parent = nullptr);

    /*!
     * @brief Returns a reference to the current game board.
     * @return A reference to the `Board` object.
     */
    Board& getBoard();

    /*!
     * @brief Checks if the current state of the puzzle board is solved.
     * @return true if the puzzle is solved, false otherwise.
     */
    bool isSolved() const;

    /*!
     * @brief Checks if the current state of the puzzle board is solvable.
     * @return true if the puzzle is solvable, false otherwise.
     */
    bool isSolvable() const;

    /*!
     * @brief Returns the number of moves made by the player.
     * @return The total count of moves performed.
     */
    int getMoveCount() const;

    /*!
     * @brief Sets the current state of the game board.
     * @param board The new `Board` object to set as the game board.
     */
    void setBoard(const Board& board);

    /*!
     * @brief Sets the number of moves made by the player.
     * @param count The new move count.
     */
    void setMoveCount(int count);

    /*!
     * @brief Attempts to move a tile on the board in the specified direction.
     *
     * This method updates the board state and increments the move count if a
     * valid move is made. It also emits the `boardChanged` and potentially
     * the `gameSolved` signals.
     * @param direction The direction in which to move a tile (Up, Down, Left, Right).
     */
    void moveTile(MoveDirection direction);

    /*!
     * @brief Shuffles the puzzle board to a random solvable state, resetting the move count.
     *
     * This method generates a new, scrambled configuration of the puzzle that is
     * guaranteed to be solvable. It also resets the `moveCount` to 0.
     */
    void shuffle();

signals:
    /*!
     * @brief Signal emitted when the state of the game board changes.
     * @param board A reference to the new `Board` object.
     */
    void boardChanged(const Board &board);

    /*!
     * @brief Signal emitted when the number of moves made changes.
     * @param moveCount The new total count of moves.
     */
    void moveCountChanged(int moveCount);

    /*!
     * @brief Signal emitted when the puzzle is solved.
     */
    void gameSolved();

private:
    /*!
     * @brief The object representing the current state of the puzzle board.
     */
    Board board;

    /*!
     * @brief The number of moves made by the player.
     */
    int moveCount;
};

#endif // PUZZLEMODEL_H
