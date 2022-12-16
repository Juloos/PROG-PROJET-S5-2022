#include <stdio.h>
#include <stdlib.h>
#include "/usr/include/elf.h"

#define STR_SIZE 256

/**ReadELFFile
 * Paramètres :
 * - un pointeur sur un fichier ELF
 * Résultat : lit le contenu du fichier ELF en paramètre
 */
void ReadELFFile(FILE *file);

/**ReadELFHeader
 * Paramètres :
 * - un pointeur sur un fichier ELF
 * - un header ELF
 * Résultat : lit l'en tête du fichier ELF en paramètre
 */
void ReadELFHeader(FILE *file, Elf32_Ehdr *ehdr);

/**create_ELFTableSection
 * Paramètres :
 * - un entier représentant le nombre de sections
 * Résultat : retourne un pointeur sur un tableau de sections initialisé
 */
Elf32_Shdr * create_ELFTableSections(int nbSection);

/**ReadELFTableSection
 * Paramètre : 
 * - un pointeur sur un fichier ELF
 * - un tableau de sections
 * - le nombre de sections
 * - l'offset de la table des sections, soit son emplacement dans le fichier ELF
 * Résultat : lit la table des sections du fichier ELF en paramètre
 */
void ReadELFTableSections(FILE *file, Elf32_Shdr *shdrTable, int nbSection, int offset);

/**sectionName2Index
 * Paramètres :
 * - une chaine de caractères initialisée
 * - un pointeur sur un fichier ELF
 * - un header ELF
 * - un tableau de sections
 * Résultat : renvoie l'index de la section dont le nom est passé en paramètre
 */
int sectionName2Index(char *name, FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable);

/**ReadELFSection
 * Paramètres :
 * - un pointeur sur un fichier ELF
 * - un header ELF
 * - un tableau de sections
 * - le numéro de section à lire
 * Résultat : lit la section numéro numSection dans le fichier ELF en paramètre
 */
void ReadELFSectionNum(FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, int numSection);

/**ReadELFSection
 * Paramètres :
 * - un pointeur sur un fichier ELF
 * - un header ELF
 * - un tableau de sections
 * - le nom de section à lire
 * Résultat : lit la section nomSection dans le fichier ELF en paramètre
 */
void ReadELFSectionNom(FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, char *nomSection);

/**create_ELFTableSymbols
 * Paramètres :
 * - la section symbol table
 * Résultat : retourne un pointeur sur un tableau de symboles initialisé
 */
Elf32_Sym * create_ELFTableSymbols(Elf32_Shdr sh_symtab);

/**ReadELFTableSymbols
 * Paramètres :
 * - un pointeur sur un fichier ELF
 * - la table des symboles dans laquelle écrire les données
 * - le header de la table des symboles
 * Résultat : lit la table des symboles du fichier ELF en paramètre
 */
void ReadELFTableSymbols(FILE *file, Elf32_Sym *symTable, Elf32_Shdr sh_symtab);

/**PrintELFTableSection
 * Paramètres :
 * - un pointeur sur un fichier ELF
 * - un header ELF
 * - un tableau des headers de section
 * Résultat : affiche sur la sortie standard le contenu du tableau des sections
 */
void PrintELFTableSections(FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable);
