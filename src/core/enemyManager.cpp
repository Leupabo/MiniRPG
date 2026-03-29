#include "enemyManager.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <cstdlib>
#include <ctime>

std::string EnemyManager::getEnemiesFilePath(int mapId) const {
    // Génère le chemin du fichier JSON pour les ennemis d'une carte spécifique
    return "data/enemies/enemies_map_" + std::to_string(mapId) + ".json";
}

EnemyManager::EnemyManager() {
    // Initialise le générateur de nombres aléatoires avec l'heure actuelle
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

EnemyManager::~EnemyManager() {
}

void EnemyManager::createEnemies(int numberOfEnemies, const Map& map, const Player& player) {
    // Vide la liste d'ennemis existante
    enemies.clear();

    for (int i = 0; i < numberOfEnemies; i++) {
        int enemyX, enemyY;
        bool validPosition = false;

        int attempts = 0;

        // Essaie de trouver une position valide pour l'ennemi
        while (!validPosition && attempts < MAX_PLACEMENT_ATTEMPTS) {
            // Génère une position aléatoire
            enemyX = rand() % map.getWidth();
            enemyY = rand() % map.getHeight();

            // Vérifie que la position est praticable et n'est pas occupée par le joueur
            validPosition = map.isWalkable(enemyX, enemyY) && 
                           (enemyX != player.getX() || enemyY != player.getY());

            // Vérifie que la position n'est pas déjà occupée par un autre ennemi
            for (const auto& enemy : enemies) {
                if (enemy.getX() == enemyX && enemy.getY() == enemyY) {
                    validPosition = false;
                    break;
                }
            }

            attempts++;
        }

        // Si une position valide a été trouvée, crée un nouvel ennemi
        if (validPosition) {
            enemies.push_back(Enemy(enemyX, enemyY, ENEMY_MOVE_SPEED));
        } else {
            std::cerr << "Impossible de placer l'ennemi " << i+1 << " après " << MAX_PLACEMENT_ATTEMPTS << " tentatives." << std::endl;
        }
    }
}

void EnemyManager::saveEnemies(int mapId) const {
    // Crée le répertoire de sauvegarde s'il n'existe pas
    std::filesystem::create_directories("data/enemies");

    // Convertit tous les ennemis en format JSON
    nlohmann::json j = nlohmann::json::array();
    for (const auto& enemy : enemies) {
        j.push_back(enemy.toJson());
    }

    // Écrit le JSON dans un fichier
    std::string filePath = getEnemiesFilePath(mapId);
    std::ofstream file(filePath);
    if (file.is_open()) {
        file << j.dump(4);  // Indentation de 4 espaces pour lisibilité
        file.close();
    } else {
        std::cerr << "Erreur: Impossible de sauvegarder les ennemis dans " << filePath << std::endl;
    }
}

void EnemyManager::loadEnemies(int mapId, const Map& map, const Player& player) {
    std::string filePath = getEnemiesFilePath(mapId);
    std::ifstream file(filePath);

    if (file.is_open()) {
        try {
            // Charge le JSON depuis le fichier
            nlohmann::json j;
            file >> j;

            enemies.clear();

            // Crée les ennemis à partir des données JSON
            for (const auto& enemyJson : j) {
                enemies.push_back(Enemy(enemyJson));
            }

            std::cout << "Ennemis chargés depuis " << filePath << std::endl;
        } catch (const std::exception& e) {
            // En cas d'erreur, crée de nouveaux ennemis
            std::cerr << "Erreur lors du chargement des ennemis: " << e.what() << std::endl;
            createEnemies(DEFAULT_ENEMY_COUNT, map, player);
        }
    } else {
        // Si le fichier n'existe pas, crée de nouveaux ennemis
        std::cout << "Aucun fichier d'ennemis trouvé pour la carte " << mapId << ", création de nouveaux ennemis." << std::endl;
        createEnemies(DEFAULT_ENEMY_COUNT, map, player);
    }
}

bool EnemyManager::enemiesFileExists(int mapId) const {
    // Vérifie si le fichier d'ennemis existe pour une carte donnée
    std::string filePath = getEnemiesFilePath(mapId);
    std::ifstream file(filePath);
    return file.good();
}

void EnemyManager::updateEnemies(Map& map, const Player& player, ItemManager& itemManager, std::chrono::duration<double> elapsedTime) {
    // Supprime les ennemis morts et gère les objets qu'ils laissent tomber
    for (auto it = enemies.begin(); it != enemies.end();) {
        if (it->gethealth() <= 0) {
            // L'ennemi est mort, il peut laisser tomber un objet
            Item* droppedItem = it->dropItem();
            if (droppedItem != nullptr) {
                itemManager.addItem(droppedItem);
            }
            
            // Supprime l'ennemi de la liste
            it = enemies.erase(it);
            nbEnemies--;
        } else {
            ++it;
        }
    }

    int playerX = player.getX();
    int playerY = player.getY();

    // Met à jour chaque ennemi
    for (auto& enemy : enemies) {
        // Calcule la distance de Manhattan entre l'ennemi et le joueur
        int distance = abs(enemy.getX() - playerX) + abs(enemy.getY() - playerY);

        // Si le joueur est à portée de détection, l'ennemi le prend pour cible
        if (distance <= ENEMY_DETECTION_RANGE) {
            enemy.setTarget(playerX, playerY);
        } else {
            // Sinon, l'ennemi perd sa cible
            enemy.clearTarget();
        }

        // Met à jour la position et l'état de l'ennemi
        enemy.update(map, elapsedTime);
    }
}

void EnemyManager::cleanup() {
    // Supprime le répertoire contenant les fichiers d'ennemis sauvegardés
    std::string enemiesDir = "data/enemies";

    if (std::filesystem::exists(enemiesDir)) {
        try {
            std::filesystem::remove_all(enemiesDir);
            std::cout << "Dossier supprimé: " << enemiesDir << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Erreur lors de la suppression du dossier d'ennemis: " << e.what() << std::endl;
        }
    }
}