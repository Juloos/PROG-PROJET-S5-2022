#include "utils.h"


/* ReadELFFile
 * Parametres :
 * - un pointeur sur un fichier ELF
 * Resultat : lit le contenu du fichier ELF en parametre
 */
void ReadELFFile(FILE *file);

/* ReadELFHeader
 * Parametres :
 *  - file : un pointeur sur un fichier ELF
 *  - ehdr : un pointeur sur l'en-tete d'un fichier ELF
 * Resultat : lit l'en-tete du fichier ELF et l'ecrit dans ehdr
 */
void ReadELFHeader(FILE *file, Elf32_Ehdr *ehdr);

/* ReadELFTableSection
 * Parametre : 
 *  - file : un pointeur sur un fichier ELF
 *  - ehdr : l'en-tete du fichier ELF
 *  - shdrTable : une table des sections initialisee
 * Resultat : lit la table des sections du fichier ELF et l'ecrit dans shdrTable
 */
void ReadELFTableSections(FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable);

/* ReadELFTableSymbols
 * Parametres :
 *  - file : un pointeur sur un fichier ELF
 *  - symTable : une table des symboles initialisee
 *  - sh_symtab : la section contenant la table des symboles du fichier ELF
 * Resultat : lit la table des symboles du fichier ELF et l'ecrit dans symTable
 */
void ReadELFTableSymbols(FILE *file, Elf32_Sym *symTable, Elf32_Shdr sh_symtab);

/* ReadELFRelocationTable
 * Parametres :
 *  - file : un pointeur sur un fichier ELF
 *  - relTables : une table des tables de relocations initialisee
 *  - ehdr : l'en-tete du fichier ELF
 *  - shdrTable : la table des sections du fichier ELF
 *  - symTable : la table des symboles du fichier ELF
 * Resultat : lit la table des relocations du fichier ELF et l'ecrit dans relTables
 */
void ReadELFRelocationTable(FILE *file, Elf32_Rel **relTables, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, Elf32_Sym *symTable);


/* PrintELFHeader
 * Parametres :
 *  - ehdr : l'en-tete d'un fichier ELF
 * Resultat : affiche l'en-tete du fichier ELF
 */
void PrintELFHeader(Elf32_Ehdr ehdr);

/* PrintELFTableSection
 * Parametres :
 *  - file : un pointeur sur un fichier ELF
 *  - ehdr : l'en-tete du fichier ELF
 *  - shdrTable : la table des sections du fichier ELF
 * Resultat : affiche la table des sections du fichier ELF
 */
void PrintELFTableSections(FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable);

/* ReadELFSection
 * Parametres :
 *  - file : un pointeur sur un fichier ELF
 *  - ehdr : l'en-tete du fichier ELF
 *  - shdrTable : la table des sections du fichier ELF
 * - le numero de section a lire
 * Resultat : affiche le contenu de la section numero sectionNumber du fichier ELF
 */
void PrintELFSectionNum(FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, int numSection);

/* ReadELFSection
 * Parametres :
 *  - file : un pointeur sur un fichier ELF
 *  - ehdr : l'en-tete du fichier ELF
 *  - shdrTable : la table des sections du fichier ELF
 *  - nomSection : le nom d'une section
 * Resultat : affiche le contenu de la section nomSection du fichier ELF
 */
void PrintELFSectionNom(FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, char *nomSection);

/* PrintELFTableSymbols
 * Parametres :
 *  - file : un pointeur sur un fichier ELF
 *  - ehdr : l'en-tete du fichier ELF
 *  - shdrTable : la table des sections du fichier ELF
 *  - symTable : la table des symboles du fichier ELF
 * Resultat : affiche la table des symboles du fichier ELF
 */
void PrintELFTableSymbols(FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, Elf32_Sym *symTable);

/* PrintELFRelocationTable
 * Parametres :
 *  - file : un pointeur sur un fichier ELF
 *  - ehdr : l'en-tete du fichier ELF
 *  - shdrTable : la table des sections du fichier ELF
 *  - symTable : la table des symboles du fichier ELF
 *  - relTables : la table des tables de relocation du fichier ELF
 * Resultat : affiche la tables des relocations du fichier ELF
 */
void PrintELFRelocationTable(FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, Elf32_Sym *symTable, Elf32_Rel **relTables);


/* LinkELFRenumSections
 * Parametres :
 *  - input1 : un premier pointeur sur un fichier ELF
 *  - input2 : un second pointeur sur un fichier ELF
 *  - output : un pointeur sur le fichier de sortie de la fusion
 * Resultat : fusionne les deux fichiers ELF en parametre et ecrit le resultat dans output, affiche les sections renumerotees
 */
void LinkELFRenumSections(FILE *input1, FILE *input2, FILE *output);
