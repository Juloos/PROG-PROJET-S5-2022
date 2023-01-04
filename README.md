# PROG-PROJET-S5-2022
Projet de Programmation de 2022 à l'IM²AG


# Installation
Une fois le projet git cloné, executer les scripts shell `./setup` et `./compile`, ce dernier permet de générer
le fichier Makefile et de compiler le projet.


# Execution
Le programme `./oracle <fichiers>` permet de lancer une série de tests sur les fichiers passés en paramètre, ces 
fichiers doivent être au format ELF32 Big-Endian.

Le programme `./readELF <fichiers>` permet de lire les fichiers passés en paramètre, au format ELF32 Big-Endian de même,
et d'afficher le résultat de la lecture sur la sortie standard.
