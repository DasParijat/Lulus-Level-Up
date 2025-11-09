#include "TextInput.h"
#include <iostream>

using namespace sf;

TextInput::TextInput() {
    // bright background so you can see it
    box.setFillColor(Color(71, 18, 70));
    box.setOutlineColor(Color(168, 0, 173));
    box.setOutlineThickness(3.f);
    box.setSize({ 400.f, 50.f });

    text.setCharacterSize(28);
    text.setFillColor(sf::Color::White);
    text.setPosition(15.f, 8.f);
}


void TextInput::setFont(sf::Font& font) {
    text.setFont(font);
}

void TextInput::setPosition(float x, float y) {
    box.setPosition(x, y);
    text.setPosition(x + 10.f, y + 5.f);
}

void TextInput::setBoxSize(float width, float height) {
    box.setSize({ width, height });
}

void TextInput::handleEvent(sf::Event& event) {
    // Check for mouse click -> toggle focus
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(
            static_cast<float>(event.mouseButton.x),
            static_cast<float>(event.mouseButton.y)
        );

        // Activate if the click was inside the box
        if (box.getGlobalBounds().contains(mousePos)) {
            isActive = true;
            box.setOutlineColor(Color(255, 61, 203));   // active border
        }
        else {
            isActive = false;
            box.setOutlineColor(Color(168, 0, 173));  // inactive border
        }
    }

    // Handle typing and backspace only when active
    if (isActive && event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 8 && !content.empty()) {
            // Backspace key
            content.pop_back();
        }
        else if (event.text.unicode >= 32 && event.text.unicode < 128) {
            // Printable characters
            content += static_cast<char>(event.text.unicode);
        }
        text.setString(content);
    }

    // Handle Enter -> submit and clear
    if (isActive && event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::Enter) {
        if (!content.empty()) {
            std::cout << "Submitted text: " << content << std::endl;
            hasSubmitted = true;  // signal that new text is ready
            isActive = false;
            box.setOutlineColor(sf::Color::Yellow);
        }
    }
}



void TextInput::clear() {
    content.clear();
    text.setString("");
}

void TextInput::draw(sf::RenderWindow& window) {
    window.draw(box);
    window.draw(text);
}
