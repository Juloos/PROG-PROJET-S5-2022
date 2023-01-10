#ifndef ELF_H
#define ELF_H

#include "utils.h"

typedef struct ELFSymbsTable {
    int nbElems;
    Elf32_Sym* symbols;
} SymbolsTable;

typedef struct {
    FILE *file;
    Elf32_Ehdr ehdr;
    Elf32_Shdr *shdrTable;
    int nbsh;
    Elf32_Sym *symTable;
    int nbsym;
    Elf32_Rel **relTables;
    int *relTable_sizes;
} ELF;

void free_ELF(ELF *elf);

/* ReadELFFile
 * Parametres :
 * - un pointeur sur un fichier ELF
 * Resultat : lit le contenu du fichier ELF en parametre et renvoie un pointeur sur l'ensemble de ce qui a ete lu
 */
ELF *ReadELF(FILE *file);

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
 *  - ehdr1 : l'en-tete du premier fichier ELF
 *  - ehdr2 : l'en-tete du second fichier ELF
 *  - shdrTable1 : la table des sections du premier fichier ELF
 *  - shdrTable2 : la table des sections du second fichier ELF
 * Resultat : fusionne les deux fichiers ELF en parametre et ecrit le resultat dans output, renvoie les offsets de
 *             concatenation et les renumerotations des sections de input2
 */
FusionELF_Etape6 *LinkELFRenumSections(FILE *input1, FILE *input2, FILE *output, Elf32_Ehdr ehdr1, Elf32_Ehdr ehdr2, Elf32_Shdr *shdrTable1, Elf32_Shdr *shdrTable2);

/* LinkELFSymbols
 * Paramètres:
 * - un premier pointeur sur un fichier ELF
 * - un second pointeur sur un fichier
 * - un pointeur sur les sections fusionnées et renumérotées des deux fichiers en entrée
 * Résultat: ecrit dans le fichier de sortie la fusion et renumerotation des tables des symboles des 2 fichiers ELF
 *            en entree
 */
SymbolsTable* LinkELFSymbols(FILE* input1, FILE* input2, FusionELF_Etape6* sections);

/**GetSymbolsTable
 * Paramètres :
 * - input : un fichier ELF ouvert en mode lecture
 * Résultat : retourne un pointeur sur une structure SymbolsTable
 * Effet de bord : alloue de la mémoire dynamiquement, il faut ensuite la libérée manuellement
 */
SymbolsTable* GetSymbolsTable(FILE* input);

/**WriteELFFile
 * Paramètres:
 * - le nom du fichier dans lequel écrire
 * - le contenu au format ELF à écrire dans le fichier
 * Résultat: écrit le contenu au format ELF dans le fichier en paramètre
 */
void WriteELFFile(char *filename, ELF file);

#endif