# Projet HK - Projet LIFAPCD

Ce projet a été réalisé dans le cadre de l'UE LIFAPCD sur une durée de 8 semaines.
## Crédits

- Etudiant 1 : KOEUT Ethan p2207925
- Etudiant 2 : HONG Ugo   p2307653
- ID du projet sur la Forge : 38526

## Règles du jeu

Ce jeu ressemble au premier jeu Zelda sur NES, on joue un personnage en vue de dessus sur une carte.
L'objectif est de vaincre 28 ennemis éparpillés sur 4 cartes différentes.
Pour cela vous pouvez attaquer les ennemis avec les touches suivantes :
1. O : Épée, coup devant le personnage
2. P : Bombe, explose au bout de quelques secondes (touche aussi le joueur)
3. B : Arc, lance une flèche devant le personnage, avance jusqu'à toucher un mur ou un ennemi

## Structure du projet

- `src/` : Contient les fichiers source du projet
  - `core/` : Contient le core du jeu, indépendant de l'affichage
  - `include/` : Contient les headers du `core`
  - `txt/` : Contient la version textuelle du jeu
  - `sdl2/` : Contient la version sdl du jeu
- `data/` : Dossier pour stocker les images et autres ressources
- `doc/` : Documentation du projet, incluant un fichier Doxyfile pour la génération de documentation
- `bin/` : Dossier pour les exécutables compilés
- `build/` : Dossier pour les fichiers de compilation
- `external/` : Dossier contenant les lib externes

## Compilation et exécution

Le projet utilise CMake pour la compilation. Pour compiler le projet :

1. Créez un dossier de build : `mkdir build && cd build`
2. Générez les fichiers de compilation : `cmake ..`
3. Compilez le projet : `make`
4. Compilez la documentation : `make doc`

Les exécutables seront générés dans le dossier `bin/`.

## Utilisation

Après compilation, vous pouvez exécuter les différents programmes :

- `./bin/zelda_txt` : Pour lancer le jeu en version textuelle
- `./bin/zelda_sdl` : Pour exécuter le jeu en version sdl
- `./bin/test_regression` : Pour exécuter les tests de régression

Pour afficher la documentation :

- `firefox doc/html/index.html`

## Dépendances

- SDL2 pour l'affichage graphique
- CMake pour la compilation
