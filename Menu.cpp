#include "Menu.h"

Menu::Menu(sf::Font& fontRef, sf::Music& music)
    : font(fontRef), music(music), selectedIndex(0), isLevelSubmenu(false),
      isSaveSlotSubmenu(false), isScoreboardView(false), musicOn(true), selectedLevel(1), backgroundX(0.0f),
      fadeDuration(2.0f), entryCount(0) {
    // Load background
    if (!backgroundTexture.loadFromFile("Data/image_fx.jpg"))
        std::cerr << "Error loading background image\n";
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(1.5f, 1.5f);

    // Load logo
    if (!logoTexture.loadFromFile("Data/logo.png"))
        std::cerr << "Error loading logo image\n";
    float logoScale = 0.6f;
    logoSprite.setTexture(logoTexture);
    logoSprite.setScale(logoScale, logoScale);
    logoSprite.setPosition((1200 - logoTexture.getSize().x * logoScale) / 2, 20);

    // Shadow
    shadowSprite = logoSprite;
    shadowSprite.setColor(sf::Color(0, 0, 0, 120));
    shadowSprite.move(5, 5);

    // Main menu items
    const char* menuNames[6] = { "Start Game", "Load Game", "Scoreboard", "Level 1", "Music: On", "Exit Game" };
    for (int i = 0; i < 6; ++i) {
        mainMenuItems[i] = sf::Text(menuNames[i], font, 60);
        mainMenuItems[i].setPosition(420, 300 + i * 80);
    }

    // Level submenu
    const char* levelNames[4] = { "Level One", "Level Two", "Level Three", "Back" };
    for (int i = 0; i < 4; ++i) {
        levelMenuItems[i] = sf::Text(levelNames[i], font, 60);
        levelMenuItems[i].setPosition(450, 320 + i * 80);
    }

    // Save slot submenu
    const char* saveSlotNames[4] = { "Slot 1", "Slot 2", "Slot 3", "Back" };
    for (int i = 0; i < 4; ++i) {
        saveSlotItems[i] = sf::Text(saveSlotNames[i], font, 60);
        saveSlotItems[i].setPosition(450, 320 + i * 80);
    }

    // Scoreboard texts
    for (int i = 0; i < 10; ++i) {
        scoreboardTexts[i].setFont(font);
        scoreboardTexts[i].setCharacterSize(40);
        scoreboardTexts[i].setFillColor(sf::Color::White);
        scoreboardTexts[i].setPosition(300, 370 + i * 60);
        scoreboardTexts[i].setOutlineThickness(2.f);
        scoreboardTexts[i].setOutlineColor(sf::Color(89, 71, 67));
    }

    // Input prompt
    inputBox.setSize({ 600, 80 });
    inputBox.setFillColor(sf::Color(50, 50, 50, 200));
    inputBox.setPosition(350, 400);
    inputText.setFont(font);
    inputText.setCharacterSize(40);
    inputText.setFillColor(sf::Color::White);
    inputText.setPosition(360, 410);

    // Creators
    Creators = sf::Text("Created by Mubeen and Abubakar", font, 30);
    Creators.setPosition(320, 850);
    Creators.setFillColor(sf::Color::Red);
    Creators.setOutlineColor(sf::Color::White);
    Creators.setOutlineThickness(2);

    updateSelection();
    fadeClock.restart();
}

int Menu::run(sf::RenderWindow& window) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                return EXIT;
            if (event.type == sf::Event::KeyPressed) {
                if (isScoreboardView) {
                    if (event.key.code == sf::Keyboard::Escape)
                        isScoreboardView = false;
                } else if (isSaveSlotSubmenu) {
                    if (event.key.code == sf::Keyboard::Up) moveUp();
                    else if (event.key.code == sf::Keyboard::Down) moveDown();
                    else if (event.key.code == sf::Keyboard::Enter) {
                        if (selectedIndex < 3) {
                            selectedSaveSlot = "Slot " + std::to_string(selectedIndex + 1);
                            std::cout << "Selected save slot: " << selectedSaveSlot << "\n";
                        }
                        isSaveSlotSubmenu = false;
                    }
                } else if (isLevelSubmenu) {
                    if (event.key.code == sf::Keyboard::Up) moveUp();
                    else if (event.key.code == sf::Keyboard::Down) moveDown();
                    else if (event.key.code == sf::Keyboard::Enter) {
                        if (selectedIndex < 3) {
                            selectedLevel = selectedIndex + 1;
                            mainMenuItems[3].setString("Level " + std::to_string(selectedLevel));
                        }
                        isLevelSubmenu = false;
                    }
                } else {
                    if (event.key.code == sf::Keyboard::Up) moveUp();
                    else if (event.key.code == sf::Keyboard::Down) moveDown();
                    else if (event.key.code == sf::Keyboard::Enter) {
                        int action = select(window);
                        if (action != -1) return action;
                    }
                }
            }
        }

        // Animate background
        backgroundX += 0.5f;
        if (backgroundX >= backgroundTexture.getSize().x) backgroundX = 0;
        backgroundSprite.setPosition(-backgroundX, 0);

        // Fade logo
        float elapsed = fadeClock.getElapsedTime().asSeconds();
        float alpha = std::min(255.f, (elapsed / fadeDuration) * 255.f);
        sf::Color lc = logoSprite.getColor();
        sf::Color sc = shadowSprite.getColor();
        lc.a = static_cast<sf::Uint8>(alpha);
        sc.a = static_cast<sf::Uint8>(alpha * 0.5f);
        logoSprite.setColor(lc);
        shadowSprite.setColor(sc);

        // Draw
        window.clear();
        window.draw(backgroundSprite);
        window.draw(shadowSprite);
        window.draw(logoSprite);
        if (isScoreboardView) drawScoreboard(window);
        else if (isSaveSlotSubmenu) drawSaveSlots(window);
        else draw(window);
        window.display();
    }
    return EXIT;
}

int Menu::getSelectedLevel() const {
    return selectedLevel;
}

std::string Menu::getSelectedSaveSlot() const {
    return selectedSaveSlot;
}

void Menu::moveUp() {
    int max = isLevelSubmenu || isSaveSlotSubmenu ? 4 : 6;
    selectedIndex = (selectedIndex - 1 + max) % max;
    updateSelection();
}

void Menu::moveDown() {
    int max = isLevelSubmenu || isSaveSlotSubmenu ? 4 : 6;
    selectedIndex = (selectedIndex + 1) % max;
    updateSelection();
}

void Menu::updateSelection() {
    if (isLevelSubmenu) {
        for (int i = 0; i < 4; ++i)
            levelMenuItems[i].setFillColor(i == selectedIndex ? sf::Color::Yellow : sf::Color::White);
    } else if (isSaveSlotSubmenu) {
        for (int i = 0; i < 4; ++i)
            saveSlotItems[i].setFillColor(i == selectedIndex ? sf::Color::Yellow : sf::Color::White);
    } else {
        for (int i = 0; i < 6; ++i)
            mainMenuItems[i].setFillColor(i == selectedIndex ? sf::Color::Yellow : sf::Color::White);
    }
}

int Menu::select(sf::RenderWindow& window) {
    if (isLevelSubmenu) {
        if (selectedIndex < 3) {
            selectedLevel = selectedIndex + 1;
            mainMenuItems[3].setString("Level " + std::to_string(selectedLevel));
        }
        isLevelSubmenu = false;
    } else if (isSaveSlotSubmenu) {
        if (selectedIndex < 3) {
            selectedSaveSlot = "Slot " + std::to_string(selectedIndex + 1);
            std::cout << "Selected save slot: " << selectedSaveSlot << "\n";
        }
        isSaveSlotSubmenu = false;
    } else {
        switch (selectedIndex) {
        case 0: {
            char playerName[32] = { '\0' };
            getPlayerName(window, playerName);
            updateScoreboard(playerName, 0);
            return START_GAME;
        }
        case 1: isSaveSlotSubmenu = true; selectedIndex = 0; break;
        case 2: loadScores(); isScoreboardView = true; break;
        case 3: isLevelSubmenu = true; selectedIndex = 0; break;
        case 4: toggleMusic(); break;
        case 5: return EXIT;
        }
    }
    return -1;
}

void Menu::getPlayerName(sf::RenderWindow& window, char* outName) {
    std::fill(inputName, inputName + 32, '\0');
    int len = 0;
    bool entering = true;
    while (entering) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) entering = false;
            else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') {
                    if (len > 0) inputName[--len] = '\0';
                } else if (len < 31 && event.text.unicode >= 32 && event.text.unicode < 128) {
                    inputName[len++] = static_cast<char>(event.text.unicode);
                    inputName[len] = '\0';
                }
                inputText.setString(inputName);
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Return) entering = false;
            }
        }
        window.clear();
        window.draw(backgroundSprite);
        window.draw(shadowSprite);
        window.draw(logoSprite);
        window.draw(inputBox);
        window.draw(inputText);
        window.display();
    }
    for (int i = 0; i < 32; ++i) outName[i] = inputName[i];
}

void Menu::toggleMusic() {
    musicOn = !musicOn;
    mainMenuItems[4].setString(musicOn ? "Music: On" : "Music: Off");
    if (musicOn) music.play(); else music.stop();
}

void Menu::draw(sf::RenderWindow& window) {
    if (isLevelSubmenu) {
        for (int i = 0; i < 4; ++i) {
            sf::Text shadow = levelMenuItems[i];
            shadow.move(3.f, 3.f);
            shadow.setFillColor(sf::Color(50, 50, 50));
            window.draw(shadow);
            window.draw(levelMenuItems[i]);
        }
    } else if (isSaveSlotSubmenu) {
        drawSaveSlots(window);
    } else {
        for (int i = 0; i < 6; ++i) {
            sf::Text shadowText = mainMenuItems[i];
            shadowText.move(3.f, 3.f);
            shadowText.setFillColor(sf::Color(50, 50, 50));
            window.draw(shadowText);
            window.draw(mainMenuItems[i]);
        }
    }
    window.draw(Creators);
}

void Menu::drawSaveSlots(sf::RenderWindow& window) {
    for (int i = 0; i < 4; ++i) {
        sf::Text shadow = saveSlotItems[i];
        shadow.move(3.f, 3.f);
        shadow.setFillColor(sf::Color(50, 50, 50));
        window.draw(shadow);
        window.draw(saveSlotItems[i]);
    }
}

void Menu::loadScores() {
    std::ifstream file(scoreFile);
    entryCount = 0;
    if (!file.is_open()) return;

    char line[256];
    while (file.getline(line, 256) && entryCount < 100) {
        int lastSpace = -1;
        for (int i = 0; line[i] != '\0'; i++) {
            if (line[i] == ' ') lastSpace = i;
        }
        if (lastSpace == -1) continue;

        int nameLen = lastSpace;
        while (nameLen > 0 && line[nameLen - 1] == ' ') nameLen--;
        if (nameLen > 31) nameLen = 31;

        for (int i = 0; i < nameLen; i++) entries[entryCount].name[i] = line[i];
        entries[entryCount].name[nameLen] = '\0';

        int i = lastSpace + 1;
        while (line[i] == ' ') i++;
        int score = 0;
        while (line[i] >= '0' && line[i] <= '9') {
            score = score * 10 + (line[i] - '0');
            i++;
        }
        entries[entryCount].score = score;
        entryCount++;
    }
    file.close();

    for (int i = 0; i < entryCount - 1; i++) {
        for (int j = 0; j < entryCount - i - 1; j++) {
            if (entries[j].score < entries[j + 1].score) {
                Entry temp = entries[j];
                entries[j] = entries[j + 1];
                entries[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < entryCount && i < 10; i++) {
        char displayText[64];
        char scoreStr[16];
        int tempScore = entries[i].score;
        int scoreDigits = 0;
        if (tempScore == 0) {
            scoreStr[0] = '0';
            scoreStr[1] = '\0';
            scoreDigits = 1;
        } else {
            int temp = tempScore;
            while (temp > 0) {
                scoreDigits++;
                temp /= 10;
            }
            for (int j = scoreDigits - 1; j >= 0; j--) {
                scoreStr[j] = '0' + (tempScore % 10);
                tempScore /= 10;
            }
            scoreStr[scoreDigits] = '\0';
        }

        int pos = 0;
        displayText[pos++] = '0' + (i + 1) / 10;
        if ((i + 1) >= 10) displayText[pos++] = '0' + (i + 1) % 10;
        else displayText[pos - 1] = '0' + (i + 1);
        displayText[pos++] = '.';
        displayText[pos++] = ' ';
        for (int j = 0; entries[i].name[j] != '\0'; j++) {
            displayText[pos++] = entries[i].name[j];
        }
        displayText[pos++] = ' ';
        displayText[pos++] = '-';
        displayText[pos++] = ' ';
        for (int j = 0; j < scoreDigits; j++) {
            displayText[pos++] = scoreStr[j];
        }
        displayText[pos] = '\0';
        scoreboardTexts[i].setString(displayText);
    }
}

void Menu::updateScoreboard(const char* name, int score) {
    std::ofstream file(scoreFile, std::ios::app);
    if (!file.is_open()) return;
    file << name << " " << score << "\n";
}

void Menu::drawScoreboard(sf::RenderWindow& window) {
    sf::Text title("--- Top 10 Scores ---", font, 60);
    title.setPosition(250, 300);
    sf::Text titleShadow = title;
    titleShadow.move(3.f, 3.f);
    titleShadow.setFillColor(sf::Color(50, 50, 50));

    window.draw(titleShadow);
    window.draw(title);

    for (int i = 0; i < entryCount && i < 10; ++i) {
        sf::Text shadow = scoreboardTexts[i];
        shadow.move(2.f, 2.f);
        shadow.setFillColor(sf::Color(50, 50, 50));
        window.draw(shadow);
        window.draw(scoreboardTexts[i]);
    }
}