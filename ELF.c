#include "ELF.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


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
    for (int i = 0 ; i < nbSection ; i++) {
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


void getSectionName(char *name, FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, int numSection) {
    fseek(file, shdrTable[ehdr.e_shstrndx].sh_offset + shdrTable[numSection].sh_name, SEEK_SET);
    if (!fread(name, sizeof(char), STR_SIZE, file))
        fprintf(stderr, "Empty name\n");
}

int sectionName2Index(char *name, FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable) {
    char sectionName[STR_SIZE];
    for (int i = 0 ; i < ehdr.e_shnum ; i++) {
        getSectionName(sectionName, file, ehdr, shdrTable, i);
        if (strcmp(sectionName, name) == 0)
            return i;
    }
    return -1;
}

void getSectionType(char *type, Elf32_Shdr *shdrTable, int numSection) {
    switch (shdrTable[numSection].sh_type) {
        case SHT_NULL:
            strcpy(type, "NULL");
            return;
        case SHT_PROGBITS:
            strcpy(type, "PROGBITS");
            return;
        case SHT_SYMTAB:
            strcpy(type, "SYMTAB");
            return;
        case SHT_STRTAB:
            strcpy(type, "STRTAB");
            return;
        case SHT_RELA:
            strcpy(type, "RELA");
            return;
        case SHT_HASH:
            strcpy(type, "HASH");
            return;
        case SHT_DYNAMIC:
            strcpy(type, "DYNAMIC");
            return;
        case SHT_NOTE:
            strcpy(type, "NOTE");
            return;
        case SHT_NOBITS:
            strcpy(type, "NOBITS");
            return;
        case SHT_REL:
            strcpy(type, "REL");
            return;
        case SHT_SHLIB:
            strcpy(type, "SHLIB");
            return;
        case SHT_DYNSYM:
            strcpy(type, "DYNSYM");
            return;
        case SHT_LOPROC:
            strcpy(type, "LOPROC");
            return;
        case SHT_HIPROC:
            strcpy(type, "HIPROC");
            return;
        case SHT_LOUSER:
            strcpy(type, "LOUSER");
            return;
        case SHT_HIUSER:
            strcpy(type, "HIUSER");
            return;
        default:
            break;
    }
    strcpy(type, "UNKNOWN");
}

void getFlags(char *flags, Elf32_Word sh_flags) {
    strcpy(flags, "");
    strcat(flags, sh_flags & SHF_WRITE ? "W" : "-");
    strcat(flags, sh_flags & SHF_ALLOC ? "A" : "-");
    strcat(flags, sh_flags & SHF_EXECINSTR ? "X" : "-");
    strcat(flags, sh_flags & SHF_MERGE ? "M" : "-");
    strcat(flags, sh_flags & SHF_STRINGS ? "S" : "-");
    strcat(flags, sh_flags & SHF_INFO_LINK ? "I" : "-");
    strcat(flags, sh_flags & SHF_LINK_ORDER ? "L" : "-");
    strcat(flags, sh_flags & SHF_OS_NONCONFORMING ? "O" : "-");
    strcat(flags, sh_flags & SHF_GROUP ? "G" : "-");
    strcat(flags, sh_flags & SHF_TLS ? "T" : "-");
    strcat(flags, sh_flags & SHF_COMPRESSED ? "C" : "-");
    strcat(flags, sh_flags & SHF_MASKOS ? "o" : "-");
    strcat(flags, sh_flags & SHF_MASKPROC ? "p" : "-");
    strcat(flags, sh_flags & SHF_GNU_RETAIN ? "g" : "-");
    strcat(flags, sh_flags & SHF_ORDERED ? "R" : "-");
    strcat(flags, sh_flags & SHF_EXCLUDE ? "E" : "-");
}

void PrintELFTableSection(FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable) {
    printf("Section table header:\n");
    printf("  [N°]  Section Name              Type      Addr     Off    Size   ES Flg Flg Keys        Lk Inf Al\n");
    char name[STR_SIZE];
    char type[STR_SIZE];
    char flags[17];
    for (int i = 0 ; i < ehdr.e_shnum ; i++) {
        getSectionName(name, file, ehdr, shdrTable, i);
        getSectionType(type, shdrTable, i);
        getFlags(flags, shdrTable[i].sh_flags);
        printf("  [%2d]  %-24.24s  %-8s  %8.8x %6.6x %6.6x %2.2x %3.3x %16s %2d %3d %2d\n", i,
               name,
               type,
               shdrTable[i].sh_addr,
               shdrTable[i].sh_offset,
               shdrTable[i].sh_size,
               shdrTable[i].sh_entsize,
               shdrTable[i].sh_flags,
               flags,
               shdrTable[i].sh_link,
               shdrTable[i].sh_info,
               shdrTable[i].sh_addralign
        );
    }
    printf("Key to Flags:\n"
           "  W: WRITE, A: ALLOC, X: EXECINSTR, M: MERGE, S: STRINGS\n"
           "  I: INFO_LINK, L: LINK_ORDER, O: OS_NONCONFORMING\n"
           "  G: GROUP, T: TLS, C: COMPRESSED, o: MASKOS\n"
           "  p: MASKPROC, g: GNU_RETAIN, R: ORDERED, E: EXCLUDE\n");
}

void ReadELFSectionNum(FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, int numSection) {

}

void ReadELFSectionNom(FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, char *nomSection) {
    ReadELFSectionNum(file, ehdr, shdrTable, sectionName2Index(nomSection, file, ehdr, shdrTable));
}
