#include "ELF.h"


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
 * Résultat: vérifie que la fonction ReadELFHeader retourne le même résultat que la commande readelf -h
 *           pour le fichier donnée en paramètre.
 * Affiche un message d'erreur si ce n'est pas le cas
 * sinon affiche succes
 */
void oracleEtape1(char *filename);

/**oracleEtape2
 * Paramètres:
 * - fileName : le nom du fichier utilisé pour le test doit être un fichier .o
 * Résultat: vérifie que la fonction ReadELFTableSections retourne le même résultat que la commande readelf -S
 *           pour le fichier donnée en paramètre.
 * Affiche un message d'erreur si ce n'est pas le cas.
 * sinon affiche succes
 */
void oracleEtape2(char *filename);

/**oracleEtape4
 * Paramètres:
 * - fileName : le nom du fichier utilisé pour le test doit être un fichier .o
 * Résultat: vérifie que la fonction ReadELFTableSymbols retourne le même résultat que la commande readelf -s
 *           pour le fichier donnée en paramètre.
 * Affiche un message d'erreur si ce n'est pas le cas.
 * sinon affiche succes
 */
void oracleEtape4(char *filename);