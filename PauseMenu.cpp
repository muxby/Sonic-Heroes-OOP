#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::Font& fontRef) : font(fontRef), selectedIndex(0) {
    menuItems[0] = sf::Text("Resume Game", font, 60);
    menuItems[1] = sf::Text("Exit to Main Menu", font, 60);
    for (int i = 0; i < 2; ++i) {
        menuItems[i].setPosition(420, 400 + i * 80);
    }
    updateSelection();
}

int PauseMenu::run(sf::RenderWindow& window) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                return 1; // Exit to main menu
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) moveUp();
                else if (event.key.code == sf::Keyboard::Down) moveDown();
                else if (event.key.code == sf::Keyboard::Enter) {
                    if (selectedIndex == 0) return 0; // Resume game
                    else return 1; // Exit to main menu
                }
            }
        }

        window.clear();
        draw(window);
        window.display();
    }
    return 1; // Exit to main menu if window is closed
}

void PauseMenu::moveUp() {
    selectedIndex = (selectedIndex - 1 + 2) % 2;
    updateSelection();
}

void PauseMenu::moveDown() {
    selectedIndex = (selectedIndex + 1) % 2;
    updateSelection();
}

void PauseMenu::updateSelection() {
    for (int i = 0; i < 2; ++i) {
        menuItems[i].setFillColor(i == selectedIndex ? sf::Color::Yellow : sf::Color::White);
    }
}

void PauseMenu::draw(sf::RenderWindow& window) {
    for (int i = 0; i < 2; ++i) {
        sf::Text shadow = menuItems[i];
        shadow.move(3.f, 3.f);
        shadow.setFillColor(sf::Color(50, 50, 50));
        window.draw(shadow);
        window.draw(menuItems[i]);
    }
}