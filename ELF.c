#include "ELF.h"

void ReadELFile(FILE* file) {
}

void ReadELFHeader(FILE* file, Elf32_Ehdr* header) {
    for(int i = 0 ; i < EI_NIDENT ; i++) {
        if (!fread(&header->e_ident[i], sizeof(unsigned char), 1, file))
            perror("Read error\n");
    }

    if (!fread(&header->e_type, 2, 1, file))
        perror("Read error\n");

    if (!fread(&header->e_machine, 2, 1, file))
        perror("Read error\n");

    if (!fread(&header->e_version, 4, 1, file))
        perror("Read error\n");

    if (!fread(&header->e_entry, 4, 1, file))
        perror("Read error\n");

    if (!fread(&header->e_phoff, 4, 1, file))
        perror("Read error\n");

    if (!fread(&header->e_shoff, 4, 1, file))
        perror("Read error\n");

    if (!fread(&header->e_flags, 4, 1, file))
        perror("Read error\n");

    if (!fread(&header->e_ehsize, 2, 1, file))
        perror("Read error\n");

    if (!fread(&header->e_phentsize, 2, 1, file))
        perror("Read error\n");

    if (!fread(&header->e_phnum, 2, 1, file))
        perror("Read error\n");

    if (!fread(&header->e_shentsize, 2, 1, file))
        perror("Read error\n");

    if (!fread(&header->e_shnum, 2, 1, file))
        perror("Read error\n");

    if (!fread(&header->e_shstrndx, 2, 1, file))
        perror("Read error\n");
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