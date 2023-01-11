#include "ELF.h"


ELF *ReadELF(FILE *file) {
    ELF *elf = create_ELF();
    elf->file = file;
    ReadELFHeader(elf);
    elf->nbsh = elf->ehdr.e_shnum;
    elf->shdrTable = create_ELFTableSections(elf->ehdr);
    ReadELFTableSections(elf);
    Elf32_Shdr sh_symtab = elf->shdrTable[sectionName2Index(".symtab", file, elf->ehdr, elf->shdrTable)];
    elf->nbsym = sh_symtab.sh_size / sh_symtab.sh_entsize;
    elf->symTable = create_ELFTableSymbols(sh_symtab);
    ReadELFTableSymbols(elf);
    elf->relTables = create_ELFTablesRel(elf->ehdr);
    ReadELFRelocationTable(elf);
    elf->relTable_sizes = (int *) malloc(elf->nbsh * sizeof(int));
    for (int i = 0; i < elf->nbsh; i++) {
        if (elf->relTables[i] != NULL)
            elf->relTable_sizes[i] = elf->shdrTable[i].sh_size / elf->shdrTable[i].sh_entsize;
        else
            elf->relTable_sizes[i] = 0;
    }
    return elf;
}

void ReadELFHeader(ELF *elf) {
    fseek(elf->file, 0, SEEK_SET);

    for (int i = 0; i < EI_NIDENT; i++) {
        if (!fread(&elf->ehdr.e_ident[i], sizeof(unsigned char), 1, elf->file))
            fprintf(stderr, "Read error : (header) magic\n");
    }

    if (!fread(&elf->ehdr.e_type, sizeof(Elf32_Half), 1, elf->file))
        fprintf(stderr, "Read error : (header) type\n");

    if (!fread(&elf->ehdr.e_machine, sizeof(Elf32_Half), 1, elf->file))
        fprintf(stderr, "Read error : (header) machine\n");

    if (!fread(&elf->ehdr.e_version, sizeof(Elf32_Word), 1, elf->file))
        fprintf(stderr, "Read error : (header) version\n");

    if (!fread(&elf->ehdr.e_entry, sizeof(Elf32_Addr), 1, elf->file))
        fprintf(stderr, "Read error : (header) address to which the system first transfers control, thus starting the process\n");

    if (!fread(&elf->ehdr.e_phoff, sizeof(Elf32_Off), 1, elf->file))
        fprintf(stderr, "Read error : (header) program header table's elf->file\n");

    if (!fread(&elf->ehdr.e_shoff, sizeof(Elf32_Off), 1, elf->file))
        fprintf(stderr, "Read error : (header) section header table's\n");

    if (!fread(&elf->ehdr.e_flags, sizeof(Elf32_Word), 1, elf->file))
        fprintf(stderr, "Read error : (header) flags\n");

    if (!fread(&elf->ehdr.e_ehsize, sizeof(Elf32_Half), 1, elf->file))
        fprintf(stderr, "Read error : (header) size\n");

    if (!fread(&elf->ehdr.e_phentsize, sizeof(Elf32_Half), 1, elf->file))
        fprintf(stderr, "Read error : (header) size in bytes of one entry in the elf->file's program header table\n");

    if (!fread(&elf->ehdr.e_phnum, sizeof(Elf32_Half), 1, elf->file))
        fprintf(stderr, "Read error : (header) number of entries in the program header table\n");

    if (!fread(&elf->ehdr.e_shentsize, sizeof(Elf32_Half), 1, elf->file))
        fprintf(stderr, "Read error : (header) section header's size\n");

    if (!fread(&elf->ehdr.e_shnum, sizeof(Elf32_Half), 1, elf->file))
        fprintf(stderr, "Read error : (header) number of entries in the section header table\n");

    if (!fread(&elf->ehdr.e_shstrndx, sizeof(Elf32_Half), 1, elf->file))
        fprintf(stderr, "Read error : (header) section header table index of the entry associated with the section name string table\n");

    if (!IS_BIGENDIAN()) {
        // Not swapping Magic because apparently it's not endian dependent
        SWAPB(&elf->ehdr.e_type, sizeof(Elf32_Half));
        SWAPB(&elf->ehdr.e_machine, sizeof(Elf32_Half));
        SWAPB(&elf->ehdr.e_version, sizeof(Elf32_Word));
        SWAPB(&elf->ehdr.e_entry, sizeof(Elf32_Addr));
        SWAPB(&elf->ehdr.e_phoff, sizeof(Elf32_Off));
        SWAPB(&elf->ehdr.e_shoff, sizeof(Elf32_Off));
        SWAPB(&elf->ehdr.e_flags, sizeof(Elf32_Word));
        SWAPB(&elf->ehdr.e_ehsize, sizeof(Elf32_Half));
        SWAPB(&elf->ehdr.e_phentsize, sizeof(Elf32_Half));
        SWAPB(&elf->ehdr.e_phnum, sizeof(Elf32_Half));
        SWAPB(&elf->ehdr.e_shentsize, sizeof(Elf32_Half));
        SWAPB(&elf->ehdr.e_shnum, sizeof(Elf32_Half));
        SWAPB(&elf->ehdr.e_shstrndx, sizeof(Elf32_Half));
    }
}

void ReadELFTableSections(ELF *elf) {
    fseek(elf->file, elf->ehdr.e_shoff, SEEK_SET);
    for (int i = 0; i < elf->ehdr.e_shnum; i++) {
        if (!fread(&elf->shdrTable[i].sh_name, sizeof(Elf32_Word), 1, elf->file))
            fprintf(stderr, "Read error : (table section) name\n");

        if (!fread(&elf->shdrTable[i].sh_type, sizeof(Elf32_Word), 1, elf->file))
            fprintf(stderr, "Read error : (table section) type\n");

        if (!fread(&elf->shdrTable[i].sh_flags, sizeof(Elf32_Word), 1, elf->file))
            fprintf(stderr, "Read error : (table section) flags\n");

        if (!fread(&elf->shdrTable[i].sh_addr, sizeof(Elf32_Addr), 1, elf->file))
            fprintf(stderr, "Read error : (table section) address at which the section's first byte should reside\n");

        if (!fread(&elf->shdrTable[i].sh_offset, sizeof(Elf32_Off), 1, elf->file))
            fprintf(stderr, "Read error : (table section) value gives the byte offset from the beginning of the elf->file to the first byte in the section\n");

        if (!fread(&elf->shdrTable[i].sh_size, sizeof(Elf32_Word), 1, elf->file))
            fprintf(stderr, "Read error : (table section) section's size\n");

        if (!fread(&elf->shdrTable[i].sh_link, sizeof(Elf32_Word), 1, elf->file))
            fprintf(stderr, "Read error : (table section) section header table index link\n");

        if (!fread(&elf->shdrTable[i].sh_info, sizeof(Elf32_Word), 1, elf->file))
            fprintf(stderr, "Read error : (table section) extra information\n");

        if (!fread(&elf->shdrTable[i].sh_addralign, sizeof(Elf32_Word), 1, elf->file))
            fprintf(stderr, "Read error : (table section) address alignment constraints\n");

        if (!fread(&elf->shdrTable[i].sh_entsize, sizeof(Elf32_Word), 1, elf->file))
            fprintf(stderr, "Read error : (table section) table of fixed-size entries\n");

        if (!IS_BIGENDIAN()) {
            SWAPB(&elf->shdrTable[i].sh_name, sizeof(Elf32_Word));
            SWAPB(&elf->shdrTable[i].sh_type, sizeof(Elf32_Word));
            SWAPB(&elf->shdrTable[i].sh_flags, sizeof(Elf32_Word));
            SWAPB(&elf->shdrTable[i].sh_addr, sizeof(Elf32_Addr));
            SWAPB(&elf->shdrTable[i].sh_offset, sizeof(Elf32_Off));
            SWAPB(&elf->shdrTable[i].sh_size, sizeof(Elf32_Word));
            SWAPB(&elf->shdrTable[i].sh_link, sizeof(Elf32_Word));
            SWAPB(&elf->shdrTable[i].sh_info, sizeof(Elf32_Word));
            SWAPB(&elf->shdrTable[i].sh_addralign, sizeof(Elf32_Word));
            SWAPB(&elf->shdrTable[i].sh_entsize, sizeof(Elf32_Word));
        }
    }
}

void ReadELFTableSymbols(ELF *elf) {
    Elf32_Shdr sh_symtab = elf->shdrTable[sectionName2Index(".symtab", elf->file, elf->ehdr, elf->shdrTable)];
    
    fseek(elf->file, sh_symtab.sh_offset, SEEK_SET);
    int nbEntries = sh_symtab.sh_size / sh_symtab.sh_entsize;
    for (int i = 0; i < nbEntries; i++) {
        if (!fread(&elf->symTable[i].st_name, sizeof(Elf32_Word), 1, elf->file))
            fprintf(stderr, "Read error : (TableSymbols) name\n");

        if (!fread(&elf->symTable[i].st_value, sizeof(Elf32_Addr), 1, elf->file))
            fprintf(stderr, "Read error : (TableSymbols) value\n");

        if (!fread(&elf->symTable[i].st_size, sizeof(Elf32_Word), 1, elf->file))
            fprintf(stderr, "Read error : (TableSymbols) size\n");

        if (!fread(&elf->symTable[i].st_info, sizeof(unsigned char), 1, elf->file))
            fprintf(stderr, "Read error : (TableSymbols) information about symbol's type and binding attributes\n");

        if (!fread(&elf->symTable[i].st_other, sizeof(unsigned char), 1, elf->file))
            fprintf(stderr, "Read error : (TableSymbols) no defined meaning\n");

        if (!fread(&elf->symTable[i].st_shndx, sizeof(Elf32_Half), 1, elf->file))
            fprintf(stderr, "Read error : (TableSymbols) the relevant section header table index\n");
    }

    if (!IS_BIGENDIAN()) {
        for (int i = 0; i < nbEntries; i++) {
            SWAPB(&elf->symTable[i].st_name, sizeof(Elf32_Word));
            SWAPB(&elf->symTable[i].st_value, sizeof(Elf32_Addr));
            SWAPB(&elf->symTable[i].st_size, sizeof(Elf32_Word));
            SWAPB(&elf->symTable[i].st_info, sizeof(unsigned char));
            SWAPB(&elf->symTable[i].st_other, sizeof(unsigned char));
            SWAPB(&elf->symTable[i].st_shndx, sizeof(Elf32_Half));
        }
    }
}

void ReadELFRelocationTable(ELF *elf) {
    for (int i = 0; i < elf->ehdr.e_shnum; i++) {
        if (elf->shdrTable[i].sh_type == SHT_REL) {
            elf->relTables[i] = create_ELFTableRel(elf->shdrTable[i]);
            fseek(elf->file, elf->shdrTable[i].sh_offset, SEEK_SET);
            for (int j = 0; j < elf->shdrTable[i].sh_size / elf->shdrTable[i].sh_entsize; j++) {
                if (!fread(&elf->relTables[i][j].r_offset, sizeof(Elf32_Addr), 1, elf->file))
                    fprintf(stderr, "Read error : (ReadELFRelocationTable) r_offset\n");

                if (!fread(&elf->relTables[i][j].r_info, sizeof(Elf32_Word), 1, elf->file))
                    fprintf(stderr, "Read error : (ReadELFRelocationTable) r_info\n");
            }
            if (!IS_BIGENDIAN()) {
                for (int j = 0; j < elf->shdrTable[i].sh_size / elf->shdrTable[i].sh_entsize; j++) {
                    SWAPB(&elf->relTables[i][j].r_offset, sizeof(Elf32_Addr));
                    SWAPB(&elf->relTables[i][j].r_info, sizeof(Elf32_Word));
                }
            }
        }
    }
}


void PrintELFHeader(ELF *elf) {
    printf("ELF File's Header:");
    printf("\n  Ident: ");
    for (int i = 0; i < EI_NIDENT; i++)
        printf("%.2x ", elf->ehdr.e_ident[i]);

    char class[STR_SIZE];
    char data[STR_SIZE];
    char osabi[STR_SIZE];
    char type[STR_SIZE];
    char machine[STR_SIZE];

    getHeaderClass(class, elf->ehdr);
    printf("\n  Class: \t\t\t\t%s", class);

    getHeaderData(data, elf->ehdr);
    printf("\n  Data: \t\t\t\t%s", data);

    // File Version
    printf("\n  Version: \t\t\t\t");
    if (elf->ehdr.e_ident[EI_VERSION] == EV_NONE)
        printf("%d (invalid)", elf->ehdr.e_ident[EI_VERSION]);
    else
        printf("%d (current)", elf->ehdr.e_ident[EI_VERSION]);

    // OS/ABI
    getHeaderOSABI(osabi, elf->ehdr);
    printf("\n  OS/ABI: \t\t\t\t%s", osabi);

    // ABI Version
    printf("\n  ABI Version: \t\t\t\t%d", elf->ehdr.e_ident[EI_ABIVERSION]);

    // File type
    getHeaderType(type, elf->ehdr);
    printf("\n  Type: \t\t\t\t%s", type);

    // Required architecture
    getHeaderMachine(machine, elf->ehdr);
    printf("\n  Machine: \t\t\t\t%s", machine);

    printf("\n  Version: \t\t\t\t0x%x", elf->ehdr.e_version);

    printf("\n  Entry point address: \t\t\t0x%x", elf->ehdr.e_entry);

    printf("\n  Start of program headers: \t\t%d (bytes into file)", elf->ehdr.e_phoff);

    printf("\n  Start of section headers: \t\t%d (bytes into file)", elf->ehdr.e_shoff);

    printf("\n  Flags: \t\t\t\t0x%x", elf->ehdr.e_flags);

    printf("\n  Size of this header: \t\t\t%d (bytes)", elf->ehdr.e_ehsize);

    printf("\n  Size of program headers: \t\t%d (bytes)", elf->ehdr.e_phentsize);

    printf("\n  Number of program headers: \t\t%d", elf->ehdr.e_phnum);

    printf("\n  Size of section headers: \t\t%d (bytes)", elf->ehdr.e_shentsize);

    printf("\n  Number of section headers: \t\t%d", elf->ehdr.e_shnum);

    printf("\n  Section header string table index: \t%d\n\n", elf->ehdr.e_shstrndx);
}

void PrintELFTableSections(ELF *elf) {
    printf("Section table headers:\n");
    printf("  [N°]  Section Name              Type            Addr     Off    Size   ES Flg Flg Keys        Lk Inf Al\n");
    char name[STR_SIZE];
    char type[STR_SIZE];
    char flags[16];
    for (int i = 0; i < elf->ehdr.e_shnum; i++) {
        getSectionName(name, elf->file, elf->ehdr, elf->shdrTable, i);
        getSectionType(type, elf->shdrTable[i]);
        getSectionFlags(flags, elf->shdrTable[i]);
        printf("  [%2d]  %-24.24s  %-14s  %8.8x %6.6x %6.6x %2.2x %3.3x %15s %2d %3d %2d\n", i,
               name,
               type,
               elf->shdrTable[i].sh_addr,
               elf->shdrTable[i].sh_offset,
               elf->shdrTable[i].sh_size,
               elf->shdrTable[i].sh_entsize,
               elf->shdrTable[i].sh_flags,
               flags,
               elf->shdrTable[i].sh_link,
               elf->shdrTable[i].sh_info,
               elf->shdrTable[i].sh_addralign
        );
    }
    printf("Key to Flags:\n"
           "  W: WRITE, A: ALLOC, X: EXECINSTR, M: MERGE, S: STRINGS\n"
           "  I: INFO_LINK, L: LINK_ORDER, O: OS_NONCONFORMING\n"
           "  G: GROUP, T: TLS, C: COMPRESSED, o: MASKOS\n"
           "  p: MASKPROC, g: GNU_RETAIN, R: ORDERED, E: EXCLUDE\n\n");
}

void PrintELFSectionNum(ELF *elf, int numSection) {
    if (numSection < 0 || numSection >= elf->ehdr.e_shnum) {
        fprintf(stderr, "Section number out of range\n");
        return;
    }

    char name[STR_SIZE];
    getSectionName(name, elf->file, elf->ehdr, elf->shdrTable, numSection);
    printf("Section %d (%s):", numSection, name);

    if (elf->shdrTable[numSection].sh_size) {
        int i;
        uint8_t *buff = getSectionContent(elf->file, elf->shdrTable[numSection]);
        uint8_t buff16[17];
        buff16[16] = 0;
        for (i = 0; i < elf->shdrTable[numSection].sh_size; i++) {
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

void PrintELFSectionNom(ELF *elf, char *nomSection) {
    PrintELFSectionNum(elf, sectionName2Index(nomSection, elf->file, elf->ehdr, elf->shdrTable));
}

void PrintELFTableSymbols(ELF *elf) {
    printf("Symbol table entries:\n");
    printf("  [N°]    Value  Size Type    Bind   Vis      Ndx Name\n");
    char name[STR_SIZE];
    char type[STR_SIZE];
    char bind[STR_SIZE];
    char vis[STR_SIZE];
    char ndx[STR_SIZE];
    Elf32_Shdr sh_symtab = elf->shdrTable[sectionName2Index(".symtab", elf->file, elf->ehdr, elf->shdrTable)];
    for (int i = 0; i < sh_symtab.sh_size / sh_symtab.sh_entsize; i++) {
        getSymbolName(name, elf->file, elf->ehdr, elf->shdrTable, elf->symTable[i]);
        getSymbolType(type, elf->symTable[i]);
        getSymbolBind(bind, elf->symTable[i]);
        getSymbolVis(vis, elf->symTable[i]);
        getSymbolNdx(ndx, elf->symTable[i]);
        printf("  [%2d] %08x %5d %-7s %-6s %-7s %4s %s \n", i,
               elf->symTable[i].st_value,
               elf->symTable[i].st_size,
               type,
               bind,
               vis,
               ndx,
               name
        );
    }
    printf("\n");
}

void PrintELFRelocationTable(ELF *elf) {
    char name[STR_SIZE];
    char type[STR_SIZE];

    int nbRel = 0;
    for (int i = 0; i < elf->ehdr.e_shnum; i++) {
        if (elf->relTables[i] != NULL) {
            strcpy(name, "");
            getSectionName(name, elf->file, elf->ehdr, elf->shdrTable, i);
            printf("Relocation section '%s' at offset 0x%x contains %d entries:\n",
                   name,
                   elf->shdrTable[i].sh_offset,
                   elf->shdrTable[i].sh_size / elf->shdrTable[i].sh_entsize);

            int rsym;
            printf(" Offset      Info         Type           Sym.value   Sym.name\n");
            for (int j = 0; j < elf->shdrTable[i].sh_size / elf->shdrTable[i].sh_entsize; j++) {
                rsym = ELF32_R_SYM(elf->relTables[i][j].r_info);
                strcpy(name, "");
                getSymbolName(name, elf->file, elf->ehdr, elf->shdrTable, elf->symTable[rsym]);
                strcpy(type, "");
                getRelType(type, elf->relTables[i][j]);
                printf(" %.8x  %.8x    %-12s      %.8x    %s\n",
                       elf->relTables[i][j].r_offset,
                       elf->relTables[i][j].r_info,
                       type,
                       elf->symTable[rsym].st_value,
                       name);
            }
            printf("\n");
            nbRel++;
        }
    }
    if (nbRel == 0)
        printf("There are no relocations in this elf->file.\n\n");
}


FusionELF_Etape6 *LinkELFRenumSections(ELF *elf1, ELF *elf2) {
    char name1[STR_SIZE], name2[STR_SIZE];

    FusionELF_Etape6 *res = create_fusion6(elf1, elf2);
    res->renum[0] = 0;
    for (int j = 0; j < elf2->nbsh; j++)
        res->offsets[j] = -1;

    uint8_t *buff;
    for (int i = 0; i < elf1->ehdr.e_shnum; i++) {
        if (elf1->shdrTable[i].sh_size)
            res->contents[i] = getSectionContent(elf1->file, elf1->shdrTable[i]);

        if (elf1->shdrTable[i].sh_type == SHT_PROGBITS) {
            strcpy(name1, "");
            getSectionName(name1, elf1->file, elf1->ehdr, elf1->shdrTable, i);

            for (int j = 1; j < elf2->nbsh; j++) {
                strcpy(name2, "");
                getSectionName(name2, elf2->file, elf2->ehdr, elf2->shdrTable, j);
                if (elf2->shdrTable[j].sh_size && strcmp(name1, name2) == 0) {
                    if (elf1->shdrTable[i].sh_size) {
                        res->contents[i] = (uint8_t *) realloc(res->contents[i], elf1->shdrTable[i].sh_size + elf2->shdrTable[j].sh_size);
                        buff = getSectionContent(elf2->file, elf2->shdrTable[j]);
                        memcpy(res->contents[i] + elf1->shdrTable[i].sh_size, buff, elf2->shdrTable[j].sh_size);
                        free(buff);
                    } else
                        res->contents[i] = getSectionContent(elf2->file, elf2->shdrTable[j]);
                    res->offsets[j] = elf1->shdrTable[i].sh_size;
                    res->renum[j] = i;
                }
            }
        }
    }

    int e_shnum_acc = 0;
    for (int j = 1; j < elf2->nbsh; j++) {
        if (res->offsets[j] == -1) {
            res->renum[j] = elf1->nbsh + e_shnum_acc;
            if (elf2->shdrTable[j].sh_size)
                res->contents[res->renum[j]] = getSectionContent(elf2->file, elf2->shdrTable[j]);
            e_shnum_acc++;
        }
    }

    res->snb = elf1->nbsh + e_shnum_acc;
    return res;
}


ELF *LinkELFSymbols(ELF *elf1, ELF *elf2, FusionELF_Etape6 *fusion6) {
    Elf32_Shdr sh_symtab1 = elf1->shdrTable[sectionName2Index(".symtab", elf1->file, elf1->ehdr, elf1->shdrTable)];
    Elf32_Shdr sh_symtab2 = elf2->shdrTable[sectionName2Index(".symtab", elf2->file, elf2->ehdr, elf2->shdrTable)];
    int nb_sym1 = sh_symtab1.sh_size / sh_symtab1.sh_entsize;
    int nb_sym2 = sh_symtab2.sh_size / sh_symtab2.sh_entsize;

    // Fusion des deux tables des symboles
    // Vérification qu'il n'y a pas deux symboles globaux définis avec le même nom dans les deux tables des symboles
    int i = 0;
    int j = 0;
    int error = 0;
    while (i < nb_sym1 && !error) {
        j = i + 1;
        while (j < nb_sym2 && !error) {
            error = ELF32_ST_BIND(elf1->symTable[i].st_info) == STB_GLOBAL
                    && ELF32_ST_BIND(elf2->symTable[i].st_info) == STB_GLOBAL
                    && elf1->symTable[i].st_name == elf2->symTable[i].st_name
                    && ELF32_ST_TYPE(elf1->symTable[i].st_info) != STT_NOTYPE
                    && ELF32_ST_TYPE(elf2->symTable[j].st_info) != STT_NOTYPE;
            j++;
        }
        i++;
    }

    // Si la fusion est impossible
    if (error) {
        fprintf(stderr, "Erreur : 2 symboles avec le même nom sont définis dans les deux tables des symboles des fichiers d'entrées\n");
        return NULL;
    }

    ELF *res = create_ELF();
    res->symTable = (Elf32_Sym *) malloc(sizeof(Elf32_Sym) * (nb_sym1 + nb_sym2));
    int nbElems = 0;

    for (int i = 0; i < nb_sym1; i++) {
        res->symTable[nbElems] = elf1->symTable[i];
        nbElems++;
    }
    for (int i = 0; i < nb_sym2; i++) {
        // Pour un symbole local
        if (ELF32_ST_BIND(elf2->symTable[i].st_info) == STB_LOCAL) {
            int j = 0;
            while (i < nb_sym1 && elf1->symTable[j].st_name != elf2->symTable[i].st_name)
                j++;
            if (j == nb_sym1) {
                if(elf2->symTable[i].st_shndx == SHN_COMMON)
                    elf2->symTable[i].st_shndx = fusion6->renum[elf2->symTable[i].st_shndx];
                res->symTable[nbElems] = elf2->symTable[i];
                nbElems++;
            }
        }
            // Pour un symbole global on l'écrit que s'il est défini dans la table des symboles de file2 mais pas dans celle de input1
        else {
            if (ELF32_ST_TYPE(elf2->symTable[i].st_info) != STT_NOTYPE) {
                j = 0;
                while (j < nb_sym1 && elf1->symTable[j].st_name != elf2->symTable[i].st_name)
                    j++;
                if (j == nb_sym1 || ELF32_ST_TYPE(elf1->symTable[j].st_info) == STT_NOTYPE) {
                    if(elf2->symTable[i].st_shndx == SHN_COMMON)
                        elf2->symTable[i].st_shndx = fusion6->renum[elf2->symTable[i].st_shndx];
                    res->symTable[nbElems] = elf2->symTable[i];
                    nbElems++;
                }
            }
        }
    }

    res->nbsym = nbElems;
    return res;
}
