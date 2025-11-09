#include "LayoutManager.h"

LayoutManager::LayoutManager(float width, float height) {
    update(width, height);
}

void LayoutManager::update(float width, float height) {
    windowWidth = width;
    windowHeight = height;

    leftPanelWidth = width * 0.25f;  // 25% of window for Lulu + buttons
    boardWidth = width - leftPanelWidth;
    panelPadding = 20.f;
}

sf::FloatRect LayoutManager::getLeftPanelBounds() const {
    return sf::FloatRect(0, 0, leftPanelWidth, windowHeight);
}

sf::FloatRect LayoutManager::getBoardBounds() const {
    return sf::FloatRect(leftPanelWidth, 0, boardWidth, windowHeight);
}

sf::Vector2f LayoutManager::getTaskSize(int columnCount) const {
    float noteWidth = (boardWidth - (columnCount + 1) * panelPadding) / columnCount;
    float noteHeight = windowHeight * 0.15f;
    return sf::Vector2f(noteWidth, noteHeight);
}

sf::Vector2f LayoutManager::getTaskPosition(int index, int columnCount) const {
    int column = index % columnCount;
    int row = index / columnCount;

    sf::Vector2f taskSize = getTaskSize(columnCount);

    float startX = leftPanelWidth + panelPadding;
    float startY = windowHeight * 0.15f;

    float x = startX + column * (taskSize.x + panelPadding);
    float y = startY + row * (taskSize.y + panelPadding);

    return sf::Vector2f(x, y);
}
