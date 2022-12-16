#include "ELF.h"
#include <stdlib.h>
#include <stdio.h>


void ReadELFile(FILE *file) {
}

void ReadELFHeader(FILE *file, Elf32_Ehdr *ehdr) {
    fseek(file, 0, SEEK_SET);

    for(int i = 0 ; i < EI_NIDENT ; i++) {
        if (!fread(&ehdr->e_ident[i], sizeof(unsigned char), 1, file))
            fprintf(stderr, "Read error\n");
    }

    if (!fread(&ehdr->e_type, 2, 1, file))
        fprintf(stderr, "Read error\n");

    if (!fread(&ehdr->e_machine, 2, 1, file))
        fprintf(stderr, "Read error\n");

    if (!fread(&ehdr->e_version, 4, 1, file))
        fprintf(stderr, "Read error\n");

    if (!fread(&ehdr->e_entry, 4, 1, file))
        fprintf(stderr, "Read error\n");

    if (!fread(&ehdr->e_phoff, 4, 1, file))
        fprintf(stderr, "Read error\n");

    if (!fread(&ehdr->e_shoff, 4, 1, file))
        fprintf(stderr, "Read error\n");

    if (!fread(&ehdr->e_flags, 4, 1, file))
        fprintf(stderr, "Read error\n");

    if (!fread(&ehdr->e_ehsize, 2, 1, file))
        fprintf(stderr, "Read error\n");

    if (!fread(&ehdr->e_phentsize, 2, 1, file))
        fprintf(stderr, "Read error\n");

    if (!fread(&ehdr->e_phnum, 2, 1, file))
        fprintf(stderr, "Read error\n");

    if (!fread(&ehdr->e_shentsize, 2, 1, file))
        fprintf(stderr, "Read error\n");

    if (!fread(&ehdr->e_shnum, 2, 1, file))
        fprintf(stderr, "Read error\n");

    if (!fread(&ehdr->e_shstrndx, 2, 1, file))
        fprintf(stderr, "Read error\n");
}

Elf32_Shdr * create_ELFTableSection(int nbSection) {
    return (Elf32_Shdr *) calloc(sizeof(Elf32_Shdr), nbSection);
}

void ReadELFTableSection(FILE *file, Elf32_Shdr *shdrTable, int nbSection, int offset) {
    fseek(file, offset, SEEK_SET);
    for (int i = 0; i < nbSection; i++) {
        if (!fread(&shdrTable[i].sh_name, sizeof(Elf32_Word), 1, file))
            fprintf(stderr, "Read error\n");

        if (!fread(&shdrTable[i].sh_type, sizeof(Elf32_Word), 1, file))
            fprintf(stderr, "Read error\n");

        if (!fread(&shdrTable[i].sh_flags, sizeof(Elf32_Word), 1, file))
            fprintf(stderr, "Read error\n");

        if (!fread(&shdrTable[i].sh_addr, sizeof(Elf32_Addr), 1, file))
            fprintf(stderr, "Read error\n");

        if (!fread(&shdrTable[i].sh_offset, sizeof(Elf32_Off), 1, file))
            fprintf(stderr, "Read error\n");

        if (!fread(&shdrTable[i].sh_size, sizeof(Elf32_Word), 1, file))
            fprintf(stderr, "Read error\n");

        if (!fread(&shdrTable[i].sh_link, sizeof(Elf32_Word), 1, file))
            fprintf(stderr, "Read error\n");

        if (!fread(&shdrTable[i].sh_info, sizeof(Elf32_Word), 1, file))
            fprintf(stderr, "Read error\n");

        if (!fread(&shdrTable[i].sh_addralign, sizeof(Elf32_Word), 1, file))
            fprintf(stderr, "Read error\n");

        if (!fread(&shdrTable[i].sh_entsize, sizeof(Elf32_Word), 1, file))
            fprintf(stderr, "Read error\n");
    }
}


char * getSectionName(FILE *file, Elf32_Shdr *shdrTable, int numSection, int offset) {
    char *name = (char *) calloc(sizeof(char), shdrTable[numSection].sh_size);
    fseek(file, offset + shdrTable[numSection].sh_name, SEEK_SET);
    if (!fread(name, sizeof(char), shdrTable[numSection].sh_size, file))
        fprintf(stderr, "Empty name\n");
    return name;
}

char * getSectionType(Elf32_Shdr *shdrTable, int numSection) {
    switch (shdrTable[numSection].sh_type) {
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

void PrintELFTableSection(FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable) {
    printf("Section table header\n");
    printf("[N°]  Section Name              Type      Addr     Off    Size   ES Flg Lk Inf Al\n");
    for (int i = 0; i < ehdr.e_shnum; i++)
        printf("[%2d]  %-24.24s  %-8s  %8.8x %6.6x %6.6x %2.2x %3.3x %2d %3d %2d\n", i,
               getSectionName(file, shdrTable, i, shdrTable[ehdr.e_shstrndx].sh_offset),
               getSectionType(shdrTable, i),
               shdrTable[i].sh_addr,
               shdrTable[i].sh_offset,
               shdrTable[i].sh_size,
               shdrTable[i].sh_flags,
               shdrTable[i].sh_entsize,
               shdrTable[i].sh_link,
               shdrTable[i].sh_info,
               shdrTable[i].sh_addralign
        );
}
