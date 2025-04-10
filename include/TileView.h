/*!
 * @file TileView.h
 * @brief Definition of the `TileView` class, the visual representation of a single tile.
 *
 * Contains the definition of the `TileView` class, a Qt widget responsible for
 * displaying a single tile of the puzzle, including its value and handling
 * user clicks.
 */

#ifndef TILEVIEW_H
#define TILEVIEW_H

#include <QWidget>
#include <QLabel>
#include "tile.h"
#include <QMouseEvent>

/*!
 * @brief Class representing the visual representation of a single puzzle tile.
 *
 * This class is a `QWidget` that displays the value of a `Tile` object using a
 * `QLabel`. It also handles mouse press events to emit a signal when the tile
 * is clicked by the user. The size of the tile's font is dynamically adjusted
 * based on the board size.
 */
class TileView : public QWidget {
    Q_OBJECT

public:
    /*!
     * @brief Constructor for the TileView class.
     * @param tile A constant reference to the `Tile` object whose value will be displayed.
     * @param parent The parent widget for this `TileView` (defaults to nullptr).
     * @param boardSize The size of the puzzle board. This is used to dynamically
     * adjust the font size of the tile's value.
     */
    TileView(const Tile &tile, int boardSize, QWidget *parent = nullptr);

    /*!
     * @brief Updates the visual representation of the tile to reflect a new `Tile` state.
     * @param tile A constant reference to the new `Tile` object. This method will
     * update the displayed value of the tile.
     */
    void updateTile(const Tile &tile);

protected:
    /*!
     * @brief Handles mouse press events on the tile.
     *
     * When the tile is clicked, this method emits the `clicked()` signal.
     * @param event The mouse event object.
     */
    void mousePressEvent(QMouseEvent *event) override;

signals:
    /*!
     * @brief Signal emitted when the tile is clicked by the user.
     */
    void clicked();

private:
    /*!
     * @brief The label used to display the value of the tile.
     */
    QLabel *label;

    /*!
     * @brief Sets the opacity of the tile.
     * @param opacity The desired opacity level.
     */
    void setOpacity(qreal opacity);
};

#endif // TILEVIEW_H
