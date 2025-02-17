# initC_V1

## Description
**initC_V1** est un programme en langage C permettant de créer rapidement la structure d'un projet console en C. Il automatise la création des dossiers et fichiers nécessaires, avec un code de base prérempli.

## Fonctionnalités
- Demande le nom du projet.
- Génération automatique d'un `Makefile`.
- Création automatique de l'arborescence suivante :
  ```
  projets/
  ├── [nom_du_projet]/
      ├── bin/       # Contient l'exécutable
      ├── src/       # Contient les fichiers source .c
          ├── main.c
          ├── fct.c
      ├── headers/   # Contient les fichiers d'en-tête .h
          ├── fct.h
      ├── Makefile   # Fichier Makefile généré automatiquement
  ```
- Préremplit les fichiers `.c` et `.h` avec le code minimal obligatoire.
- Ouvre automatiquement le projet dans Visual Studio Code après sa création.

## Installation
### Téléchargement et Exécution
1. Télécharge le programme sous forme de fichier ZIP.
2. Décompresse le dossier ZIP.
3. Double-clique sur `InitC_V1.exe` pour l'exécuter.

### Compilation
Utilise `gcc` pour compiler le programme :
```sh
gcc -o initC_V1 initC_V1.c
```

### Utilisation
Exécute simplement le programme :
```sh
./initC_V1
```
Puis, suis les instructions pour créer un nouveau projet.

## Licence
Ce projet est sous licence MIT. Tu es libre de l'utiliser et de le modifier.

## Auteur
Développé par **yann PICHAT**.

