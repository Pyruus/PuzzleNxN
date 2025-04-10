/*!
 * @file BoardView.h
 * @brief Definition of the class representing the visual representation of the puzzle board.
 *
 * Contains the definition of the `BoardView` class, which is a Qt widget responsible
 * for displaying the puzzle board to the user and handling user interactions.
 */

#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QWidget>
#include <vector>
#include "board.h"
#include "tileview.h"

/*!
 * @brief Class representing the visual representation of the puzzle board.
 *
 * This class is a `QWidget` that displays the tiles of the puzzle board. It creates
 * and manages instances of `TileView` to represent each tile.
 */
class BoardView : public QWidget {
    Q_OBJECT

public:
    /*!
     * @brief Constructor for the BoardView class.
     * @param board A constant reference to the `Board` object containing the current
     * state of the puzzle.
     * @param parent The parent widget for this `BoardView` (defaults to nullptr).
     */
    BoardView(const Board &board, QWidget *parent = nullptr);

    /*!
     * @brief Updates the visual representation of the board to reflect a new state.
     * @param board A constant reference to the new `Board` object. This method will
     * update the `TileView` instances to match the new tile arrangement.
     */
    void updateBoard(const Board &board);

signals:
    /*!
     * @brief Signal emitted when a tile on the board is clicked by the user.
     * @param x The row index (X-coordinate) of the clicked tile.
     * @param y The column index (Y-coordinate) of the clicked tile.
     */
    void tileClicked(int x, int y);

private:
    /*!
     * @brief A 2D vector storing pointers to the `TileView` widgets that represent
     * each tile on the board.
     */
    std::vector<std::vector<TileView*>> tileViews;

    /*!
     * @brief The size of the board (number of rows or columns).
     */
    int size;
};

#endif // BOARDVIEW_H
