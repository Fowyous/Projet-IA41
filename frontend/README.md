# Rasende Roboter : prototype du frontend (Qt 6 / QML)

Prototype visuel avec des données factices. Il sert à valider le design avant de brancher le modèle C++ et les solveurs (Prolog / Python).

## Lancer (terminal)

```
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="C:/Qt/6.11.2/mingw_64"
cmake --build build
./build/appRasendeRoboter        (Windows : .\build\appRasendeRoboter.exe)
```

Adapter `CMAKE_PREFIX_PATH` à votre dossier Qt (celui qui contient `lib/cmake`).

## Structure

- `src/main.cpp` : démarre l'application et charge le module QML.
- `qml/Theme.qml` : toutes les couleurs, mode jour et mode nuit (un seul endroit).
- `qml/Textes.qml` : tous les textes en français et en anglais (aucun texte écrit en dur dans les écrans).
- `qml/Reglages.qml` : choix du joueur (solveur, force de l'IA, volume, langue).
- `qml/Main.qml` : fenêtre, barre du haut (bouton mode nuit), navigation entre écrans.
- `qml/Ecran*.qml` : les 5 écrans (menu, défis, paramètres, jeu, fin de manche).
- `qml/` (autres) : composants réutilisables (boutons, cartes, plateau, pions, sablier, panneau de recherche IA).

## Mode nuit

`Theme.sombre = true` recolore tout l'écran. Le choix est mémorisé entre deux lancements.
