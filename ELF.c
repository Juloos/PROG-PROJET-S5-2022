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
        tableSection[i].sh_name = fread(file, sizeof(Elf32_Word), 1);
        printf("%x ", tableSection[i].sh_name);
        tableSection[i].sh_type = fread(file, sizeof(Elf32_Word), 1);
        printf("%x ", tableSection[i].sh_type);
        tableSection[i].sh_flags = fread(file, sizeof(Elf32_Word), 1);
        printf("%x ", tableSection[i].sh_flags);
        tableSection[i].sh_addr = fread(file, sizeof(Elf32_Addr), 1);
        printf("%x ", tableSection[i].sh_addr);
        tableSection[i].sh_offset = fread(file, sizeof(Elf32_Off), 1);
        printf("%x ", tableSection[i].sh_offset);
        tableSection[i].sh_size = fread(file, sizeof(Elf32_Word), 1);
        printf("%x ", tableSection[i].sh_size);
        tableSection[i].sh_link = fread(file, sizeof(Elf32_Word), 1);
        printf("%x ", tableSection[i].sh_link);
        tableSection[i].sh_info = fread(file, sizeof(Elf32_Word), 1);
        printf("%x ", tableSection[i].sh_info);
        tableSection[i].sh_addralign = fread(file, sizeof(Elf32_Word), 1);
        printf("%x ", tableSection[i].sh_addralign);
        tableSection[i].sh_entsize = fread(file, sizeof(Elf32_Word), 1);
        printf("%x\n", tableSection[i].sh_entsize);
    }
}