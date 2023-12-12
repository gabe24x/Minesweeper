#include "WelcomeWindow.h"

WelcomeWindow::WelcomeWindow(int windowWidth, int windowHeight) {
        this->windowWidth = windowWidth;
        this->windowHeight = windowHeight;
}

string WelcomeWindow::Display() {
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Minesweeper");
    sf::Font font;
    font.loadFromFile("font.ttf");

    sf::Text welcomeText;
    welcomeText.setString("WELCOME TO MINESWEEPER!");
    welcomeText.setFont(font);
    welcomeText.setCharacterSize(24);
    welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    welcomeText.setFillColor(sf::Color::White);

    sf::FloatRect welcomeTextRect = welcomeText.getLocalBounds();
    welcomeText.setOrigin(welcomeTextRect.left + welcomeTextRect.width / 2.0f, welcomeTextRect.top + welcomeTextRect.height / 2.0f);
    welcomeText.setPosition(sf::Vector2f(static_cast<float>(windowWidth)/2.0f, static_cast<float>(windowHeight)/2.0f - 150));

    sf::Text enterNameText;
    enterNameText.setString("Enter your name:");
    enterNameText.setFont(font);
    enterNameText.setCharacterSize(20);
    enterNameText.setStyle(sf::Text::Bold);
    enterNameText.setFillColor(sf::Color::White);

    sf::FloatRect enterNameTextRect = enterNameText.getLocalBounds();
    enterNameText.setOrigin(enterNameTextRect.left + enterNameTextRect.width / 2.0f, enterNameTextRect.top + enterNameTextRect.height / 2.0f);
    enterNameText.setPosition(sf::Vector2f(static_cast<float>(windowWidth)/2.0f, static_cast<float>(windowHeight)/2.0f - 75));

    Textbox textbox1;
    textbox1.setFont(font);
    textbox1.setPosition(sf::Vector2f(static_cast<float>(windowWidth)/2.0f, static_cast<float>(windowHeight)/2.0f - 45));

    std::string userName;

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
                std::exit(0);
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    if (!textbox1.getText().empty()){
                        std::string capitalized = userName;
                        capitalized[0] = std::toupper(capitalized[0]);
                        window.close();
                        return capitalized;
                    }
                }
            }

            if (event.type == sf::Event::TextEntered) {
                textbox1.typedOn(event, userName);
            }

        }

        window.clear(sf::Color::Blue);
        window.draw(welcomeText);
        window.draw(enterNameText);
        textbox1.drawTo(window);
        window.display();
    }
}
