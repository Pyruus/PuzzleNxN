/*!
 * @file StatisticsView.h
 * @brief Definition of the `StatisticsView` class for displaying game statistics.
 *
 * Contains the definition of the `StatisticsView` class, which is a Qt widget
 * responsible for displaying the current number of moves made by the player
 * and the elapsed time of the game.
 */

#ifndef STATISTICSVIEW_H
#define STATISTICSVIEW_H

#include <QWidget>
#include <QLabel>

/*!
 * @brief Class representing a widget that displays game statistics.
 *
 * This class is a `QWidget` that shows the current number of moves the player
 * has made and the time elapsed since the start of the game.
 */
class StatisticsView : public QWidget {
    Q_OBJECT

public:
    /*!
     * @brief Constructor for the StatisticsView class.
     * @param parent The parent widget for this statistics view (defaults to nullptr).
     */
    StatisticsView(QWidget *parent = nullptr);

    /*!
     * @brief Updates the displayed move count.
     * @param moveCount The current number of moves made. This value will be
     * displayed in the move count label.
     */
    void updateMoveCount(int moveCount);

    /*!
     * @brief Updates the displayed elapsed time.
     * @param hours The number of elapsed hours.
     * @param minutes The number of elapsed minutes.
     * @param seconds The number of elapsed seconds. These values will be
     * formatted and displayed in the time label.
     */
    void updateTime(int hours, int minutes, int seconds);

private:
    /*!
     * @brief The label used to display the current move count.
     */
    QLabel *moveCountLabel;

    /*!
     * @brief The label used to display the elapsed game time.
     */
    QLabel *timeLabel;
};


#endif // STATISTICSVIEW_H
