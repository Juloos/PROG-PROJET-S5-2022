#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/usr/include/elf.h"

#define STR_SIZE 256


/* IS_BIGENDIAN
 * Resultat : renvoie 1 si le systeme operand est au format Big Endian
 */
int IS_BIGENDIAN();


/* SWAPB
 * Parametres :
 *  - ptr : un pointeur
 *  - size : la taille pointee par ptr
 * Resultat : inverse l'ordre des octets de ptr
 */
void SWAPB(void *ptr, int size);


typedef struct {
    FILE *file;             // le fichier ELF (peut être NULL)
    Elf32_Ehdr ehdr;        // le header
    Elf32_Shdr *shdrTable;  // la table des sections
    int nbsh;               // le nombre de sections
    Elf32_Sym *symTable;    // la table des symboles
    int nbsym;              // le nombre de symboles
    Elf32_Rel **relTables;  // les tables de réimplantation
    int *relTable_sizes;    // les tailles de chaque table de réimplantation
} ELF;

ELF *create_ELF();

void free_ELF(ELF *elf);


/* create_ELFTableSections
 * Parametre :
 *  - ehdr : l'en-tete d'un fichier ELF
 * Resultat : alloue la memoire necessaire a la creation de la table des sections
 */
Elf32_Shdr *create_ELFTableSections(Elf32_Ehdr ehdr);


/* create_ELFTableSymbols
 * Parametre :
 *  - sh_symtab : le header de la table des symboles
 * Resultat : alloue la memoire necessaire a la creation de la table des symboles
 */
Elf32_Sym *create_ELFTableSymbols(Elf32_Shdr sh_symtab);


/* create_ELFTableRel
 * Parametre :
 *  - shdr : l'en-tete d'une section
 * Resultat : alloue la memoire necessaire a la creation de la table des relocations d'une section
 */
Elf32_Rel *create_ELFTableRel(Elf32_Shdr shdr);


/* create_ELFTablesRel
 * Parametre :
 *  - ehdr : l'en-tete d'un fichier ELF
 * Resultat : alloue la memoire necessaire a la creation de la table des relocations de toutes les sections concernees
 */
Elf32_Rel **create_ELFTablesRel(Elf32_Ehdr ehdr);


/* free_relTables
 * Parametres :
 *  - relTables : une table des tables des relocations
 *  - nbsh : le nombre de sections
 * Resultat : libere la memoire allouee aux tables des relocations
 */
void free_relTables(Elf32_Rel **relTables, uint nbsh);


/* getSectionContent
 * Parametres :
 *  - file : un pointeur sur un fichier ELF
 *  - shdr : l'en-tete d'une section
 * Resultat : alloue, ecrit et renvoie le contenue d'une section sous la forme d'un tableau d'octets
 */
uint8_t *getSectionContent(FILE *file, Elf32_Shdr shdr);


/* getHeaderClass
 * Parametres :
 *  - class : une chaine de caracteres initialisee dans laquelle mettre le resultat
 *  - ehdr : l'en-tete d'un fichier ELF
 * Resultat : la classe du fichier ELF est ecrit dans la chaine class
 */
void getHeaderClass(char *class, Elf32_Ehdr ehdr);


/* getHeaderData
 * Parametres :
 *  - data : une chaine de caracteres initialisee dans laquelle mettre le resultat
 *  - ehdr : l'en-tete d'un fichier ELF
 * Resultat : l'endianness et la complementarite du fichier ELF est ecrit dans la chaine data
 */
void getHeaderData(char *data, Elf32_Ehdr ehdr);


/* getHeaderOSABI
 * Parametres :
 *  - osabi : une chaine de caracteres initialisee dans laquelle mettre le resultat
 *  - ehdr : l'en-tete d'un fichier ELF
 * Resultat : l'architecture logicielle pour laquelle a ete concue le fichier ELF est ecrit dans la chaine osabi
 */
void getHeaderOSABI(char *osabi, Elf32_Ehdr ehdr);


/* getHeaderType
 * Parametres :
 *  - type : une chaine de caracteres initialisee dans laquelle mettre le resultat
 *  - ehdr : l'en-tete d'un fichier ELF
 * Resultat : le type du fichier ELF est ecrit dans la chaine type
 */
void getHeaderType(char *type, Elf32_Ehdr ehdr);


/* getHeaderMachine
 * Parametres :
 *  - machine : une chaine de caracteres initialisee dans laquelle mettre le resultat
 *  - ehdr : l'en-tete d'un fichier ELF
 * Resultat : l'architecture materielle pour laquelle a ete concue le fichier ELF est ecrit dans la chaine machine
 */
void getHeaderMachine(char *machine, Elf32_Ehdr ehdr);


/* getSectionName
 * Parametres :
 *  - name : une chaine de caracteres initialisee dans laquelle mettre le resultat
 *  - file : pointeur sur un fichier ELF
 *  - ehdr : l'en-tete d'un fichier ELF
 *  - shdrTable : la table des sections
 *  - numSection : le numero de la section recherchee
 * Resultat : le nom de la section est ecrit dans la chaine name
 */
void getSectionName(char *name, FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, int numSection);


/* getSectionName2Index
 * Parametres :
 *  - name : le nom de la section a chercher, chaine de caracteres
 *  - file : pointeur sur un fichier ELF
 *  - ehdr : l'en-tete d'un fichier ELF
 *  - shdrTable : la table des sections
 * Resultat : renvoie l'indice de la section portant le nom recherhe dans le fichier ELF
 */
int sectionName2Index(char *name, FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable);


/* getSectionType
 * Parametres :
 *  - type : une chaine de caracteres initialisee dans laquelle mettre le resultat
 *  - shdr : l'en-tete d'une section
 * Resultat : le type de la section est ecrit dans la chaine type
 */
void getSectionType(char *type, Elf32_Shdr shdr);


/* getSectionFlags
 * Parametres :
 *  - flags : une chaine de caracteres initialisee dans laquelle mettre le resultat
 *  - shdr : l'en-tete d'une section
 * Resultat : les flags de la section sont ecrits dans la chaine flags (des '-' remplacent les flags manquants)
 */
void getSectionFlags(char *flags, Elf32_Shdr shdr);


// Meme chose que getSectionFlags, avec les caracteres '-' en moins
void getSectionFlags2(char *flags, Elf32_Shdr shdr);


/* getSymbolName
 * Parametres :
 *  - name : une chaine de caracteres initialisee dans laquelle mettre le resultat
 *  - file : pointeur sur un fichier ELF
 *  - ehdr : l'en-tete d'un fichier ELF
 *  - shdrTable : la table des sections
 *  - symEntry : un symbole, de la table des symboles du fichier ELF
 * Resultat : le nom du symbole est ecrit dans la chaine name
 */
void getSymbolName(char *name, FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, Elf32_Sym symEntry);


/* getSymbolType
 * Parametres :
 *  - type : une chaine de caracteres initialisee dans laquelle mettre le resultat
 *  - symEntry : un symbole, de la table des symboles du fichier ELF
 * Resultat : le type du symbole est ecrit dans la chaine type
 */
void getSymbolType(char *type, Elf32_Sym symEntry);


/* Type2symType
 * Parametre :
 *  - type : le type d'un symbole sous la forme d'une chaine de caracteres
 * Resultat : renvoie la valeur correspondant au type
 */
unsigned char Type2symType(char *type);


/* Type2shType
 * Parametre :
 *  - type : le type d'une section sous la forme d'une chaine de caracteres
 * Resultat : renvoie la valeur correspondant au type
 */
Elf32_Word Type2shType(char *type);


/* getSymbolBind
 * Parametres :
 *  - bind : une chaine de caracteres initialisee dans laquelle mettre le resultat
 *  - symEntry : un symbole, de la table des symboles du fichier ELF
 * Resultat : la portee du symbole est ecrit dans la chaine bind
 */
void getSymbolBind(char *bind, Elf32_Sym symEntry);

/* Bind2SymBind
 * Parametre :
 *  - bind : la portee d'un symbole sous la forme d'une chaine de caracteres
 * Resultat : renvoie la valeur correspondant a la liaison
 */
unsigned char Bind2symBind(char *bind);


/* getSymBolVis
 * Parametres :
 *  - visibility : une chaine de caracteres initialisee dans laquelle mettre le resultat
 *  - symEntry : un symbole, de la table des symboles du fichier ELF
 * Resultat : la visibilite du symbole est ecrit dans la chaine visibility
 */
void getSymbolVis(char *visibility, Elf32_Sym symEntry);


/* Vis2symVis
 * Parametre :
 *  - vis : la visibilite d'un symbole sous la forme d'une chaine de caracteres
 * Resultat : renvoie la valeur correspondant a la visibilite
 */
unsigned char Vis2symVis(char *vis);


/* getSymBolNdx
 * Parametres :
 *  - ndx : une chaine de caracteres initialisee dans laquelle mettre le resultat
 *  - symEntry : un symbole, de la table des symboles du fichier ELF
 * Resultat : le ndx du symbole est ecrit dans la chaine ndx
 */
void getSymbolNdx(char *ndx, Elf32_Sym symEntry);

/* Ndx2symNdx
 * Parametre :
 *  - ndx : le ndx d'un symbole sous la forme d'une chaine de caracteres
 * Resultat : renvoie la valeur correspondant au ndx
 */
Elf32_Half Ndx2symNdx(char *ndx);


/* getRelType
 * Parametres :
 *  - type : une chaine de caracteres initialisee dans laquelle mettre le resultat
 *  - rel : une relocation, de la table des relocations d'une section
 * Resultat : le type de la relocation est ecrit dans la chaine type
 */
void getRelType(char *type, Elf32_Rel rel);


/* passerNLignes
 * Parametres :
 *  - file : un pointeur sur un fichier
 *  - n : un entier positif
 * Resultat : passe les n lignes suivants dans le fichier
 */
void passerNLignes(FILE *file, uint n);


typedef struct FusionELF_Etape6 {
    uint8_t **contents;  // tableux contenant les contenues des sections, de taille snb
    int *offsets;        // offsets de concatenation des sections PROGBITS du second fichier
    int *renum;          // renumerations des sections du second fichier
    int size;            // taille des tableaux offsets et renum
    int snb;             // nombre de sections apres fusion
} FusionELF_Etape6;

/* create_fusion6
 * Paramètres:
 * - elf1: un pointeur sur une structure ELF
 * - elf2: un pointeur sur une structure ELF
 * Résultat: retourne un pointeur sur une structure FusionELF_Etape6 contenant size sections
 */
FusionELF_Etape6 *create_fusion6(ELF *elf1, ELF *elf2);

/* free_fusion6
 * Paramètres:
 * - f: un pointeur non NULL sur une structure FusionELF_Etape6
 * Résultat: libère la mémoire allouée pour f
 */
void free_fusion6(FusionELF_Etape6 *f);


#endif