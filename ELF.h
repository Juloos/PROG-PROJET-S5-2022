#include "utils.h"


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
 * - un header ELF
 * Résultat : retourne un pointeur sur un tableau de sections initialisé
 */
Elf32_Shdr *create_ELFTableSections(Elf32_Ehdr ehdr);

/**ReadELFTableSection
 * Paramètre : 
 * - un pointeur sur un fichier ELF
 * - un header ELF
 * - un tableau de sections
 * Résultat : lit la table des sections du fichier ELF en paramètre
 */
void ReadELFTableSections(FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable);

/**ReadELFSection
 * Paramètres :
 * - un pointeur sur un fichier ELF
 * - un header ELF
 * - un tableau de sections
 * - le numéro de section à lire
 * Résultat : lit la section numéro numSection dans le fichier ELF en paramètre
 */
void PrintELFSectionNum(FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, int numSection);

/**ReadELFSection
 * Paramètres :
 * - un pointeur sur un fichier ELF
 * - un header ELF
 * - un tableau de sections
 * - le nom de section à lire
 * Résultat : lit la section nomSection dans le fichier ELF en paramètre
 */
void PrintELFSectionNom(FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, char *nomSection);

/**create_ELFTableSymbols
 * Paramètres :
 * - la section symbol table
 * Résultat : retourne un pointeur sur un tableau de symboles initialisé
 */
Elf32_Sym *create_ELFTableSymbols(Elf32_Shdr sh_symtab);

/**ReadELFTableSymbols
 * Paramètres :
 * - un pointeur sur un fichier ELF
 * - la table des symboles dans laquelle écrire les données
 * - le header de la table des symboles
 * Résultat : lit la table des symboles du fichier ELF et l'écrit dans la table des symboles donnée
 */
void ReadELFTableSymbols(FILE *file, Elf32_Sym *symTable, Elf32_Shdr sh_symtab);

/**getSectionName
 * Paramètres :
 * - une chaine de caractères initialisée dans laquelle écrire le nom
 * - un pointeur sur un fichier ELF
 * - un header ELF
 * - un tableau de sections
 * - le numéro de la section dont on veut le nom
 * Résultat : le nom de la section (numéro numSection) est écrit dans la chaine de caractères donnée
 */
void getSectionName(char *name, FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, int numSection);

/**sectionName2Index
 * Paramètres :
 * - une chaine de caractères initialisée
 * - un pointeur sur un fichier ELF
 * - un header ELF
 * - un tableau de sections
 * Résultat : renvoie l'index de la section dont le nom est passé en paramètre
 */
int sectionName2Index(char *name, FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable);

/**getSymbolName
 * Paramètres :
 * - une chaine de caractères initialisée dans laquelle écrire le nom
 * - un pointeur sur un fichier ELF
 * - un header ELF
 * - un tableau de sections
 * - un élément de la table des symboles
 * Résultat : le nom de la section (numéro numSection) est écrit dans la chaine de caractères donnée
 */
void getSymbolName(char *name, FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, Elf32_Sym symEntry);

/**PrintELFHeader
 * Paramètres :
 * - un header ELF
 * Résultat: affiche les informations contenues dans le header
 */
void PrintELFHeader(Elf32_Ehdr ehdr);

/**PrintELFTableSection
 * Paramètres :
 * - un pointeur sur un fichier ELF
 * - un header ELF
 * - un tableau des headers de section
 * Résultat : affiche sur la sortie standard le contenu du tableau des sections
 */
void PrintELFTableSections(FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable);

/**PrintELFTableSymbols
 * Paramètres :
 * - un pointeur sur un fichier ELF
 * - un header ELF
 * - un tableau des headers de section
 * - la table des symboles
 * Résultat : affiche sur la sortie standard le contenu de la table des symboles
 */
void PrintELFTableSymbols(FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, Elf32_Sym *symTable);
