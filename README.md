# initC_V1
(compatible Windows uniquement)


## Description
**initC_V1** est un programme pour Windows en langage C permettant de créer rapidement la structure d'un projet console en C. Il automatise la création des dossiers et fichiers nécessaires, avec un code de base prérempli.

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
1. Télécharge le programme sous forme de fichier ZIP. https://github.com/yaya66659/InitC_V1/blob/main/InitC_V1.7z
2. Décompresse le dossier ZIP.
3. Double-clique sur `InitC_V1.exe` pour l'exécuter.
4. Puis, suis les instructions pour créer un nouveau projet.

### Compilation
Utilise `gcc` pour compiler le programme :
```sh
cd mon_chemmin_ver_le_dossier/InitC_V1
gcc -o bin/initC_V1 src/*.c
```
Ou avec le Makefile :
```sh
make all
```
#Pour nettoyer le dossier obj (efface tout les fichier object)
```sh
make clean
```
#Pour nettoyer tout (le fichier .o et l'executable)
```sh
make cleanall
```

### Utilisation (compatible Windows uniquement)
Exécute simplement le programme :
```sh
bin\initC_V1.exe
```
Puis, suis les instructions pour créer un nouveau projet.

## 📩 Contact
Si vous avez des suggestions ou des retours, contactez-moi sur **[GitHub Issues](https://github.com/yaya66659/BlocKeyboard/issues)** ou par mail : **yann55446@gmail.com**.  


## 📜 Licence

Ce projet est sous licence **GNU General Public License v3.0 (GPL v3)**.  
Vous êtes libre de l’utiliser, le modifier et le redistribuer sous les termes de cette licence.  

📌 **Résumé des conditions principales** :
- Vous **pouvez modifier** et redistribuer le programme.
- Toute version modifiée **doit rester sous GPL v3**.
- Ce programme est fourni **"tel quel", sans garantie**.  

🔗 Texte complet de la licence : [LICENSE](LICENSE)  
🔗 Plus d’informations : [https://www.gnu.org/licenses/gpl-3.0.html](https://www.gnu.org/licenses/gpl-3.0.html)  

## Auteur
Développé par **yann PICHAT**.

