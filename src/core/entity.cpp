#include "entity.h"
#include <cassert>
#include <algorithm>

Entity::Entity(int startX, int startY, char entitySymbol, int pv, int maxPv)
    : x(startX), y(startY), symbol(entitySymbol), health(pv), maxHealth(maxPv) {
     // Vérification des paramètres d'entrée
     assert(startX >= 0 && "La position X de départ doit être positive ou nulle");
     assert(startY >= 0 && "La position Y de départ doit être positive ou nulle");
     assert(pv > 0 && "Les points de vie initiaux doivent être positifs");
     assert(maxPv >= pv && "Les points de vie maximum doivent être supérieurs ou égaux aux points de vie initiaux");
}

Entity::Entity(){
    // Constructeur par défaut
}

Entity::~Entity() {
    // Destructeur
}

void Entity::setPosition(int newX, int newY) {
    // Vérification des nouvelles coordonnées
    assert(newX >= 0 && "La nouvelle position X doit être positive ou nulle");
    assert(newY >= 0 && "La nouvelle position Y doit être positive ou nulle");
    x = newX;
    y = newY;
}

void Entity::setDmg(int dmg) {
    // Vérification que les dégâts sont positifs ou nuls
    assert(dmg >= 0 && "Les dégâts doivent être positifs ou nuls");
    
    // Réduction des points de vie avec un minimum de 0
    health = std::max(0, health - dmg);
    
    // Vérification que la santé reste dans les limites valides
    assert(health >= 0 && health <= maxHealth && "La santé doit rester dans les limites valides");
}

void Entity::addHp(int hlt) {
    // Vérification que la guérison est positive ou nulle
    assert(hlt >= 0 && "La guérison doit être positive ou nulle");
    
    // Augmentation des points de vie avec un maximum de maxHealth
    health = std::min(maxHealth, health + hlt);
    
    // Vérification que la santé reste dans les limites valides
    assert(health >= 0 && health <= maxHealth && "La santé doit rester dans les limites valides");
}

bool Entity::move(int dx, int dy, const Map& map) {
    // Calcul de la nouvelle position
    int newX = x + dx;
    int newY = y + dy;

    // Vérification que la nouvelle position est dans les limites de la carte
    if (newX < 0 || newX >= map.getWidth() || newY < 0 || newY >= map.getHeight()) {
        return false;  // Mouvement hors des limites de la carte
    }

    // Vérification que la nouvelle position est praticable
    if (!map.isWalkable(newX, newY)) {
        return false;  // Mouvement vers une case non praticable
    }

    // Mise à jour de la position
    x = newX;
    y = newY;
    
    // Vérification que l'entité est bien sur une case praticable après le déplacement
    assert(map.isWalkable(x, y) && "L'entité doit être sur une case praticable après le déplacement");
    return true;  // Mouvement réussi
}
