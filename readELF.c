#include "ELF.h"
#include <elf.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    for(int i = 1; i < argc; i++) {
        FILE* file = fopen(argv[i], "r");
        if(file == NULL) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }
        Elf32_Ehdr* header = malloc(sizeof(Elf32_Ehdr));

        ReadELFHeader(file, header);

        // Affichage du contenu du fichier
        printf("HEADER\n");
        // Ident
        printf("Ident: ");
        for(int i = 0; i < EI_NIDENT; i++) {
            printf("%.2x ", header->e_ident[i]);
        }

        // Class
        printf("\nClass: ");
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
        printf("\nData: ");
        switch(header->e_ident[EI_DATA]) {
            case ELFDATANONE:
                printf("Invalid data encoding");
                break;
            case ELFDATA2LSB:
                printf("2's complement values, little endian");
                break;
            case ELFDATA2MSB:
                printf("2's complement values, big endian");
                break;
        }

        // File Version
        printf("\nVersion: ");
        if(header->e_ident[EI_VERSION] == EV_NONE) {
            printf("%d (invalid)", header->e_ident[EI_VERSION]);
        } else {
            printf("%d (current)", header->e_ident[EI_VERSION]);
        }

        // File type
        printf("\nType: ");
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
        printf("\nMachine: ");
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
        printf("\nVersion: 0x%x", header->e_version);

        // Entry point address
        printf("\nEntry point address: 0x%x", header->e_entry);

        // Start of program headers
        printf("\nStart of program headers: %d (bytes into file)", header->e_phoff);

        // Start of section headers
        printf("\nStart of section headers: %d (bytes into file)", header->e_shoff);

        // Flags
        printf("\nFlags: 0x%x", header->e_flags);

        // Header's size
        printf("\nSize of this header: %d (bytes)", header->e_ehsize);

        // Size of program headers
        printf("\nSize of program headers: %d (bytes)", header->e_phentsize);

        // Number of program headers
        printf("\nNumber of program headers: %d", header->e_phnum);

        // Size of section headers
        printf("\nSize of section headers: %d (bytes)", header->e_shentsize);

        // Number of section headers
        printf("\nNumber of section headers: %d", header->e_shnum);

        // Section header string table index
        printf("\nSection header string table index: %d\n", header->e_shstrndx);
    }

    return 0;
}