#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/usr/include/elf.h"

#define STR_SIZE 256


int IS_BIGENDIAN();

void SWAPB(void *ptr, int size);

Elf32_Shdr *create_ELFTableSections(Elf32_Ehdr ehdr);

Elf32_Sym *create_ELFTableSymbols(Elf32_Shdr sh_symtab);

void getHeaderClass(char *class, Elf32_Ehdr ehdr);

void getHeaderData(char *data, Elf32_Ehdr ehdr);

void getHeaderOSABI(char *osabi, Elf32_Ehdr ehdr);

void getHeaderType(char *type, Elf32_Ehdr ehdr);

void getHeaderMachine(char *machine, Elf32_Ehdr ehdr);

void getSectionName(char *name, FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, int numSection);

int sectionName2Index(char *name, FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable);

void getSectionType(char *type, Elf32_Shdr shdr);

void getSectionFlags(char *flags, Elf32_Shdr shdr);

void getSymbolName(char *name, FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, Elf32_Sym symEntry);

void getSymbolType(char *type, Elf32_Sym symEntry);

void getSymbolBind(char *bind, Elf32_Sym symEntry);

void getSymbolVis(char *visibility, Elf32_Sym symEntry);

void getSymbolNdx(char *ndx, Elf32_Sym symEntry);
