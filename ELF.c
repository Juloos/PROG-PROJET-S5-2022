#include "ELF.h"


void ReadELFile(FILE *file) {
}

void ReadELFHeader(FILE *file, Elf32_Ehdr *ehdr) {
    fseek(file, 0, SEEK_SET);

    for (int i = 0; i < EI_NIDENT; i++) {
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
        fprintf(stderr,
                "Read error : (header) address to which the system first transfers control, thus starting the process\n");

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
        fprintf(stderr,
                "Read error : (header) section header table index of the entry associated with the section name string table\n");

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
    for (int i = 0; i < ehdr.e_shnum; i++) {
        if (!fread(&shdrTable[i].sh_name, sizeof(Elf32_Word), 1, file))
            fprintf(stderr, "Read error : (table section) name\n");

        if (!fread(&shdrTable[i].sh_type, sizeof(Elf32_Word), 1, file))
            fprintf(stderr, "Read error : (table section) type\n");

        if (!fread(&shdrTable[i].sh_flags, sizeof(Elf32_Word), 1, file))
            fprintf(stderr, "Read error : (table section) flags\n");

        if (!fread(&shdrTable[i].sh_addr, sizeof(Elf32_Addr), 1, file))
            fprintf(stderr, "Read error : (table section) address at which the section's first byte should reside\n");

        if (!fread(&shdrTable[i].sh_offset, sizeof(Elf32_Off), 1, file))
            fprintf(stderr,
                    "Read error : (table section) value gives the byte offset from the beginning of the file to the first byte in the section\n");

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
    for (int i = 0; i < nbEntries; i++) {
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
        for (int i = 0; i < nbEntries; i++) {
            SWAPB(&symTable[i].st_name, sizeof(Elf32_Word));
            SWAPB(&symTable[i].st_value, sizeof(Elf32_Addr));
            SWAPB(&symTable[i].st_size, sizeof(Elf32_Word));
            SWAPB(&symTable[i].st_info, sizeof(unsigned char));
            SWAPB(&symTable[i].st_other, sizeof(unsigned char));
            SWAPB(&symTable[i].st_shndx, sizeof(Elf32_Half));
        }
    }
}

void
ReadELFRelocationTable(FILE *file, Elf32_Rel **relTables, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, Elf32_Sym *symTable) {
    for (int i = 0; i < ehdr.e_shnum; i++) {
        if (shdrTable[i].sh_type == SHT_REL) {
            relTables[i] = create_ELFTableRel(shdrTable[i]);
            fseek(file, shdrTable[i].sh_offset, SEEK_SET);
            for (int j = 0; j < shdrTable[i].sh_size / shdrTable[i].sh_entsize; j++) {

                if (!fread(&relTables[i][j].r_offset, sizeof(Elf32_Addr), 1, file))
                    fprintf(stderr, "Read error : (ReadELFRelocationTable) r_offset\n");

                if (!fread(&relTables[i][j].r_info, sizeof(Elf32_Word), 1, file))
                    fprintf(stderr, "Read error : (ReadELFRelocationTable) r_info\n");
            }
            if (!IS_BIGENDIAN()) {
                for (int j = 0; j < shdrTable[i].sh_size / shdrTable[i].sh_entsize; j++) {
                    SWAPB(&relTables[i][j].r_offset, sizeof(Elf32_Addr));
                    SWAPB(&relTables[i][j].r_info, sizeof(Elf32_Word));
                }
            }
        }
    }
}


void PrintELFHeader(Elf32_Ehdr ehdr) {
    printf("ELF File's Header:");
    printf("\n  Ident: ");
    for (int i = 0; i < EI_NIDENT; i++) {
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

    printf("\n  Section header string table index: \t%d\n\n", ehdr.e_shstrndx);
}

void PrintELFTableSections(FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable) {
    printf("Section table headers:\n");
    printf("  [N°]  Section Name              Type            Addr     Off    Size   ES Flg Flg Keys        Lk Inf Al\n");
    char name[STR_SIZE];
    char type[STR_SIZE];
    char flags[16];
    for (int i = 0; i < ehdr.e_shnum; i++) {
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
           "  p: MASKPROC, g: GNU_RETAIN, R: ORDERED, E: EXCLUDE\n\n");
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
        int i;
        uint8_t *buff = getSectionContent(file, shdrTable[numSection]);
        uint8_t buff16[17];
        buff16[16] = 0;
        for (i = 0; i < shdrTable[numSection].sh_size; i++) {
            if (i % 16 == 0)
                printf("\n  0x%.8x ", i);
            if (i % 4 == 0)
                printf(" ");
            printf("%.2x", buff[i]);
            buff16[i % 16] = (32 <= buff[i] && buff[i] <= 126) ? buff[i] : '.';
            if (i % 16 == 15)
                printf("  %s", buff16);
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
            printf("  %s", buff16);

        free(buff);

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
    for (int i = 0; i < sh_symtab.sh_size / sh_symtab.sh_entsize; i++) {
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
    printf("\n");
}

void PrintELFRelocationTable(FILE *file, Elf32_Ehdr ehdr, Elf32_Shdr *shdrTable, Elf32_Sym *symTable,
                             Elf32_Rel **relTables) {
    char name[STR_SIZE];
    char type[STR_SIZE];

    int nbRel = 0;
    for (int i = 0; i < ehdr.e_shnum; i++) {
        if (relTables[i] != NULL) {
            strcpy(name, "");
            getSectionName(name, file, ehdr, shdrTable, i);
            printf("Relocation section '%s' at offset 0x%x contains %d entries:\n",
                   name,
                   shdrTable[i].sh_offset,
                   shdrTable[i].sh_size / shdrTable[i].sh_entsize);

            int rsym;
            printf(" Offset      Info         Type           Sym.value   Sym.name\n");
            for (int j = 0; j < shdrTable[i].sh_size / shdrTable[i].sh_entsize; j++) {
                rsym = ELF32_R_SYM(relTables[i][j].r_info);
                strcpy(name, "");
                getSymbolName(name, file, ehdr, shdrTable, symTable[rsym]);
                strcpy(type, "");
                getRelType(type, relTables[i][j]);
                printf(" %.8x  %.8x    %-12s      %.8x    %s\n",
                       relTables[i][j].r_offset,
                       relTables[i][j].r_info,
                       type,
                       symTable[rsym].st_value,
                       name);
            }
            printf("\n");
            nbRel++;
        }
    }
    if (nbRel == 0)
        printf("There are no relocations in this file.\n\n");
}


FusionELF_Etape6 *LinkELFRenumSections(FILE *input1, FILE *input2, FILE *output) {
    Elf32_Ehdr ehdr1, ehdr2;
    Elf32_Shdr *shdrTable1, *shdrTable2;
    char name1[STR_SIZE], name2[STR_SIZE];

    ReadELFHeader(input1, &ehdr1);
    ReadELFHeader(input2, &ehdr2);
    shdrTable1 = create_ELFTableSections(ehdr1);
    shdrTable2 = create_ELFTableSections(ehdr2);
    ReadELFTableSections(input1, ehdr1, shdrTable1);
    ReadELFTableSections(input2, ehdr2, shdrTable2);

    FusionELF_Etape6 *res = create_fusion6(ehdr2.e_shnum);
    res->renum[0] = 0;
    for (int j = 0; j < ehdr2.e_shnum; j++)
        res->offsets[j] = -1;

    uint8_t *buff;
    for (int i = 0; i < ehdr1.e_shnum; i++) {
        if (shdrTable1[i].sh_size) {
            buff = getSectionContent(input1, shdrTable1[i]);
            if (!fwrite(buff, 1, shdrTable1[i].sh_size, output))
                fprintf(stderr, "Write error : (LinkELFRenumSections) section %d of input1\n", i);
            free(buff);
        }

        if (shdrTable1[i].sh_type == SHT_PROGBITS) {
            strcpy(name1, "");
            getSectionName(name1, input1, ehdr1, shdrTable1, i);

            for (int j = 1; j < ehdr2.e_shnum; j++) {
                strcpy(name2, "");
                getSectionName(name2, input2, ehdr2, shdrTable2, j);
                if (shdrTable2[j].sh_size && strcmp(name1, name2) == 0) {
                    buff = getSectionContent(input2, shdrTable2[j]);
                    if (!fwrite(buff, 1, shdrTable2[j].sh_size, output))
                        fprintf(stderr, "Write error : (LinkELFRenumSections) section %d of input2\n", j);
                    free(buff);
                    res->offsets[j] = shdrTable1[i].sh_size;
                    res->renum[j] = i;
                }
            }
        }
    }

    int e_shnum_acc = 0;
    for (int j = 1; j < ehdr2.e_shnum; j++) {
        if (res->offsets[j] == -1) {
            res->renum[j] = ehdr1.e_shnum + e_shnum_acc;
            if (shdrTable2[j].sh_size) {
                buff = getSectionContent(input2, shdrTable2[j]);
                if (!fwrite(buff, 1, shdrTable2[j].sh_size, output))
                    fprintf(stderr, "Write error : (LinkELFRenumSections) section %d of input2\n", j);
                free(buff);
            }
            e_shnum_acc++;
        }
    }

    res->snb = ehdr1.e_shnum + e_shnum_acc;
    return res;
}


SymbolsTable *LinkELFSymbols(FILE *input1, FILE *input2, FusionELF_Etape6 *sections) {
    // Table des symboles de input1
    SymbolsTable *input1SymbsTable = GetSymbolsTable(input1);
    // Table des symboles de input2
    SymbolsTable *input2SymbsTable = GetSymbolsTable(input2);

    // Fusion des deux tables des symboles
    // Vérification qu'il n'y a pas deux symboles globaux définis avec le même nom dans les deux tables des symboles
    int i = 0;
    int j = 0;
    int error = 0;
    while (i < input1SymbsTable->nbElems && !error) {
        j = i + 1;
        while (j < input2SymbsTable->nbElems && !error) {
            error = ELF32_ST_BIND(input1SymbsTable->symbols[i].st_info) == STB_GLOBAL &&
                    ELF32_ST_BIND(input2SymbsTable->symbols[i].st_info) == STB_GLOBAL
                    && input1SymbsTable->symbols[i].st_name == input2SymbsTable->symbols[i].st_name
                    && ELF32_ST_TYPE(input1SymbsTable->symbols[i].st_info) != STT_NOTYPE
                    && ELF32_ST_TYPE(input2SymbsTable->symbols[j].st_info) != STT_NOTYPE;
            j++;
        }
        i++;
    }

    Elf32_Sym symbolsResult[input1SymbsTable->nbElems + input2SymbsTable->nbElems];
    SymbolsTable *resultTable = NULL;
    int nbElems = 0;

    // Si la fusion est possible
    if (!error) {
        for (int i = 0; i < input1SymbsTable->nbElems; i++) {
            nbElems++;
            symbolsResult[nbElems - 1] = input1SymbsTable->symbols[i];
        }

        for (int i = 0; i < input2SymbsTable->nbElems; i++) {
            // Pour un symbole local
            if (ELF32_ST_BIND(input2SymbsTable->symbols[i].st_info) == STB_LOCAL) {
                int j = 0;
                while (i < input1SymbsTable->nbElems &&
                       input1SymbsTable->symbols[j].st_name != input2SymbsTable->symbols[i].st_name) {
                    j++;
                }
                if (j == input1SymbsTable->nbElems) {
                    if(input2SymbsTable->symbols[i].st_shndx == SHN_COMMON) {
                        input2SymbsTable->symbols[i].st_shndx = sections->renum[input2SymbsTable->symbols[i].st_shndx];
                    }
                    nbElems++;
                    symbolsResult[nbElems - 1] = input2SymbsTable->symbols[i];
                }
            }
                // Pour un symbole global on l'écrit que s'il est défini dans la table des symboles de input2 mais pas dans celle de input1
            else {
                if (ELF32_ST_TYPE(input2SymbsTable->symbols[i].st_info) != STT_NOTYPE) {
                    j = 0;
                    while (j < input1SymbsTable->nbElems &&
                           input1SymbsTable->symbols[j].st_name != input2SymbsTable->symbols[i].st_name) {
                        j++;
                    }
                    if (j == input1SymbsTable->nbElems ||
                        ELF32_ST_TYPE(input1SymbsTable->symbols[j].st_info) == STT_NOTYPE) {
                        if(input2SymbsTable->symbols[i].st_shndx == SHN_COMMON) {
                            input2SymbsTable->symbols[i].st_shndx = sections->renum[input2SymbsTable->symbols[i].st_shndx];
                        }
                        nbElems++;
                        symbolsResult[nbElems - 1] = input2SymbsTable->symbols[i];
                    }
                }
            }
        }

        resultTable = malloc(sizeof(SymbolsTable));
        resultTable->nbElems = nbElems;
        resultTable->symbols = malloc(sizeof(Elf32_Sym) * nbElems);

        for (int i = 0; i < nbElems; i++) {
            resultTable->symbols[i] = symbolsResult[i];
        }
    } else {
        fprintf(stderr,
                "Erreur deux symboles avec le même sont définis dans les deux tables des symboles des fichiers d'entrées\n");
    }

    // Libération de la mémoire
    free(input1SymbsTable);
    free(input2SymbsTable);

    return resultTable;
}

SymbolsTable *GetSymbolsTable(FILE *input) {
    Elf32_Ehdr *header = malloc(sizeof(Elf32_Ehdr));
    ReadELFHeader(input, header);

    Elf32_Shdr *sectionsTable = create_ELFTableSections(*header);
    ReadELFTableSections(input, *header, sectionsTable);

    Elf32_Shdr symbolsTableSection = sectionsTable[sectionName2Index(".symtab", input, *header, sectionsTable)];

    Elf32_Sym *symbolsTable = create_ELFTableSymbols(symbolsTableSection);
    ReadELFTableSymbols(input, symbolsTable, symbolsTableSection);

    free(header);
    free(sectionsTable);

    SymbolsTable *table = malloc(sizeof(SymbolsTable));
    table->nbElems = symbolsTableSection.sh_size / symbolsTableSection.sh_entsize;
    table->symbols = symbolsTable;

    return table;
}