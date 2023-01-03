#include "utils.h"


int IS_BIGENDIAN() {
    static int one = 1;
    return ((*(char *) &one) == 0);
}

// This function will help us swap bytes depending on the endianness of the machine
void SWAPB(void *ptr, size_t size) {
    char *tmp = malloc(size);
    memcpy(tmp, ptr, size);
    for (int i = 0 ; i < size ; i++) {
        ((char *) ptr)[i] = tmp[size - i - 1];
    }
    free(tmp);
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