#include "ELF.h"

void ReadELFFile(FILE* file) {
}

void ReadELFHeader(FILE* file, Elf32_Ehdr* header) {
    printf("HEADER\n");
    // Bytes initiaux pour indiquer que le fichier est un fichier objet
    for(int i = 0; i < EI_NIDENT; i++) {
        fscanf(file, "%c", &header->e_ident[i]);
        printf("%c\n", header->e_ident[i]);
    }

    // Le type de l'objet
    uint32_t e_type = 0;
    fscanf(file, "%d", &e_type);
    printf("Type : ");
    if(e_type == 0) {
        printf("ET_NONE");
    } else if(e_type == 1) {
        printf("ET_REL");
    } else if(e_type == 2) {
        printf("ET_EXEC");
    } else if (e_type == 3) {
        printf("ET_DYN");
    } else if(e_type == 4) {
        printf("ET_CORE");
    } else if(e_type == 0xff00) {
        printf("ET_LOPPROC");
    } else if(e_type == 0xffff) {
        printf("ET_HIPROC");
    }
    printf("\n");

    // Required architecture
    uint32_t e_machine = 0;
    printf("Required architecture : ");
    switch(e_machine) {
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
            if(e_machine >= 11 && e_machine <= 16) {
                printf("RESERVED");
            }
            break;
    }
    printf("\n");

    // Version de l'objet
    uint32_t e_version = 0;
    fscanf(file, "%d", &e_version);
    printf("Version : ");
    if(e_version == 0) {
        printf("EV_NONE");
    } else if(e_version == 1) {
        printf("EV_CURRENT");
    }
    printf("\n");

    // Adresse virtuelle
    uint32_t e_entry = 0;
    fscanf(file, "%d", &e_entry);
    printf("Adresse virtuelle : %d\n", e_entry);

    // Program header table's offset en bytes
    uint32_t e_phoff = 0;
    fscanf(file, "%d", &e_phoff);
    printf("Program header table's offset : %d\n", e_phoff);

    // Section header table's offset en bytes
    uint32_t e_shoff = 0;
    fscanf(file, "%d", &e_shoff);
    printf("Section header table's offset : %d\n", e_shoff);

    // Flags processor-specifi associés au fichier
    uint32_t e_flags = 0;
    fscanf(file, "%d", &e_flags);
    printf("Flags processor-specific : %d\n", e_flags);

    // Taille du header en nombre de bytes
    uint32_t e_ehsize = 0;
    fscanf(file, "%d", &e_ehsize);
    printf("Header size : %d\n", e_ehsize);

    // 
} 