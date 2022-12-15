#include "ELF.h"
#include <stdlib.h>
#include <stdio.h>


void ReadELFFile(FILE* file) {
}

Elf32_Shdr * init_TabSection(int nbSection) {
    Elf32_Shdr *tabSection = (Elf32_Shdr *) calloc(sizeof(Elf32_Shdr), nbSection);
    return tabSection;
}

void ReadELFTabSection(FILE* file, Elf32_Shdr* tableSection, int nbSection) {
    printf("Section Header Table\n")
    for (int i = 0; i < nbSection; i++) {
        printf("\nSection %d\n    ", i);
        if (!fread(&tableSection[i].sh_name, sizeof(uint32_t), 1, file))
            perror("Read error\n");
        if (!fread(&tableSection[i].sh_type, sizeof(uint32_t), 1, file))
            perror("Read error\n");
        if (!fread(&tableSection[i].sh_flags, sizeof(uint32_t), 1, file))
            perror("Read error\n");
        if (!fread(&tableSection[i].sh_addr, sizeof(Elf32_Addr), 1, file))
            perror("Read error\n");
        if (!fread(&tableSection[i].sh_offset, sizeof(Elf32_Off), 1, file))
            perror("Read error\n");
        if (!fread(&tableSection[i].sh_size, sizeof(uint32_t), 1, file))
            perror("Read error\n");
        if (!fread(&tableSection[i].sh_link, sizeof(uint32_t), 1, file))
            perror("Read error\n");
        if (!fread(&tableSection[i].sh_info, sizeof(uint32_t), 1, file))
            perror("Read error\n");
        if (!fread(&tableSection[i].sh_addralign, sizeof(uint32_t), 1, file))
            perror("Read error\n");
        if (!fread(&tableSection[i].sh_entsize, sizeof(uint32_t), 1, file))
            perror("Read error\n");
    }
}