#ifndef ELF_H
#define ELF_H

#include "utils.h"


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
 *  - elf : un pointeur sur une structure ELF
 * Resultat : lit l'en-tete du fichier ELF et l'ecrit dans le champ ehdr de la structure ELF
 */
void ReadELFHeader(ELF *elf);

/* ReadELFTableSection
 * Parametre :
 *  - elf : un pointeur sur une structure ELF
 * Resultat : lit la table des sections du fichier ELF et l'ecrit dans le champ shdrTable de la structure ELF
 */
void ReadELFTableSections(ELF *elf);

/* ReadELFTableSymbols
 * Parametres :
 *  - elf : un pointeur sur une structure ELF
 * Resultat : lit la table des symboles du fichier ELF et l'ecrit dans le champ symTable de la structure ELF
 */
void ReadELFTableSymbols(ELF *elf);

/* ReadELFRelocationTable
 * Parametres :
 *  - elf : un pointeur sur une structure ELF
 * Resultat : lit la table des relocations du fichier ELF et l'ecrit dans le champ relTables de la structure ELF
 */
void ReadELFRelocationTable(ELF *elf);


/* PrintELFHeader
 * Parametres :
 *  - elf : un pointeur sur une structure ELF
 * Resultat : affiche l'en-tete du fichier ELF
 */
void PrintELFHeader(ELF *elf);

/* PrintELFTableSection
 * Parametres :
 *  - elf : un pointeur sur une structure ELF
 * Resultat : affiche la table des sections du fichier ELF
 */
void PrintELFTableSections(ELF *elf);

/* ReadELFSection
 * Parametres :
 *  - elf : un pointeur sur une structure ELF
 *  - le numero de section a lire
 * Resultat : affiche le contenu de la section numero sectionNumber du fichier ELF
 */
void PrintELFSectionNum(ELF *elf, int numSection);

/* ReadELFSection
 * Parametres :
 *  - elf : un pointeur sur une structure ELF
 *  - nomSection : le nom d'une section
 * Resultat : affiche le contenu de la section nomSection du fichier ELF
 */
void PrintELFSectionNom(ELF *elf, char *nomSection);

/* PrintELFTableSymbols
 * Parametres :
 *  - elf : un pointeur sur une structure ELF
 * Resultat : affiche la table des symboles du fichier ELF
 */
void PrintELFTableSymbols(ELF *elf);

/* PrintELFRelocationTable
 * Parametres :
 *  - elf : un pointeur sur une structure ELF
 * Resultat : affiche la tables des relocations du fichier ELF
 */
void PrintELFRelocationTable(ELF *elf);


/* LinkELFRenumSections
 * Parametres :
 *  - elf1 : un pointeur sur une premiere structure ELF
 *  - elf2 : un pointeur sur une seconde structure ELF
 *  - output : un pointeur sur le fichier de sortie de la fusion
 * Resultat : fusionne les deux ELF en parametre et ecrit le resultat dans output, renvoie les offsets de
 *             concatenation et les renumerotations des sections de elf2
 */
FusionELF_Etape6 *LinkELFRenumSections(ELF *elf1, ELF *elf2, FILE *output);

/* LinkELFSymbols
 * Parametres:
 *  - elf1 : un pointeur sur une premiere structure ELF
 *  - elf2 : un pointeur sur une seconde structure ELF
 *  - le resultat de la fusion et renumerotations des sections
 * Resultat: renvoie la table des symboles fusionnee des 2 ELF en parametre
 */
ELF *LinkELFSymbols(ELF *elf1, ELF *elf2, FusionELF_Etape6 *fusion6);

#endif