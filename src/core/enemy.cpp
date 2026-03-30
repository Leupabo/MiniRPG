#include "enemy.h"
#include <cstdlib>
#include <cmath>
#include <nlohmann/json.hpp>
#include <cassert>
#include <iostream>

Enemy::Enemy(int startX, int startY, double speed)
    : Entity(startX, startY, 'E', 3, 3), targetX(-1), targetY(-1), hasTarget(false), attackCooldown(0), moveSpeed(speed) {
    // Vérifications des paramètres d'entrée
    assert(startX >= 0 && "La position X de départ doit être positive ou nulle");
    assert(startY >= 0 && "La position Y de départ doit être positive ou nulle");
    assert(speed > 0 && "La vitesse doit être positive");
    normalSymbol = 'E';
    alertSymbol = 'X';
    dir = DOWN;
    assert(normalSymbol != alertSymbol && "Les symboles normal et d'alerte doivent être différents");
}

Enemy::Enemy() : Entity(), targetX(-1), targetY(-1), hasTarget(false), attackCooldown(0), moveSpeed(1.0) {
}

Enemy::~Enemy() {
}

Enemy::Enemy(const nlohmann::json& j)
    : Entity(j["x"].get<int>(), j["y"].get<int>(), j["symbol"].get<char>(), j["health"].get<int>(), j["maxHealth"].get<int>()),
      targetX(j["targetX"].get<int>()),
      targetY(j["targetY"].get<int>()),
      hasTarget(j["hasTarget"].get<bool>()),
      moveSpeed(j["moveSpeed"].get<double>()) {
    // Vérification des champs JSON requis
    assert(j.contains("normalSymbol") && j.contains("alertSymbol") && "JSON doit contenir normalSymbol et alertSymbol");
    normalSymbol = j["normalSymbol"].get<char>();
    alertSymbol = j["alertSymbol"].get<char>();
    dir = j["dir"];
    assert(normalSymbol != alertSymbol && "Le symboles normal et d'alerte doivent être différents");
}

nlohmann::json Enemy::toJson() const {
    // Sérialisation de l'ennemi en JSON
    nlohmann::json j;
    j["x"] = getX();
    j["y"] = getY();
    j["symbol"] = getSymbol();
    j["health"] = gethealth();
    j["maxHealth"] = getMaxHealth();
    j["targetX"] = targetX;
    j["targetY"] = targetY;
    j["hasTarget"] = hasTarget;
    j["normalSymbol"] = normalSymbol;
    j["alertSymbol"] = alertSymbol;
    j["dir"] = dir;
    j["moveSpeed"] = moveSpeed;
    return j;
}

void Enemy::setTarget(int x, int y) {
    assert(x >= 0 && y >= 0 && "Les coordonnées de la cible doivent être positives ou nulles");
    targetX = x;
    targetY = y;
    hasTarget = true;
    symbol = alertSymbol;  // Changer le symbole pour indiquer que l'ennemi est en alerte
    assert(symbol == alertSymbol && "Le symbole doit être changé en symbole d'alerte");
}

void Enemy::clearTarget() {
    hasTarget = false;
    symbol = normalSymbol;  // Revenir au symbole normal
    assert(symbol == normalSymbol && "Le symbole doit revenir au symbole normal");
}

void Enemy::update(Map& map, std::chrono::duration<double> elapsedTime) {
    assert(map.isWalkable(x, y) && "L'ennemi doit être sur une case praticable");

    if (hasTarget) {
        // Si l'ennemi a une cible, essayer de trouver un chemin vers elle
        auto path = findPath(map, targetX, targetY);
        
        if (!path.empty()) {
            // Suivre le chemin trouvé
            int nextX = path[0].first;
            int nextY = path[0].second;
            
            // Accumuler le déplacement en fonction de la vitesse et du temps écoulé
            accumulatedDx += (nextX - x) * moveSpeed * elapsedTime.count();
            accumulatedDy += (nextY - y) * moveSpeed * elapsedTime.count();
            
            // Convertir les déplacements accumulés en déplacements entiers
            int dx = static_cast<int>(accumulatedDx);
            int dy = static_cast<int>(accumulatedDy);
            
            if (dx != 0 || dy != 0) {
                if (move(dx, dy, map)) {
                    // Soustraire les déplacements effectués
                    accumulatedDx -= dx;
                    accumulatedDy -= dy;
                    
                    // Mettre à jour la direction de l'ennemi
                    if (dx > 0) dir = RIGHT;
                    else if (dx < 0) dir = LEFT;
                    else if (dy > 0) dir = DOWN;
                    else if (dy < 0) dir = UP;
                } else {
                    // Si le mouvement a échoué, réinitialiser les accumulations
                    accumulatedDx = 0.0;
                    accumulatedDy = 0.0;
                    moveRandomly(map, elapsedTime);
                }
            }
        } else {
            // Si aucun chemin n'est trouvé, se déplacer aléatoirement
            moveRandomly(map, elapsedTime);
        }
    } else {
        // Si l'ennemi n'a pas de cible, se déplacer aléatoirement
        moveRandomly(map, elapsedTime);
    }
    updateAttackCooldown(elapsedTime);
}

void Enemy::moveRandomly(Map& map, std::chrono::duration<double> elapsedTime) {
    // Choisir une direction aléatoire (0-3 pour les directions, 4 pour rester immobile)
    int direction = rand() % 5;
    double randomMoveSpeed = 2.0;
    
    // Accumuler le déplacement en fonction de la direction choisie
    switch (direction) {
        case 0: accumulatedDx += randomMoveSpeed * elapsedTime.count(); break;  // Droite
        case 1: accumulatedDx -= randomMoveSpeed * elapsedTime.count(); break;  // Gauche
        case 2: accumulatedDy += randomMoveSpeed * elapsedTime.count(); break;  // Bas
        case 3: accumulatedDy -= randomMoveSpeed * elapsedTime.count(); break;  // Haut
        default: break;  // Immobile
    }

    // Convertir les déplacements accumulés en déplacements entiers
    int dx = static_cast<int>(accumulatedDx);
    int dy = static_cast<int>(accumulatedDy);

    if (dx != 0 || dy != 0) {
        if (move(dx, dy, map)) {
            // Soustraire les déplacements effectués
            accumulatedDx -= dx;
            accumulatedDy -= dy;
            
            // Mettre à jour la direction de l'ennemi
            if (dx > 0) dir = RIGHT;
            else if (dx < 0) dir = LEFT;
            else if (dy > 0) dir = DOWN;
            else if (dy < 0) dir = UP;
        } else {
            // Si le mouvement a échoué, réinitialiser les accumulations
            accumulatedDx = 0.0;
            accumulatedDy = 0.0;
        }
    }
}

void Enemy::updateAttackCooldown(std::chrono::duration<double> elapsedTime) {
    // Réduire le cooldown d'attaque en fonction du temps écoulé
    if (attackCooldown > 0) {
        attackCooldown -= elapsedTime.count();
        if (attackCooldown < 0) attackCooldown = 0;
    }
    assert(attackCooldown >= 0 && "Le cooldown d'attaque ne doit pas être négatif");
}

bool Enemy::canAttack() const {
    return attackCooldown <= 0;
}

void Enemy::resetAttackCooldown() {
    attackCooldown = ATTACK_COOLDOWN_DURATION;
    assert(attackCooldown == ATTACK_COOLDOWN_DURATION && "Le cooldown d'attaque doit être réinitialisé correctement");
}

std::vector<std::pair<int, int>> Enemy::findPath(const Map& map, int targetX, int targetY) {
    // Algorithme de recherche de chemin BFS (Breadth-First Search)
    std::queue<std::pair<int, int>> queue;
    std::vector<std::vector<bool>> visited(map.getHeight(), std::vector<bool>(map.getWidth(), false));
    std::vector<std::vector<std::pair<int, int>>> parent(map.getHeight(), std::vector<std::pair<int, int>>(map.getWidth(), {-1, -1}));

    // Commencer à la position actuelle de l'ennemi
    queue.push({x, y});
    visited[y][x] = true;

    while (!queue.empty()) {
        auto [currentX, currentY] = queue.front();
        queue.pop();

        // Si on a atteint la cible, reconstruire le chemin
        if (currentX == targetX && currentY == targetY) {
            std::vector<std::pair<int, int>> path;
            while (currentX != x || currentY != y) {
                path.push_back({currentX, currentY});
                auto [parentX, parentY] = parent[currentY][currentX];
                currentX = parentX;
                currentY = parentY;
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        // Explorer les 4 directions adjacentes (haut, bas, gauche, droite)
        const int dx[] = {-1, 1, 0, 0};
        const int dy[] = {0, 0, -1, 1};
        for (int i = 0; i < 4; ++i) {
            int newX = currentX + dx[i];
            int newY = currentY + dy[i];

            // Vérifier si la nouvelle position est valide et non visitée
            if (map.isWalkable(newX, newY) && map.getTile(newX, newY) != TILE_WALL && !visited[newY][newX]) {
                queue.push({newX, newY});
                visited[newY][newX] = true;
                parent[newY][newX] = {currentX, currentY};
            }
        }
    }

    // Aucun chemin trouvé
    return {};
}

Item* Enemy::dropItem() const {
    // 40% de chance de lâcher un cœur
    if (rand() % 100 < 40) {
        Item* droppedItem = new Item(getX(), getY(), ItemType::HEART);
        assert(droppedItem != nullptr && "L'item droppé ne doit pas être null");
        return droppedItem;
    }
    return nullptr;
}

// Fonctions de test pour la régression

void testCreateEnemy() {
    Enemy enemy(5, 5, 1.0);
    std::cout << "Test de creation de l'ennemi : OK" << std::endl;
}

void testEnemyPosition() {
    Enemy enemy(5, 5, 1.0);
    assert(enemy.getX() == 5 && enemy.getY() == 5 && "Position initiale de l'ennemi incorrecte");
    std::cout << "Test de la position initiale de l'ennemi : OK" << std::endl;
}

void testEnemyHealth() {
    Enemy enemy(5, 5, 1.0);
    assert(enemy.gethealth() > 0 && "La sante de l'ennemi devrait etre positive");
    std::cout << "Test de la sante initiale de l'ennemi : OK" << std::endl;
}

void testEnemyMovement() {
    Map map("data/maps/test_map.txt");
    Enemy enemy(5, 5, 1.0);
    int initialX = enemy.getX();
    int initialY = enemy.getY();
    enemy.update(map, std::chrono::duration<double>(1.0));
    assert((enemy.getX() != initialX || enemy.getY() != initialY) && "L'ennemi devrait avoir bouge");
    std::cout << "Test du mouvement de l'ennemi : OK" << std::endl;
}

void testEnemyDamage() {
    Enemy enemy(5, 5, 1.0);
    int initialHealth = enemy.gethealth();
    enemy.setDmg(2);
    assert(enemy.gethealth() == initialHealth - 2 && "La sante de l'ennemi devrait avoir diminue de 2");
    std::cout << "Test des degats subis par l'ennemi : OK" << std::endl;
}

void testEnemySymbol() {
    Enemy enemy(5, 5, 1.0);
    assert(enemy.getSymbol() == 'E' && "Le symbole de l'ennemi devrait etre 'E'");
    std::cout << "Test du symbole de l'ennemi : OK" << std::endl;
}

int Enemy::regressionTest() {
    try {
        testCreateEnemy();
        testEnemyPosition();
        testEnemyHealth();
        testEnemyMovement();
        testEnemyDamage();
        testEnemySymbol();

        std::cout << "Tous les tests pour la classe Enemy ont reussi !" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Une exception s'est produite : " << e.what() << std::endl;
        return 1;
    }
    return 0;
}