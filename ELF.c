#include "ELF.h"

void ReadELFile(FILE* file) {
}

void ReadELFHeader(FILE* file, Elf32_Ehdr* header) {
    printf("HEADER\n");
    // Bytes initiaux pour indiquer que le fichier est un fichier objet
    for(int i = 0; i < EI_NIDENT; i++) {
        fread(&header->e_ident[i], sizeof(unsigned char), 1, file);
        printf("%c\n", header->e_ident[i]);
    }

    // Le type de l'objet
    fread(&header->e_type, 2, 1, file);
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
    fread(&header->e_machine, 2, 1, file);
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
    fread(&header->e_version, 4, 1, file);
    printf("Version : ");
    if(header->e_version == 0) {
        printf("EV_NONE");
    } else if(header->e_version == 1) {
        printf("EV_CURRENT");
    }
    printf("\n");

    // Adresse virtuelle
    fread(&header->e_entry, 4, 1, file);
    printf("Adresse virtuelle : %d\n", header->e_entry);

    // Program header table's offset en bytes
    fread(&header->e_phoff, 4, 1, file);
    printf("Program header table's offset : %d\n", header->e_phoff);

    // Section header table's offset en bytes
    fread(&header->e_shoff, 4, 1, file);
    printf("Section header table's offset : %d\n", header->e_shoff);

    // Flags processor-specifi associés au fichier
    fread(&header->e_flags, 4, 1, file);
    printf("Flags processor-specific : %d\n", header->e_flags);

    // Taille du header en nombre de bytes
    fread(&header->e_ehsize, 2, 1, file);
    printf("Header size : %d\n", header->e_ehsize);

    // Taille 
    fread(&header->e_phentsize, 2, 1, file);
    printf("Phentsize : %d\n", header->e_phentsize);

    // 
    fread(&header->e_phnum, 2, 1, file);
    printf("Phnum : %d\n", header->e_phnum);

    // 
    fread(&header->e_shentsize, 2, 1, file);
    printf("Shentsize : %d\n", header->e_shentsize);

    // 
    fread(&header->e_shnum, 2, 1, file);
    printf("Shnum : %d\n", header->e_shnum);

    //
    fread(&header->e_shstrndx, 2, 1, file);
    printf("e_shstrndx : %d\n", header->e_shstrndx);
} 