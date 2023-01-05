#include "ELF.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gelf.h>
#include <libelf.h>

// This will help determine the endianness of the machine
const int BIG_ENDIAN_THROTTLE = 1;
#define IS_BIGENDIAN() ((*(char *) &BIG_ENDIAN_THROTTLE) == 0)

// This function will help us swap bytes depending on the endianness of the machine
void SWAPB(void *ptr, size_t size) {
    char *tmp = malloc(size);
    memcpy(tmp, ptr, size);
    for (int i = 0 ; i < size ; i++) {
        ((char *) ptr)[i] = tmp[size - i - 1];
    }
    free(tmp);
}


void ReadELFile(FILE *file) {
}

void ReadELFHeader(FILE *file, Elf32_Ehdr *ehdr) {
    fseek(file, 0, SEEK_SET);

    for (int i = 0 ; i < EI_NIDENT ; i++) {
        if (!fread(&ehdr->e_ident[i], sizeof(unsigned char), 1, file))
            fprintf(stderr, "Read error\n");
    }

    if (!fread(&ehdr->e_type, sizeof(Elf32_Half), 1, file))
        fprintf(stderr, "Read error\n");

    if (!fread(&ehdr->e_machine, sizeof(Elf32_Half), 1, file))
        fprintf(stderr, "Read error\n");

    if (!fread(&ehdr->e_version, sizeof(Elf32_Word), 1, file))
        fprintf(stderr, "Read error\n");

    if (!fread(&ehdr->e_entry, sizeof(Elf32_Addr), 1, file))
        fprintf(stderr, "Read error\n");

    if (!fread(&ehdr->e_phoff, sizeof(Elf32_Off), 1, file))
        fprintf(stderr, "Read error\n");

    if (!fread(&ehdr->e_shoff, sizeof(Elf32_Off), 1, file))
        fprintf(stderr, "Read error\n");

    if (!fread(&ehdr->e_flags, sizeof(Elf32_Word), 1, file))
        fprintf(stderr, "Read error\n");

    if (!fread(&ehdr->e_ehsize, sizeof(Elf32_Half), 1, file))
        fprintf(stderr, "Read error\n");

    if (!fread(&ehdr->e_phentsize, sizeof(Elf32_Half), 1, file))
        fprintf(stderr, "Read error\n");

    if (!fread(&ehdr->e_phnum, sizeof(Elf32_Half), 1, file))
        fprintf(stderr, "Read error\n");

    if (!fread(&ehdr->e_shentsize, sizeof(Elf32_Half), 1, file))
        fprintf(stderr, "Read error\n");

    if (!fread(&ehdr->e_shnum, sizeof(Elf32_Half), 1, file))
        fprintf(stderr, "Read error\n");

    if (!fread(&ehdr->e_shstrndx, sizeof(Elf32_Half), 1, file))
        fprintf(stderr, "Read error\n");

    if (!IS_BIGENDIAN()) {
        // Not swapping Magic because apparently it's not endian dependent
        SWAPB(&ehdr->e_type, sizeof(Elf32_Half));
        SWAPB(&ehdr->e_machine, sizeof(Elf32_Half));
        SWAPB(&ehdr->e_version, sizeof(Elf32_Word));
        SWAPB(&ehdr->e_entry, sizeof(Elf32_Addr));
        SWAPB(&ehdr->e_phoff, sizeof(Elf32_Off));
        SWAPB(&ehdr->e_shoff, sizeof(Elf32_Off));
        SWAPB(&ehdr->e_flags, sizeof(Elf32_Word));
        SWAPB(&ehdr->e_ehsize, sizeof(Elf32_Half));
        SWAPB(&ehdr->e_phentsize, sizeof(Elf32_Half));
        SWAPB(&ehdr->e_phnum, sizeof(Elf32_Half));
        SWAPB(&ehdr->e_shentsize, sizeof(Elf32_Half));
        SWAPB(&ehdr->e_shnum, sizeof(Elf32_Half));
        SWAPB(&ehdr->e_shstrndx, sizeof(Elf32_Half));
    }
}

Elf32_Shdr *create_ELFTableSections(Elf32_Ehdr ehdr) {
    return (Elf32_Shdr *)
            malloc(sizeof(Elf32_Shdr) * ehdr.e_shnum);
}

void ReadELFTableSections(FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable) {
    fseek(file, ehdr.e_shoff, SEEK_SET);
    for (int i = 0 ; i < ehdr.e_shnum ; i++) {
        if (!fread(&shdrTable[i].sh_name, sizeof(Elf32_Word), 1, file))
            fprintf(stderr, "Read error\n");

        if (!fread(&shdrTable[i].sh_type, sizeof(Elf32_Word), 1, file))
            fprintf(stderr, "Read error\n");

        if (!fread(&shdrTable[i].sh_flags, sizeof(Elf32_Word), 1, file))
            fprintf(stderr, "Read error\n");

        if (!fread(&shdrTable[i].sh_addr, sizeof(Elf32_Addr), 1, file))
            fprintf(stderr, "Read error\n");

        if (!fread(&shdrTable[i].sh_offset, sizeof(Elf32_Off), 1, file))
            fprintf(stderr, "Read error\n");

        if (!fread(&shdrTable[i].sh_size, sizeof(Elf32_Word), 1, file))
            fprintf(stderr, "Read error\n");

        if (!fread(&shdrTable[i].sh_link, sizeof(Elf32_Word), 1, file))
            fprintf(stderr, "Read error\n");

        if (!fread(&shdrTable[i].sh_info, sizeof(Elf32_Word), 1, file))
            fprintf(stderr, "Read error\n");

        if (!fread(&shdrTable[i].sh_addralign, sizeof(Elf32_Word), 1, file))
            fprintf(stderr, "Read error\n");

        if (!fread(&shdrTable[i].sh_entsize, sizeof(Elf32_Word), 1, file))
            fprintf(stderr, "Read error\n");

        if (!IS_BIGENDIAN()) {
            SWAPB(&shdrTable[i].sh_name, sizeof(Elf32_Word));
            SWAPB(&shdrTable[i].sh_type, sizeof(Elf32_Word));
            SWAPB(&shdrTable[i].sh_flags, sizeof(Elf32_Word));
            SWAPB(&shdrTable[i].sh_addr, sizeof(Elf32_Addr));
            SWAPB(&shdrTable[i].sh_offset, sizeof(Elf32_Off));
            SWAPB(&shdrTable[i].sh_size, sizeof(Elf32_Word));
            SWAPB(&shdrTable[i].sh_link, sizeof(Elf32_Word));
            SWAPB(&shdrTable[i].sh_info, sizeof(Elf32_Word));
            SWAPB(&shdrTable[i].sh_addralign, sizeof(Elf32_Word));
            SWAPB(&shdrTable[i].sh_entsize, sizeof(Elf32_Word));
        }
    }
}

Elf32_Sym *create_ELFTableSymbols(Elf32_Shdr sh_symtab) {
    return (Elf32_Sym *) malloc(sh_symtab.sh_size);
}

void ReadELFTableSymbols(FILE *file, Elf32_Sym *symTable, Elf32_Shdr sh_symtab) {
    if (sh_symtab.sh_type != SHT_SYMTAB) {
        fprintf(stderr, "Not a symbol table\n");
        return;
    }
    fseek(file, sh_symtab.sh_offset, SEEK_SET);
    int nbEntries = sh_symtab.sh_size / sh_symtab.sh_entsize;
    for (int i = 0 ; i < nbEntries ; i++) {
        if (!fread(&symTable[i].st_name, sizeof(Elf32_Word), 1, file))
            fprintf(stderr, "Read error\n");

        if (!fread(&symTable[i].st_value, sizeof(Elf32_Addr), 1, file))
            fprintf(stderr, "Read error\n");

        if (!fread(&symTable[i].st_size, sizeof(Elf32_Word), 1, file))
            fprintf(stderr, "Read error\n");

        if (!fread(&symTable[i].st_info, sizeof(unsigned char), 1, file))
            fprintf(stderr, "Read error\n");

        if (!fread(&symTable[i].st_other, sizeof(unsigned char), 1, file))
            fprintf(stderr, "Read error\n");

        if (!fread(&symTable[i].st_shndx, sizeof(Elf32_Half), 1, file))
            fprintf(stderr, "Read error\n");
    }

    if (!IS_BIGENDIAN()) {
        for (int i = 0 ; i < nbEntries ; i++) {
            SWAPB(&symTable[i].st_name, sizeof(Elf32_Word));
            SWAPB(&symTable[i].st_value, sizeof(Elf32_Addr));
            SWAPB(&symTable[i].st_size, sizeof(Elf32_Word));
            SWAPB(&symTable[i].st_info, sizeof(unsigned char));
            SWAPB(&symTable[i].st_other, sizeof(unsigned char));
            SWAPB(&symTable[i].st_shndx, sizeof(Elf32_Half));
        }
    }
}


void getHeaderClass(char *class, Elf32_Ehdr ehdr) {
    switch (ehdr.e_ident[EI_CLASS]) {
        case ELFCLASSNONE:
            strcpy(class, "ELFNONE");
            return;
        case ELFCLASS32:
            strcpy(class, "ELF32");
            return;
        case ELFCLASS64:
            strcpy(class, "ELF64");
            return;
        default:
            break;
    }
    strcpy(class, "UNKNOWN");
}

void getHeaderData(char *data, Elf32_Ehdr ehdr) {
    switch (ehdr.e_ident[EI_DATA]) {
        case ELFDATANONE:
            strcpy(data, "Invalid data encoding");
            return;
        case ELFDATA2LSB:
            strcpy(data, "2's complement, little endian");
            return;
        case ELFDATA2MSB:
            strcpy(data, "2's complement, big endian");
            return;
        default:
            break;
    }
    strcpy(data, "UNKNOWN");
}

void getHeaderOSABI(char *osabi, Elf32_Ehdr ehdr) {
    switch (ehdr.e_ident[EI_OSABI]) {
        case ELFOSABI_SYSV:
            strcpy(osabi, "UNIX - System V");
            return;
        case ELFOSABI_HPUX:
            strcpy(osabi, "HP-UX");
            return;
        case ELFOSABI_NETBSD:
            strcpy(osabi, "NetBSD");
            return;
        case ELFOSABI_LINUX:
            strcpy(osabi, "Linux");
            return;
        case ELFOSABI_SOLARIS:
            strcpy(osabi, "Solaris");
            return;
        case ELFOSABI_IRIX:
            strcpy(osabi, "IRIX");
            return;
        case ELFOSABI_FREEBSD:
            strcpy(osabi, "FreeBSD");
            return;
        case ELFOSABI_TRU64:
            strcpy(osabi, "TRU64 UNIX");
            return;
        case ELFOSABI_ARM:
            strcpy(osabi, "ARM architecture");
            return;
        case ELFOSABI_STANDALONE:
            strcpy(osabi, "Stand-alone (embedded)");
            return;
        default:
            if (ehdr.e_ident[EI_OSABI] == ELFOSABI_NONE) {
                strcpy(osabi, "UNIX - System V");
                return;
            }
            break;
    }
    strcpy(osabi, "UNKNOWN");
}

void getHeaderType(char *type, Elf32_Ehdr ehdr) {
    switch (ehdr.e_type) {
        case ET_NONE:
            strcpy(type, "NONE (No file type)");
            return;
        case ET_REL:
            strcpy(type, "REL (Relocatable file)");
            return;
        case ET_EXEC:
            strcpy(type, "EXEC (Executable file)");
            return;
        case ET_DYN:
            strcpy(type, "DYN (Shared object file)");
            return;
        case ET_CORE:
            strcpy(type, "CORE (Core file)");
            return;
        case ET_LOPROC:
            strcpy(type, "LOPROC (Processor-specific)");
            return;
        case ET_HIPROC:
            strcpy(type, "HIPROC (Processor-specific)");
            return;
        default:
            break;
    }
    strcpy(type, "UNKNOWN");
}

void getHeaderMachine(char *machine, Elf32_Ehdr ehdr) {
    switch (ehdr.e_machine) {
        case ET_NONE:
            strcpy(machine, "No machine");
            return;
        case EM_M32:
            strcpy(machine, "AT&T WE 32100");
            return;
        case EM_SPARC:
            strcpy(machine, "SPARC");
            return;
        case EM_386:
            strcpy(machine, "Intel architecture");
            return;
        case EM_68K:
            strcpy(machine, "Motorola 68000");
            return;
        case EM_88K:
            strcpy(machine, "Motorola 88000");
            return;
        case EM_860:
            strcpy(machine, "Intel 80860");
            return;
        case EM_MIPS:
            strcpy(machine, "MIPS RS3000 Big-Endian");
            return;
        case EM_ARM:
            strcpy(machine, "ARM");
            return;
        default:
            if (ehdr.e_machine >= 11 && ehdr.e_machine <= 16) {
                strcpy(machine, "RESERVED");
                return;
            }
            break;
    }
    strcpy(machine, "UNKNOWN");
}

void getSectionName(char *name, FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, int numSection) {
    fseek(file, shdrTable[ehdr.e_shstrndx].sh_offset + shdrTable[numSection].sh_name, SEEK_SET);
    if (!fread(name, sizeof(char), STR_SIZE, file))
        fprintf(stderr, "Empty name\n");
}

int sectionName2Index(char *name, FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable) {
    char sectionName[STR_SIZE];
    for (int i = 0 ; i < ehdr.e_shnum ; i++) {
        getSectionName(sectionName, file, ehdr, shdrTable, i);
        if (strcmp(sectionName, name) == 0)
            return i;
    }
    fprintf(stderr, "Section not found '%s'\n", name);
    return -1;
}

void getSectionType(char *type, Elf32_Shdr shdr) {
    switch (shdr.sh_type) {
        case SHT_NULL:
            strcpy(type, "NULL");
            return;
        case SHT_PROGBITS:
            strcpy(type, "PROGBITS");
            return;
        case SHT_SYMTAB:
            strcpy(type, "SYMTAB");
            return;
        case SHT_STRTAB:
            strcpy(type, "STRTAB");
            return;
        case SHT_RELA:
            strcpy(type, "RELA");
            return;
        case SHT_HASH:
            strcpy(type, "HASH");
            return;
        case SHT_DYNAMIC:
            strcpy(type, "DYNAMIC");
            return;
        case SHT_NOTE:
            strcpy(type, "NOTE");
            return;
        case SHT_NOBITS:
            strcpy(type, "NOBITS");
            return;
        case SHT_REL:
            strcpy(type, "REL");
            return;
        case SHT_SHLIB:
            strcpy(type, "SHLIB");
            return;
        case SHT_DYNSYM:
            strcpy(type, "DYNSYM");
            return;
        case SHT_LOPROC:
            strcpy(type, "LOPROC");
            return;
        case SHT_HIPROC:
            strcpy(type, "HIPROC");
            return;
        case SHT_LOUSER:
            strcpy(type, "LOUSER");
            return;
        case SHT_HIUSER:
            strcpy(type, "HIUSER");
            return;
        case SHT_ARM_ATTRIBUTES:
            strcpy(type, "ARM_ATTRIBUTES");
            return;
        default:
            break;
    }
    strcpy(type, "UNKNOWN");
}

void getSectionFlags(char *flags, Elf32_Shdr shdr) {
    strcpy(flags, "");
    Elf32_Word sh_flags = shdr.sh_flags;
    strcat(flags, sh_flags & SHF_WRITE ? "W" : "-");
    strcat(flags, sh_flags & SHF_ALLOC ? "A" : "-");
    strcat(flags, sh_flags & SHF_EXECINSTR ? "X" : "-");
    strcat(flags, sh_flags & SHF_MERGE ? "M" : "-");
    strcat(flags, sh_flags & SHF_STRINGS ? "S" : "-");
    strcat(flags, sh_flags & SHF_INFO_LINK ? "I" : "-");
    strcat(flags, sh_flags & SHF_LINK_ORDER ? "L" : "-");
    strcat(flags, sh_flags & SHF_OS_NONCONFORMING ? "O" : "-");
    strcat(flags, sh_flags & SHF_GROUP ? "G" : "-");
    strcat(flags, sh_flags & SHF_TLS ? "T" : "-");
    strcat(flags, sh_flags & SHF_COMPRESSED ? "C" : "-");
    strcat(flags, sh_flags & SHF_MASKOS ? "o" : "-");
    strcat(flags, sh_flags & SHF_MASKPROC ? "p" : "-");
    strcat(flags, sh_flags & SHF_ORDERED ? "R" : "-");
    strcat(flags, sh_flags & SHF_EXCLUDE ? "E" : "-");
}

void getSymbolName(char *name, FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, Elf32_Sym symEntry) {
    if (symEntry.st_name == STN_UNDEF) {
        getSectionName(name, file, ehdr, shdrTable, symEntry.st_shndx);
        return;
    }
    Elf32_Shdr sh_strtab = shdrTable[sectionName2Index(".strtab", file, ehdr, shdrTable)];
    fseek(file, sh_strtab.sh_offset + symEntry.st_name, SEEK_SET);
    if (!fread(name, sizeof(char), STR_SIZE, file))
        fprintf(stderr, "Read error\n");
}

void getSymbolType(char *type, Elf32_Sym symEntry) {
    switch (ELF32_ST_TYPE(symEntry.st_info)) {
        case STT_NOTYPE:
            strcpy(type, "NOTYPE");
            return;
        case STT_OBJECT:
            strcpy(type, "OBJECT");
            return;
        case STT_FUNC:
            strcpy(type, "FUNC");
            return;
        case STT_SECTION:
            strcpy(type, "SECTION");
            return;
        case STT_FILE:
            strcpy(type, "FILE");
            return;
        case STT_LOPROC:
            strcpy(type, "LOPROC");
            return;
        case STT_HIPROC:
            strcpy(type, "HIPROC");
            return;
        default:
            break;
    }
    strcpy(type, "UNKNOWN");
}

void getSymbolBind(char *bind, Elf32_Sym symEntry) {
    switch (ELF32_ST_BIND(symEntry.st_info)) {
        case STB_LOCAL:
            strcpy(bind, "LOCAL");
            return;
        case STB_GLOBAL:
            strcpy(bind, "GLOBAL");
            return;
        case STB_WEAK:
            strcpy(bind, "WEAK");
            return;
        case STB_LOPROC:
            strcpy(bind, "LOPROC");
            return;
        case STB_HIPROC:
            strcpy(bind, "HIPROC");
            return;
        default:
            break;
    }
    strcpy(bind, "UNKNOWN");
}

void getSymbolVis(char *visibility, Elf32_Sym symEntry) {
    switch (ELF32_ST_VISIBILITY(symEntry.st_other)) {
        case STV_DEFAULT:
            strcpy(visibility, "DEFAULT");
            return;
        case STV_INTERNAL:
            strcpy(visibility, "INTERNAL");
            return;
        case STV_HIDDEN:
            strcpy(visibility, "HIDDEN");
            return;
        case STV_PROTECTED:
            strcpy(visibility, "PROTECTED");
            return;
        default:
            break;
    }
    strcpy(visibility, "UNKNOWN");
}

void getSymbolNdx(char *ndx, Elf32_Sym symEntry) {
    switch (symEntry.st_shndx) {
        case SHN_UNDEF:
            strcpy(ndx, "UND");
            return;
        case SHN_ABS:
            strcpy(ndx, "ABS");
            return;
        case SHN_COMMON:
            strcpy(ndx, "COM");
            return;
        default:
            break;
    }
    sprintf(ndx, "%d", symEntry.st_shndx);
}


void PrintELFHeader(Elf32_Ehdr ehdr) {
    printf("ELF File's Header:");
    printf("\n  Ident: ");
    for (int i = 0 ; i < EI_NIDENT ; i++) {
        printf("%.2x ", ehdr.e_ident[i]);
    }

    char class[STR_SIZE];
    char data[STR_SIZE];
    char osabi[STR_SIZE];
    char type[STR_SIZE];
    char machine[STR_SIZE];

    getHeaderClass(class, ehdr);
    printf("\n  Class: \t\t\t\t%s", class);

    getHeaderData(data, ehdr);
    printf("\n  Data: \t\t\t\t%s", data);

    // File Version
    printf("\n  Version: \t\t\t\t");
    if (ehdr.e_ident[EI_VERSION] == EV_NONE)
        printf("%d (invalid)", ehdr.e_ident[EI_VERSION]);
    else
        printf("%d (current)", ehdr.e_ident[EI_VERSION]);

    // OS/ABI
    getHeaderOSABI(osabi, ehdr);
    printf("\n  OS/ABI: \t\t\t\t%s", osabi);

    // ABI Version
    printf("\n  ABI Version: \t\t\t\t%d", ehdr.e_ident[EI_ABIVERSION]);

    // File type
    getHeaderType(type, ehdr);
    printf("\n  Type: \t\t\t\t%s", type);

    // Required architecture
    getHeaderMachine(machine, ehdr);
    printf("\n  Machine: \t\t\t\t%s", machine);

    printf("\n  Version: \t\t\t\t0x%x", ehdr.e_version);

    printf("\n  Entry point address: \t\t\t0x%x", ehdr.e_entry);

    printf("\n  Start of program headers: \t\t%d (bytes into file)", ehdr.e_phoff);

    printf("\n  Start of section headers: \t\t%d (bytes into file)", ehdr.e_shoff);

    printf("\n  Flags: \t\t\t\t0x%x", ehdr.e_flags);

    printf("\n  Size of this header: \t\t\t%d (bytes)", ehdr.e_ehsize);

    printf("\n  Size of program headers: \t\t%d (bytes)", ehdr.e_phentsize);

    printf("\n  Number of program headers: \t\t%d", ehdr.e_phnum);

    printf("\n  Size of section headers: \t\t%d (bytes)", ehdr.e_shentsize);

    printf("\n  Number of section headers: \t\t%d", ehdr.e_shnum);

    printf("\n  Section header string table index: \t%d\n", ehdr.e_shstrndx);
}

void PrintELFTableSections(FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable) {
    printf("Section table headers:\n");
    printf("  [N°]  Section Name              Type            Addr     Off    Size   ES Flg Flg Keys        Lk Inf Al\n");
    char name[STR_SIZE];
    char type[STR_SIZE];
    char flags[16];
    for (int i = 0 ; i < ehdr.e_shnum ; i++) {
        getSectionName(name, file, ehdr, shdrTable, i);
        getSectionType(type, shdrTable[i]);
        getSectionFlags(flags, shdrTable[i]);
        printf("  [%2d]  %-24.24s  %-14s  %8.8x %6.6x %6.6x %2.2x %3.3x %15s %2d %3d %2d\n", i,
               name,
               type,
               shdrTable[i].sh_addr,
               shdrTable[i].sh_offset,
               shdrTable[i].sh_size,
               shdrTable[i].sh_entsize,
               shdrTable[i].sh_flags,
               flags,
               shdrTable[i].sh_link,
               shdrTable[i].sh_info,
               shdrTable[i].sh_addralign
        );
    }
    printf("Key to Flags:\n"
           "  W: WRITE, A: ALLOC, X: EXECINSTR, M: MERGE, S: STRINGS\n"
           "  I: INFO_LINK, L: LINK_ORDER, O: OS_NONCONFORMING\n"
           "  G: GROUP, T: TLS, C: COMPRESSED, o: MASKOS\n"
           "  p: MASKPROC, g: GNU_RETAIN, R: ORDERED, E: EXCLUDE\n");
}

void PrintELFSectionNum(FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, int numSection) {
    if (numSection < 0 || numSection >= ehdr.e_shnum) {
        fprintf(stderr, "Section number out of range\n");
        return;
    }

    char *buff = malloc(shdrTable[ehdr.e_shstrndx].sh_size);

    if (buff != NULL) {
        fseek(file, shdrTable[numSection].sh_offset, SEEK_SET);
        if (!fread(buff, 1, shdrTable[ehdr.e_shstrndx].sh_size, file))
            fprintf(stderr, "Read error\n");
    }

    char name[STR_SIZE];
    getSectionName(name, file, ehdr, shdrTable, numSection);
    printf("Section %d (%s):", numSection, name);

    int i;
    char buff16[17] = "";
    for (i = 0 ; i < shdrTable[numSection].sh_size ; i++) {
        if (i % 16 == 0) {
            if (i != 0)
                printf("  |%s|", buff16);
            printf("\n  0x%.8x ", shdrTable[numSection].sh_addr + i);
        }
        if (i % 4 == 0)
            printf(" ");
        printf("%.2x", buff[i]);
        buff16[i % 16] = buff[i] == 0 ? '.' : buff[i];
    }
    while (i % 16 != 0) {
        if (i % 4 == 0)
            printf(" ");
        printf("  ");
        buff16[i % 16] = ' ';
        i++;
    }

    if (shdrTable[numSection].sh_size == 0)
        printf("\n  No data");
    else
        printf("  |%s|", buff16);
    printf("\n");

    free(buff);
}

void PrintELFSectionNom(FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, char *nomSection) {
    PrintELFSectionNum(file, ehdr, shdrTable, sectionName2Index(nomSection, file, ehdr, shdrTable));
}

void PrintELFTableSymbols(FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, Elf32_Sym *symTable) {
    printf("Symbol table entries:\n");
    printf("  [N°]    Value  Size Type    Bind   Vis      Ndx Name\n");
    char name[STR_SIZE];
    char type[STR_SIZE];
    char bind[STR_SIZE];
    char vis[STR_SIZE];
    char ndx[STR_SIZE];
    Elf32_Shdr sh_symtab = shdrTable[sectionName2Index(".symtab", file, ehdr, shdrTable)];
    for (int i = 0 ; i < sh_symtab.sh_size / sh_symtab.sh_entsize ; i++) {
        getSymbolName(name, file, ehdr, shdrTable, symTable[i]);
        getSymbolType(type, symTable[i]);
        getSymbolBind(bind, symTable[i]);
        getSymbolVis(vis, symTable[i]);
        getSymbolNdx(ndx, symTable[i]);
        printf("  [%2d] %08x %5d %-7s %-6s %-7s %4s %s \n", i,
               symTable[i].st_value,
               symTable[i].st_size,
               type,
               bind,
               vis,
               ndx,
               name
        );
    }
}

char *getSymType(char c){
    switch(c){
        case 'd':
            return "R_ARM_JUMP_24";
        case '2':
            return "R_ARM_ABS_32";
        case 'c':
            return "R_ARM_CALL";
        case '4':
            return "ARM_ABS_8";
        default:
            return strcat(" ",&c);
    }
}
void PrintRelocationTable(FILE *file, Elf32_Ehdr *ehdr, Elf32_Shdr *shdr, Elf32_Sym *symTable){
    int shstrndx = ehdr->e_shstrndx;
    Elf32_Shdr *shstrhdr = &shdr[shstrndx];

    // Get the section header string table
    char *shstrtab = malloc(shstrhdr->sh_size);
    fseek(file, shstrhdr->sh_offset, SEEK_SET);
    if(!fread(shstrtab, shstrhdr->sh_size, 1, file))
        fprintf(stderr, "Read error\n");

    // Iterate through the section headers and print the relocation sections
    for (int i = 0; i <= ehdr->e_shnum; i++) {
        if (shdr[i].sh_type == SHT_REL) {
            printf("Relocation section '%s' at offset 0x%x contains %d entries:\n",
                   &shstrtab[shdr[i].sh_name], shdr[i].sh_offset, shdr[i].sh_size / shdr[i].sh_entsize);
            Elf32_Rel *rel = malloc(shdr[i].sh_size);
            fseek(file, shdr[i].sh_offset, SEEK_SET);
            if(!fread(rel, shdr[i].sh_size, 1, file))
                fprintf(stderr, "Read error\n");
            printf(" Offset      Info         Type          Sym.value   Sym.name\n");
            char name[STR_SIZE]="";
            // Iterate through the relocation entries and print them
            for (int j = 0; j < shdr[i].sh_size / sizeof(Elf32_Rel); j++) {
                int r = rel[j].r_info;
                char nombre[STR_SIZE]="";
                sprintf(nombre,"%x",r);
                if(nombre[0]=='1'){
                    nombre[0]=nombre[1];
                }
                strcpy(name,"");
                r = (r << 8) >> 24;
                getSymbolName(name, file, *ehdr, shdr, symTable[r]);
                printf(" %08x  %08x    %s      %08x    %s\n", rel[j].r_offset, rel[j].r_info,
                       getSymType(nombre[0]), symTable[r].st_value, name);
            }
            free(rel);
        }
    }

    free(shstrtab);
}
