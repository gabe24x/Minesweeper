#include "LeaderboardWindow.h"

LeaderboardWindow::LeaderboardWindow(int windowWidth, int windowHeight) {
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
    this->displayed = false;
}

bool compareEntries(const LeaderboardWindow::LeaderboardEntry& entry1, const LeaderboardWindow::LeaderboardEntry& entry2) {
    return entry1.time < entry2.time;
}

void LeaderboardWindow::Display() {
    displayed = true;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Minesweeper");
    sf::Font font;
    font.loadFromFile("font.ttf");

    sf::Text leaderboardText;
    leaderboardText.setString("LEADERBOARD");
    leaderboardText.setFont(font);
    leaderboardText.setCharacterSize(20);
    leaderboardText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    leaderboardText.setFillColor(sf::Color::White);

    sf::FloatRect leaderboardTextRect = leaderboardText.getLocalBounds();
    leaderboardText.setOrigin(leaderboardTextRect.left + leaderboardTextRect.width / 2.0f, leaderboardTextRect.top + leaderboardTextRect.height / 2.0f);
    leaderboardText.setPosition(sf::Vector2f(static_cast<float>(windowWidth)/2.0f, static_cast<float>(windowHeight)/2.0f - 120));

    std::ifstream in_file("leaderboard.txt");

    std::vector<LeaderboardEntry> leaderboard;

    std::string line;

    while (std::getline(in_file, line)) {
        std::stringstream ss(line);
        LeaderboardEntry entry;
        std::getline(ss, entry.time, ',');
        std::getline(ss, entry.name);
        leaderboard.push_back(entry);
    }

    in_file.close();

    std::sort(leaderboard.begin(), leaderboard.end(), compareEntries);

    std::string leaderboardContent;
    for (int i = 0; i < 4; ++i) {
        leaderboardContent += std::to_string(i + 1) + ".\t" + leaderboard[i].time + "\t" + leaderboard[i].name + "\n\n";
    }

    sf::Text contentText;
    contentText.setString(leaderboardContent);
    contentText.setFont(font);
    contentText.setCharacterSize(18);
    contentText.setStyle(sf::Text::Bold);
    contentText.setFillColor(sf::Color::White);

    sf::FloatRect contentTextRect = contentText.getLocalBounds();
    contentText.setOrigin(contentTextRect.left + contentTextRect.width / 2.0f, contentTextRect.top + contentTextRect.height / 2.0f);
    contentText.setPosition(sf::Vector2f(static_cast<float>(windowWidth)/2.0f, static_cast<float>(windowHeight)/2.0f + 20));

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
                displayed = false;
            }
        }

        window.clear(sf::Color::Blue);
        window.draw(leaderboardText);
        window.draw(contentText);
        window.display();
    }
}

bool LeaderboardWindow::IsDisplayed() {
    return displayed;
}

void LeaderboardWindow::ToggleDisplayed() {
    displayed = !displayed;
}

/*
void LeaderboardWindow::SetWinningTime(vector<int> winningTime, std::string& userName) {
    int winningSeconds = winningTime[0] * 60 + winningTime[1];

    std::ifstream in_file("leaderboard.txt");

    std::vector<LeaderboardEntry> leaderboard;

    std::string line;

    while (std::getline(in_file, line)) {
        std::stringstream ss(line);
        LeaderboardEntry entry;
        std::getline(ss, entry.time, ',');
        std::getline(ss, entry.name);
        leaderboard.push_back(entry);
    }

    in_file.close();

    std::sort(leaderboard.begin(), leaderboard.end(), compareEntries);

    std::string leaderboardContent;

    for (int i = 0; i < 4; ++i) {
        int minutes = std::stoi(leaderboard[i].time.substr(0, 2));
        int seconds = std::stoi(leaderboard[i].time.substr(3, 2));

        int entryTime = minutes * 60 + seconds;

        if (winningSeconds > entryTime) {
            leaderboardContent += std::to_string(i + 1) + ".\t" + leaderboard[i].time + "\t" + leaderboard[i].name + "\n\n";
        }
        else {
            LeaderboardEntry newEntry;
            string winningMinutesString;
            string winningSecondsString;
            if (winningTime[0] < 10)
                winningMinutesString = "0" + to_string(winningTime[0]);
            else
                winningMinutesString = to_string(winningTime[0]);
            if (winningTime[1] < 10)
                winningSecondsString = "0" + to_string(winningTime[1]);
            else
                winningSecondsString = to_string(winningTime[1]);
            newEntry.time = winningMinutesString + ":" + winningSecondsString;
            newEntry.name = userName;
            leaderboardContent += newEntry.time + ',' + newEntry.name + "\n";
            for (int j = i; j < 5; ++j) {
                leaderboardContent += leaderboard[j].time + ',' + leaderboard[j].name + "\n";
            }
        }
    }

    std::ofstream outputFile("leaderboard.txt", std::ios::trunc);

    outputFile << leaderboardContent;

    outputFile.close();
}
*/