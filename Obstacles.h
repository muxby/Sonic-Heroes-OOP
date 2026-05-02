#include "Game.h"
#include "Menu.cpp"

// Obstacle Base Class
class Obstacle {
public:
    virtual void handleCollision(Character* chara, bool isMain, int& sharedHP, Game* game) = 0;
};

// Spike Class
class Spike : public Obstacle {
public:
    void handleCollision(Character* chara, bool isMain, int& sharedHP, Game* game) override {
        if (isMain) {
            std::cout << "fall on spike" << std::endl;
            sharedHP--;
            if (sharedHP <= 0) {
                std::cout << "Game Over!" << std::endl;
                game->gameOver = true; // Flag to handle game over
            }
        } else {
            std::cout << "follower collides on it" << std::endl;
        }
        game->respawnCharacter(chara); // Respawn after collision
    }
};

// Pit Class
class Pit : public Obstacle {
public:
    void handleCollision(Character* chara, bool isMain, int& sharedHP, Game* game) override {
        if (isMain) {
            std::cout << "Game Over" << std::endl;
            sharedHP = 0;
            game->gameOver = true; // Flag to handle game over
        } else {
            game->respawnCharacter(chara); // Respawn follower
        }
    }
};