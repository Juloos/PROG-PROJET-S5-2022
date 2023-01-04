#include "ELF.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    for(int i = 1; i < argc; i++) {
        FILE* file = fopen(argv[i], "r");
        if (file == NULL) {
            fprintf(stderr, "Error opening file\n");
            exit(EXIT_FAILURE);
        }

        Elf32_Ehdr header;
        ReadELFHeader(file, &header);
//        PrintELFHeader(header);

        Elf32_Shdr *sectionTable = create_ELFTableSections(header);
        ReadELFTableSections(file, header, sectionTable);
//        PrintELFTableSections(file, header, sectionTable);

        for (int i = 0; i < header.e_shnum; i++) {
            PrintELFSectionNum(file, header, sectionTable, i);
            printf("\n");
        }
//        PrintELFSectionNom(file, header, sectionTable, ".text");

        Elf32_Shdr sh_symtab = sectionTable[sectionName2Index(".symtab", file, header, sectionTable)];
        Elf32_Sym *symbolTable = create_ELFTableSymbols(sh_symtab);
        ReadELFTableSymbols(file, symbolTable, sh_symtab);
//        PrintELFTableSymbols(file, header, sectionTable, symbolTable);

        free(sectionTable);
        free(symbolTable);
    }

    return 0;
}