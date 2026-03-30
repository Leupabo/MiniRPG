#include "bombManager.h"
#include <algorithm>

BombManager::~BombManager() {
    // Libérer la mémoire de toutes les bombes
    for (auto bomb : bombs) {
        delete bomb;
    }
}

void BombManager::updateBombs(Map& map, std::chrono::duration<double> elapsedTime) {
    // Mettre à jour toutes les bombes
    for (auto bomb : bombs) {
        bomb->update(map, elapsedTime);
    }
}

void BombManager::checkBombExplosions(std::vector<Enemy>& enemies, Player& player) {
    for (auto bomb : bombs) {
        if (bomb->isExploding()) {
            // Vérifier si des ennemis sont dans le rayon d'explosion
            for (auto& enemy : enemies) {
                // Utilisation de la distance de Manhattan pour déterminer si l'ennemi est touché
                // (|x1-x2| + |y1-y2| <= rayon)
                if (std::abs(enemy.getX() - bomb->getX()) <= bomb->getExplosionRadius() &&
                    std::abs(enemy.getY() - bomb->getY()) <= bomb->getExplosionRadius()) {
                    enemy.setDmg(bomb->getDamage());
                }
            }
            
            // Vérifier si le joueur est dans le rayon d'explosion
            if (std::abs(player.getX() - bomb->getX()) <= bomb->getExplosionRadius() &&
                std::abs(player.getY() - bomb->getY()) <= bomb->getExplosionRadius()) {
                player.setDmg(bomb->getDamage());
            }
        }
    }
}

void BombManager::cleanupBombs() {
    // Supprimer toutes les bombes qui ont fini d'exploser en utilisant l'idiome remove-erase
    bombs.erase(std::remove_if(bombs.begin(), bombs.end(),
        [](const Bomb* bomb) {
            if (!bomb->isActive() && !bomb->isExploding()) {
                delete bomb;  // Libérer la mémoire
                return true;  // Supprimer de la liste
            }
            return false;     // Garder dans la liste
        }), bombs.end());
}

void BombManager::clearAllBombs() {
    // Supprimer toutes les bombes
    for (auto& bomb : bombs) {
        delete bomb;
    }
    bombs.clear();
}

void BombManager::addBomb(Bomb* bomb) {
    // Ajouter une nouvelle bombe à la liste
    bombs.push_back(bomb);
}

const std::vector<Bomb*>& BombManager::getBombs() const {
    return bombs;
}