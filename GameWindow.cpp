#include "GameWindow.h"

GameWindow::GameWindow(int windowWidth, int windowHeight, int rowCount, int colCount, int mineCount, string& userName) {
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
    this->rowCount = rowCount;
    this->colCount = colCount;
    this->mineCount = mineCount;
    this->userName = userName;
}

void GameWindow::Display() {
    bool minesShown = false;
    sf::RenderWindow gameWindow(sf::VideoMode(windowWidth, windowHeight), "Game Window");
    Board gameBoard(rowCount, colCount, mineCount);
    Timer timer(rowCount, colCount);

    Button happyFace(1, rowCount, colCount);

    Button debug(3, rowCount, colCount);

    Button leaderboard(4, rowCount, colCount);

    int leaderboardWidth = colCount * 16;
    int leaderboardHeight = rowCount * 16 + 50;

    LeaderboardWindow leaderboardWindow = LeaderboardWindow(leaderboardWidth, leaderboardHeight);

    while (gameWindow.isOpen()) {
        sf::Event event;
        while (gameWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gameWindow.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (happyFace.Click(event, gameWindow)) {
                    gameBoard = Board(rowCount, colCount, mineCount);
                    happyFace.SetTexture(gameWindow, 3);
                    timer = Timer(rowCount, colCount);
                }

                if (debug.Click(event, gameWindow)) {
                    minesShown = !minesShown;
                    gameBoard.ToggleShowMines(gameWindow);
                }

                if (!(gameBoard.CheckLoss() || gameBoard.CheckWin())) {
                    gameBoard.Click(event, gameWindow);
                    timer.PauseUnpause(event, gameWindow);

                }
                if(leaderboard.Click(event, gameWindow)) {
                    leaderboardWindow.Display();
                    leaderboardWindow.ToggleDisplayed();
                }
            }
        }

        gameWindow.clear(sf::Color::White);
        gameBoard.Draw(gameWindow);
        if (minesShown) {
            gameBoard.ToggleShowMines(gameWindow);
        }
        if (gameBoard.CheckLoss()) {
            happyFace.SetTexture(gameWindow, 2);
        }

        if (gameBoard.CheckWin() && !leaderboardWindow.IsDisplayed()) {
            happyFace.SetTexture(gameWindow, 1);
            if (!timer.IsPaused())
                timer.TogglePaused();
            //leaderboardWindow.SetWinningTime(timer.GetWinningTime(), userName);
            timer.Draw(gameWindow);
            debug.Draw(gameWindow);
            leaderboard.Draw(gameWindow);
            gameWindow.display();
            leaderboardWindow.Display();
            leaderboardWindow.ToggleDisplayed();
        } else if (gameBoard.CheckWin()) {
            happyFace.SetTexture(gameWindow, 1);
            if (!timer.IsPaused())
                timer.TogglePaused();
            //leaderboardWindow.SetWinningTime(timer.GetWinningTime(), userName);
            timer.Draw(gameWindow);
            debug.Draw(gameWindow);
            leaderboard.Draw(gameWindow);
            gameWindow.display();
        } else {
            happyFace.Draw(gameWindow);
        }

        timer.Draw(gameWindow);
        debug.Draw(gameWindow);
        leaderboard.Draw(gameWindow);
        gameWindow.display();
    }
}
