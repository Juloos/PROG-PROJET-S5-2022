#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/usr/include/elf.h"

#define STR_SIZE 256


int IS_BIGENDIAN();

void SWAPB(void *ptr, int size);

Elf32_Shdr *create_ELFTableSections(Elf32_Ehdr ehdr);

Elf32_Sym *create_ELFTableSymbols(Elf32_Shdr sh_symtab);

Elf32_Rel * create_ELFTableRel(Elf32_Shdr shdr);

Elf32_Rel * create_ELFTableRel(Elf32_Shdr shdr);

void getHeaderClass(char *class, Elf32_Ehdr ehdr);

void getHeaderData(char *data, Elf32_Ehdr ehdr);

void getHeaderOSABI(char *osabi, Elf32_Ehdr ehdr);

void getHeaderType(char *type, Elf32_Ehdr ehdr);

void getHeaderMachine(char *machine, Elf32_Ehdr ehdr);

void getSectionName(char *name, FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, int numSection);

int sectionName2Index(char *name, FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable);

void getSectionType(char *type, Elf32_Shdr shdr);

void getSectionFlags(char *flags, Elf32_Shdr shdr);

void getSectionFlags2(char *flags, Elf32_Shdr shdr);

void getSymbolName(char *name, FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, Elf32_Sym symEntry);

void getSymbolType(char *type, Elf32_Sym symEntry);

unsigned char Type2symType(char *type);

Elf32_Word Type2shType(char *type);

void getSymbolBind(char *bind, Elf32_Sym symEntry);

unsigned char Bind2symBind(char *bind);

void getSymbolVis(char *visibility, Elf32_Sym symEntry);

unsigned char Vis2symVis(char *vis);

void getSymbolNdx(char *ndx, Elf32_Sym symEntry);

Elf32_Half Ndx2symNdx(char *ndx);

void getSymType(char *type, Elf32_Rel rel);

void getRelType(char *type, Elf32_Rel rel);

void passerNLignes(FILE *file, uint n);