#include "bomb.h"
#include <cassert>
#include <iostream>

Bomb::Bomb(int startX, int startY, double timer, int radius, int dmg)
    : Entity(startX, startY, 'O', 1, 1), timer(timer), explosionRadius(radius), damage(dmg), active(true), exploding(false) {
    // Vérifications des paramètres d'entrée
    assert(startX >= 0 && "La position X de départ doit être positive ou nulle");
    assert(startY >= 0 && "La position Y de départ doit être positive ou nulle");
    assert(timer > 0 && "Le timer doit être positif");
    assert(radius > 0 && "Le rayon d'explosion doit être positif");
    assert(dmg > 0 && "Les dégâts doivent être positifs");
}

Bomb::Bomb() : Entity(), timer(0), explosionRadius(0), damage(0), active(false), exploding(false) {
}

Bomb::~Bomb() {}

void Bomb::update(Map& map, std::chrono::duration<double> elapsedTime) {
    assert(active || exploding && "Une bombe inactive et non explosante ne devrait pas être mise à jour");
    
    if (active && !exploding) {
        // Décrémenter le timer de la bombe
        timer -= elapsedTime.count();
        
        // S'assurer que le timer ne devient pas négatif
        if (timer < 0) {
            timer = 0;
        }
        
        // Si le timer atteint zéro, déclencher l'explosion
        if (timer <= 0) {
            explode(map);
        }
    } else if (exploding) {
        // Terminer l'explosion après une mise à jour
        active = false;
        exploding = false;
    }
}

void Bomb::explode(Map& map) {
    assert(active && !exploding && "Une bombe ne peut exploser que si elle est active et pas déjà en train d'exploser");
    
    // Marquer la bombe comme explosant et désactivée
    exploding = true;
    active = false;
    timer = 0;
}

bool Bomb::hasFinishedExploding() const {
    // Une bombe a fini d'exploser si elle n'est ni active ni en train d'exploser
    return !active && !exploding;
}

void testCreateBomb() {
    Bomb bomb(5, 5, 1.0, 2, 3);
    std::cout << "Test de creation de la bombe : OK" << std::endl;
}

void testBombPosition() {
    Bomb bomb(5, 5, 1.0, 2, 3);
    assert(bomb.getX() == 5 && bomb.getY() == 5 && "Position de la bombe incorrecte");
    std::cout << "Test de la position de la bombe : OK" << std::endl;
}

void testBombTimer() {
    Bomb bomb(5, 5, 1.0, 2, 3);
    assert(bomb.getTimer() == 1.0 && "Timer initial de la bombe incorrect");
    std::cout << "Test du timer initial de la bombe : OK" << std::endl;
}

void testBombUpdate() {
    Map map("data/maps/test_map.txt");
    Bomb bomb(5, 5, 1.0, 2, 3);
    
    // Tester la réduction du timer
    bomb.update(map, std::chrono::duration<double>(0.5));
    assert(bomb.getTimer() == 0.5 && "Le timer de la bombe devrait être réduit de 0.5");
    
    // Tester l'explosion quand le timer atteint 0
    bomb.update(map, std::chrono::duration<double>(0.6));
    assert(!bomb.isActive() && bomb.isExploding() && "La bombe devrait être en train d'exploser");
    
    // Tester la fin de l'explosion
    bomb.update(map, std::chrono::duration<double>(0.1));
    assert(bomb.hasFinishedExploding() && "La bombe devrait avoir fini d'exploser");
    
    std::cout << "Test de l'explosion de la bombe : OK" << std::endl;
}

void testBombSymbol() {
    Bomb bomb(5, 5, 1.0, 2, 3);
    assert(bomb.getSymbol() == 'O' && "Le symbole de la bombe devrait être 'O'");
    std::cout << "Test du symbole de la bombe : OK" << std::endl;
}

void testBombDamage() {
    Bomb bomb(5, 5, 1.0, 2, 3);
    assert(bomb.getDamage() == 3 && "Les dégâts de la bombe sont incorrects");
    std::cout << "Test des dégâts de la bombe : OK" << std::endl;
}

void testBombRadius() {
    Bomb bomb(5, 5, 1.0, 2, 3);
    assert(bomb.getExplosionRadius() == 2 && "Le rayon d'explosion de la bombe est incorrect");
    std::cout << "Test du rayon d'explosion de la bombe : OK" << std::endl;
}

int Bomb::regressionTest() {
    try {
        // Exécuter tous les tests unitaires pour la classe Bomb
        testCreateBomb();
        testBombPosition();
        testBombTimer();
        testBombUpdate();
        testBombSymbol();
        testBombDamage();
        testBombRadius();

        std::cout << "Tous les tests pour la classe Bomb ont réussi !" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Une exception s'est produite : " << e.what() << std::endl;
        return 1;
    }
    return 0;
}