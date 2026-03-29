#include "itemManager.h"
#include <algorithm>

ItemManager::ItemManager() {}

ItemManager::~ItemManager() {
    // Libération de la mémoire pour tous les items lors de la destruction
    clearAllItems();
}

void ItemManager::addItem(Item* item) {
    // Ajout d'un nouvel item à la liste
    items.push_back(item);
}

void ItemManager::update(Map& map, std::chrono::duration<double> deltaTime) {
    // Mise à jour de tous les items avec le temps écoulé
    for (auto item : items) {
        item->update(map, deltaTime);
    }
    // Suppression des items dont la durée de vie est écoulée
    removeExpiredItems();
}

void ItemManager::checkCollisions(Player& player) {
    // Vérification des collisions entre le joueur et les items
    for (auto it = items.begin(); it != items.end(); ) {
        // Si le joueur est sur la même case que l'item
        if ((*it)->getX() == player.getX() && (*it)->getY() == player.getY()) {
            // Application de l'effet de l'item selon son type
            if ((*it)->getType() == ItemType::HEART) {
                // Augmentation des points de vie du joueur
                player.addHp((*it)->getValue());
            }
            // Libération de la mémoire et suppression de l'item de la liste
            delete *it;
            it = items.erase(it);
        } else {
            // Passage à l'item suivant si pas de collision
            ++it;
        }
    }
}

void ItemManager::clearAllItems() {
    // Libération de la mémoire pour tous les items
    for (auto item : items) {
        delete item;
    }
    // Vidage de la liste d'items
    items.clear();
}

void ItemManager::removeExpiredItems() {
    // Utilisation de l'algorithme remove_if pour supprimer les items expirés
    items.erase(
        std::remove_if(items.begin(), items.end(),
            [](const Item* item) { 
                // Si l'item est expiré, libérer sa mémoire et le marquer pour suppression
                if (item->isExpired()) {
                    delete item;
                    return true;
                }
                return false;
            }),
        // Suppression effective des éléments marqués
        items.end()
    );
}