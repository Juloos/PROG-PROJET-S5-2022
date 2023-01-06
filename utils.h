#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/usr/include/elf.h"

#define STR_SIZE 256

/* IS_BIGENDIAN
 * Résultat : Vérifie *...* bien au format Big Endian
 */
int IS_BIGENDIAN();


/* SWAPB
 * Paramètres :
 *  - ptr : un pointeur
 *  - size : un taille
 * Résultat : Change le format en Big Endian si ce n'est pas déjà le cas
 */
void SWAPB(void *ptr, int size);


/* create_ELFTableSections
 * Paramètre :
 *  - ehdr : un header ELF
 * Résultat : Alloue la mémoire nécessaire pour pouvoir afficher par la suite la table des sections d'un fichier ELF
 */
Elf32_Shdr *create_ELFTableSections(Elf32_Ehdr ehdr);


/* create_ELFTableSymbols
 * Paramètre :
 *  - sh_symtab : le header de la table des symboles
 * Résultat : Alloue la mémoire nécessaire pour pouvoir afficher par la suite la table des symboles d'un fichier ELF
 */
Elf32_Sym *create_ELFTableSymbols(Elf32_Shdr sh_symtab);


/* create_ELFTableRel
 * Paramètre :
 *  - shdr : Une section
 * Résultat : Alloue la mémoire nécessaire pour pouvoir afficher par la suite les tables des réimplantations d'un fichier ELF
 */
Elf32_Rel *create_ELFTableRel(Elf32_Shdr shdr);

Elf32_Rel *create_ELFTableRel(Elf32_Shdr shdr);

Elf32_Rel *create_ELFTableRel(Elf32_Shdr shdr);


/* create_ELFTablesRel
 * Paramètre :
 *  - ehdr : un header ELF
 * Résultat :
 */
Elf32_Rel **create_ELFTablesRel(Elf32_Ehdr ehdr);


/* getSectionContent
 * Paramètres :
 *  - file : un pointeur sur un fichier ELF
 *  - shdr : une section
 * Résultat : Permet de récupérer le contenu d'une section
 */
uint8_t *getSectionContent(FILE *file, Elf32_Shdr shdr);


/* getHeaderClass
 * Paramètres :
 *  - class : un pointeur sur class
 *  - ehdr : un header ELF
 * Résultat : Permet d'obtenir la capacité d'un fichier ELF
 *  - invalide si ELFNONE
 *  - 32 bits si ELF32
 *  - 64 bits si ELF64
 */
void getHeaderClass(char *class, Elf32_Ehdr ehdr);


/* getHeaderData
 * Paramètres :
 *  - data : un pointeur sur data
 *  - ehdr : un header ELF
 * Résultat : Permet d'obtenir la spécification d'encodage d'un fichier ELF
 *  - invalide
 *  - Little endian
 *  - Big endian
 */
void getHeaderData(char *data, Elf32_Ehdr ehdr);


/* getHeaderOSABI
 * Paramètres :
 *  - osabi : un pointeur sur osabi
 *  - ehdr : un header ELF
 * Résultat : Permet de connaitre (pas trop compris ce que ça fait, obtenir le type de systeme d'exploitation necessaire?)
 */
void getHeaderOSABI(char *osabi, Elf32_Ehdr ehdr);


/* getHeaderType
 * Paramètres :
 *  - type : un pointeur sur type
 *  - ehdr : un header ELF
 * Résultat : Permet d'obtenir le type d'un fichier ELF
 *              (ennumerer tout les type possible ?)
 */
void getHeaderType(char *type, Elf32_Ehdr ehdr);


/* getHeaderMachine
 * Paramètres :
 *  - machine : un pointeur sur machine
 *  - ehdr : un header ELF
 * Résultat : Permet de connaitre l'architecture necessaire d'un fichier ELF
 */
void getHeaderMachine(char *machine, Elf32_Ehdr ehdr);


/* getSectionName
 * Paramètres :
 *  - name :
 *  - file : pointeur sur un fichier ELF
 *  - ehdr : un header ELF
 *  - shdrTable : un tableau de sections
 *  - numSection : un entier définissant le numéro de la section
 * Résultat : Obtenir le nom de la section voulue
 */
void getSectionName(char *name, FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, int numSection);


/* getSectionName2Index
 * Paramètres :
 *  - name :
 *  - file : pointeur sur un fichier ELF
 *  - ehdr : un header ELF
 *  - shdrTable : un tableau de sections
 * Résultat : Obtenir l'indice du nom de la section voulue
 */
int sectionName2Index(char *name, FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable);


/* getSectionType
 * Paramètres :
 *  - type : pointeur sur le type de section
 *  - shdr : Une section
 * Résultat : Obtenir le type de la section voulue
 */
void getSectionType(char *type, Elf32_Shdr shdr);


/* getSectionFlags
 * Paramètres :
 *  - flags : pointeur sur les flags de section
 *  - shdr : Une section
 * Résultat : Obtenir le flag de la section voulue
 */
void getSectionFlags(char *flags, Elf32_Shdr shdr);


/* getSectionFlags2
 * Paramètres :
 *  - flags : pointeur sur les flags de section
 *  - shdr : Une section
 * Résultat : Obtenir le second flag de la section voulue
 */
void getSectionFlags2(char *flags, Elf32_Shdr shdr);


/* getSymbolName
 * Paramètres :
 *  - name : pointeur
 *  - file : pointeur sur un fichier ELF
 *  - ehdr : un header ELF
 *  - shdrTable : un tableau de sections
 *  - symEntry :
 * Résultat : Obtenir le nom de la table des symboles
 */
void getSymbolName(char *name, FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, Elf32_Sym symEntry);


/* getSymbolType
 * Paramètres :
 *  - type : pointeur sur la partie du type de la table des symboles
 *  - symEntry :
 * Résultat : Obtenir le type de la table des symboles
 */
void getSymbolType(char *type, Elf32_Sym symEntry);


/* Type2symType
 * Paramètre :
 *  - type : pointeur sur la partie du type de la table des symboles
 * Résultat : Fournit le type de symbole nécessaire à l'édition de liens
 */
unsigned char Type2symType(char *type);


/* Type2shType
 * Paramètre :
 *  - type : pointeur sur la partie du type de la table des sections
 * Résultat : Fournit le type de la section nécessaire à l'édition de liens
 */
Elf32_Word Type2shType(char *type);


/* getSymbolBind
 * Paramètres :
 *  - bind : pointeur sur la partie bind de la table des symboles
 *  - symEntry :
 * Résultat :
 */
void getSymbolBind(char *bind, Elf32_Sym symEntry);


/* Bind2SymBind
 * Paramètre :
 *  - bind : pointeur sur la partie bind de la table des symboles
 * Résultat : Obtenir le type de liaison (?)
 */
unsigned char Bind2symBind(char *bind);


/* getSymBolVis ?
 * Paramètres :
 *  - visibility :
 *  - symEntry :
 * Résultat :
 */
void getSymbolVis(char *visibility, Elf32_Sym symEntry);


/* Vis2symVis ?
 * Paramètre :
 *  - vis :
 * Résultat :
 */
unsigned char Vis2symVis(char *vis);


/* getSymBolNdx
 * Paramètres :
 *  - ndx : pointeur sur l'indice de section (moyen sûre)
 *  - symEntry :
 * Résultat :
 */
void getSymbolNdx(char *ndx, Elf32_Sym symEntry);


/* Ndx2symNdx
 * Paramètre :
 *  - ndx : pointeur sur l'indice de section
 * Résultat :
 */
Elf32_Half Ndx2symNdx(char *ndx);


/* getSymType
 * Paramètres :
 *  - type :
 *  - rel :
 * Résultat :
 */
void getSymType(char *type, Elf32_Rel rel);


/* getRelType
 * Paramètres :
 *  - type :
 *  - rel :
 * Résultat : Obtenir le type des tables de réimplantation
 */
void getRelType(char *type, Elf32_Rel rel);


/* passerNLignes
 * Paramètres :
 *  - file : un pointeur sur un fichier
 *  - n : un entier >= 0
 * Résultat : passe les n lignes suivants dans le fichier
 */
void passerNLignes(FILE *file, uint n);

Elf32_Shdr ReadOneSection(FILE* file);

int SectionCmp(Elf32_Shdr section1, Elf32_Shdr section2);