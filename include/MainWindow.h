/*!
 * @file MainWindow.h
 * @brief Definition of the main window class for the application.
 *
 * Contains the definition of the `MainWindow` class, which serves as the main
 * window of the application. It manages the game model, the visual representation
 * of the board, the statistics display, and user interactions.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "PuzzleModel.h"
#include "BoardView.h"
#include "StatisticsView.h"

#include <QComboBox>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTimer>
#include <QMessageBox>

/*!
 * @brief The main window class for the sliding puzzle application.
 *
 * This class is the central component of the application's user interface.
 * It creates and manages the `PuzzleModel` (the game logic), the `BoardView`
 * (the visual representation of the puzzle board), the `StatisticsView`
 * (displaying moves and time), and handles user interactions such as starting
 * a new game, saving, and loading.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * @brief Constructor for the MainWindow class.
     * @param size The initial size of the puzzle board (e.g., 3 for a 3x3 board).
     * @param parent The parent widget for this main window (defaults to nullptr).
     */
    MainWindow(int size, QWidget *parent = nullptr);

private:
    /*!
     * @brief The model containing the game logic and state.
     */
    PuzzleModel puzzleModel;

    /*!
     * @brief The widget responsible for displaying the puzzle board.
     */
    BoardView *boardView;

    /*!
     * @brief The combo box allowing the user to select the board size.
     */
    QComboBox *boardSizeComboBox;

    /*!
     * @brief The widget displaying game statistics such as move count and elapsed time.
     */
    StatisticsView *statisticsView;

    /*!
     * @brief A timer used to track the elapsed game time.
     */
    QTimer *timer;

    /*!
     * @brief Stores the elapsed game time in seconds.
     */
    int elapsedTime = 0;

    /*!
     * @brief A flag indicating whether the game has been solved.
     */
    bool gameFinished = false;

    /*!
     * @brief Updates the displayed game time in the statistics view.
     *
     * Called periodically by the timer.
     */
    void updateTime();

    /*!
     * @brief Saves the current game state to a file.
     *
     * Prompts the user for a filename and uses the `GameState` class to save
     * the current board configuration, elapsed time, and move count.
     */
    void saveGame();

    /*!
     * @brief Loads a previously saved game state from a file.
     *
     * Prompts the user to select a file and uses the `GameState` class to load
     * the saved board configuration, elapsed time, and move count, then updates
     * the game accordingly.
     */
    void loadGame();
};
#endif // MAINWINDOW_H
