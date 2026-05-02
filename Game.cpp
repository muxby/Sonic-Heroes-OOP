#include "Game.h"
#include "Menu.cpp"
#include"PauseMenu.cpp"
Game::Game() : jumpQueues{ JumpQueue(), JumpQueue(), JumpQueue() }, positionQueue(100), delayFrames(30), enemyCount(0), projectileCount(0), pauseMenu(font), isPaused(false) {
    // Load assets
    if (!wallTexture.loadFromFile("Data/brick1.png") ||
        !backgroundTexture[0].loadFromFile("Data/background_level1.png") || // Background for level 1
        !backgroundTexture[1].loadFromFile("Data/background_level2.png") || // Background for level 2
        !backgroundTexture[2].loadFromFile("Data/background_level3.png") || // Background for level 3
        !blockTexture.loadFromFile("Data/block.png") ||
        !platformTexture.loadFromFile("Data/platform.png") ||
        !crystalTexture.loadFromFile("Data/crystal.png") ||
        !block3Texture.loadFromFile("Data/block3.png") ||
        !spikeTexture.loadFromFile("Data/spik.png") ||
        !pitTexture.loadFromFile("Data/pit.png") ||
        !grassTexture.loadFromFile("Data/grass.png") ||
        !block4Texture.loadFromFile("Data/block4.png")||
        !font.loadFromFile("Data/arial.ttf") ||
        !backgroundMusic.openFromFile("Data/labrynth.ogg")) {
        std::cout << "Failed to load assets.\n";
        return;
    }

    // Load character textures
    if (!sonicIdleLeftTexture.loadFromFile("Data/0left_still.png") ||
        !sonicIdleRightTexture.loadFromFile("Data/0right_still.png") ||
        !sonicRunLeftTexture.loadFromFile("Data/sonic_runl.png") ||
        !sonicRunRightTexture.loadFromFile("Data/sonic_runr.png") ||
        !sonicJumpTexture.loadFromFile("Data/sonic_jump.png") ||
        !sonicPushLeftTexture.loadFromFile("Data/sonic_pushl.png") ||
        !sonicPushRightTexture.loadFromFile("Data/sonic_pushr.png") ||
        !sonicEdgeLeftTexture.loadFromFile("Data/sonic_edgel.png") ||
        !sonicEdgeRightTexture.loadFromFile("Data/sonic_edger.png") ||
        !knucklesIdleLeftTexture.loadFromFile("Data/knuckles_idle_left.png") ||
        !knucklesIdleRightTexture.loadFromFile("Data/knuckles_idle_right.png") ||
        !knucklesRunLeftTexture.loadFromFile("Data/knuckles_run_left.png") ||
        !knucklesRunRightTexture.loadFromFile("Data/knuckles_run_right.png") ||
        !knucklesJumpLeftTexture.loadFromFile("Data/knuckles_jump_left.png") ||
        !knucklesJumpRightTexture.loadFromFile("Data/knuckles_jump_right.png") ||
        !knucklesPushLeftTexture.loadFromFile("Data/knuckles_push_left.png") ||
        !knucklesPushRightTexture.loadFromFile("Data/knuckles_push_right.png") ||
        !knucklesEdgeLeftTexture.loadFromFile("Data/knuckles_edge_left.png") ||
        !knucklesEdgeRightTexture.loadFromFile("Data/knuckles_edge_right.png") ||
        !knucklesPunchLeftTexture.loadFromFile("Data/knuckles_punch_left.png") ||
        !knucklesPunchRightTexture.loadFromFile("Data/knuckles_punch_right.png") ||
        !tailsIdleLeftTexture.loadFromFile("Data/tails_idle_left.png") ||
        !tailsFlyLeftTexture.loadFromFile("Data/tails_fly_left.png") ||
        !tailsFlyRightTexture.loadFromFile("Data/tails_fly_right.png") ||
        !tailsIdleRightTexture.loadFromFile("Data/tails_idle_right.png") ||
        !tailsRunLeftTexture.loadFromFile("Data/tails_run_left.png") ||
        !tailsRunRightTexture.loadFromFile("Data/tails_run_right.png") ||
        !tailsJumpTexture.loadFromFile("Data/tails_jump.png") ||
        !tailsPushLeftTexture.loadFromFile("Data/tails_push_left.png") ||
        !tailsPushRightTexture.loadFromFile("Data/tails_push_right.png") ||
        !tailsEdgeLeftTexture.loadFromFile("Data/tails_edge_left.png") ||
        !tailsEdgeRightTexture.loadFromFile("Data/tails_edge_right.png")) {
        std::cout << "Failed to load character textures.\n";
        return;
    }

    // Load enemy textures
    if (!batBrainIdleLeftTexture.loadFromFile("Data/batbrain_idle_left.png") ||
        !batBrainIdleRightTexture.loadFromFile("Data/batbrain_idle_right.png") ||
        !batBrainMoveLeftTexture.loadFromFile("Data/batbrain_move_left.png") ||
        !batBrainMoveRightTexture.loadFromFile("Data/batbrain_move_right.png") ||
        !beeBotIdleLeftTexture.loadFromFile("Data/beebot_idle_left.png") ||
        !beeBotIdleRightTexture.loadFromFile("Data/beebot_idle_right.png") ||
        !beeBotMoveLeftTexture.loadFromFile("Data/beebot_move_left.png") ||
        !beeBotMoveRightTexture.loadFromFile("Data/beebot_move_right.png") ||
        !motobugIdleLeftTexture.loadFromFile("Data/motobug_idle_left.png") ||
        !motobugIdleRightTexture.loadFromFile("Data/motobug_idle_right.png") ||
        !motobugMoveLeftTexture.loadFromFile("Data/motobug_move_left.png") ||
        !motobugMoveRightTexture.loadFromFile("Data/motobug_move_right.png") ||
        !crabMeatIdleLeftTexture.loadFromFile("Data/crabmeat_idle_left.png") ||
        !crabMeatIdleRightTexture.loadFromFile("Data/crabmeat_idle_right.png") ||
        !crabMeatMoveLeftTexture.loadFromFile("Data/crabmeat_move_left.png") ||
        !crabMeatMoveRightTexture.loadFromFile("Data/crabmeat_move_right.png") ||
        !eggStingerIdleLeftTexture.loadFromFile("Data/eggstinger_idle_left.png") ||
        !eggStingerIdleRightTexture.loadFromFile("Data/eggstinger_idle_right.png") ||
        !eggStingerMoveLeftTexture.loadFromFile("Data/eggstinger_move_left.png") ||
        !eggStingerMoveRightTexture.loadFromFile("Data/eggstinger_move_right.png") ||
        !projectileTexture.loadFromFile("Data/projectile.png")) {
        std::cout << "Failed to load enemy or projectile textures.\n";
        return;
    }

    // Initialize arrays
    for (int i = 0; i < MAX_ENEMIES; ++i) {
        enemies[i] = nullptr;
    }
    for (int i = 0; i < MAX_PROJECTILES; ++i) {
        projectiles[i] = nullptr;
    }

    // Set up sprites
    backgroundSprite.setTexture(backgroundTexture[0]); // Default to level 1 background
    backgroundSprite.setScale(1.4f, 1.4f);
    blockSprite.setTexture(blockTexture);
    platformSprite.setTexture(platformTexture);
    crystalSprite.setTexture(crystalTexture);
    block3Sprite.setTexture(block3Texture);
    block4Sprite.setTexture(block4Texture);
    spikeSprite.setTexture(spikeTexture);
    pitSprite.setTexture(pitTexture);
    grassSprite.setTexture(grassTexture);
    // Set up audio
    backgroundMusic.setLoop(true);
    backgroundMusic.setVolume(30);
    backgroundMusic.play();

    // Set up text
    timerText.setFont(font);
    timerText.setCharacterSize(20);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(10, 10);

    gameTimerText.setFont(font);
    gameTimerText.setCharacterSize(20);
    gameTimerText.setFillColor(sf::Color::White);
    timerX = 10;
    timerY = 40;
    gameTimerText.setPosition(timerX, timerY);

    // Load map and enemies
    loadMap("Data/map.txt");
    if (!level || rows <= 0 || cols <= 0) {
        std::cout << "Failed to load valid level data.\n";
        return;
    }
    loadEnemies("Data/enemies.txt");

    levelWidth = cols * CELL_SIZE;
    levelHeight = rows * CELL_SIZE;

    // Set up characters
    float sonicScale = 2.8f;
    float knucklesScale = 2.8f;
    float tailsScale = 2.8f;

    startX = CELL_SIZE * 1.0f;
    startY = CELL_SIZE * 11.1f;
    maxSpeed = 14.0f;

    characters[0] = new Sonic(startX, startY, 40, 40, maxSpeed, sonicScale,
        sonicIdleLeftTexture, sonicIdleRightTexture,
        sonicRunLeftTexture, sonicRunRightTexture, sonicJumpTexture,
        sonicPushLeftTexture, sonicPushRightTexture,
        sonicEdgeLeftTexture, sonicEdgeRightTexture);

    characters[1] = new Knuckles(startX, startY, 40, 40, maxSpeed, knucklesScale,
        knucklesIdleLeftTexture, knucklesIdleRightTexture,
        knucklesRunLeftTexture, knucklesRunRightTexture,
        knucklesJumpLeftTexture, knucklesJumpRightTexture,
        knucklesPushLeftTexture, knucklesPushRightTexture,
        knucklesEdgeLeftTexture, knucklesEdgeRightTexture,
        knucklesPunchLeftTexture, knucklesPunchRightTexture);

    characters[2] = new Tails(startX, startY, 40, 40, maxSpeed, tailsScale,
        tailsIdleLeftTexture, tailsIdleRightTexture,
        tailsRunLeftTexture, tailsRunRightTexture, tailsJumpTexture,
        tailsPushLeftTexture, tailsPushRightTexture,
        tailsEdgeLeftTexture, tailsEdgeRightTexture,
        tailsFlyLeftTexture, tailsFlyRightTexture);

    mainIndex = 0;

    for (int i = 0; i < 3; ++i) {
        characters[i]->currentMaxSpeed = characters[i]->getBaseMaxSpeed();
    }
    characters[mainIndex]->currentMaxSpeed = characters[mainIndex]->getBaseMaxSpeed() * 1.2f;

    updateDrawOrder();
}

Game::~Game() {
    for (int i = 0; i < 3; ++i) delete characters[i];
    for (int i = 0; i < rows; ++i) delete[] mapData[i];
    delete[] mapData;
    for (int i = 0; i < enemyCount; ++i) delete enemies[i];
    for (int i = 0; i < projectileCount; ++i) delete projectiles[i];
}

void Game::checkCharacterRespawn(float cameraX, float cameraY) {
    for (int i = 0; i < 3; ++i) {
        float charX = characters[i]->getPosX();
        float charY = characters[i]->getPosY();
        bool isMain = (i == mainIndex);

        // Check if character falls below the map
        if (charY > levelHeight + 100.0f) {
            charX = isMain ? startX : characters[mainIndex]->getPosX() - 200.0f;
            charY = isMain ? startY : characters[mainIndex]->getPosY();
            characters[i]->setPosX(charX);
            characters[i]->setPosY(charY);
            characters[i]->setVelX(0.0f);
            characters[i]->setVelY(0.0f);
            characters[i]->setOnGround(true);
            offScreenTimers[i] = 0.0f;
            std::cout << "Character " << i << " respawned due to falling below map.\n";
            continue;
        }

        // Check if follower is stuck off-screen
        if (!isMain) {
            float screenLeft = cameraX;
            float screenRight = cameraX + SCREEN_X;
            float screenTop = cameraY;
            float screenBottom = cameraY + SCREEN_Y;

            bool isOnScreen = (charX >= screenLeft && charX <= screenRight &&
                charY >= screenTop && charY <= screenBottom);

            if (!isOnScreen) {
                offScreenTimers[i] += 1.0f / 60.0f;
                if (offScreenTimers[i] >= 4.0f) {
                    characters[i]->setPosX(characters[mainIndex]->getPosX() - 1200.0f);
                    characters[i]->setPosY(characters[mainIndex]->getPosY());
                    characters[i]->setVelX(0.0f);
                    characters[i]->setVelY(0.0f);
                    characters[i]->setOnGround(true);
                    offScreenTimers[i] = 0.0f;
                    std::cout << "Follower " << i << " respawned due to being stuck off-screen.\n";
                }
            }
            else {
                offScreenTimers[i] = 0.0f;
            }
        }
    }
}

void Game::respawnCharacter(int charIndex, bool isMain) {
    float charX = characters[charIndex]->getPosX();
    float charY = characters[charIndex]->getPosY();
    int col = static_cast<int>(charX / CELL_SIZE);
    int row = static_cast<int>(charY / CELL_SIZE);

    // Find nearest block (b or p) above
    float newX = charX;
    float newY = charY;
    bool found = false;

    for (int y = row - 1; y >= 0 && !found; --y) {
        for (int x = col - 2; x <= col + 2; ++x) {
            if (x >= 0 && x < cols && y >= 0 && y < rows) {
                if (mapData[y][x] == 'b' || mapData[y][x] == 'p') {
                    newX = x * CELL_SIZE + CELL_SIZE / 2.0f;
                    newY = y * CELL_SIZE - characters[charIndex]->getHeight() - 64.0f;
                    found = true;
                    break;
                }
            }
        }
    }

    if (!found) {
        newX = isMain ? startX : characters[mainIndex]->getPosX() - 200.0f;
        newY = isMain ? startY : characters[mainIndex]->getPosY();
    }

    characters[charIndex]->setPosX(newX);
    characters[charIndex]->setPosY(newY);
    characters[charIndex]->setVelX(0.0f);
    characters[charIndex]->setVelY(0.0f);
    characters[charIndex]->setOnGround(true);
}

void Game::checkHazardCollisions(int& sharedHP, float& invincibilityTimer) {
    if (invincibilityTimer > 0.0f) {
        invincibilityTimer -= 1.0f / 60.0f;
        return;
    }

    for (int i = 0; i < 3; ++i) {
        float charX = characters[i]->getPosX();
        float charY = characters[i]->getPosY();
        float charWidth = characters[i]->getWidth();
        float charHeight = characters[i]->getHeight();
        bool isMain = (i == mainIndex);

        int leftCol = static_cast<int>(charX / CELL_SIZE);
        int rightCol = static_cast<int>((charX + charWidth) / CELL_SIZE);
        int topRow = static_cast<int>(charY / CELL_SIZE);
        int botRow = static_cast<int>((charY + charHeight) / CELL_SIZE);

        for (int y = topRow; y <= botRow; ++y) {
            for (int x = leftCol; x <= rightCol; ++x) {
                if (x >= 0 && x < cols && y >= 0 && y < rows) {
                    char tile = level[y][x];
                    if (tile == 'u') {
                        if (isMain) {
                            std::cout << "Fall on spike\n";
                            sharedHP--;
                            invincibilityTimer = 1.0f;
                            std::cout << "Player HP: " << sharedHP << "\n";
                            if (sharedHP <= 0) {
                                std::cout << "Game Over!\n";
                            }
                        }
                        else {
                            std::cout << "Follower collides on spike\n";
                        }
                        respawnCharacter(i, isMain);
                        return;
                    }
                    else if (tile == 'x') {
                        if (isMain) {
                            std::cout << "Game Over\n";
                            sharedHP = 0;
                        }
                        else {
                            std::cout << "Follower falls in pit\n";
                        }
                        respawnCharacter(i, isMain);
                        return;
                    }
                }
            }
        }
    }
}

void Game::run() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_X, SCREEN_Y), "Sonic Platformer", sf::Style::Close);
    window.setFramerateLimit(60);
    Menu menu(font, backgroundMusic);
    int action = menu.run(window);

    if (action == Menu::EXIT) {
        window.close();
        return;
    }

    if (action == Menu::START_GAME) {
        int selectedLevel = menu.getSelectedLevel();
        initializeLevel(selectedLevel); // Load the selected level
    }
    else {
        return;
    }

    sf::Sprite wallSprite(wallTexture);
    const float gravity = 3.0f;
    const float terminalVel = 19.0f;
    const float jumpStrength = -26.0f;
    sf::Clock clock;
    int sharedHP = 3;
    float invincibilityTimer = 0.0f;

    while (window.isOpen()) {
        sf::Event ev;
        while (window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) window.close();
            if (ev.key.code == sf::Keyboard::Escape) {
                isPaused = !isPaused;
                if (isPaused) {
                    int pauseAction = pauseMenu.run(window);
                    if (pauseAction == 1) {
                        // Exit to main menu
                        window.close();
                        return;
                    }
                    else {
                        isPaused = false;
                    }
                }
            }

            else if (!isPaused && ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::A) {
                for (int idx = 0; idx < 3; ++idx) {
                    characters[idx]->currentMaxSpeed = characters[idx]->getBaseMaxSpeed();
                }
                mainIndex = (mainIndex + 1) % 3;
                characters[mainIndex]->currentMaxSpeed = characters[mainIndex]->getBaseMaxSpeed() * 1.2f;
                updateDrawOrder();
            }
        }

        float deltaTime = clock.restart().asSeconds();

        positionQueue.enqueue(characters[mainIndex]->getPosX(), characters[mainIndex]->getPosY());
        while (positionQueue.size > delayFrames) positionQueue.dequeue();

        characters[mainIndex]->update(gravity, terminalVel, jumpStrength, level, rows, cols, deltaTime);

        if (characters[mainIndex]->justJumped) {
            float xPos = characters[mainIndex]->getPosX();
            for (int i = 0; i < 3; ++i) {
                if (i != mainIndex) jumpQueues[i].enqueue(xPos);
            }
        }
        for (int i = 0; i < 3; ++i) {
            if (Knuckles* knuckles = dynamic_cast<Knuckles*>(characters[i])) {
                for (int j = 0; j < knuckles->numBlocksToBreak; ++j) {
                    int x = knuckles->blocksToBreak[j].x;
                    int y = knuckles->blocksToBreak[j].y;
                    if (x >= 0 && x < cols && y >= 0 && y < rows) {
                        mapData[y][x] = ' ';
                    }
                }
                knuckles->numBlocksToBreak = 0;
            }
        }

        for (int i = 0; i < 3; ++i) {
            if (i != mainIndex) {
                PositionQueue::Position targetPos = positionQueue.isEmpty() ?
                    PositionQueue::Position{ characters[mainIndex]->getPosX(), characters[mainIndex]->getPosY() } :
                    positionQueue.peek();
                characters[i]->updateFollower(gravity, terminalVel, jumpStrength, level, rows, cols, deltaTime,
                    targetPos.x, targetPos.y, jumpQueues[i]);
            }
        }

        for (int i = 0; i < 3; ++i) characters[i]->jumpedWhileStillThisFrame = false;

        updateEnemies(deltaTime, gravity, terminalVel);
        checkCollisions();
        checkHazardCollisions(sharedHP, invincibilityTimer);
        updateProjectiles(deltaTime);

        for (int i = 0; i < 3; ++i) {
            if (Tails* tailsPtr = dynamic_cast<Tails*>(characters[i])) {
                timerText.setString(tailsPtr->getTimerText());
                break;
            }
        }

        int elapsedSeconds = static_cast<int>(gameTimerClock.getElapsedTime().asSeconds());
        gameTimerText.setString("Time: " + std::to_string(elapsedSeconds) + "s");

        // Calculate camera position
        float centerX = characters[mainIndex]->getPosX();
        float centerY = characters[mainIndex]->getPosY();
        float idealCameraX = centerX - SCREEN_X / 2.0f;
        float idealCameraY = centerY - SCREEN_Y / 2.0f;

        float cameraX, cameraY;
        if (levelWidth < SCREEN_X) cameraX = -(SCREEN_X - levelWidth) / 2.0f;
        else cameraX = std::max(0.0f, std::min(idealCameraX, levelWidth - SCREEN_X));
        if (levelHeight < SCREEN_Y) cameraY = -(SCREEN_Y - levelHeight) / 2.0f;
        else cameraY = std::max(0.0f, std::min(idealCameraY, levelHeight - SCREEN_Y));

        // Check for character respawn
        checkCharacterRespawn(cameraX, cameraY);

        sf::RenderStates states;
        states.transform.translate(-cameraX, -cameraY);

        window.clear();
        window.draw(backgroundSprite);
        drawLevel(window, wallSprite, states);
        for (int i = 0; i < 3; ++i) characters[drawOrder[i]]->draw(window, states);
        drawEnemies(window, states);
        drawProjectiles(window, states);
        window.draw(timerText);
        window.draw(gameTimerText);
        window.display();
    }
}

void Game::initializeLevel(int level) {
    std::string mapFile = "Data/map_" + std::to_string(level) + ".txt";
    std::string enemiesFile = "Data/enemies_" + std::to_string(level) + ".txt";

    // Clean up existing map data
    if (mapData) {
        for (int i = 0; i < rows; ++i) delete[] mapData[i];
        delete[] mapData;
    }
    // Clean up existing enemies
    for (int i = 0; i < enemyCount; ++i) delete enemies[i];
    enemyCount = 0;

    loadMap(mapFile);
    if (!level || rows <= 0 || cols <= 0) {
        std::cout << "Failed to load valid level data for level " << level << ".\n";
        loadMap("Data/map.txt"); // Fallback to default map
        loadEnemies("Data/enemies.txt");
        backgroundSprite.setTexture(backgroundTexture[0]); // Fallback to level 1 background
        return;
    }
    loadEnemies(enemiesFile);

    // Set background based on level
    if (level >= 1 && level <= 3) {
        backgroundSprite.setTexture(backgroundTexture[level - 1]);
        backgroundSprite.setScale(1.4f, 1.4f);
    }
    else {
        backgroundSprite.setTexture(backgroundTexture[0]); // Default to level 1 background
        backgroundSprite.setScale(1.4f, 1.4f);
    }

    levelWidth = cols * CELL_SIZE;
    levelHeight = rows * CELL_SIZE;

    startX = CELL_SIZE * 1.0f;
    startY = CELL_SIZE * 11.1f;
    for (int i = 0; i < 3; ++i) {
        characters[i]->setPosX(startX);
        characters[i]->setPosY(startY);
        characters[i]->setVelX(0.0f);
        characters[i]->setVelY(0.0f);
        characters[i]->setOnGround(true);
    }
}

void Game::updateDrawOrder() {
    int idx = 0;
    for (int i = 0; i < 3; ++i) {
        if (i != mainIndex) drawOrder[idx++] = i;
    }
    drawOrder[2] = mainIndex;
}

void Game::loadMap(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cout << "MAP ERROR: Could not open " << filename << "\n";
        return;
    }

    in >> rows >> cols;
    if (rows <= 0 || cols <= 0) {
        std::cout << "MAP ERROR: Invalid dimensions (" << rows << "x" << cols << ")\n";
        in.close();
        return;
    }

    mapData = new char* [rows];
    for (int i = 0; i < rows; ++i) {
        mapData[i] = new char[cols];
        for (int j = 0; j < cols; ++j) mapData[i][j] = ' ';
    }

    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string line;
    int y = 0;
    while (y < rows && std::getline(in, line)) {
        if (line.empty()) continue;
        for (int x = 0; x < cols && x < line.length(); ++x) {
            mapData[y][x] = line[x];
        }
        y++;
    }

    in.close();
    level = const_cast<const char**>(mapData);
}

void Game::loadEnemies(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cout << "ENEMY ERROR: Could not open " << filename << "\n";
        return;
    }

    enemyCount = 0;
    char enemyType;
    float x, y;

    while (enemyCount < MAX_ENEMIES && in >> enemyType >> x >> y) {
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        float scale = 2.0f;
        switch (enemyType) {
        case 'B':
            enemies[enemyCount] = new BatBrain(
                x * CELL_SIZE, y * CELL_SIZE, scale,
                batBrainIdleLeftTexture, batBrainIdleRightTexture,
                batBrainMoveLeftTexture, batBrainMoveRightTexture);
            break;
        case 'E':
            enemies[enemyCount] = new BeeBot(
                x * CELL_SIZE, y * CELL_SIZE, scale,
                beeBotIdleLeftTexture, beeBotIdleRightTexture,
                beeBotMoveLeftTexture, beeBotMoveRightTexture);
            break;
        case 'M':
            enemies[enemyCount] = new Motobug(
                x * CELL_SIZE, y * CELL_SIZE, scale,
                motobugIdleLeftTexture, motobugIdleRightTexture,
                motobugMoveLeftTexture, motobugMoveRightTexture);
            break;
        case 'C':
            enemies[enemyCount] = new CrabMeat(
                x * CELL_SIZE, y * CELL_SIZE, scale,
                crabMeatIdleLeftTexture, crabMeatIdleRightTexture,
                crabMeatMoveLeftTexture, crabMeatMoveRightTexture);
            break;
        case 'S':
            enemies[enemyCount] = new EggStinger(
                x * CELL_SIZE, y * CELL_SIZE, scale,
                eggStingerIdleLeftTexture, eggStingerIdleRightTexture,
                eggStingerMoveLeftTexture, eggStingerMoveRightTexture);
            break;
        default:
            continue;
        }
        enemyCount++;
    }

    in.close();
    std::cout << "Loaded " << enemyCount << " enemies.\n";
}

void Game::updateEnemies(float deltaTime, float gravity, float terminalVelocity) {
    float playerX = characters[mainIndex]->getPosX();
    float playerY = characters[mainIndex]->getPosY();
    bool playerInBallForm = (characters[mainIndex]->getCurrentState() == Character::Jumping);

    for (int i = 0; i < enemyCount; ++i) {
        if (enemies[i] && enemies[i]->isAlive()) {
            enemies[i]->update(gravity, terminalVelocity, level, rows, cols, deltaTime,
                playerX, playerY, playerInBallForm);
        }
    }
}

void Game::drawEnemies(sf::RenderWindow& window, const sf::RenderStates& states) {
    for (int i = 0; i < enemyCount; ++i) {
        if (enemies[i] && enemies[i]->isAlive()) {
            enemies[i]->draw(window, states);
        }
    }
}

void Game::updateProjectiles(float deltaTime) {
    // Update existing projectiles
    for (int i = 0; i < projectileCount; ++i) {
        if (projectiles[i] && projectiles[i]->isAlive()) {
            projectiles[i]->update(deltaTime);
        }
    }

    // Remove dead projectiles
    int writeIndex = 0;
    for (int i = 0; i < projectileCount; ++i) {
        if (projectiles[i] && projectiles[i]->isAlive()) {
            projectiles[writeIndex] = projectiles[i];
            writeIndex++;
        }
        else {
            delete projectiles[i];
            projectiles[i] = nullptr;
        }
    }
    projectileCount = writeIndex;

    // Check projectile collisions
    static float invincibilityTimer = 0.0f;
    static int sharedHP = 3;
    if (invincibilityTimer > 0.0f) {
        invincibilityTimer -= deltaTime;
    }

    for (int i = 0; i < projectileCount; ++i) {
        if (!projectiles[i] || !projectiles[i]->isAlive()) continue;
        float projX = projectiles[i]->getPosX();
        float projY = projectiles[i]->getPosY();
        float projWidth = projectiles[i]->getWidth();
        float projHeight = projectiles[i]->getHeight();

        float charX = characters[mainIndex]->getPosX();
        float charY = characters[mainIndex]->getPosY();
        float charWidth = characters[mainIndex]->getWidth();
        float charHeight = characters[mainIndex]->getHeight();

        if (charX < projX + projWidth &&
            charX + charWidth > projX &&
            charY < projY + projHeight &&
            charY + charHeight > projY &&
            invincibilityTimer <= 0.0f) {
            sharedHP--;
            invincibilityTimer = 1.0f;
            projectiles[i]->setActive(false);
            std::cout << "Player hit by projectile! HP: " << sharedHP << "\n";
            if (sharedHP <= 0) {
                std::cout << "Game Over!\n";
            }
        }
    }
}

void Game::drawProjectiles(sf::RenderWindow& window, const sf::RenderStates& states) {
    for (int i = 0; i < projectileCount; ++i) {
        if (projectiles[i] && projectiles[i]->isAlive()) {
            projectiles[i]->draw(window, states);
        }
    }
}

void Game::checkCollisions() {
    static float invincibilityTimer = 0.0f;
    static int sharedHP = 3;

    if (invincibilityTimer > 0.0f) {
        invincibilityTimer -= 1.0f / 60.0f;
    }

    for (int i = 0; i < 3; ++i) {
        float charX = characters[i]->getPosX();
        float charY = characters[i]->getPosY();
        float charWidth = characters[i]->getWidth();
        float charHeight = characters[i]->getHeight();
        bool isMain = (i == mainIndex);
        bool inBallForm = (characters[i]->getCurrentState() == Character::Jumping);

        for (int j = 0; j < enemyCount; ++j) {
            if (!enemies[j] || !enemies[j]->isAlive()) continue;

            float enemyX = enemies[j]->getPosX();
            float enemyY = enemies[j]->getPosY();
            float enemyWidth = enemies[j]->getEnemyWidth();
            float enemyHeight = enemies[j]->getEnemyHeight();

            bool collision = (charX < enemyX + enemyWidth &&
                charX + charWidth > enemyX &&
                charY < enemyY + enemyHeight &&
                charY + charHeight > enemyY);

            if (collision) {
                if (inBallForm) {
                    if (enemies[j]->takeDamage(1, true)) {
                        std::cout << "Enemy defeated!\n";
                    }
                }
                else if (isMain && invincibilityTimer <= 0.0f) {
                    sharedHP--;
                    invincibilityTimer = 10.0f;
                    std::cout << "Player HP: " << sharedHP << "\n";
                    if (sharedHP <= 0) {
                        std::cout << "Game Over!\n";
                    }
                }
                else if (!isMain) {
                    std::cout << "Follower hit!\n";
                }
            }
        }
    }
}

void Game::drawLevel(sf::RenderWindow& window, sf::Sprite& wallSprite, const sf::RenderStates& states) {
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            char c = level[y][x];
            if (c == 'w' || c == 'f' || c == 'r') {
                wallSprite.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                window.draw(wallSprite, states);
            }
            else if (c == 'b') {
                blockSprite.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                window.draw(blockSprite, states);
            }
            else if (c == 'p') {
                platformSprite.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                window.draw(platformSprite, states);
            }
            else if (c == 'c') {
                crystalSprite.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                window.draw(crystalSprite, states);
            }
            else if (c == 'l') {
                block3Sprite.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                window.draw(block3Sprite, states);
            }
            else if (c == 'u') {
                spikeSprite.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                window.draw(spikeSprite, states);
            }
            else if (c == 'x') {
                pitSprite.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                window.draw(pitSprite, states);
            }
            else if (c == 'g') {
                grassSprite.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                window.draw(grassSprite, states);
            }
            else if (c == 'N') {
                block4Sprite.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                window.draw(block4Sprite, states);
            }
        }
    }
}