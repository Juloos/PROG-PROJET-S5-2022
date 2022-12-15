#include <stdio.h>
#include <stdlib.h>
#include "/usr/include/elf.h"

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
void ReadELFHeader(FILE* file, Elf32_Ehdr* header);


/**create_ELFTableSection
 * Paramètres :
 * - un entier représentant le nombre de sections
 * Résultat : retourne un pointeur sur un tableau de sections initialiser
*/
Elf32_Shdr * create_ELFTableSection(int nbSection);

/**ReadELFTableSection
 * Paramètre : 
 * - un pointeur sur un fichier ELF
 * Résultat : lit et affiche sur la sortie standard la table des sections du fichier ELF en paramètre
*/
void ReadELFTableSection(FILE* file, Elf32_Shdr* tableSection, int nbSection);

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