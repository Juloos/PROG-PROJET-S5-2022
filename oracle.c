#include "oracle.h"

void passerNLignes(FILE *file, uint n) {
    char ligne[200];
    for (int i = 0 ; i < n ; i++) {
        if (!fgets(ligne, sizeof(ligne), file)) {
            printf("Erreur lors de la lecture\n");
        }
    }
}

void lireLigne(FILE *file, char *ligne, size_t tailleLigne) {
    if (!fgets(ligne, tailleLigne, file)) {
        printf("Erreur lors de la lecture\n");
    }
}

void oracleEtape1(char *filename) {
    /* On execute la commande readelf -h filename et on crée un header avec le résultat */
    char command[STR_SIZE] = "readelf -h ";
    FILE *resultCommand = popen(strcat(command, filename), "r");
    Elf32_Ehdr headerCommand;

    // Chaine de caractères pour lire les lignes de resultCommand
    char ligne[STR_SIZE];

    // Token utilisé lorsqu'on découpé une ligne en tableau
    char *token;

    // On ignore la première ligne
    passerNLignes(resultCommand, 1);

    // Ligne Magic
    lireLigne(resultCommand, ligne, sizeof(char)*STR_SIZE);
    // Découpage de la ligne avec l'espace comme délimiteur
    token = strtok(ligne, ":");
    // On ignore le premier mot
    token = strtok(NULL, " ");
    // Champ e_ident
    for (int i = 0 ; i < EI_NIDENT ; i++) {
        headerCommand.e_ident[i] = (unsigned char) strtol(token, NULL, 16);
        token = strtok(NULL, " ");
    }

    // On ignore les 5 prochaines lignes
    passerNLignes(resultCommand, 5);

    // Ligne Type
    lireLigne(resultCommand, ligne, sizeof(char)*STR_SIZE);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    if (strcmp(token, "NONE") == 0)
        headerCommand.e_type = ET_NONE;
    else if (strcmp(token, "REL") == 0)
        headerCommand.e_type = ET_REL;
    else if (strcmp(token, "EXEC") == 0)
        headerCommand.e_type = ET_EXEC;
    else if (strcmp(token, "DYN") == 0)
        headerCommand.e_type = ET_DYN;
    else if (strcmp(token, "CORE") == 0)
        headerCommand.e_type = ET_CORE;
    else if (strcmp(token, "LOPROC") == 0)
        headerCommand.e_type = ET_LOPROC;
    else if (strcmp(token, "HIPROC") == 0)
        headerCommand.e_type = ET_HIPROC;

    // Ligne Machine
    lireLigne(resultCommand, ligne, sizeof(char)*STR_SIZE);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    if (strcmp(token, "NONE\n") == 0)
        headerCommand.e_machine = ET_NONE;
    else if (strcmp(token, "M32\n") == 0)
        headerCommand.e_machine = EM_M32;
    else if (strcmp(token, "SPARC\n") == 0)
        headerCommand.e_machine = EM_SPARC;
    else if (strcmp(token, "386\n") == 0)
        headerCommand.e_machine = EM_386;
    else if (strcmp(token, "68K\n") == 0)
        headerCommand.e_machine = EM_68K;
    else if (strcmp(token, "860\n") == 0)
        headerCommand.e_machine = EM_860;
    else if (strcmp(token, "MIPS\n") == 0)
        headerCommand.e_machine = EM_MIPS;
    else if (strcmp(token, "ARM\n") == 0)
        headerCommand.e_machine = EM_ARM;

    // Ligne Version
    lireLigne(resultCommand, ligne, sizeof(char)*STR_SIZE);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_version = strtol(token, NULL, 16);

    // Entry point address
    lireLigne(resultCommand, ligne, sizeof(char)*STR_SIZE);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_entry = strtol(token, NULL, 16);

    // Start of program headers
    lireLigne(resultCommand, ligne, sizeof(char)*STR_SIZE);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_phoff = strtol(token, NULL, 16);

    // Start of section headers
    lireLigne(resultCommand, ligne, sizeof(char)*STR_SIZE);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_shoff = atoi(token);

    // Flags
    lireLigne(resultCommand, ligne, sizeof(char)*STR_SIZE);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_flags = strtol(token, NULL, 16);

    // Size of this header
    lireLigne(resultCommand, ligne, sizeof(char)*STR_SIZE);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_ehsize = atoi(token);

    // Size of program headers
    lireLigne(resultCommand, ligne, sizeof(char)*STR_SIZE);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_phentsize = atoi(token);

    // Number of program headers
    lireLigne(resultCommand, ligne, sizeof(char)*STR_SIZE);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_phnum = atoi(token);

    // Size of section headers
    lireLigne(resultCommand, ligne, sizeof(char)*STR_SIZE);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_shentsize = atoi(token);

    // Number of section headers
    lireLigne(resultCommand, ligne, sizeof(char)*STR_SIZE);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_shnum = atoi(token);

    // Section header string table index
    lireLigne(resultCommand, ligne, sizeof(char)*STR_SIZE);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_shstrndx = atoi(token);

    pclose(resultCommand);

    /* On exécute la fonction ReadELFHeader pour le fichier en paramètre */
    FILE *file = fopen(filename, "r");
    Elf32_Ehdr headerProgram;
    ReadELFHeader(file, &headerProgram);
    fclose(file);

    /* On compare les deux headers */
    int echec = 0;
    // Champ e_ident
    int i = 0;
    while (i < EI_NIDENT && headerProgram.e_ident[i] == headerCommand.e_ident[i])
        i++;

    if (i < EI_NIDENT) {
        printf("Erreur sur le champ e_ident\n");
        printf("  e_ident obtenu avec la commande readelf -h : ");
        for (int i = 0 ; i < EI_NIDENT ; i++) {
            printf("%d ", headerCommand.e_ident[i]);
        }
        printf("\n  e_ident obtenu avec la fonction ReadELFHeader : ");
        for (int i = 0 ; i < EI_NIDENT ; i++) {
            printf("%d ", headerCommand.e_ident[i]);
        }
        printf("\n");
        echec = 1;
    }

//    // Champ e_type
//    if (headerProgram.e_type != headerCommand.e_type) {
//        printf("Erreur sur le champ e_type\n");
//        printf("  e_type obtenu avec la commande readelf -h : %d\n", headerCommand.e_type);
//        printf("  e_type obtenu avec la fonction ReadELFHeader : %d\n\n", headerProgram.e_type);
//        echec = 1;
//    }
//
//    // Champ e_machine
//    if (headerProgram.e_machine != headerCommand.e_machine) {
//        printf("Erreur sur le champ e_machine\n");
//        printf("  e_machine obtenu avec la commande readelf -h : %d\n", headerCommand.e_machine);
//        printf("  e_machine obtenu avec la fonction ReadELFHeader : %d\n\n", headerProgram.e_machine);
//        echec = 1;
//    }

    // Champ e_version
    if (headerProgram.e_version != headerCommand.e_version) {
        printf("Erreur sur le champ e_version\n");
        printf("  e_version obtenu avec la commande readelf -h : 0x%.2x\n", headerCommand.e_version);
        printf("  e_version obtenu avec la fonction ReadELFHeader : 0x%.2x\n\n", headerProgram.e_version);
        echec = 1;
    }

    // Champ e_entry
    if (headerProgram.e_entry != headerCommand.e_entry) {
        printf("Erreur sur le champ e_entry\n");
        printf("  e_entry obtenu avec la commande readelf -h : 0x%.2x\n", headerCommand.e_entry);
        printf("  e_entry obtenu avec la fonction ReadELFHeader : 0x%.2x\n\n", headerProgram.e_entry);
        echec = 1;
    }

    // Champ e_phoff
    if (headerProgram.e_phoff != headerCommand.e_phoff) {
        printf("Erreur sur le champ e_phoff\n");
        printf("  e_phoff obtenu avec la commande readelf -h : %d\n", headerCommand.e_phoff);
        printf("  e_phoff obtenu avec la fonction ReadELFHeader : %d\n\n", headerProgram.e_phoff);
        echec = 1;
    }

    // Champ e_shoff
    if (headerProgram.e_shoff != headerCommand.e_shoff) {
        printf("Erreur sur le champ e_shoff\n");
        printf("  e_shoff obtenu avec la commande readelf -h : %d\n", headerCommand.e_shoff);
        printf("  e_shoff obtenu avec la fonction ReadELFHeader : %d\n\n", headerProgram.e_shoff);
        echec = 1;
    }

    // Champ e_flags
    if (headerProgram.e_flags != headerCommand.e_flags) {
        printf("Erreur sur le champ e_flags\n");
        printf("  e_flags obtenu avec la commande readelf -h : 0x%.2x\n", headerCommand.e_flags);
        printf("  e_flags obtenu avec la fonction ReadELFHeader : 0x%.2x\n\n", headerProgram.e_flags);
        echec = 1;
    }

    // Champ e_ehsize
    if (headerProgram.e_ehsize != headerCommand.e_ehsize) {
        printf("Erreur sur le champ e_ehsize\n");
        printf("  e_ehsize obtenu avec la commande readelf -h : %d\n", headerCommand.e_ehsize);
        printf("  e_ehsize obtenu avec la fonction ReadELFHeader : %d\n\n", headerProgram.e_ehsize);
        echec = 1;
    }

    // Champ e_phentsize
    if (headerProgram.e_phentsize != headerCommand.e_phentsize) {
        printf("Erreur sur le champ e_phentsize\n");
        printf("  e_phentsize obtenu avec la commande readelf -h : %d\n", headerCommand.e_phentsize);
        printf("  e_phentsize obtenu avec la fonction ReadELFHeader : %d\n\n", headerProgram.e_phentsize);
        echec = 1;
    }

    // Champ e_phnum
    if (headerProgram.e_phnum != headerCommand.e_phnum) {
        printf("Erreur sur le champ e_phnum\n");
        printf("  e_phnum obtenu avec la commande readelf -h : %d\n", headerCommand.e_phnum);
        printf("  e_phnum obtenu avec la fonction ReadELFHeader : %d\n\n", headerProgram.e_phnum);
        echec = 1;
    }

    // Champ e_shentsize
    if (headerProgram.e_shentsize != headerCommand.e_shentsize) {
        printf("Erreur sur le champ e_shentsize\n");
        printf("  e_shentsize obtenu avec la commande readelf -h : %d\n", headerCommand.e_shentsize);
        printf("  e_shentsize obtenu avec la fonction ReadELFHeader : %d\n\n", headerProgram.e_shentsize);
        echec = 1;
    }

    // Champ e_shnum
    if (headerProgram.e_shnum != headerCommand.e_shnum) {
        printf("Erreur sur le champ e_shnum\n");
        printf("  e_shnum obtenu avec la commande readelf -h : %d\n", headerCommand.e_shnum);
        printf("  e_shnum obtenu avec la fonction ReadELFHeader : %d\n\n", headerProgram.e_shnum);
        echec = 1;
    }

    // Champ e_shstrndx
    if (headerProgram.e_shstrndx != headerCommand.e_shstrndx) {
        printf("Erreur sur le champ e_shstrndx\n");
        printf("  e_shstrndx obtenu avec la commande readelf -h : %d\n", headerCommand.e_shstrndx);
        printf("  e_shstrndx obtenu avec la fonction ReadELFHeader : %d\n\n", headerProgram.e_shstrndx);
        echec = 1;
    }

    if (echec)
        printf("Echec pour l'etape 1\n");
    else
        printf("Succes pour l'etape 1\n");
}

void getSectionFlags2(char *flags, Elf32_Shdr shdr) {
    strcpy(flags, "");
    Elf32_Word sh_flags = shdr.sh_flags;
    strcat(flags, sh_flags & SHF_WRITE ? "W" : "");
    strcat(flags, sh_flags & SHF_ALLOC ? "A" : "");
    strcat(flags, sh_flags & SHF_EXECINSTR ? "X" : "");
    strcat(flags, sh_flags & SHF_MERGE ? "M" : "");
    strcat(flags, sh_flags & SHF_STRINGS ? "S" : "");
    strcat(flags, sh_flags & SHF_INFO_LINK ? "I" : "");
    strcat(flags, sh_flags & SHF_LINK_ORDER ? "L" : "");
    strcat(flags, sh_flags & SHF_OS_NONCONFORMING ? "O" : "");
    strcat(flags, sh_flags & SHF_GROUP ? "G" : "");
    strcat(flags, sh_flags & SHF_TLS ? "T" : "");
    strcat(flags, sh_flags & SHF_COMPRESSED ? "C" : "");
    strcat(flags, sh_flags & SHF_MASKOS ? "o" : "");
    strcat(flags, sh_flags & SHF_MASKPROC ? "p" : "");
    strcat(flags, sh_flags & SHF_ORDERED ? "R" : "");
    strcat(flags, sh_flags & SHF_EXCLUDE ? "E" : "");
}

Elf32_Word Type2shType(char *type) {
    if (strcmp(type, "NULL") == 0) return SHT_NULL;
    if (strcmp(type, "PROGBITS") == 0) return SHT_PROGBITS;
    if (strcmp(type, "SYMTAB") == 0) return SHT_SYMTAB;
    if (strcmp(type, "STRTAB") == 0) return SHT_STRTAB;
    if (strcmp(type, "RELA") == 0) return SHT_RELA;
    if (strcmp(type, "HASH") == 0) return SHT_HASH;
    if (strcmp(type, "DYNAMIC") == 0) return SHT_DYNAMIC;
    if (strcmp(type, "NOTE") == 0) return SHT_NOTE;
    if (strcmp(type, "NOBITS") == 0) return SHT_NOBITS;
    if (strcmp(type, "REL") == 0) return SHT_REL;
    if (strcmp(type, "SHLIB") == 0) return SHT_SHLIB;
    if (strcmp(type, "DYNSYM") == 0) return SHT_DYNSYM;
    if (strcmp(type, "LOPROC") == 0) return SHT_LOPROC;
    if (strcmp(type, "HIPROC") == 0) return SHT_HIPROC;
    if (strcmp(type, "LOUSER") == 0) return SHT_LOUSER;
    if (strcmp(type, "HIUSER") == 0) return SHT_HIUSER;
    if (strcmp(type, "ARM_ATTRIBUTES") == 0) return SHT_ARM_ATTRIBUTES;
    return SHT_NULL;
}

void oracleEtape2(char *filename) {
    char command[STR_SIZE] = "readelf -S ";
    FILE *resultCommand = popen(strcat(command, filename), "r");

    int imax;
    if (fscanf(resultCommand, "There are %d", &imax) != 1)
        fprintf(stderr, "Erreur de lecture du nombre de sections\n");
    passerNLignes(resultCommand, 3);

    Elf32_Shdr shdr[imax];

    // lecture de la taille de chaque colonne
    char buffer[STR_SIZE];
    if (fgets(buffer, STR_SIZE, resultCommand) == NULL)
        fprintf(stderr, "Erreur de lecture de la ligne des titres\n");
    int espaces[11];
    int iespaces = 0;
    int nb_espace = 0;
    for (int i = 0 ; i < strlen(buffer) ; i++) {
        if (buffer[i] == ' ')
            nb_espace++;
        else if (nb_espace > 0) {
            espaces[iespaces] = nb_espace;
            nb_espace = 0;
            iespaces++;
        }
    }
    int colonnes[10];
    colonnes[0] = espaces[2] + 4;  // nb_espace + 4 (à cause de "Name") + 1 (décalage entre colonnes)
    colonnes[1] = espaces[3] + 4;
    colonnes[2] = espaces[4] + 4;
    colonnes[3] = espaces[5] + 3;
    colonnes[4] = espaces[6] + 4;
    colonnes[5] = espaces[7] + 2;
    colonnes[6] = espaces[8] + 3;
    colonnes[7] = espaces[9] + 2;
    colonnes[8] = espaces[10] + 3;
    colonnes[9] = 2;

    int i = 0;
    char names[STR_SIZE][imax];
    char type[STR_SIZE];
    char flags[STR_SIZE][imax];
    while (i < imax) {
        strcpy(names[i], "");
        if (fgets(buffer, 7 + colonnes[0] + 1, resultCommand) == NULL)
            fprintf(stderr, "Read error\n");
        else
            sscanf(buffer, "  [%*[^]]] %s", names[i]);

        strcpy(type, "");
        if (fgets(buffer, colonnes[1] + 1, resultCommand) == NULL)
            fprintf(stderr, "Read error\n");
        else {
            sscanf(buffer, "%s", type);
            shdr[i].sh_type = Type2shType(type);
        }

        if (fgets(buffer, colonnes[2] + 1, resultCommand) == NULL)
            fprintf(stderr, "Read error\n");
        else
            sscanf(buffer, "%x", &shdr[i].sh_addr);

        if (fgets(buffer, colonnes[3] + 1, resultCommand) == NULL)
            fprintf(stderr, "Read error\n");
        else
            sscanf(buffer, "%x", &shdr[i].sh_offset);

        if (fgets(buffer, colonnes[4] + 1, resultCommand) == NULL)
            fprintf(stderr, "Read error\n");
        else
            sscanf(buffer, "%x", &shdr[i].sh_size);

        if (fgets(buffer, colonnes[5] + 1, resultCommand) == NULL)
            fprintf(stderr, "Read error\n");
        else
            sscanf(buffer, "%x", &shdr[i].sh_entsize);

        strcpy(flags[i], "");
        if (fgets(buffer, colonnes[6] + 1, resultCommand) == NULL)
            fprintf(stderr, "Read error\n");
        else
            sscanf(buffer, "%s", flags[i]);

        if (fgets(buffer, colonnes[7] + 1, resultCommand) == NULL)
            fprintf(stderr, "Read error\n");
        else
            sscanf(buffer, "%d", &shdr[i].sh_link);

        if (fgets(buffer, colonnes[8] + 1, resultCommand) == NULL)
            fprintf(stderr, "Read error\n");
        else
            sscanf(buffer, "%d", &shdr[i].sh_info);

        if (fgets(buffer, colonnes[9] + 1, resultCommand) == NULL)
            fprintf(stderr, "Read error\n");
        else
            sscanf(buffer, "%d", &shdr[i].sh_addralign);

        passerNLignes(resultCommand, 1);
        i++;
    }
    pclose(resultCommand);

    FILE *file = fopen(filename, "r");
    Elf32_Ehdr header;
    ReadELFHeader(file, &header);
    Elf32_Shdr *shdrProgram = create_ELFTableSections(header);
    ReadELFTableSections(file, header, shdrProgram);
//    PrintELFTableSections(file, header, shdrProgram);
    char name[STR_SIZE];
    char flag[STR_SIZE];
    char beforecmp[2];
    int echec = 0;
    for (i = 0 ; i < imax ; i++) {
        getSectionName(name, file, header, shdrProgram, i);
        if (strcmp(names[i], name) != 0) {
            beforecmp[0] = names[i][colonnes[0] - 6];  // - 5 (pour '[...]') - 1 (pour le décalage entre colonnes)
            beforecmp[1] = name[colonnes[0] - 6];
            names[i][colonnes[0] - 6] = 0;
            name[colonnes[0] - 6] = 0;
            if (strcmp(names[i], name) != 0) {
                names[i][colonnes[0] - 6] = beforecmp[0];
                name[colonnes[0] - 6] = beforecmp[1];
                printf("Erreur sur le nom de la section %d\n", i);
                printf("  nom obtenu avec la commande readelf -S : '%s'\n", names[i]);
                printf("  nom obtenu avec la fonction ReadELFTableSections : '%s'\n\n", name);
                echec = 1;
            }
        }
        if (shdr[i].sh_type != shdrProgram[i].sh_type) {
            printf("Erreur sur le champ sh_type de la section %d\n", i);
            printf("  sh_type obtenu avec la commande readelf -S : %x\n", shdr[i].sh_type);
            printf("  sh_type obtenu avec la fonction ReadELFTableSections : %x\n\n", shdrProgram[i].sh_type);
            echec = 1;
        }
        if (shdr[i].sh_addr != shdrProgram[i].sh_addr) {
            printf("Erreur sur le champ sh_addr de la section %d\n", i);
            printf("  sh_addr obtenu avec la commande readelf -S : %x\n", shdr[i].sh_addr);
            printf("  sh_addr obtenu avec la fonction ReadELFTableSections : %x\n\n", shdrProgram[i].sh_addr);
            echec = 1;
        }
        if (shdr[i].sh_offset != shdrProgram[i].sh_offset) {
            printf("Erreur sur le champ sh_offset de la section %d\n", i);
            printf("  sh_offset obtenu avec la commande readelf -S : %x\n", shdr[i].sh_offset);
            printf("  sh_offset obtenu avec la fonction ReadELFTableSections : %x\n\n", shdrProgram[i].sh_offset);
            echec = 1;
        }
        if (shdr[i].sh_size != shdrProgram[i].sh_size) {
            printf("Erreur sur le champ sh_size de la section %d\n", i);
            printf("  sh_size obtenu avec la commande readelf -S : %x\n", shdr[i].sh_size);
            printf("  sh_size obtenu avec la fonction ReadELFTableSections : %x\n\n", shdrProgram[i].sh_size);
            echec = 1;
        }
        if (shdr[i].sh_entsize != shdrProgram[i].sh_entsize) {
            printf("Erreur sur le champ sh_entsize de la section %d\n", i);
            printf("  sh_entsize obtenu avec la commande readelf -S : %x\n", shdr[i].sh_entsize);
            printf("  sh_entsize obtenu avec la fonction ReadELFTableSections : %x\n\n", shdrProgram[i].sh_entsize);
            echec = 1;
        }
        getSectionFlags2(flag, shdrProgram[i]);
        if (strcmp(flags[i], flag) != 0) {
            printf("Erreur sur le champ sh_flags de la section %d\n", i);
            printf("  sh_flags obtenu avec la commande readelf -S : %s\n", flags[i]);
            printf("  sh_flags obtenu avec la fonction ReadELFTableSections : %s\n\n", flag);
            echec = 1;
        }
        if (shdr[i].sh_link != shdrProgram[i].sh_link) {
            printf("Erreur sur le champ sh_link de la section %d\n", i);
            printf("  sh_link obtenu avec la commande readelf -S : %x\n", shdr[i].sh_link);
            printf("  sh_link obtenu avec la fonction ReadELFTableSections : %x\n\n", shdrProgram[i].sh_link);
            echec = 1;
        }
        if (shdr[i].sh_info != shdrProgram[i].sh_info) {
            printf("Erreur sur le champ sh_info de la section %d\n", i);
            printf("  sh_info obtenu avec la commande readelf -S : %x\n", shdr[i].sh_info);
            printf("  sh_info obtenu avec la fonction ReadELFTableSections : %x\n\n", shdrProgram[i].sh_info);
            echec = 1;
        }
        if (shdr[i].sh_addralign != shdrProgram[i].sh_addralign) {
            printf("Erreur sur le champ sh_addralign de la section %d\n", i);
            printf("  sh_addralign obtenu avec la commande readelf -S : %x\n", shdr[i].sh_addralign);
            printf("  sh_addralign obtenu avec la fonction ReadELFTableSections : %x\n\n", shdrProgram[i].sh_addralign);
            echec = 1;
        }
    }
    if (echec)
        printf("Echec pour l'etape 2\n");
    else
        printf("Succes pour l'etape 2\n");
}

unsigned char Type2symType(char *type) {
    if (strcmp(type, "NOTYPE") == 0) return STT_NOTYPE;
    if (strcmp(type, "OBJECT") == 0) return STT_OBJECT;
    if (strcmp(type, "FUNC") == 0) return STT_FUNC;
    if (strcmp(type, "SECTION") == 0) return STT_SECTION;
    if (strcmp(type, "FILE") == 0) return STT_FILE;
    if (strcmp(type, "LOPROC") == 0) return STT_LOPROC;
    if (strcmp(type, "HIPROC") == 0) return STT_HIPROC;
    return STT_NOTYPE;
}

unsigned char Bind2symBind(char *bind) {
    if (strcmp(bind, "LOCAL") == 0) return STB_LOCAL;
    if (strcmp(bind, "GLOBAL") == 0) return STB_GLOBAL;
    if (strcmp(bind, "WEAK") == 0) return STB_WEAK;
    if (strcmp(bind, "LOPROC") == 0) return STB_LOPROC;
    if (strcmp(bind, "HIPROC") == 0) return STB_HIPROC;
    return STB_LOCAL;
}

unsigned char Vis2symVis(char *vis) {
    if (strcmp(vis, "DEFAULT") == 0) return STV_DEFAULT;
    if (strcmp(vis, "INTERNAL") == 0) return STV_INTERNAL;
    if (strcmp(vis, "HIDDEN") == 0) return STV_HIDDEN;
    if (strcmp(vis, "PROTECTED") == 0) return STV_PROTECTED;
    return STV_DEFAULT;
}

Elf32_Half Ndx2symNdx(char *ndx) {
    if (strcmp(ndx, "UND") == 0) return SHN_UNDEF;
    if (strcmp(ndx, "ABS") == 0) return SHN_ABS;
    if (strcmp(ndx, "COM") == 0) return SHN_COMMON;
    return (Elf32_Half) strtol(ndx, NULL, 10);
}

void oracleEtape4(char *filename) {
    char command[STR_SIZE] = "readelf -sW ";
    FILE *resultCommand = popen(strcat(command, filename), "r");

    int imax;
    passerNLignes(resultCommand, 1);
    if (fscanf(resultCommand, "Symbol table '%*[^']' contains %d", &imax) != 1)
        fprintf(stderr, "Erreur de lecture du nombre d'entrees\n");
    passerNLignes(resultCommand, 1);

    Elf32_Sym st[imax];

    // lecture de la taille de chaque colonne
    char buffer[STR_SIZE];
    if (fgets(buffer, STR_SIZE, resultCommand) == NULL)
        fprintf(stderr, "Erreur de lecture de la ligne des titres\n");
    int espaces[8];
    int iespaces = 0;
    int nb_espace = 0;
    for (int i = 0 ; i < strlen(buffer) ; i++) {
        if (buffer[i] == ' ')
            nb_espace++;
        else if (nb_espace > 0) {
            espaces[iespaces] = nb_espace;
            nb_espace = 0;
            iespaces++;
        }
    }
    int colonnes[7];
    colonnes[0] = 9;
    colonnes[1] = 6;
    colonnes[2] = espaces[4] + 4;  // nb_espace + 4 (à cause de "Type")
    colonnes[3] = espaces[5] + 4;
    colonnes[4] = espaces[6] + 2;
    colonnes[5] = 5;

    int i = 0;
    char type[STR_SIZE];
    char bind[STR_SIZE];
    char vis[STR_SIZE];
    char ndx[STR_SIZE];
    char names[STR_SIZE][imax];
    while (i < imax) {
        if (fgets(buffer, 8 + colonnes[0] + 1, resultCommand) == NULL)
            fprintf(stderr, "Read error\n");
        else
            sscanf(buffer, "%*[^:]: %x", &st[i].st_value);

        if (fgets(buffer, colonnes[1] + 1, resultCommand) == NULL)
            fprintf(stderr, "Read error\n");
        else
            sscanf(buffer, "%d", &st[i].st_size);

        if (fgets(buffer, colonnes[2] + 1, resultCommand) == NULL)
            fprintf(stderr, "Read error\n");
        else {
            sscanf(buffer, "%s", type);
        }

        if (fgets(buffer, colonnes[3] + 1, resultCommand) == NULL)
            fprintf(stderr, "Read error\n");
        else {
            sscanf(buffer, "%s", bind);
            st[i].st_info = ELF32_ST_INFO(Bind2symBind(bind), Type2symType(type));
        }

        if (fgets(buffer, colonnes[4] + 1, resultCommand) == NULL)
            fprintf(stderr, "Read error\n");
        else {
            sscanf(buffer, "%s", vis);
            st[i].st_other = Vis2symVis(vis);
        }

        if (fgets(buffer, colonnes[5] + 1, resultCommand) == NULL)
            fprintf(stderr, "Read error\n");
        else {
            sscanf(buffer, "%s", ndx);
            st[i].st_shndx = Ndx2symNdx(ndx);
        }

        strcpy(names[i], "");
        if (fgets(buffer, STR_SIZE, resultCommand) == NULL)
            fprintf(stderr, "Read error\n");
        else
            sscanf(buffer, "%s", names[i]);

        i++;
    }
    pclose(resultCommand);

    FILE *file = fopen(filename, "r");
    Elf32_Ehdr header;
    ReadELFHeader(file, &header);
    Elf32_Shdr *shdrProgram = create_ELFTableSections(header);
    ReadELFTableSections(file, header, shdrProgram);
    Elf32_Shdr sh_symtab = shdrProgram[sectionName2Index(".symtab", file, header, shdrProgram)];
    Elf32_Sym *stProgram = create_ELFTableSymbols(sh_symtab);
    ReadELFTableSymbols(file, stProgram, sh_symtab);
//    PrintELFTableSymbols(file, header, shdr, stProgram);
    char name[STR_SIZE];
    int echec = 0;
    for (i = 0 ; i < imax ; i++) {
        getSymbolName(name, file, header, shdrProgram, stProgram[i]);
        if (strcmp(names[i], name) != 0) {
            printf("Erreur sur le nom de l'entrée %d\n", i);
            printf("  nom obtenu avec la commande readelf -s : '%s'\n", names[i]);
            printf("  nom obtenu avec la fonction ReadELFTableSymbols : '%s'\n\n", name);
            echec = 1;
        }
        if (st[i].st_value != stProgram[i].st_value) {
            printf("Erreur sur le champ st_value de l'entrée %d\n", i);
            printf("  st_value obtenu avec la commande readelf -s : %x\n", st[i].st_value);
            printf("  st_value obtenu avec la fonction ReadELFTableSymbols : %x\n\n", stProgram[i].st_value);
            echec = 1;
        }
        if (st[i].st_size != stProgram[i].st_size) {
            printf("Erreur sur le champ st_size de l'entrée %d\n", i);
            printf("  st_size obtenu avec la commande readelf -s : %x\n", st[i].st_size);
            printf("  st_size obtenu avec la fonction ReadELFTableSymbols : %x\n\n", stProgram[i].st_size);
            echec = 1;
        }
        if (st[i].st_info != stProgram[i].st_info) {
            printf("Erreur sur le champ st_info de l'entrée %d\n", i);
            printf("  st_info obtenu avec la commande readelf -s : %x\n", st[i].st_info);
            printf("  st_info obtenu avec la fonction ReadELFTableSymbols : %x\n\n", stProgram[i].st_info);
            echec = 1;
        }
        if (st[i].st_other != stProgram[i].st_other) {
            printf("Erreur sur le champ st_other de l'entrée %d\n", i);
            printf("  st_other obtenu avec la commande readelf -s : %x\n", st[i].st_other);
            printf("  st_other obtenu avec la fonction ReadELFTableSymbols : %x\n\n", stProgram[i].st_other);
            echec = 1;
        }
        if (st[i].st_shndx != stProgram[i].st_shndx) {
            printf("Erreur sur le champ st_shndx de l'entrée %d\n", i);
            printf("  st_shndx obtenu avec la commande readelf -s : %x\n", st[i].st_shndx);
            printf("  st_shndx obtenu avec la fonction ReadELFTableSymbols : %x\n\n", stProgram[i].st_shndx);
            echec = 1;
        }
    }
    if (echec)
        printf("Echec pour l'etape 4\n");
    else
        printf("Succes pour l'etape 4\n");
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Il faut au moins un fichier de test\n");
    } else {
        for (int i = 1 ; i < argc ; i++) {
            printf("Tests avec le fichier '%s'\n", argv[i]);
            oracleEtape1(argv[i]);
            oracleEtape2(argv[i]);
            oracleEtape4(argv[i]);
        }
    }

    return 0;
}
