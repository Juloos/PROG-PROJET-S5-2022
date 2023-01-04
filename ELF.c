#include "ELF.h"


void ReadELFile(FILE *file) {
}

void ReadELFHeader(FILE *file, Elf32_Ehdr *ehdr) {
    fseek(file, 0, SEEK_SET);

    for (int i = 0 ; i < EI_NIDENT ; i++) {
        if (!fread(&ehdr->e_ident[i], sizeof(unsigned char), 1, file))
            fprintf(stderr, "Read error : (header) magic\n");
    }

    if (!fread(&ehdr->e_type, sizeof(Elf32_Half), 1, file))
        fprintf(stderr, "Read error : (header) type\n");

    if (!fread(&ehdr->e_machine, sizeof(Elf32_Half), 1, file))
        fprintf(stderr, "Read error : (header) machine\n");

    if (!fread(&ehdr->e_version, sizeof(Elf32_Word), 1, file))
        fprintf(stderr, "Read error : (header) version\n");

    if (!fread(&ehdr->e_entry, sizeof(Elf32_Addr), 1, file))
        fprintf(stderr, "Read error : (header) address to which the system first transfers control, thus starting the process\n");

    if (!fread(&ehdr->e_phoff, sizeof(Elf32_Off), 1, file))
        fprintf(stderr, "Read error : (header) program header table's file\n");

    if (!fread(&ehdr->e_shoff, sizeof(Elf32_Off), 1, file))
        fprintf(stderr, "Read error : (header) section header table's\n");

    if (!fread(&ehdr->e_flags, sizeof(Elf32_Word), 1, file))
        fprintf(stderr, "Read error : (header) flags\n");

    if (!fread(&ehdr->e_ehsize, sizeof(Elf32_Half), 1, file))
        fprintf(stderr, "Read error : (header) size\n");

    if (!fread(&ehdr->e_phentsize, sizeof(Elf32_Half), 1, file))
        fprintf(stderr, "Read error : (header) size in bytes of one entry in the file's program header table\n");

    if (!fread(&ehdr->e_phnum, sizeof(Elf32_Half), 1, file))
        fprintf(stderr, "Read error : (header) number of entries in the program header table\n");

    if (!fread(&ehdr->e_shentsize, sizeof(Elf32_Half), 1, file))
        fprintf(stderr, "Read error : (header) section header's size\n");

    if (!fread(&ehdr->e_shnum, sizeof(Elf32_Half), 1, file))
        fprintf(stderr, "Read error : (header) number of entries in the section header table\n");

    if (!fread(&ehdr->e_shstrndx, sizeof(Elf32_Half), 1, file))
        fprintf(stderr, "Read error : (header) section header table index of the entry associated with the section name string table\n");

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

void ReadELFTableSections(FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable) {
    fseek(file, ehdr.e_shoff, SEEK_SET);
    for (int i = 0 ; i < ehdr.e_shnum ; i++) {
        if (!fread(&shdrTable[i].sh_name, sizeof(Elf32_Word), 1, file))
            fprintf(stderr, "Read error : (table section) name\n");

        if (!fread(&shdrTable[i].sh_type, sizeof(Elf32_Word), 1, file))
            fprintf(stderr, "Read error : (table section) type\n");

        if (!fread(&shdrTable[i].sh_flags, sizeof(Elf32_Word), 1, file))
            fprintf(stderr, "Read error : (table section) flags\n");

        if (!fread(&shdrTable[i].sh_addr, sizeof(Elf32_Addr), 1, file))
            fprintf(stderr, "Read error : (table section) address at which the section's first byte should reside\n");

        if (!fread(&shdrTable[i].sh_offset, sizeof(Elf32_Off), 1, file))
            fprintf(stderr, "Read error : (table section) value gives the byte offset from the beginning of the file to the first byte in the section\n");

        if (!fread(&shdrTable[i].sh_size, sizeof(Elf32_Word), 1, file))
            fprintf(stderr, "Read error : (table section) section's size\n");

        if (!fread(&shdrTable[i].sh_link, sizeof(Elf32_Word), 1, file))
            fprintf(stderr, "Read error : (table section) section header table index link\n");

        if (!fread(&shdrTable[i].sh_info, sizeof(Elf32_Word), 1, file))
            fprintf(stderr, "Read error : (table section) extra information\n");

        if (!fread(&shdrTable[i].sh_addralign, sizeof(Elf32_Word), 1, file))
            fprintf(stderr, "Read error : (table section) address alignment constraints\n");

        if (!fread(&shdrTable[i].sh_entsize, sizeof(Elf32_Word), 1, file))
            fprintf(stderr, "Read error : (table section) table of fixed-size entries\n");

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

void ReadELFTableSymbols(FILE *file, Elf32_Sym *symTable, Elf32_Shdr sh_symtab) {
    if (sh_symtab.sh_type != SHT_SYMTAB) {
        fprintf(stderr, "Not a symbol table\n");
        return;
    }
    fseek(file, sh_symtab.sh_offset, SEEK_SET);
    int nbEntries = sh_symtab.sh_size / sh_symtab.sh_entsize;
    for (int i = 0 ; i < nbEntries ; i++) {
        if (!fread(&symTable[i].st_name, sizeof(Elf32_Word), 1, file))
            fprintf(stderr, "Read error : (TableSymbols) name\n");

        if (!fread(&symTable[i].st_value, sizeof(Elf32_Addr), 1, file))
            fprintf(stderr, "Read error : (TableSymbols) value\n");

        if (!fread(&symTable[i].st_size, sizeof(Elf32_Word), 1, file))
            fprintf(stderr, "Read error : (TableSymbols) size\n");

        if (!fread(&symTable[i].st_info, sizeof(unsigned char), 1, file))
            fprintf(stderr, "Read error : (TableSymbols) information about symbol's type and binding attributes\n");

        if (!fread(&symTable[i].st_other, sizeof(unsigned char), 1, file))
            fprintf(stderr, "Read error : (TableSymbols) no defined meaning\n");

        if (!fread(&symTable[i].st_shndx, sizeof(Elf32_Half), 1, file))
            fprintf(stderr, "Read error : (TableSymbols) the relevant section header table index\n");
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

    char name[STR_SIZE];
    getSectionName(name, file, ehdr, shdrTable, numSection);
    printf("Section %d (%s):", numSection, name);

    if (shdrTable[numSection].sh_size) {
        uint8_t buff[shdrTable[numSection].sh_size];
        fseek(file, shdrTable[numSection].sh_offset, SEEK_SET);
        if (!fread(buff, 1, shdrTable[numSection].sh_size, file))
            fprintf(stderr, "Read error : (ELFSectionNum)\n");

        int i;
        uint8_t buff16[17];
        buff16[16] = 0;
        for (i = 0 ; i < shdrTable[numSection].sh_size ; i++) {
            if (i % 16 == 0)
                printf("\n  0x%.8x ", i);
            if (i % 4 == 0)
                printf(" ");
            printf("%.2x", buff[i]);
            buff16[i % 16] = (32 <= buff[i] && buff[i] <= 126) ? buff[i] : '.';
            if (i % 16 == 15)
                printf(" %s", buff16);
        }
        int j = i;
        while (j % 16 != 0) {
            if (j % 4 == 0)
                printf(" ");
            printf("  ");
            buff16[j % 16] = ' ';
            j++;
        }

        if (i % 16 != 0)
            printf(" %s", buff16);
    } else
        printf("\n  No data");

    printf("\n");
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
