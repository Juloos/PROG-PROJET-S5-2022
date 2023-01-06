#include "ELF.h"

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

/**oracleEtape3
 * Paramètres:
 * - fileName : le nom du fichier utilisé pour le test doit être un fichier .o
 * - nomSection: le nom de la section à lire
 * Résultat: vérifie que la fonction readELFTableSections retourne le même résultat que la commande readelf -S pour le fichier donnée en paramètre
 * affiche un message d'erreur si ce n'est pas le cas
 * sinon affiche sucess
 */
void oracleEtape3 (char *filename);

/**oracleEtape4
 * Paramètres:
 * - fileName : le nom du fichier utilisé pour le test doit être un fichier .o
 * Résultat: vérifie que la fonction ReadELFTableSymbols retourne le même résultat que la commande readelf -s
 *           pour le fichier donnée en paramètre.
 * Affiche un message d'erreur si ce n'est pas le cas.
 * sinon affiche succes
 */
void oracleEtape4(char *filename);

/**oracleEtape6
 * Paramètres:
 * - filename1 : le nom du premier fichier utilisé pour le test doit être un fichier .o
 * - filename2 : le nom du deuxième fichier utilisé pour le test doit être un fichier .o
 * Résultat: vérifie que la fonction LinkELFRenumSections fonctionne correctement
 * Affiche un message d'erreur en cas d'échec
 * Sinon affiche Succès
 */
void oracleEtape6(char* filename1, char* filename2);

typedef struct RelocationSection {
    char* name;
    int offset;
    char** inputs;
} RelocationSection;