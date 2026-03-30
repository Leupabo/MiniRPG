#include "Map.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>

Map::Map() : id(0), width(0), height(0) {
    // Initialisation de toutes les tuiles comme des murs par défaut
    for (int y = 0; y < MAX_MAP_HEIGHT; y++) {
        for (int x = 0; x < MAX_MAP_WIDTH; x++) {
            tiles[y][x] = TILE_WALL;
        }
    }
}

Map::Map(const std::string& filename) : id(0), width(0), height(0) {
    // Initialisation de toutes les tuiles comme des murs par défaut
    for (int y = 0; y < MAX_MAP_HEIGHT; y++) {
        for (int x = 0; x < MAX_MAP_WIDTH; x++) {
            tiles[y][x] = TILE_WALL;
        }
    }
    
    // Chargement de la carte depuis un fichier
    loadFromFile(filename);
}

Map::~Map() {
    // Destructeur
}

bool Map::loadFromFile(const std::string& filename) {
    // Ouverture du fichier de carte
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erreur: Impossible d'ouvrir le fichier " << filename << std::endl;
        return false;
    }
    
    // Lecture de l'ID de la carte
    file >> id;
    
    // Lecture des dimensions de la carte
    file >> width >> height;
    
    // Ignorer le caractère de fin de ligne
    file.ignore();
    
    // Lecture des tuiles de la carte
    for (int y = 0; y < height; y++) {
        std::string line;
        std::getline(file, line);
        
        for (int x = 0; x < width && x < line.length(); x++) {
            char c = line[x];
            setTile(x, y, c);
        }
    }
    
    // Lecture des portails
    portals.clear();
    
    int numPortals;
    if (file >> numPortals) {
        file.ignore();
        for (int i = 0; i < numPortals; i++) {
            int sourceX, sourceY, targetMapId, targetX, targetY;
            if (file >> sourceX >> sourceY >> targetMapId >> targetX >> targetY) {
                // Ajout du portail à la liste et marquage de la tuile comme portail
                addPortal(sourceX, sourceY, targetMapId, targetX, targetY);
                setTile(sourceX, sourceY, TILE_PORTAL);
            }
        }
    }
    
    file.close();
    return true;
}

bool Map::loadFromId(int mapId) {
    // Construction du chemin du fichier à partir de l'ID de la carte
    std::string filename = "data/maps/map_" + std::to_string(mapId) + ".txt";
    
    // Tentative de chargement du fichier
    if (loadFromFile(filename)) {
        return true;
    }
    
    std::cerr << "Erreur: Impossible de charger la carte avec l'ID " << mapId << std::endl;
    return false;
}

int Map::getId() const {
    return id;
}

int Map::getWidth() const {
    return width;
}

int Map::getHeight() const {
    return height;
}

TileType Map::getTile(int x, int y) const {
    // Vérification que les coordonnées sont dans les limites
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return tiles[y][x];
    }
    // Par défaut, retourne un mur pour les coordonnées hors limites
    return TILE_WALL;
}

char Map::getTileChar(int x, int y) const {
    // Vérification que les coordonnées sont dans les limites
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return static_cast<char>(tiles[y][x]);
    }
    // Par défaut, retourne un mur pour les coordonnées hors limites
    return static_cast<char>(TILE_WALL);
}

void Map::setTile(int x, int y, TileType tile) {
    // Vérification que les coordonnées sont dans les limites
    if (x >= 0 && x < width && y >= 0 && y < height) {
        tiles[y][x] = tile;
    }
}

void Map::setTile(int x, int y, char tileChar) {
    // Vérification que les coordonnées sont dans les limites
    if (x >= 0 && x < width && y >= 0 && y < height) {
        // Conversion du caractère en type de tuile
        switch (tileChar) {
            case '.': tiles[y][x] = TILE_FLOOR; break;  // Sol
            case '#': tiles[y][x] = TILE_WALL; break;   // Mur
            case 'T': tiles[y][x] = TILE_TREE; break;   // Arbre
            case 'W': tiles[y][x] = TILE_WATER; break;  // Eau
            case 'P': tiles[y][x] = TILE_PORTAL; break; // Portail
            default: tiles[y][x] = TILE_WALL; break;    // Par défaut, mur
        }
    }
}


bool Map::isWalkable(int x, int y) const {
    // Vérification que les coordonnées sont dans les limites
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return false;
    }
    
    // Vérification si la tuile est praticable (sol ou portail)
    TileType tile = getTile(x, y);
    return (tile == TILE_FLOOR || tile == TILE_PORTAL);
}

bool Map::isPortal(int x, int y) const {
    // Vérification que les coordonnées sont dans les limites
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return false;
    }
    
    // Vérification si la tuile est un portail
    return getTile(x, y) == TILE_PORTAL;
}

void Map::addPortal(int sourceX, int sourceY, int targetMapId, int targetX, int targetY) {
    // Création et ajout d'un nouveau portail
    Portal portal = {sourceX, sourceY, targetMapId, targetX, targetY};
    portals.push_back(portal);
}

const Portal* Map::getPortalAt(int x, int y) const {
    // Recherche d'un portail aux coordonnées spécifiées
    for (const auto& portal : portals) {
        if (portal.sourceX == x && portal.sourceY == y) {
            return &portal;
        }
    }
    // Aucun portail trouvé
    return nullptr;
}

void testCreateMap() {
    // Test de création d'une carte vide
    Map map;
    std::cout << "Test de creation de la carte : OK" << std::endl;
}

void testLoadMap() {
    // Test de chargement d'une carte depuis un fichier
    Map map;
    bool loaded = map.loadFromFile("data/maps/test_map.txt");
    assert(loaded && "echec du chargement de la carte");
    std::cout << "Test de chargement de la carte : OK" << std::endl;
}

void testMapDimensions() {
    // Test des dimensions de la carte
    Map map("data/maps/test_map.txt");
    assert(map.getWidth() == 20 && "Largeur de la carte incorrecte");
    assert(map.getHeight() == 15 && "Hauteur de la carte incorrecte");
    std::cout << "Test des dimensions de la carte : OK" << std::endl;
}

void testAccessMapElements() {
    // Test d'accès aux éléments de la carte
    Map map("data/maps/test_map.txt");
    assert(map.getTileChar(0, 0) == '#' && "element incorrect en (0,0)");
    assert(map.getTileChar(10, 10) == '.' && "element incorrect en (10,10)");
    std::cout << "Test d'acces aux elements de la carte : OK" << std::endl;
}

void testModifyMapElement() {
    // Test de modification d'un élément de la carte
    Map map("data/maps/test_map.txt");
    map.setTile(5, 5, TILE_TREE);
    assert(map.getTileChar(5, 5) == 'T' && "echec de la modification de l'element");
    std::cout << "Test de modification d'un element de la carte : OK" << std::endl;
}

void testWalkableCheck() {
    // Test de vérification de praticabilité des tuiles
    Map map("data/maps/test_map.txt");
    assert(!map.isWalkable(0, 0) && "La tuile (0,0) devrait etre non praticable");
    assert(map.isWalkable(10, 10) && "La tuile (10,10) devrait etre praticable");
    std::cout << "Test de verification de praticabilite : OK" << std::endl;
}

void testPortalCheck() {
    // Test de vérification des portails
    Map map("data/maps/test_map.txt");
    map.setTile(5, 5, TILE_PORTAL);
    assert(map.isPortal(5, 5) && "Un portail devrait etre present en (5,5)");
    assert(!map.isPortal(0, 0) && "Aucun portail ne devrait etre present en (0,0)");
    std::cout << "Test de verification de portail : OK" << std::endl;
}

void testGetId() {
    // Test de récupération de l'ID de la carte
    Map map("data/maps/test_map.txt");
    assert(map.getId() > 0 && "L'ID de la carte devrait etre positif");
    std::cout << "Test de recuperation de l'ID de la carte : OK" << std::endl;

    // Test de chargement d'une carte spécifique par ID
    Map specificMap;
    specificMap.loadFromId(1);
    assert(specificMap.getId() == 1 && "L'ID de la carte specifique devrait etre 1");
    std::cout << "Test de recuperation de l'ID d'une carte specifique : OK" << std::endl;
}

int Map::regressionTest() {
    try {
        // Exécution de tous les tests unitaires pour la classe Map
        testCreateMap();
        testLoadMap();
        testMapDimensions();
        testAccessMapElements();
        testModifyMapElement();
        testWalkableCheck();
        testPortalCheck();
        testGetId();

        std::cout << "Tous les tests ont reussi !" << std::endl;

    } catch (const std::exception& e) {
        // Capture et affichage de toute exception qui pourrait se produire
        std::cerr << "Une exception s'est produite : " << e.what() << std::endl;
        return 1;  // Indique l'échec
    }
    return 0;  // Indique le succès
}