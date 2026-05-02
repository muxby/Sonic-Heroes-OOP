#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Clock.hpp>
#include <cmath>

using namespace sf;
using namespace std;


#include "..\OOP_PROJECt\JumpQueue.h"
#include "..\OOP_PROJECt\PositionQueue.h"
#include"..\OOP_PROJECt\Game.cpp"

#include "..\OOP_PROJECt\Character.h"
#include "..\OOP_PROJECt\Animation.h"
#include "..\OOP_PROJECt\Enemies.h"
int main() {
    Game game;
    game.run();
    return 0;
}