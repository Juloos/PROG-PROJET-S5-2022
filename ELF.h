#include <stdio.h>
#include <stdlib.h>
#include "/usr/include/elf.h"

#define STR_SIZE 256

/**ReadELFFile
 * Paramètres :
 * - un pointeur sur un fichier ELF
 * Résultat : lit et affiche sur la sortie standard le contenu du fichier ELF en paramètre
 */
void ReadELFFile(FILE *file);

/**ReadELFHeader
 * Paramètres :
 * - un pointeur sur un fichier ELF
 * - un header ELF
 * Résultat : lit et affiche sur la sortie standard l'en tête du fichier ELF en paramètre
 */
void ReadELFHeader(FILE *file, Elf32_Ehdr *ehdr);

/**create_ELFTableSection
 * Paramètres :
 * - un entier représentant le nombre de sections
 * Résultat : retourne un pointeur sur un tableau de sections initialiser
 */
Elf32_Shdr * create_ELFTableSection(int nbSection);

/**ReadELFTableSection
 * Paramètre : 
 * - un pointeur sur un fichier ELF
 * - un tableau de sections
 * - le nombre de sections
 * - l'offset de la table des sections, soit son emplacement dans le fichier ELF
 * Résultat : lit et affiche sur la sortie standard la table des sections du fichier ELF en paramètre
 */
void ReadELFTableSection(FILE *file, Elf32_Shdr *shdrTable, int nbSection, int offset);

/**ReadELFSection
 * Paramètres :
 * - un pointeur sur un fichier ELF
 * - un header ELF
 * - un tableau de sections
 * - le numéro de section à lire
 * Résultat : lit et affiche sur la sortie standard la section numéro numSection dans le fichier ELF en paramètre
 */
void ReadELFSectionNum(FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, int numSection);

/**ReadELFSection
 * Paramètres :
 * - un pointeur sur un fichier ELF
 * - un header ELF
 * - un tableau de sections
 * - le nom de section à lire
 * Résultat : lit et affiche sur la sortie standard la section nomSection dans le fichier ELF en paramètre
 */
void ReadELFSectionNom(FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, char *nomSection);

/**ReadELFTableSymbols
 * Paramètres :
 * - un pointeur sur un fichier ELF
 * Résultat : lit et affiche sur la sortie standard la table des symboles du fichier ELF en paramètre
 */
void ReadELFTableSymbols(FILE *file);

/**PrintELFTableSection
 * Paramètres :
 * - un pointeur sur un fichier ELF
 * - un header ELF
 * - un tableau des headers de section
 * Résultat : affiche sur la sortie standard le contenu du tableau de headers
 */
void PrintELFTableSection(FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable);
