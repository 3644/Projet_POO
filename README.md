# Projet POO : Le Jeu de la Vie

---

## Principe
Le jeu de la vie est un automate cellulaire imaginé par le mathématicien John Conway. Il modélise l'évolution d'une population de cellules sur un intervalle de temps discret. Les cellules sont disposées dans une grille rectangulaire bidimensionnelle, où chaque cellule peut être vivante ou morte. En dehors des bordures, chaque cellule est entourée par 8 voisines directement adjacentes.

Pour passer de l'état à l'itération ‘t’ à celui de l'itération ‘t+1’, les règles suivantes s'appliquent :

- **Une cellule morte possédant exactement trois voisines vivantes devient vivante.**
- **Une cellule vivante possédant deux ou trois voisines vivantes reste vivante, sinon elle meurt.**

Ce projet implémente le jeu de la vie en C++ en utilisant les concepts de la programmation orientée objet (POO).

---

## Fonctionnalités

### Entrée utilisateur
Le programme consomme un fichier de configuration dont la première ligne spécifie la taille de la grille, suivie par une matrice d'état initial indiquant si chaque cellule est vivante (1) ou morte (0).

Exemple de fichier d'entrée :

```plaintext
5 10
0 0 1 0 0 0 0 0 0 0
0 0 0 1 0 0 0 0 0 0
0 1 1 1 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
```

### Simulation et Interface Graphique
- **Modes de fonctionnement** :
  1. **Mode Console** : Écrit l'état des cellules dans des fichiers à chaque itération pour un nombre donné d'itérations.
  2. **Mode Graphique** : Utilise la bibliothèque SFML pour afficher l'état de la grille de manière visuelle avec une simulation en temps réel.

- **Extensions possibles** :
  - **Grille Torique** : Les cellules des bords sont considérées adjacentes aux cellules du côté opposé, simulant une surface torique.
  - **Cellules Obstacles** : Introduction de cellules obstacle dont l'état reste constant pendant la simulation.
  - **Motifs pré-programmés** : Possibilité d'ajouter de nouveaux motifs à la grille pendant l'exécution à l'aide des touches du clavier.
  - **Parallélisation** : Améliorer la performance en parallélisant la mise à jour des états des cellules.

---



### Contrôle de la simulation
La simulation démarre automatiquement et affiche la grille à chaque itération.

---

## Architecture du Projet

- **`Grid.h` et `Grid.cpp`** : Définissent la classe `Grid` qui modélise la grille de cellules et implémente les méthodes pour l'évolution de la grille.
- **`main.cpp`** : Point d'entrée du programme, gère l'initialisation de la grille et la boucle de simulation.

---

## Diagrammes

Les diagrammes suivants ont été utilisés pour modéliser le projet :
- **Diagramme de cas d'utilisation** : Décrit les interactions possibles de l'utilisateur avec le programme.
- **Diagramme de classes** : Montre la structure des classes et leur relation.
- **Diagramme d'activité** : Modélise les différentes étapes de la simulation.
- **Diagramme de séquence** : Décrit l'ordre des opérations lors de l'exécution.

---


## Contribution

- Ce projet est réalisé en binôme avec YETBOII

