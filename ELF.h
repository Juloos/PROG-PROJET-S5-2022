#include <stdio.h>

#define EI_NIDENT 16

/**ReadELFFile
 * Paramètres :
 * - un pointeur sur un fichier ELF
 * Résultat : lit et affiche sur la sortie standard le contenu du fichier ELF en paramètre
*/
void ReadELFFile(FILE* file);

/**ReadELFHeader
 * Paramètres :
 * - un pointeur sur un fichier ELF
 * Résultat : lit et affiche sur la sortie standard l'en tête du fichier ELF en paramètre
*/
void ReadELFHeader(FILE* file);

/**ReadELFTableSection
 * Paramètre : 
 * - un pointeur sur un fichier ELF
 * Résultat : lit et affiche sur la sortie standard la table des sections du fichier ELF en paramètre
*/
void ReadELFTableSection(FILE* file);

/**ReadELFSection
 * Paramètres :
 * - un pointeur sur un fichier ELF
 * - le numéro de la section à afficher
 * Résultat : lit et affiche sur la sortie standard la section numéro numSection dans le fichier ELF en paramètre
*/
void ReadELFSectionNum(FILE* file, int numSection);

/**ReadELFSection
 * Paramètres :
 * - un pointeur sur un fichier ELF
 * - le numéro de la section à afficher
 * Résultat : lit et affiche sur la sortie standard la section nomSection dans le fichier ELF en paramètre
*/
void ReadELFSectionNom(FILE* file, char* nomSection);

/**ReadELFTableSymbols
 * Paramètres :
 * - un pointeur sur un fichier ELF
 * Résultat : lit et affiche sur la sortie standard la table des symboles du fichier ELF en paramètre
*/
void ReadELFTableSymbols(FILE* file);