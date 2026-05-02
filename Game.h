#pragma once
#include "..\OOP_PROJECT\Character.h"
#include "..\OOP_PROJECT\JumpQueue.h"
#include "..\OOP_PROJECT\PositionQueue.h"
#include "..\OOP_PROJECT\Enemies.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "Menu.h"
#include "PauseMenu.h"

class Game {
public:
    Game();
    ~Game();
    void run();
    void initializeLevel(int level); // Added to load specific level

private:
    // Textures
    sf::Texture wallTexture, backgroundTexture[3], blockTexture, platformTexture, crystalTexture, block3Texture, spikeTexture, pitTexture ,block4Texture;
    sf::Texture grassTexture;  
    sf::Texture sonicIdleLeftTexture, sonicIdleRightTexture;
    sf::Texture sonicRunLeftTexture, sonicRunRightTexture;
    sf::Texture sonicJumpTexture;
    sf::Texture sonicPushLeftTexture, sonicPushRightTexture;
    sf::Texture sonicEdgeLeftTexture, sonicEdgeRightTexture;
    sf::Texture knucklesIdleLeftTexture, knucklesIdleRightTexture;
    sf::Texture knucklesRunLeftTexture, knucklesRunRightTexture;
    sf::Texture knucklesJumpLeftTexture, knucklesJumpRightTexture;
    sf::Texture knucklesPushLeftTexture, knucklesPushRightTexture;
    sf::Texture knucklesEdgeLeftTexture, knucklesEdgeRightTexture;
    sf::Texture knucklesPunchLeftTexture, knucklesPunchRightTexture;
    sf::Texture tailsIdleLeftTexture, tailsIdleRightTexture;
    sf::Texture tailsRunLeftTexture, tailsRunRightTexture;
    sf::Texture tailsJumpTexture;
    sf::Texture tailsFlyLeftTexture, tailsFlyRightTexture;
    sf::Texture tailsPushLeftTexture, tailsPushRightTexture;
    sf::Texture tailsEdgeLeftTexture, tailsEdgeRightTexture;
    sf::Texture batBrainIdleLeftTexture, batBrainIdleRightTexture;
    sf::Texture batBrainMoveLeftTexture, batBrainMoveRightTexture;
    sf::Texture beeBotIdleLeftTexture, beeBotIdleRightTexture;
    sf::Texture beeBotMoveLeftTexture, beeBotMoveRightTexture;
    sf::Texture motobugIdleLeftTexture, motobugIdleRightTexture;
    sf::Texture motobugMoveLeftTexture, motobugMoveRightTexture;
    sf::Texture crabMeatIdleLeftTexture, crabMeatIdleRightTexture;
    sf::Texture crabMeatMoveLeftTexture, crabMeatMoveRightTexture;
    sf::Texture eggStingerIdleLeftTexture, eggStingerIdleRightTexture;
    sf::Texture eggStingerMoveLeftTexture, eggStingerMoveRightTexture;
    sf::Texture projectileTexture;

    // Sprites
    sf::Sprite backgroundSprite, blockSprite, platformSprite, crystalSprite, block3Sprite, block4Sprite, spikeSprite, pitSprite;
    sf::Sprite grassSprite;
    // UI
    sf::Font font;
    sf::Text timerText;
    sf::Text gameTimerText;
    sf::Clock gameTimerClock;
    float timerX, timerY;

    // Audio
    sf::Music backgroundMusic;

    // Level data
    const char** level;
    char** mapData;
    int rows, cols;
    float startX, startY;
    float levelWidth, levelHeight;

    // Characters
    Character* characters[3];
    int mainIndex;
    float offScreenTimers[3];
    int drawOrder[3];
    float maxSpeed;

    // Queues for follower mechanics
    JumpQueue jumpQueues[3];
    PositionQueue positionQueue;
    const int delayFrames;

    // Enemies
    static const int MAX_ENEMIES = 50;
    Enemy* enemies[MAX_ENEMIES];
    int enemyCount;

    // Projectiles
    static const int MAX_PROJECTILES = 100;
    Projectile* projectiles[MAX_PROJECTILES];
    int projectileCount;
    PauseMenu pauseMenu; // Added for pause menu
    bool isPaused; // Added to track paused state

    // Methods

    void updateDrawOrder();
    void loadMap(const std::string& filename);
    void loadEnemies(const std::string& filename);
    void updateEnemies(float deltaTime, float gravity, float terminalVelocity);
    void drawEnemies(sf::RenderWindow& window, const sf::RenderStates& states);
    void updateProjectiles(float deltaTime);
    void drawProjectiles(sf::RenderWindow& window, const sf::RenderStates& states);
    void checkCollisions();
    void drawLevel(sf::RenderWindow& window, sf::Sprite& wallSprite, const sf::RenderStates& states);
    void checkCharacterRespawn(float cameraX, float cameraY);
    void checkHazardCollisions(int& sharedHP, float& invincibilityTimer);
    void respawnCharacter(int charIndex, bool isMain);
    void handlePause(sf::RenderWindow& window);
};