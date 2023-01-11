# PROG-PROJET-S5-2022
Projet de Programmation de 2022 à l'IM²AG. Auteurs :
- Romain ALVES
- Romain BOSSY
- Victoria FIORI
- Lancelin FOUSSADIER
- Jules SEBAN


# Installation
Une fois le projet git cloné, executer les scripts shell `./setup` et `./compile`, ce dernier permet de générer
le fichier Makefile et de compiler le projet. Vous pourrez tester l'ensemble du projet avec `./test_all.sh`


# Execution
Le programme `./oracle <fichiers>` permet de lancer une série de tests sur les fichiers passés en paramètre, ces 
fichiers doivent être au format ELF32 Big-Endian. Ne mettre que 2 fichiers en arguments lancera en plus une batterie de
tests pour la Partie 2 sur la fusion.

Le programme `./readELF [-options] <fichiers>` permet de lire les fichiers passés en paramètre, au format ELF32 Big-Endian de même,
et d'afficher le résultat de la lecture sur la sortie standard. Il prend en compte les mêmes options que la commande
`readelf` pour les parties de l'éditeur de liens concernées par le projet.

Le programme `./linkELF <fichier 1> <fichier 2> <fichier sortie>` permet de fusionner les 2 premiers fichiers au format
ELF et d'écrire le résultat, au format ELF aussi, dans le fichier de sortie donné.
Ce progamme est incomplet.