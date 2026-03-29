#include "arrow.h"
#include <cassert>
#include <iostream>
#include <cmath>

Arrow::Arrow(int startX, int startY, Direction dir, int dmg, double spd)
    : Entity(startX, startY, '>', 1, 1), direction(dir), damage(dmg), active(true), speed(spd), oldX(startX), oldY(startY) {
    assert(startX >= 0 && "La position X de départ doit être positive ou nulle");
    assert(startY >= 0 && "La position Y de départ doit être positive ou nulle");
    assert(dmg > 0 && "Les dégâts doivent être positifs");
    assert(spd > 0 && "La vitesse doit être positive");
    
    // Définir le symbole de la flèche en fonction de sa direction
    switch (dir) {
        case Direction::UP: symbol = '^'; break;
        case Direction::DOWN: symbol = 'v'; break;
        case Direction::LEFT: symbol = '<'; break;
        case Direction::RIGHT: symbol = '>'; break;
    }

    assert((symbol == '^' || symbol == 'v' || symbol == '<' || symbol == '>') && "Le symbole de la flèche doit correspondre à sa direction");
}

Arrow::Arrow() : Entity(), direction(Direction::RIGHT), damage(0), active(false), speed(0), oldX(0), oldY(0) {
}

Arrow::~Arrow() {}

void Arrow::update(Map& map, std::chrono::duration<double> elapsedTime) {
    assert(active && "Une flèche inactive ne devrait pas être mise à jour");
    
    // Sauvegarder la position actuelle
    oldX = x;
    oldY = y;
    
    // Calculer la distance à parcourir en fonction de la vitesse et du temps écoulé
    double distance = speed * elapsedTime.count();
    
    // Convertir la distance en nombre d'étapes (cases) à parcourir
    // On utilise ceil pour s'assurer que même une petite distance sera au moins 1 étape
    int steps = static_cast<int>(std::ceil(distance));

    // Déplacer la flèche étape par étape pour vérifier les collisions à chaque case
    for (int i = 0; i < steps; ++i) {
        int dx = 0, dy = 0;
        
        // Déterminer la direction du mouvement
        switch (direction) {
            case Direction::UP: dy = -1; break;
            case Direction::DOWN: dy = 1; break;
            case Direction::LEFT: dx = -1; break;
            case Direction::RIGHT: dx = 1; break;
        }

        int newX = x + dx;
        int newY = y + dy;

        // Vérifier si la nouvelle position est valide
        if (map.isWalkable(newX, newY)) {
            x = newX;
            y = newY;
        } else {
            // Si la flèche rencontre un obstacle, la désactiver
            active = false;
            break;
        }
    }

    assert((active && (x != oldX || y != oldY)) || !active && "La flèche doit soit se déplacer, soit être désactivée");
}

// Fonctions de test pour la régression

void testCreateArrow() {
    Arrow arrow(5, 5, Direction::RIGHT, 1, 10.0);
    std::cout << "Test de creation de la fleche : OK" << std::endl;
}

void testArrowPosition() {
    Arrow arrow(5, 5, Direction::RIGHT, 1, 10.0);
    assert(arrow.getX() == 5 && arrow.getY() == 5 && "Position initiale de la fleche incorrecte");
    std::cout << "Test de la position initiale de la fleche : OK" << std::endl;
}

void testArrowMovement() {
    Map map("data/maps/test_map.txt");
    Arrow arrow(5, 5, Direction::RIGHT, 1, 10.0);
    arrow.update(map, std::chrono::duration<double>(0.1));
    assert(arrow.getX() == 6 && arrow.getY() == 5 && "La flèche devrait s'être déplacée d'une case vers la droite");
    std::cout << "Test du mouvement de la flèche : OK" << std::endl;
}

void testArrowLongMovement() {
    Map map("data/maps/test_map.txt");
    Arrow arrow(5, 5, Direction::RIGHT, 1, 20.0);
    // Test avec une vitesse plus élevée et un temps plus long pour vérifier le déplacement sur plusieurs cases
    arrow.update(map, std::chrono::duration<double>(0.5));
    assert(arrow.getX() == 15 && arrow.getY() == 5 && "La flèche devrait s'être déplacée de 10 cases vers la droite");
    std::cout << "Test du mouvement long de la flèche : OK" << std::endl;
}

void testArrowCollision() {
    Map map("data/maps/test_map.txt");
    Arrow arrow(5, 5, Direction::RIGHT, 1, 10.0);
    // Placer un mur sur le chemin de la flèche
    map.setTile(6, 5, TILE_WALL);
    arrow.update(map, std::chrono::duration<double>(0.1));
    assert(!arrow.isActive() && "La fleche devrait etre desactivee apres une collision");
    std::cout << "Test de la collision de la fleche : OK" << std::endl;
}

void testArrowSymbol() {
    Arrow arrow(5, 5, Direction::RIGHT, 1, 10.0);
    assert(arrow.getSymbol() == '>' && "Le symbole de la fleche devrait etre '>'");
    std::cout << "Test du symbole de la fleche : OK" << std::endl;
}

void testArrowDamage() {
    Arrow arrow(5, 5, Direction::RIGHT, 1, 10.0);
    assert(arrow.getDamage() > 0 && "Les degats de la fleche devraient etre positifs");
    std::cout << "Test des degats de la fleche : OK" << std::endl;
}

void testArrowDeactivation() {
    Arrow arrow(5, 5, Direction::RIGHT, 1, 10.0);
    assert(arrow.isActive() && "La fleche devrait etre active initialement");
    arrow.deactivate();
    assert(!arrow.isActive() && "La fleche devrait etre desactivee apres appel a deactivate()");
    std::cout << "Test de la desactivation de la fleche : OK" << std::endl;
}

int Arrow::regressionTest() {
    try {
        // Exécuter tous les tests unitaires pour la classe Arrow
        testCreateArrow();
        testArrowPosition();
        testArrowMovement();
        testArrowLongMovement();
        testArrowCollision();
        testArrowSymbol();
        testArrowDamage();
        testArrowDeactivation();

        std::cout << "Tous les tests pour la classe Arrow ont réussi !" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Une exception s'est produite : " << e.what() << std::endl;
        return 1;
    }
    return 0;
}