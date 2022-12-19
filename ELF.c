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

void PrintELFHeader(Elf32_Ehdr* header) {
    printf("ELF File's Header:\n");
    // Ident
    printf("  Ident: ");
    for(int i = 0; i < EI_NIDENT; i++) {
        printf("%.2x ", header->e_ident[i]);
    }

    // Class
    printf("\n  Class: \t\t\t\t");
    switch(header->e_ident[EI_CLASS]) {
        case 0:
            printf("ELFNONE");
            break;
        case 1:
            printf("ELF32");
            break;
        case 2:
            printf("ELF64");
            break;
    }

    // Data
    printf("\n  Data: \t\t\t\t");
    switch(header->e_ident[EI_DATA]) {
        case ELFDATANONE:
            printf("Invalid data encoding");
            break;
        case ELFDATA2LSB:
            printf("2's complement, little endian");
            break;
        case ELFDATA2MSB:
            printf("2's complement, big endian");
            break;
    }

    // File Version
    printf("\n  Version: \t\t\t\t");
    if(header->e_ident[EI_VERSION] == EV_NONE) {
        printf("%d (invalid)", header->e_ident[EI_VERSION]);
    } else {
        printf("%d (current)", header->e_ident[EI_VERSION]);
    }

    // File type
    printf("\n  Type: \t\t\t\t");
    switch(header->e_type) {
        case ET_NONE:
            printf("NONE (No file type)");
            break;
        case ET_REL:
            printf("REL (Relocatable file)");
            break;
        case ET_EXEC:
            printf("EXEC (Executable file)");
            break;
        case ET_DYN:
            printf("DYN (Shared object file)");
            break;
        case ET_CORE:
            printf("CORE (Core file)");
            break;
        case ET_LOPROC:
            printf("LOPROC (Processor-specific)");
            break;
        case ET_HIPROC:
            printf("HIPROC (Processor-specific)");
            break;
    }

    // Required architecture
    printf("\n  Machine: \t\t\t\t");
    switch(header->e_machine) {
        case ET_NONE:
            printf("No machine");
            break;
        case EM_M32:
            printf("AT&T WE 32100");
            break;
        case EM_SPARC:
            printf("SPARC");
            break;
        case EM_386:
            printf("Intel architecture");
            break;
        case EM_68K:
            printf("Motorola 68000");
            break;
        case EM_88K:
            printf("Motorola 88000");
            break;
        case EM_860:
            printf("Intel 80860");
            break;
        case EM_MIPS:
            printf("MIPS RS3000 Big-Endian");
            break;
        case EM_ARM:
            printf("ARM");
            break;
        default:
            if(header->e_machine >= 11 && header->e_machine <= 16) {
                printf("RESERVED");
            }
            break;
    }

    // File version
    printf("\n  Version: \t\t\t\t0x%x", header->e_version);

    // Entry point address
    printf("\n  Entry point address: \t\t\t0x%x", header->e_entry);

    // Start of program headers
    printf("\n  Start of program headers: \t\t%d (bytes into file)", header->e_phoff);

    // Start of section headers
    printf("\n  Start of section headers: \t\t%d (bytes into file)", header->e_shoff);

    // Flags
    printf("\n  Flags: \t\t\t\t0x%x", header->e_flags);

    // Header's size
    printf("\n  Size of this header: \t\t\t%d (bytes)", header->e_ehsize);

    // Size of program headers
    printf("\n  Size of program headers: \t\t%d (bytes)", header->e_phentsize);

    // Number of program headers
    printf("\n  Number of program headers: \t\t%d", header->e_phnum);

    // Size of section headers
    printf("\n  Size of section headers: \t\t%d (bytes)", header->e_shentsize);

    // Number of section headers
    printf("\n  Number of section headers: \t\t%d", header->e_shnum);

    // Section header string table index
    printf("\n  Section header string table index: \t%d\n", header->e_shstrndx);
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
