#include "ELF.h"
#include <stdlib.h>
#include <stdio.h>


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

Elf32_Shdr * create_ELFTableSection(int nbSection) {
    return (Elf32_Shdr *) calloc(sizeof(Elf32_Shdr), nbSection);
}

void ReadELFTabSection(FILE* file, Elf32_Shdr* tableSection, int nbSection) {
    for (int i = 0; i < nbSection; i++) {
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
