#include "ELF.h"

void ReadELFile(FILE* file) {
}

void ReadELFHeader(FILE* file, Elf32_Ehdr* header) {
    printf("HEADER\n");
    // Bytes initiaux pour indiquer que le fichier est un fichier objet
    for(int i = 0; i < EI_NIDENT; i++) {
        if (!fread(&header->e_ident[i], sizeof(unsigned char), 1, file))
            perror("Read error\n");
        printf("%c\n", header->e_ident[i]);
    }

    // Le type de l'objet
    if (!fread(&header->e_type, 2, 1, file))
        perror("Read error\n");
    printf("Type : ");
    switch(header->e_type) {
        case 0:
            printf("ET_NONE");
            break;
        case 1:
            printf("ET_REL");
            break;
        case 2:
            printf("ET_EXEC");
            break;
        case 3:
            printf("ET_DYN");
            break;
        case 4:
            printf("ET_CORE");
            break;
        case 0xff00:
            printf("ET_LOPPROC");
            break;
        case 0xffff:
            printf("ET_HIPROC");
            break;
    }
    printf("\n");

    // Required architecture
    if (!fread(&header->e_machine, 2, 1, file))
        perror("Read error\n");
    printf("Required architecture : ");
    switch(header->e_machine) {
        case 0:
            printf("ET_NONE");
            break;
        case 1:
            printf("EM_M32");
            break;
        case 2:
            printf("EM_SPARC");
            break;
        case 3:
            printf("EM_386");
            break;
        case 4:
            printf("EM_68K");
            break;
        case 5:
            printf("EM_88K");
            break;
        case 7:
            printf("EM_860");
            break;
        case 8:
            printf("EM_MIPS");
            break;
        case 10:
            printf("EM_MIPS_RS4_BE");
            break;
        default:
            if(header->e_machine >= 11 && header->e_machine <= 16) {
                printf("RESERVED");
            }
            break;
    }
    printf("\n");

    // Version de l'objet
    if (!fread(&header->e_version, 4, 1, file))
        perror("Read error\n");
    printf("Version : ");
    if(header->e_version == 0) {
        printf("EV_NONE");
    } else if(header->e_version == 1) {
        printf("EV_CURRENT");
    }
    printf("\n");

    // Adresse virtuelle
    if (!fread(&header->e_entry, 4, 1, file))
        perror("Read error\n");
    printf("Adresse virtuelle : %d\n", header->e_entry);

    // Program header table's offset en bytes
    if (!fread(&header->e_phoff, 4, 1, file))
        perror("Read error\n");
    printf("Program header table's offset : %d\n", header->e_phoff);

    // Section header table's offset en bytes
    if (!fread(&header->e_shoff, 4, 1, file))
        perror("Read error\n");
    printf("Section header table's offset : %d\n", header->e_shoff);

    // Flags processor-specifi associés au fichier
    if (!fread(&header->e_flags, 4, 1, file))
        perror("Read error\n");
    printf("Flags processor-specific : %d\n", header->e_flags);

    // Taille du header en nombre de bytes
    if (!fread(&header->e_ehsize, 2, 1, file))
        perror("Read error\n");
    printf("Header size : %d\n", header->e_ehsize);

    // Taille 
    if (!fread(&header->e_phentsize, 2, 1, file))
        perror("Read error\n");
    printf("Phentsize : %d\n", header->e_phentsize);

    // 
    if (!fread(&header->e_phnum, 2, 1, file))
        perror("Read error\n");
    printf("Phnum : %d\n", header->e_phnum);

    // 
    if (!fread(&header->e_shentsize, 2, 1, file))
        perror("Read error\n");
    printf("Shentsize : %d\n", header->e_shentsize);

    // 
    if (!fread(&header->e_shnum, 2, 1, file))
        perror("Read error\n");
    printf("Shnum : %d\n", header->e_shnum);

    //
    if (!fread(&header->e_shstrndx, 2, 1, file))
        perror("Read error\n");
    printf("e_shstrndx : %d\n", header->e_shstrndx);
} 