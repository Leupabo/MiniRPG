#include "game.h"
#include <iostream>
#include <unistd.h>
#include <nlohmann/json.hpp>
#include <filesystem>
#include <fstream>

Game::Game() : player(INITIAL_PLAYER_X, INITIAL_PLAYER_Y), gameRunning(false){
    // Initialisation du temps pour le calcul du deltaTime
    lastUpdateTime = std::chrono::steady_clock::now();
}

Game::~Game() {
}

bool Game::initialize() {
    // Chargement de la carte initiale
    if (!loadMap(INITIAL_MAP_ID)) {
        std::cerr << "Erreur lors du chargement de la carte initiale" << std::endl;
        return false;
    }

    // Positionnement initial du joueur
    player.setPosition(INITIAL_PLAYER_X, INITIAL_PLAYER_Y);

    // Création des ennemis pour la carte initiale
    enemyManager.createEnemies(DEFAULT_ENEMY_COUNT, currentMap, player);

    // Démarrage du jeu
    gameRunning = true;
    return true;
}

void Game::cleanup() {
    // Nettoyage des ressources du gestionnaire d'ennemis
    enemyManager.cleanup();
}

void Game::calculateDeltaTime() {
    // Calcul du temps écoulé depuis la dernière mise à jour
    auto currentTime = std::chrono::steady_clock::now();
    deltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - lastUpdateTime);
    lastUpdateTime = currentTime;
}

void Game::update() {
    // Mise à jour du temps écoulé
    calculateDeltaTime();

    // Mise à jour du joueur
    player.update(currentMap, deltaTime);
    
    // Mise à jour et gestion des flèches
    arrowManager.updateArrows(currentMap, deltaTime);
    arrowManager.checkArrowCollisions(enemyManager.getEnemiesModif());
    arrowManager.cleanupArrows();

    // Mise à jour et gestion des bombes
    bombManager.updateBombs(currentMap, deltaTime);
    bombManager.checkBombExplosions(enemyManager.getEnemiesModif(), player);
    bombManager.cleanupBombs();

    // Mise à jour des ennemis et des objets
    enemyManager.updateEnemies(currentMap, player, itemManager, deltaTime);
    itemManager.update(currentMap, deltaTime);
    itemManager.checkCollisions(player);

    // Vérification des attaques des ennemis contre le joueur
    for (auto& enemy : enemyManager.getEnemiesModif()) {
        enemy.updateAttackCooldown(deltaTime);
        // Si l'ennemi peut attaquer et est sur la même case que le joueur
        if (enemy.canAttack() && player.getX() == enemy.getX() && player.getY() == enemy.getY()) {
            player.setDmg(ENEMY_DAMAGE);
            enemy.resetAttackCooldown();
        }
    }
}

bool Game::handleInput(char input) {
    // Gestion des déplacements du joueur
    bool playerMoved = player.handleInput(input, currentMap);

    // Tir d'une flèche avec la touche 'b'
    if (input == 'b') {
        Arrow* newArrow = player.shootArrow();
        if (newArrow) {
            arrowManager.addArrow(newArrow);
        }
    }

    // Placement d'une bombe avec la touche 'p'
    if (input == 'p') {
        Bomb* newBomb = player.placeBomb();
        if (newBomb) {
            bombManager.addBomb(newBomb);
        }
    }

    // Attaque au corps à corps avec la touche 'o'
    if (input == 'o') {
        handlePlayerAttack();
    }

    // Vérification si le joueur est sur un portail après déplacement
    if (playerMoved && currentMap.isPortal(player.getX(), player.getY())) {
        const Portal* portal = currentMap.getPortalAt(player.getX(), player.getY());
        handlePortalTransition(portal);
    }

    return playerMoved;
}

void Game::handlePlayerAttack() {
    // Exécution de l'attaque du joueur contre les ennemis
    bool hit = player.performAttack(enemyManager.getEnemiesModif());
}

bool Game::loadMap(int mapId) {
    // Sauvegarde des ennemis de la carte actuelle avant de changer
    int currentMapId = currentMap.getId();
    if (currentMapId > 0) {
        enemyManager.saveEnemies(currentMapId);
    }

    // Nettoyage des objets de la carte actuelle
    bombManager.clearAllBombs();
    arrowManager.clearAllArrows();
    itemManager.clearAllItems();

    // Chargement de la nouvelle carte
    if (!currentMap.loadFromId(mapId)) {
        std::cerr << "Erreur lors du chargement de la carte " << mapId << std::endl;
        return false;
    }

    // Chargement ou création des ennemis pour la nouvelle carte
    if (enemyManager.enemiesFileExists(mapId)) {
        enemyManager.loadEnemies(mapId, currentMap, player);
    } else {
        enemyManager.createEnemies(DEFAULT_ENEMY_COUNT, currentMap, player);
    }
    return true;
}

void Game::setRunning(bool running) {
    // Définit l'état d'exécution du jeu
    gameRunning = running;
}

void Game::handlePortalTransition(const Portal* portal) {
    // Gestion de la transition entre les cartes via un portail
    if (portal) {
        int targetMapId = portal->targetMapId;
        int targetX = portal->targetX;
        int targetY = portal->targetY;

        // Chargement de la carte cible et positionnement du joueur
        if (loadMap(targetMapId)) {
            player.setPosition(targetX, targetY);
        }
    }
}

void Game::displayGameInfo() const {
    // Affichage des informations de débogage du jeu
    std::cout << "=== Informations du jeu ===" << std::endl;
    std::cout << "Carte actuelle: ID " << currentMap.getId() << std::endl;
    std::cout << "Dimensions de la carte: " << currentMap.getWidth() << "x" << currentMap.getHeight() << std::endl;
    std::cout << std::endl;

    // Informations sur le joueur
    std::cout << "--- Joueur ---" << std::endl;
    std::cout << "Position: (" << player.getX() << ", " << player.getY() << ")" << std::endl;
    std::cout << "Sante: " << player.gethealth() << " " << std::endl;
    std::cout << "Cooldown d'attaque: " << player.getAttackCooldown() << " " << std::endl;
    std::cout << "Cooldown de l'arc: " << player.getBowCooldown() << " " << std::endl;
    std::cout << "Cooldown des bombes: " << player.getBombCooldown() << " " << " " << std::endl;
    std::cout << std::endl;

    // Informations sur les ennemis
    std::cout << "--- Ennemis ---" << std::endl;
    std::cout << "Nombre d'ennemis: " << enemyManager.getEnemies().size() << std::endl;
    std::cout << std::endl;
    std::cout << "=== Fin des informations ===" << std::endl;
}
