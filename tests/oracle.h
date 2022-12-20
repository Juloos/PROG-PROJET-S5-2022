#include "/usr/include/elf.h"
#include "../ELF.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**lireNLignes
 * Paramètres:
 * - file: un pointeur sur un fichier en mode lecture
 * - n: un entier >= 0
 * Résultat: passe les n lignes suivants dans le fichier
 */
void passerNLignes(FILE *file, uint n);

/**lireLigne
 * Paramètres:
 * - file: un pointeur sur un fichier en mode lecture
 * - ligne: une chaine de caractères
 * - tailleLigne: la taille de ligne
 * Résultat: le contenu de la ligne lue dans le fichier est mis dans le paramètre ligne
 */
void lireLigne(FILE *file, char *ligne, size_t tailleLigne);

/**oracleEtape1
 * Paramètres:
 * - fileName : le nom du fichier utilisé pour le test doit être un fichier .o
 * Résultat: vérifie que la fonction readELFHeader retourne le même résultat que la commande readelf -h pour le fichier donnée en paramètre
 * affiche un message d'erreur si ce n'est pas le cas
 * sinon affiche sucess
 */
void oracleEtape1(char *fileName);