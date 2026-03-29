#include <iostream>
#include <string>
#include <sstream>
#include "map.h"

void clearScreen() {
    // Efface l'écran de la console en fonction du système d'exploitation
#ifdef _WIN32
    system("cls");  // Pour Windows
#else
    system("clear");  // Pour Unix/Linux/MacOS
#endif
}

void displayMap(const Map &map) {
    // Efface l'écran avant d'afficher la carte
    clearScreen();
    
    // Affiche les informations générales de la carte
    std::cout << "Carte ID: " << map.getId() << " (" << map.getWidth() << "x" << map.getHeight() << ")" << std::endl;
    std::cout << "Legende: # = Mur, T = Arbre, . = Sol" << std::endl;
    
    // Dessine la bordure supérieure de la carte
    std::cout << std::string(map.getWidth() + 2, '-') << std::endl;
    
    // Affiche chaque ligne de la carte avec des bordures verticales
    for (int y = 0; y < map.getHeight(); ++y) {
        std::cout << "|";  // Bordure gauche
        for (int x = 0; x < map.getWidth(); ++x) {
            std::cout << map.getTileChar(x, y);  // Affiche le caractère de la tuile
        }
        std::cout << "|" << std::endl;  // Bordure droite et nouvelle ligne
    }
    
    // Dessine la bordure inférieure de la carte
    std::cout << std::string(map.getWidth() + 2, '-') << std::endl;
}

void displayHelp() {
    // Affiche la liste des commandes disponibles et leur description
    std::cout << "\nCommandes disponibles:" << std::endl;
    std::cout << "  help                - Affiche cette aide" << std::endl;
    std::cout << "  display             - Affiche la carte" << std::endl;
    std::cout << "  getTile x y         - Affiche le type de tuile aux coordonnees (x,y)" << std::endl;
    std::cout << "  getTileChar x y     - Affiche le caractere de la tuile aux coordonnees (x,y)" << std::endl;
    std::cout << "  setTile x y type    - Modifie le type de tuile (. pour sol, # pour mur, T pour arbre)" << std::endl;
    std::cout << "  isWalkable x y      - Verifie si la tuile aux coordonnees (x,y) est praticable" << std::endl;
    std::cout << "  getWidth            - Affiche la largeur de la carte" << std::endl;
    std::cout << "  getHeight           - Affiche la hauteur de la carte" << std::endl;
    std::cout << "  getId               - Affiche l'ID de la carte" << std::endl;
    std::cout << "  loadMap id          - Charge une nouvelle carte avec l'ID specifie" << std::endl;
    std::cout << "  clear               - Efface l'ecran" << std::endl;
    std::cout << "  quit                - Quitte le programme" << std::endl;
}

void interactiveLoop(Map &map) {
    // Variables pour la boucle interactive
    std::string line;      // Ligne de commande entrée par l'utilisateur
    std::string command;   // Commande extraite de la ligne
    bool running = true;   // Contrôle de la boucle principale
    
    // Affichage initial de la carte et de l'aide
    displayMap(map);
    displayHelp();
    
    // Boucle principale d'interaction
    while (running) {
        // Affiche l'invite de commande et lit l'entrée utilisateur
        std::cout << "\n> ";
        std::getline(std::cin, line);
        
        // Extraction de la commande depuis la ligne d'entrée
        std::istringstream iss(line);
        iss >> command;
        
        // Traitement des différentes commandes
        if (command == "quit" || command == "q") {
            // Quitter le programme
            running = false;
        }
        else if (command == "help" || command == "h") {
            // Afficher l'aide
            displayHelp();
        }
        else if (command == "display" || command == "d") {
            // Afficher la carte
            displayMap(map);
        }
        else if (command == "clear" || command == "c") {
            // Effacer l'écran
            clearScreen();
        }
        else if (command == "loadMap") {
            // Charger une carte par son ID
            int id;
            if (iss >> id) {
                if (map.loadFromId(id)) {
                    std::cout << "Carte avec ID " << id << " chargee avec succes!" << std::endl;
                    displayMap(map);
                    displayHelp();
                } else {
                    std::cout << "Impossible de charger la carte avec ID " << id << ". Verifiez que le fichier existe." << std::endl;
                }
            } else {
                std::cout << "Usage: loadMap id" << std::endl;
            }
        }
        else if (command == "getTile") {
            // Obtenir le type de tuile à des coordonnées spécifiques
            int x, y;
            if (iss >> x >> y) {
                if (x >= 0 && x < map.getWidth() && y >= 0 && y < map.getHeight()) {
                    TileType tile = map.getTile(x, y);
                    std::cout << "Tuile a (" << x << "," << y << "): ";
                    // Affichage du type de tuile en texte
                    switch (tile) {
                        case TILE_FLOOR: std::cout << "Sol (TILE_FLOOR)"; break;
                        case TILE_WALL: std::cout << "Mur (TILE_WALL)"; break;
                        case TILE_TREE: std::cout << "Arbre (TILE_TREE)"; break;
                        default: std::cout << "Type inconnu"; break;
                    }
                    std::cout << std::endl;
                } else {
                    std::cout << "Coordonnees hors limites!" << std::endl;
                }
            } else {
                std::cout << "Usage: getTile x y" << std::endl;
            }
        }
        else if (command == "getTileChar") {
            // Obtenir le caractère de la tuile à des coordonnées spécifiques
            int x, y;
            if (iss >> x >> y) {
                if (x >= 0 && x < map.getWidth() && y >= 0 && y < map.getHeight()) {
                    char c = map.getTileChar(x, y);
                    std::cout << "Caractère a (" << x << "," << y << "): '" << c << "'" << std::endl;
                } else {
                    std::cout << "Coordonnees hors limites!" << std::endl;
                }
            } else {
                std::cout << "Usage: getTileChar x y" << std::endl;
            }
        }
        else if (command == "setTile") {
            // Modifier le type de tuile à des coordonnées spécifiques
            int x, y;
            char type;
            if (iss >> x >> y >> type) {
                if (x >= 0 && x < map.getWidth() && y >= 0 && y < map.getHeight()) {
                    map.setTile(x, y, type);
                    std::cout << "Tuile a (" << x << "," << y << ") modifiee en '" << type << "'" << std::endl;
                } else {
                    std::cout << "Coordonnees hors limites!" << std::endl;
                }
            } else {
                std::cout << "Usage: setTile x y type (. pour sol, # pour mur, T pour arbre)" << std::endl;
            }
        }
        else if (command == "isWalkable") {
            // Vérifier si une tuile est praticable
            int x, y;
            if (iss >> x >> y) {
                if (x >= 0 && x < map.getWidth() && y >= 0 && y < map.getHeight()) {
                    bool walkable = map.isWalkable(x, y);
                    std::cout << "La tuile a (" << x << "," << y << ") est " 
                              << (walkable ? "praticable" : "non praticable") << std::endl;
                } else {
                    std::cout << "Coordonnees hors limites!" << std::endl;
                }
            } else {
                std::cout << "Usage: isWalkable x y" << std::endl;
            }
        }
        else if (command == "getWidth") {
            // Obtenir la largeur de la carte
            std::cout << "Largeur de la carte: " << map.getWidth() << std::endl;
        }
        else if (command == "getHeight") {
            // Obtenir la hauteur de la carte
            std::cout << "Hauteur de la carte: " << map.getHeight() << std::endl;
        }
        else if (command == "getId") {
            // Obtenir l'ID de la carte
            std::cout << "ID de la carte: " << map.getId() << std::endl;
        }
        else {
            // Commande non reconnue
            std::cout << "Commande non reconnue. Tapez 'help' pour voir les commandes disponibles." << std::endl;
        }
    }
}

int main() {
    // Création d'une carte et tentative de chargement
    Map map;
    if (!map.loadFromId(1)) {
        // Si le chargement par ID échoue, essayer de charger directement depuis le fichier
        const std::string mapPath = "data/maps/map_" + std::to_string(map.getId()) + ".txt";
        std::cout << "Tentative de chargement de la carte depuis: " << mapPath << std::endl;
        
        if (!map.loadFromFile(mapPath)) {
            std::cerr << "Erreur: Impossible de charger la carte. Verifiez que le fichier existe." << std::endl;
            return 1;  // Sortie avec code d'erreur
        }
    }
    
    // Vérification que la carte a été correctement chargée
    if (map.getWidth() == 0 || map.getHeight() == 0) {
        std::cerr << "Erreur: La carte n'a pas ete chargee correctement." << std::endl;
        return 1;  // Sortie avec code d'erreur
    }
    
    std::cout << "Carte chargee avec succès!" << std::endl;
    
    // Démarrage de la boucle interactive
    interactiveLoop(map);
    
    // Nettoyage et message de fin
    clearScreen();
    std::cout << "Merci d'avoir utilise le testeur de carte!" << std::endl;
    return 0;  // Sortie normale
}