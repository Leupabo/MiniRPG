#include "item.h"
#include <cassert>
#include <iostream>

Item::Item(int x, int y, ItemType type, double lifespan) 
    : Entity(x, y, '?', 1, 1), type(type), lifespan(lifespan), elapsedTime(0.0) {
    // Vérification des paramètres d'entrée
    assert(x >= 0 && "La position X de l'item doit être positive ou nulle");
    assert(y >= 0 && "La position Y de l'item doit être positive ou nulle");
    assert(lifespan > 0 && "La durée de vie de l'item doit être positive");
    
    // Configuration des propriétés en fonction du type d'item
    switch (type) {
        case ItemType::HEART:
            value = 1;  // Valeur de guérison pour un cœur
            symbol = 'H';  // Symbole représentant un cœur
            break;
        default:
            assert(false && "Type d'item non reconnu");
            break;
    }

    // Vérification des propriétés après initialisation
    assert(value > 0 && "La valeur de l'item doit être positive");
    assert(symbol != '\0' && "Le symbole de l'item doit être défini");
}

Item::Item() : Entity(), type(ItemType::HEART), value(0), lifespan(30.0), elapsedTime(0.0) {
    // Constructeur par défaut avec des valeurs prédéfinies
}

Item::~Item() {}

void Item::update(Map& map, std::chrono::duration<double> deltaTime) {
    // Vérification que l'item est sur une case praticable
    assert(map.isWalkable(getX(), getY()) && "L'item doit être sur une case praticable");
    
    // Mise à jour du temps écoulé depuis la création de l'item
    elapsedTime += deltaTime.count();
}

void testCreateItem() {
    // Test simple de création d'un item
    Item item(5, 5, ItemType::HEART);
    std::cout << "Test de creation de l'item : OK" << std::endl;
}

void testItemPosition() {
    // Vérification que la position de l'item est correctement initialisée
    Item item(5, 5, ItemType::HEART);
    assert(item.getX() == 5 && item.getY() == 5 && "Position de l'item incorrecte");
    std::cout << "Test de la position de l'item : OK" << std::endl;
}

void testItemType() {
    // Vérification que le type de l'item est correctement défini
    Item item(5, 5, ItemType::HEART);
    assert(item.getType() == ItemType::HEART && "Type de l'item incorrect");
    std::cout << "Test du type de l'item : OK" << std::endl;
}

void testItemSymbol() {
    // Vérification que le symbole de l'item correspond au type
    Item healthItem(5, 5, ItemType::HEART);
    assert(healthItem.getSymbol() == 'H' && "Le symbole de l'item de santé devrait être 'H'");    
    std::cout << "Test des symboles des items : OK" << std::endl;
}

void testItemValue() {
    // Vérification que la valeur de l'item est positive
    Item item(5, 5, ItemType::HEART);
    assert(item.getValue() > 0 && "La valeur de l'item devrait être positive");
    std::cout << "Test de la valeur de l'item : OK" << std::endl;
}

void testItemUpdate() {
    // Vérification que la méthode update met à jour correctement le temps écoulé
    Map map("data/maps/test_map.txt");
    Item item(5, 5, ItemType::HEART);
    std::chrono::duration<double> deltaTime(1.0);
    
    // Mise à jour de l'item avec un deltaTime de 1 seconde
    item.update(map, deltaTime);
    
    // Vérification que la position n'a pas changé
    assert(item.getX() == 5 && item.getY() == 5 && "L'update ne devrait pas modifier la position de l'item");
    
    // Vérification que le temps écoulé a été mis à jour
    assert(item.getElapsedTime() == 1.0 && "Le temps écoulé devrait être mis à jour");
    std::cout << "Test de l'update de l'item : OK" << std::endl;
}

void testItemLifespan() {
    // Vérification de la durée de vie et de l'expiration de l'item
    Map map("data/maps/test_map.txt");
    Item item(5, 5, ItemType::HEART, 10.0);
    
    // Vérification des propriétés initiales
    assert(item.getLifespan() == 10.0 && "La durée de vie de l'item devrait être de 10 secondes");
    assert(!item.isExpired() && "L'item ne devrait pas être expiré initialement");
    
    // Mise à jour avec un deltaTime supérieur à la durée de vie
    std::chrono::duration<double> deltaTime(11.0);
    item.update(map, deltaTime);
    
    // Vérification que l'item est maintenant expiré
    assert(item.isExpired() && "L'item devrait être expiré après 11 secondes");
    
    std::cout << "Test de la durée de vie de l'item : OK" << std::endl;
}

int Item::regressionTest(){
    try {
        // Exécution de tous les tests unitaires pour la classe Item
        testCreateItem();
        testItemPosition();
        testItemType();
        testItemSymbol();
        testItemValue();
        testItemUpdate();
        testItemLifespan();

        std::cout << "Tous les tests pour la classe Item ont réussi !" << std::endl;

    } catch (const std::exception& e) {
        // Capture et affichage de toute exception qui pourrait se produire
        std::cerr << "Une exception s'est produite : " << e.what() << std::endl;
        return 1;  // Indique l'échec
    }
    return 0;  // Indique le succès
}
