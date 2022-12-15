#include "ELF.h"

void ReadELFile(FILE* file) {
}

void ReadELFHeader(FILE* file, Elf32_Ehdr* header) {
    size_t nbRead = 0;
    printf("HEADER\n");
    // Bytes initiaux pour indiquer que le fichier est un fichier objet
    for(int i = 0; i < EI_NIDENT; i++) {
        nbRead = fread(&header->e_ident[i], 1, 1, file);
        printf("%d", header->e_ident[i]);
    }
    printf("\n");

    printf("Class: ");
    switch(header->e_ident[EI_CLASS]) {
        case 0:
            printf("ELFCLASSNONE (Invalid class)");
            break;
        case 1:
            printf("ELFCLASS32 (32-bit objects)");
            break;
        case 2:
            printf("ELFCLASS64 (64-bit objects)");
            break;
    }
    printf("\n");

    printf("DATA: ");
    switch(header->e_ident[EI_DATA]) {
        case 0:
            printf("ELFDATANONE (Invalid data encoding)");
            break;
        case 1:
            printf("ELFDATA2LSB");
            break;
        case 2:
            printf("ELFDATA2MSB");
            break;      
    }
    printf("\n");

    printf("Version : %d\n", header->e_ident[EI_VERSION]);


    // Le type de l'objet
    nbRead = fread(&header->e_type, 2, 1, file);
    printf("Type: ");
    switch(header->e_type) {
        case 0:
            printf("NONE (No file type)");
            break;
        case 1:
            printf("REL (Relocatable file)");
            break;
        case 2:
            printf("EXEC (Executable file)");
            break;
        case 3:
            printf("DYN (Shared object file)");
            break;
        case 4:
            printf("CORE (Core file)");
            break;
        case 0xff00:
            printf("LOPROC (Processor-specific");
            break;
        case 0xffff:
            printf("HIPROC (Processor-specific)");
            break;
    }
    printf("\n");

    // Required architecture
    nbRead = fread(&header->e_machine, 2, 1, file);
    printf("Machine: ");
    switch(header->e_machine) {
        case 0:
            printf("NONE (No machine)");
            break;
        case 1:
            printf("M32 (AT&T WE 32100)");
            break;
        case 2:
            printf("SPARC (SPARC)");
            break;
        case 3:
            printf("386 (Intel architecture)");
            break;
        case 4:
            printf("68K (Motorola 68000)");
            break;
        case 5:
            printf("88K (Motorola 68000)");
            break;
        case 7:
            printf("860 (Intel 80860)");
            break;
        case 8:
            printf("MIPS (MIPS RS3000 Big-Endian)");
            break;
        case 10:
            printf("MIPS_RS4_BE (MIPS RS4000 Big-Endian)");
            break;
        default:
            if(header->e_machine >= 11 && header->e_machine <= 16) {
                printf("RESERVED");
            }
            break;
    }
    printf("\n");

    // Version de l'objet
    nbRead = fread(&header->e_version, 4, 1, file);
    printf("Version: ");
    if(header->e_version == 0) {
        printf("NONE");
    } else if(header->e_version == 1) {
        printf("CURRENT");
    }
    printf("\n");

    // Adresse virtuelle
    nbRead = fread(&header->e_entry, 4, 1, file);
    printf("Entry point: %d\n", header->e_entry);

    // Program header table's offset en bytes
    nbRead = fread(&header->e_phoff, 4, 1, file);
    printf("Program header table's offset : %d\n", header->e_phoff);

    // Section header table's offset en bytes
    nbRead = fread(&header->e_shoff, 4, 1, file);
    printf("Section header table's offset : %d\n", header->e_shoff);

    // Flags processor-specifi associés au fichier
    nbRead = fread(&header->e_flags, 4, 1, file);
    printf("Flags processor-specific : %d\n", header->e_flags);

    // Taille du header en nombre de bytes
    nbRead = fread(&header->e_ehsize, 2, 1, file);
    printf("Header size : %d\n", header->e_ehsize);

    // Taille 
    nbRead = fread(&header->e_phentsize, 2, 1, file);
    printf("Phentsize : %d\n", header->e_phentsize);

    // 
    nbRead = fread(&header->e_phnum, 2, 1, file);
    printf("Phnum : %d\n", header->e_phnum);

    // 
    nbRead = fread(&header->e_shentsize, 2, 1, file);
    printf("Shentsize : %d\n", header->e_shentsize);

    // 
    nbRead = fread(&header->e_shnum, 2, 1, file);
    printf("Shnum : %d\n", header->e_shnum);

    //
    nbRead = fread(&header->e_shstrndx, 2, 1, file);
    printf("e_shstrndx : %d\n", header->e_shstrndx);

    nbRead += 1;
} 