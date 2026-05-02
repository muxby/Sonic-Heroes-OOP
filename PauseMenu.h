#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class PauseMenu {
public:
    PauseMenu(sf::Font& font);
    int run(sf::RenderWindow& window);

private:
    sf::Font& font;
    sf::Text menuItems[2];
    int selectedIndex;

    void moveUp();
    void moveDown();
    void updateSelection();
    void draw(sf::RenderWindow& window);
};