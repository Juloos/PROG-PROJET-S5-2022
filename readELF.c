#include "ELF.h"
#include "/usr/include/elf.h"
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
                printf("NONE (No file type)\n");
                break;
            case ET_REL:
                printf("REL (Relocatable file)\n");
                break;
            case ET_EXEC:
                printf("EXEC (Executable file)\n");
                break;
            case ET_DYN:
                printf("DYN (Shared object file)\n");
                break;
            case ET_CORE:
                printf("CORE (Core file)\n");
                break;
            case ET_LOPROC:
                printf("LOPROC (Processor-specific)\n");
                break;
            case ET_HIPROC:
                printf("HIPROC (Processor-specific)\n");
                break;
        }
    }

    return 0;
}