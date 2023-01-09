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

/**ReadELFTableSection
 * Paramètre : 
 * - un pointeur sur un fichier ELF
 * - un header ELF
 * - un tableau de sections
 * Résultat : lit la table des sections du fichier ELF en paramètre
 */
void ReadELFTableSections(FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable);

/**ReadELFRelocationTable
 * Paramètres :
 * - un pointeur sur un fichier ELF
 * - la table des entrées de réimplantation
 * - un header ELF
 * - un tableau des headers de section
 * - la table des symboles
 * Résultat : affiche sur la sortie standard le contenu des tables de réimplantation
 */
void ReadELFRelocationTable(FILE *file, Elf32_Rel **relTables, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, Elf32_Sym *symTable);


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

/**ReadELFTableSymbols
 * Paramètres :
 * - un pointeur sur un fichier ELF
 * - la table des symboles dans laquelle écrire les données
 * - le header de la table des symboles
 * Résultat : lit la table des symboles du fichier ELF et l'écrit dans la table des symboles donnée
 */
void ReadELFTableSymbols(FILE *file, Elf32_Sym *symTable, Elf32_Shdr sh_symtab);

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

/**PrintELFRelocationTable
 * Paramètres :
 * - un pointeur sur un fichier ELF
 * - un header ELF
 * - un tableau des headers de section
 * - la table des symboles
 * - la table des entrées de réimplantation
 * Résultat : affiche sur la sortie standard le contenu des tables de réimplantation
 */
void PrintELFRelocationTable(FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, Elf32_Sym *symTable, Elf32_Rel **relTables);


/**LinkELFRenumSections
 * Paramètres :
 * - un premier pointeur sur un fichier ELF
 * - un second pointeur sur un fichier ELF
 * - un pointeur sur le fichier de sortie de la fusion
 * Résultat : affiche dans le fichier de sortie la fusion et renumerotation des sections des 2 fichiers ELF d'entree
 */
void LinkELFRenumSections(FILE *input1, FILE *input2, FILE *output);

/**LinkELFSymbols
 * Paramètres:
 * - un premier pointeur sur un fichier ELF ouvert en mode lecture
 * - un second pointeur sur un fichier ELF ouvert en mode lecture
 * - un pointeur sur le fichier de sortie de la fusion ouvert en écriture
 * Résultat: écrit dans le fichier de sortie la fusion et renumérotation des tables des symboles des 2 fichiers ELF en entrée
 */
void LinkELFSymbols(FILE* input1, FILE* input2, FILE* output);