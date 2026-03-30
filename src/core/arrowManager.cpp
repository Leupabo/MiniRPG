#include "arrowManager.h"
#include <algorithm>

ArrowManager::~ArrowManager() {
    // Libérer la mémoire de toutes les flèches
    for (Arrow* arrow : arrows) {
        delete arrow;
    }
    arrows.clear();
}

void ArrowManager::updateArrows(const Map& map, std::chrono::duration<double> elapsedTime) {
    // Mettre à jour toutes les flèches actives
    for (Arrow* arrow : arrows) {
        if (arrow->isActive()) {
            arrow->update(const_cast<Map&>(map), elapsedTime);
        }
    }
}

void ArrowManager::checkArrowCollisions(std::vector<Enemy>& enemies) {
    for (Arrow* arrow : arrows) {
        if (arrow->isActive()) {
            // Récupérer les positions précédente et actuelle de la flèche
            int oldX = arrow->getOldX();
            int oldY = arrow->getOldY();
            int newX = arrow->getX();
            int newY = arrow->getY();
            
            // Calculer la direction du mouvement
            int dx = (newX > oldX) ? 1 : ((newX < oldX) ? -1 : 0);
            int dy = (newY > oldY) ? 1 : ((newY < oldY) ? -1 : 0);
            
            // Vérifier les collisions sur chaque case traversée par la flèche
            // Cela permet de détecter les collisions même si la flèche "saute" par-dessus un ennemi
            // en se déplaçant de plusieurs cases en une seule mise à jour
            for (int x = oldX, y = oldY; x != newX || y != newY; x += dx, y += dy) {
                for (Enemy& enemy : enemies) {
                    if (x == enemy.getX() && y == enemy.getY()) {
                        // Infliger des dégâts à l'ennemi et désactiver la flèche
                        enemy.setDmg(arrow->getDamage());
                        arrow->deactivate();
                        break;
                    }
                }
                if (!arrow->isActive()) {
                    break;
                }
            }
            
            // Vérifier également la position finale de la flèche
            if (arrow->isActive()) {
                for (Enemy& enemy : enemies) {
                    if (newX == enemy.getX() && newY == enemy.getY()) {
                        enemy.setDmg(arrow->getDamage());
                        arrow->deactivate();
                        break;
                    }
                }
            }
        }
    }
}

void ArrowManager::cleanupArrows() {
    // Supprimer toutes les flèches inactives en utilisant l'idiome remove-erase
    arrows.erase(std::remove_if(arrows.begin(), arrows.end(),
        [](const Arrow* arrow) {
            if (!arrow->isActive()) {
                delete arrow;  // Libérer la mémoire
                return true;   // Supprimer de la liste
            }
            return false;      // Garder dans la liste
        }), arrows.end());
}

void ArrowManager::clearAllArrows() {
    // Supprimer toutes les flèches
    for (auto& arrow : arrows) {
        delete arrow;
    }
    arrows.clear();
}

void ArrowManager::addArrow(Arrow* arrow) {
    // Ajouter une nouvelle flèche à la liste
    arrows.push_back(arrow);
}

const std::vector<Arrow*>& ArrowManager::getArrows() const {
    return arrows;
}
