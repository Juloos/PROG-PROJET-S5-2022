#include "ELF.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    for(int i = 1; i < argc; i++) {
        FILE* file = fopen(argv[i], "r");
        Elf32_Ehdr header;

        ReadELFHeader(file, &header);

        Elf32_Shdr *sectionTable = create_ELFTableSections(header);
        ReadELFTableSections(file, header, sectionTable);
//        PrintELFTableSections(file, header, sectionTable);

        Elf32_Shdr sh_symtab = sectionTable[sectionName2Index(".symtab", file, header, sectionTable)];
        Elf32_Sym *symbolTable = create_ELFTableSymbols(sh_symtab);
        ReadELFTableSymbols(file, symbolTable, sh_symtab);
        PrintELFTableSymbols(file, header, sectionTable, symbolTable);

        free(sectionTable);
        free(symbolTable);
    }
    return 0;
}