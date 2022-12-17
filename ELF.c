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

Elf32_Shdr * create_ELFTableSections(Elf32_Ehdr ehdr) {
    return (Elf32_Shdr *) malloc(sizeof(Elf32_Shdr) * ehdr.e_shnum);
}

void ReadELFTableSections(FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable) {
    fseek(file, ehdr.e_shoff, SEEK_SET);
    for (int i = 0 ; i < ehdr.e_shnum ; i++) {
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
    fprintf(stderr, "Section not found '%s'\n", name);
    return -1;
}

void ReadELFSectionNum(FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, int numSection) {

}

void ReadELFSectionNom(FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, char *nomSection) {
    ReadELFSectionNum(file, ehdr, shdrTable, sectionName2Index(nomSection, file, ehdr, shdrTable));
}

Elf32_Sym * create_ELFTableSymbols(Elf32_Shdr sh_symtab) {
    return (Elf32_Sym *) malloc(sh_symtab.sh_size);
}

void ReadELFTableSymbols(FILE *file, Elf32_Sym *symTable, Elf32_Shdr sh_symtab) {
    if (sh_symtab.sh_type != SHT_SYMTAB) {
        fprintf(stderr, "Not a symbol table\n");
        return;
    }
    fseek(file, sh_symtab.sh_offset, SEEK_SET);
    int nbEntries = sh_symtab.sh_size / sh_symtab.sh_entsize;
    for (int i = 0 ; i < nbEntries ; i++) {
        if (!fread(&symTable[i].st_name, sizeof(Elf32_Word), 1, file))
            fprintf(stderr, "Read error\n");

        if (!fread(&symTable[i].st_value, sizeof(Elf32_Addr), 1, file))
            fprintf(stderr, "Read error\n");

        if (!fread(&symTable[i].st_size, sizeof(Elf32_Word), 1, file))
            fprintf(stderr, "Read error\n");

        if (!fread(&symTable[i].st_info, sizeof(unsigned char), 1, file))
            fprintf(stderr, "Read error\n");

        if (!fread(&symTable[i].st_other, sizeof(unsigned char), 1, file))
            fprintf(stderr, "Read error\n");

        if (!fread(&symTable[i].st_shndx, sizeof(Elf32_Half), 1, file))
            fprintf(stderr, "Read error\n");
    }
}


void getSectionType(char *type, Elf32_Shdr shdr) {
    switch (shdr.sh_type) {
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

void getSectionFlags(char *flags, Elf32_Shdr shdr) {
    strcpy(flags, "");
    Elf32_Word sh_flags = shdr.sh_flags;
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
    strcat(flags, sh_flags & SHF_ORDERED ? "R" : "-");
    strcat(flags, sh_flags & SHF_EXCLUDE ? "E" : "-");
}

void PrintELFTableSections(FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable) {
    printf("Section table headers:\n");
    printf("  [N°]  Section Name              Type          Addr    Off   Size ES Flg Flg Keys        Lk Inf Al\n");
    char name[STR_SIZE];
    char type[STR_SIZE];
    char flags[16];
    for (int i = 0 ; i < ehdr.e_shnum ; i++) {
        getSectionName(name, file, ehdr, shdrTable, i);
        getSectionType(type, shdrTable[i]);
        getSectionFlags(flags, shdrTable[i]);
        printf("  [%2d]  %-24.24s  %-8s  %8.8x %6.6x %6.6x %2.2x %3.3x %15s %2d %3d %2d\n", i,
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

void getSymbolName(char *name, FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, Elf32_Sym symEntry) {
    if (symEntry.st_name == STN_UNDEF) {
        getSectionName(name, file, ehdr, shdrTable, symEntry.st_shndx);
        return;
    }
    Elf32_Shdr sh_strtab = shdrTable[sectionName2Index(".strtab", file, ehdr, shdrTable)];
    fseek(file, sh_strtab.sh_offset + symEntry.st_name, SEEK_SET);
    if (!fread(name, sizeof(char), STR_SIZE, file))
        fprintf(stderr, "Read error\n");
}

void getSymbolType(char *type, Elf32_Sym symEntry) {
    switch (ELF32_ST_TYPE(symEntry.st_info)) {
        case STT_NOTYPE:
            strcpy(type, "NOTYPE");
            return;
        case STT_OBJECT:
            strcpy(type, "OBJECT");
            return;
        case STT_FUNC:
            strcpy(type, "FUNC");
            return;
        case STT_SECTION:
            strcpy(type, "SECTION");
            return;
        case STT_FILE:
            strcpy(type, "FILE");
            return;
        case STT_LOPROC:
            strcpy(type, "LOPROC");
            return;
        case STT_HIPROC:
            strcpy(type, "HIPROC");
            return;
        default:
            break;
    }
    strcpy(type, "UNKNOWN");
}

void getSymbolBind(char *bind, Elf32_Sym symEntry) {
    switch (ELF32_ST_BIND(symEntry.st_info)) {
        case STB_LOCAL:
            strcpy(bind, "LOCAL");
            return;
        case STB_GLOBAL:
            strcpy(bind, "GLOBAL");
            return;
        case STB_WEAK:
            strcpy(bind, "WEAK");
            return;
        case STB_LOPROC:
            strcpy(bind, "LOPROC");
            return;
        case STB_HIPROC:
            strcpy(bind, "HIPROC");
            return;
        default:
            break;
    }
    strcpy(bind, "UNKNOWN");
}

void getSymbolVis(char *visibility, Elf32_Sym symEntry) {
    switch (ELF32_ST_VISIBILITY(symEntry.st_other)) {
        case STV_DEFAULT:
            strcpy(visibility, "DEFAULT");
            return;
        case STV_INTERNAL:
            strcpy(visibility, "INTERNAL");
            return;
        case STV_HIDDEN:
            strcpy(visibility, "HIDDEN");
            return;
        case STV_PROTECTED:
            strcpy(visibility, "PROTECTED");
            return;
        default:
            break;
    }
    strcpy(visibility, "UNKNOWN");
}

void getSymbolNdx(char *ndx, Elf32_Sym symEntry) {
    switch (symEntry.st_shndx) {
        case SHN_UNDEF:
            strcpy(ndx, "UND");
            return;
        case SHN_ABS:
            strcpy(ndx, "ABS");
            return;
        case SHN_COMMON:
            strcpy(ndx, "COM");
            return;
        default:
            break;
    }
    sprintf(ndx, "%d", symEntry.st_shndx);
}

void PrintELFTableSymbols(FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, Elf32_Sym *symTable) {
    printf("Symbol table entries:\n");
    printf("  [N°]    Value  Size Type    Bind   Vis      Ndx Name\n");
    char name[STR_SIZE];
    char type[STR_SIZE];
    char bind[STR_SIZE];
    char vis[STR_SIZE];
    char ndx[STR_SIZE];
    Elf32_Shdr sh_symtab = shdrTable[sectionName2Index(".symtab", file, ehdr, shdrTable)];
    for (int i = 0 ; i < sh_symtab.sh_size / sh_symtab.sh_entsize ; i++) {
        getSymbolName(name, file, ehdr, shdrTable, symTable[i]);
        getSymbolType(type, symTable[i]);
        getSymbolBind(bind, symTable[i]);
        getSymbolVis(vis, symTable[i]);
        getSymbolNdx(ndx, symTable[i]);
        printf("  [%2d] %08x %5d %-7s %-6s %-7s %4s %s \n", i,
               symTable[i].st_value,
               symTable[i].st_size,
               type,
               bind,
               vis,
               ndx,
               name
        );
    }
}
