#pragma once
#include <SFML/Graphics.hpp>

class LayoutManager {
private:
    float windowWidth;
    float windowHeight;

    // Derived layout sections
    float leftPanelWidth;
    float boardWidth;
    float panelPadding;

public:
    LayoutManager(float width, float height);

    // Update layout when window resizes
    void update(float width, float height);

    // Accessors
    float getLeftPanelWidth() const { return leftPanelWidth; }
    float getBoardWidth() const { return boardWidth; }
    float getPanelPadding() const { return panelPadding; }

    // Helpers
    sf::FloatRect getLeftPanelBounds() const;
    sf::FloatRect getBoardBounds() const;

    // Task layout helpers
    sf::Vector2f getTaskPosition(int index, int columnCount = 3) const;
    sf::Vector2f getTaskSize(int columnCount = 3) const;
};
