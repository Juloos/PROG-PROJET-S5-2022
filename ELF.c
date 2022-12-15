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