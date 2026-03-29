#include "player.h"
#include "enemy.h"
#include "arrow.h"
#include <iostream>
#include <cassert>

Player::Player(int startX, int startY)
    : Entity(startX, startY, '@', 10, 10), cooldownSword(0), cooldownBow(0), dir(DOWN), attackP(false){
    // Constructeur avec position initiale, initialise le joueur avec le symbole '@', 10 points de vie et 10 de dégâts
}

Player::Player(){
    // Constructeur par défaut
}

Player::~Player() {
    // Destructeur
}

void Player::update(Map& map, std::chrono::duration<double> elapsedTime) {
    // Mise à jour des cooldowns en fonction du temps écoulé
    cooldownSword = std::max(0.0, cooldownSword - elapsedTime.count());
    cooldownBow = std::max(0.0, cooldownBow - elapsedTime.count());
    bombCooldown = std::max(0.0, bombCooldown - elapsedTime.count());
}

bool Player::handleInput(char input, Map& map) {
    // Gestion des entrées clavier pour le déplacement et l'attaque
    int dx = 0, dy = 0;

    // Détermination de la direction en fonction de la touche pressée
    switch (input) {
        case 'z': dy = -1; dir = UP; break;     // Haut
        case 's': dy = 1; dir = DOWN; break;    // Bas
        case 'q': dx = -1; dir = LEFT; break;   // Gauche
        case 'd': dx = 1; dir = RIGHT; break;   // Droite
        case 'o': attackP = true; break;        // Attaque
        default: return false;                  // Touche non reconnue
    }

    bool moved;
    moved = move(dx, dy, map);  // Tentative de déplacement

    // Vérification si le joueur est sur un portail après déplacement
    if (moved && map.isPortal(x, y)) {
        return true;  // Indique qu'un portail a été activé
    }
    attackP = false;  // Réinitialisation de l'état d'attaque

    return moved;  // Indique si le joueur s'est déplacé
}

bool Player::canAttack() const {
    // Vérifie si le joueur peut attaquer (cooldown terminé)
    return cooldownSword == 0;
}

void Player::resetAttackCooldown() {
    // Réinitialise le cooldown de l'épée après une attaque
    cooldownSword = COOLDOWN_SWORD_DURATION;
}

bool Player::performAttack(std::vector<Enemy>& enemies) {
    // Effectue une attaque contre les ennemis adjacents
    if (!canAttack()) return false;  // Vérifie si l'attaque est possible

    // Calcul de la position de l'attaque en fonction de la direction
    int attackX = x;
    int attackY = y;

    switch (dir) {
        case UP:    attackY--; break;  // Attaque vers le haut
        case DOWN:  attackY++; break;  // Attaque vers le bas
        case LEFT:  attackX--; break;  // Attaque vers la gauche
        case RIGHT: attackX++; break;  // Attaque vers la droite
    }

    // Recherche d'un ennemi à la position d'attaque
    bool hit = false;
    for (auto& enemy : enemies) {
        if (enemy.getX() == attackX && enemy.getY() == attackY) {
            enemy.setDmg(SWORD_DAMAGE);  // Inflige des dégâts à l'ennemi
            hit = true;
            break;
        }
    }
    resetAttackCooldown();  // Réinitialise le cooldown après l'attaque

    return hit;  // Indique si un ennemi a été touché
}

bool Player::canShootArrow() const {
    // Vérifie si le joueur peut tirer une flèche (cooldown terminé)
    return cooldownBow <= 0;
}

void Player::resetBowCooldown() {
    // Réinitialise le cooldown de l'arc après un tir
    cooldownBow = COOLDOWN_BOW_DURATION;
}

Arrow* Player::shootArrow() {
    // Crée et renvoie une nouvelle flèche si possible
    if (canShootArrow()) {
        resetBowCooldown();  // Réinitialise le cooldown
        return new Arrow(x, y, dir, ARROW_DAMAGE, 10.0);  // Crée une flèche avec dégâts et durée de vie
    }
    return nullptr;  // Retourne nullptr si le tir n'est pas possible
}

bool Player::canPlaceBomb() const {
    // Vérifie si le joueur peut placer une bombe (cooldown terminé)
    return bombCooldown <= 0;
}

void Player::resetBombCooldown() {
    // Réinitialise le cooldown des bombes après placement
    bombCooldown = BOMB_COOLDOWN_DURATION;
}

Bomb* Player::placeBomb() {
    // Crée et renvoie une nouvelle bombe si possible
    if (canPlaceBomb()) {
        resetBombCooldown();  // Réinitialise le cooldown
        return new Bomb(x, y, BOMB_TIMER, BOMB_RADIUS, BOMB_DAMAGE);  // Crée une bombe avec timer, rayon et dégâts
    }
    return nullptr;  // Retourne nullptr si le placement n'est pas possible
}


void testCreatePlayer() {
    // Test de création d'un joueur
    Player player(5, 5);
    std::cout << "Test de creation du joueur : OK" << std::endl;
}

void testPlayerPosition() {
    // Test de la position initiale du joueur
    Player player(5, 5);
    assert(player.getX() == 5 && player.getY() == 5 && "Position initiale du joueur incorrecte");
    std::cout << "Test de la position initiale du joueur : OK" << std::endl;
}

void testPlayerHealth() {
    // Test de la santé initiale du joueur
    Player player(5, 5);
    assert(player.gethealth() > 0 && "La sante du joueur devrait etre positive");
    std::cout << "Test de la sante initiale du joueur : OK" << std::endl;
}

void testPlayerMovement() {
    // Test du déplacement du joueur
    Map map("data/maps/test_map.txt");
    Player player(5, 5);
    player.move(1, 0, map);  // Déplacement vers la droite
    assert(player.getX() == 6 && player.getY() == 5 && "Le joueur devrait s'etre deplace vers la droite");
    std::cout << "Test du mouvement du joueur : OK" << std::endl;
}

void testPlayerDamage() {
    // Test des dégâts subis par le joueur
    Player player(5, 5);
    int initialHealth = player.gethealth();
    player.setDmg(2);  // Inflige 2 points de dégâts
    assert(player.gethealth() == initialHealth - 2 && "La sante du joueur devrait avoir diminue de 2");
    std::cout << "Test des degats subis par le joueur : OK" << std::endl;
}

void testPlayerSymbol() {
    // Test du symbole du joueur
    Player player(5, 5);
    assert(player.getSymbol() == '@' && "Le symbole du joueur devrait etre '@'");
    std::cout << "Test du symbole du joueur : OK" << std::endl;
}

void testPlayerAttackCooldown() {
    // Test du cooldown d'attaque à l'épée
    Player player(5, 5);
    Map map("data/maps/test_map.txt");
    assert(player.canAttack() && "Le joueur devrait pouvoir attaquer initialement");
    player.resetAttackCooldown();  // Déclenche le cooldown
    assert(!player.canAttack() && "Le joueur ne devrait pas pouvoir attaquer juste après avoir attaqué");
    player.update(map, std::chrono::duration<double>(player.getAttackCooldown() + 0.1));  // Avance le temps au-delà du cooldown
    assert(player.canAttack() && "Le joueur devrait pouvoir attaquer après le cooldown");
    std::cout << "Test du cooldown d'attaque du joueur : OK" << std::endl;
}

void testPlayerBowCooldown() {
    // Test du cooldown de l'arc
    Player player(5, 5);
    Map map("data/maps/test_map.txt");
    assert(player.canShootArrow() && "Le joueur devrait pouvoir tirer une flèche initialement");
    player.resetBowCooldown();  // Déclenche le cooldown
    assert(!player.canShootArrow() && "Le joueur ne devrait pas pouvoir tirer une flèche juste après en avoir tiré une");
    player.update(map, std::chrono::duration<double>(player.getBowCooldown() + 0.1));  // Avance le temps au-delà du cooldown
    assert(player.canShootArrow() && "Le joueur devrait pouvoir tirer une flèche après le cooldown");
    std::cout << "Test du cooldown de l'arc du joueur : OK" << std::endl;
}

void testPlayerBombCooldown() {
    // Test du cooldown des bombes
    Player player(5, 5);
    Map map("data/maps/test_map.txt");
    assert(player.canPlaceBomb() && "Le joueur devrait pouvoir placer une bombe initialement");
    player.resetBombCooldown();  // Déclenche le cooldown
    assert(!player.canPlaceBomb() && "Le joueur ne devrait pas pouvoir placer une bombe juste après en avoir placé une");
    player.update(map, std::chrono::duration<double>(player.getBombCooldown() + 0.1));  // Avance le temps au-delà du cooldown
    assert(player.canPlaceBomb() && "Le joueur devrait pouvoir placer une bombe après le cooldown");
    std::cout << "Test du cooldown des bombes du joueur : OK" << std::endl;
}

int Player::regressionTest(){
    try {
        // Exécution de tous les tests unitaires pour la classe Player
        testCreatePlayer();
        testPlayerPosition();
        testPlayerHealth();
        testPlayerMovement();
        testPlayerDamage();
        testPlayerSymbol();
        testPlayerAttackCooldown();
        testPlayerBowCooldown();
        testPlayerBombCooldown();

        std::cout << "Tous les tests pour la classe Player ont reussi !" << std::endl;

    } catch (const std::exception& e) {
        // Capture et affichage de toute exception qui pourrait se produire
        std::cerr << "Une exception s'est produite : " << e.what() << std::endl;
        return 1;  // Indique l'échec
    }
    return 0;  // Indique le succès
}