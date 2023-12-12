#include "Textbox.h"

Textbox::Textbox() {
    textbox.setCharacterSize(18);
    textbox.setFillColor(sf::Color::Yellow);
    textbox.setString("|");
}

void Textbox::setFont(sf::Font &font) {
    textbox.setFont(font);
}

void Textbox::setPosition(sf::Vector2f pos) {
    x_pos = pos.x;
    y_pos = pos.y;
    sf::FloatRect textRect = textbox.getLocalBounds();
    textbox.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    textbox.setPosition(sf::Vector2f(x_pos, y_pos));
}

std::string Textbox::getText() {
    return text.str();
}

void Textbox::drawTo(sf::RenderWindow &window) {
    window.draw(textbox);
}

void Textbox::typedOn(sf::Event input, std::string& userName) {
    int charTyped = input.text.unicode;
    if ((charTyped >= 65 && charTyped <= 90) || (charTyped >= 97 && charTyped <= 122) || (charTyped == 8)) {
        if (text.str().length() < 10) {
            inputLogic(charTyped);
            userName += static_cast<char>(input.text.unicode);
        }
        else if (text.str().length() >= 10 && charTyped == 8) {
            deleteLastChar();
            userName.pop_back();
        }
    }
}

void Textbox::inputLogic(int charTyped) {
    if (charTyped == 8) {
        if (text.str().length() > 0) {
            deleteLastChar();
        }
    }
    else {
        if (getText().empty()) {
            if (charTyped >= 97) {
                charTyped -= 32;
            }
        }
        else {
            if (charTyped <= 90) {
                charTyped += 32;
            }
        }

        text << static_cast<char>(charTyped);
    }
    textbox.setString(text.str() + "|");
    setPosition(sf::Vector2f(x_pos, y_pos));
}

void Textbox::deleteLastChar() {
    std::string t = text.str();
    std::string newT = "";
    for (int i = 0; i < t.length() - 1; ++i) {
        newT += t[i];
    }
    text.str("");
    text << newT;

    textbox.setString(text.str());
}
