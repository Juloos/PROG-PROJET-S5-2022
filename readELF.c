#include "ELF.h"
#include <stdio.h>

char * getSectionName(FILE * file, Elf32_Shdr * tableSection, int numSection, int offset) {
    char * name = (char *) calloc(sizeof(char), tableSection[numSection].sh_size);
    fseek(file, offset + tableSection[numSection].sh_name, SEEK_SET);
    if (!fread(name, sizeof(char), tableSection[numSection].sh_size, file))
        perror("Read error\n");
    return name;
}

char * getSectionType(Elf32_Shdr * tableSection, int numSection) {
    switch (tableSection[numSection].sh_type) {
        case SHT_NULL:
            return "NULL";
        case SHT_PROGBITS:
            return "PROGBITS";
        case SHT_SYMTAB:
            return "SYMTAB";
        case SHT_STRTAB:
            return "STRTAB";
        case SHT_RELA:
            return "RELA";
        case SHT_HASH:
            return "HASH";
        case SHT_DYNAMIC:
            return "DYNAMIC";
        case SHT_NOTE:
            return "NOTE";
        case SHT_NOBITS:
            return "NOBITS";
        case SHT_REL:
            return "REL";
        case SHT_SHLIB:
            return "SHLIB";
        case SHT_DYNSYM:
            return "DYNSYM";
        case SHT_LOPROC:
            return "LOPROC";
        case SHT_HIPROC:
            return "HIPROC";
        case SHT_LOUSER:
            return "LOUSER";
        case SHT_HIUSER:
            return "HIUSER";
        default:
    }
    return "UNKNOWN";
}

int main(int argc, char* argv[]) {
    for(int i = 1; i < argc; i++) {
        FILE* file = fopen(argv[i], "r");
        Elf32_Ehdr header;

        ReadELFHeader(file, &header);

        Elf32_Shdr *sectionTable = create_ELFTableSection(header.e_shnum);
        ReadELFTableSection(file, sectionTable, header.e_shnum, header.e_shoff);

        for (int i = 0; i < header.e_shnum; i++) {
            printf("[%2d] %s %s %x %x %x %x %x %x %x %x\n", i,
                   getSectionName(file, sectionTable, i, sectionTable[header.e_shstrndx].sh_offset),
                   getSectionType(sectionTable, i),
                   sectionTable[i].sh_flags,
                   sectionTable[i].sh_addr,
                   sectionTable[i].sh_offset,
                   sectionTable[i].sh_size,
                   sectionTable[i].sh_link,
                   sectionTable[i].sh_info,
                   sectionTable[i].sh_addralign,
                   sectionTable[i].sh_entsize
            );
        }
    }
    return 0;
}