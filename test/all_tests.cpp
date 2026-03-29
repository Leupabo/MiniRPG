#include <iostream>
#include "player.h"
#include "bomb.h"
#include "map.h"
#include "arrow.h"
#include "item.h"
#include "enemy.h"

int main() {
    try {
        Player player(0, 0);
        player.regressionTest();

        Bomb bomb;
        bomb.regressionTest();

        Map map;
        map.regressionTest();

        Arrow arrow;
        arrow.regressionTest();

        Item item;
        item.regressionTest();

        Enemy enemy;
        enemy.regressionTest();

        std::cout << "Tous les tests de régression ont réussi !" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Une exception s'est produite : " << e.what() << std::endl;
        return 1;
    }
    return 0;
}