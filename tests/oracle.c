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
    size_t tailleLigne = sizeof(char) * STR_SIZE;
    char *ligne = malloc(tailleLigne);

    // Token utilisé lorsqu'on découpé une ligne en tableau
    char *token;

    // On ignore la première ligne
    passerNLignes(resultCommand, 1);

    // Ligne Magic
    lireLigne(resultCommand, ligne, tailleLigne);
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
    lireLigne(resultCommand, ligne, tailleLigne);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    if (strcmp(token, "NONE") == 0) {
        headerCommand.e_type = ET_NONE;
    } else if (strcmp(token, "REL") == 0) {
        headerCommand.e_type = ET_REL;
    } else if (strcmp(token, "EXEC") == 0) {
        headerCommand.e_type = ET_EXEC;
    } else if (strcmp(token, "DYN") == 0) {
        headerCommand.e_type = ET_DYN;
    } else if (strcmp(token, "CORE") == 0) {
        headerCommand.e_type = ET_CORE;
    } else if (strcmp(token, "LOPROC") == 0) {
        headerCommand.e_type = ET_LOPROC;
    } else if (strcmp(token, "HIPROC") == 0) {
        headerCommand.e_type = ET_HIPROC;
    }

    // Ligne Machine
    lireLigne(resultCommand, ligne, tailleLigne);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    if (strcmp(token, "NONE\n") == 0) {
        headerCommand.e_machine = ET_NONE;
    } else if (strcmp(token, "M32\n") == 0) {
        headerCommand.e_machine = EM_M32;
    } else if (strcmp(token, "SPARC\n") == 0) {
        headerCommand.e_machine = EM_SPARC;
    } else if (strcmp(token, "386\n") == 0) {
        headerCommand.e_machine = EM_386;
    } else if (strcmp(token, "68K\n") == 0) {
        headerCommand.e_machine = EM_68K;
    } else if (strcmp(token, "860\n") == 0) {
        headerCommand.e_machine = EM_860;
    } else if (strcmp(token, "MIPS\n") == 0) {
        headerCommand.e_machine = EM_MIPS;
    } else if (strcmp(token, "ARM\n") == 0) {
        headerCommand.e_machine = EM_ARM;
    }

    // Ligne Version
    lireLigne(resultCommand, ligne, tailleLigne);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_version = strtol(token, NULL, 16);

    // Entry point address
    lireLigne(resultCommand, ligne, tailleLigne);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_entry = strtol(token, NULL, 16);

    // Start of program headers
    lireLigne(resultCommand, ligne, tailleLigne);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_phoff = strtol(token, NULL, 16);

    // Start of section headers
    lireLigne(resultCommand, ligne, tailleLigne);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_shoff = atoi(token);

    // Flags
    lireLigne(resultCommand, ligne, tailleLigne);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_flags = strtol(token, NULL, 16);

    // Size of this header
    lireLigne(resultCommand, ligne, tailleLigne);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_ehsize = atoi(token);

    // Size of program headers
    lireLigne(resultCommand, ligne, tailleLigne);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_phentsize = atoi(token);

    // Number of program headers
    lireLigne(resultCommand, ligne, tailleLigne);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_phnum = atoi(token);

    // Size of section headers
    lireLigne(resultCommand, ligne, tailleLigne);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_shentsize = atoi(token);

    // Number of section headers
    lireLigne(resultCommand, ligne, tailleLigne);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_shnum = atoi(token);

    // Section header string table index
    lireLigne(resultCommand, ligne, tailleLigne);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_shstrndx = atoi(token);

    pclose(resultCommand);
    free(ligne);

    /* On exécute la fonction ReadELFHeader pour le fichier en paramètre */
    FILE *file = fopen(filename, "r");
    Elf32_Ehdr headerProgram;
    ReadELFHeader(file, &headerProgram);
    fclose(file);

    /* On compare les deux headers */
    int echec = 0;
    // Champ e_ident
    int i = 0;
    while (i < EI_NIDENT && headerProgram.e_ident[i] == headerCommand.e_ident[i]) {
        i++;
    }

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

    if (echec) {
        printf("Echec pour l'etape 1\n");
    } else {
        printf("Succes pour l'etape 1\n");
    }
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

    char line[STR_SIZE];

    // lecture de la taille de chaque colonne
    int colonnes[10];
    if (fgets(line, STR_SIZE, resultCommand) == NULL)
        fprintf(stderr, "Erreur de lecture de la ligne des titres\n");
    int espaces[11];
    int iespaces = 0;
    int nb_espace = 0;
    for (int i = 0 ; i < strlen(line) ; i++) {
        if (line[i] == ' ')
            nb_espace++;
        else if (nb_espace > 0) {
            espaces[iespaces] = nb_espace;
            nb_espace = 0;
            iespaces++;
        }
    }
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

    char buffer[STR_SIZE];

    int i = 0;
    int iNULL;
    char names[STR_SIZE][imax];
    char type[STR_SIZE];
    char flags[STR_SIZE][imax];
    while (i < imax) {
        strcpy(names[i], "");
        if (fgets(buffer, 7 + colonnes[0] + 1, resultCommand) == NULL)
            fprintf(stderr, "Read error\n");
        else
            sscanf(buffer, "  [%d] %s", &iNULL, names[i]);

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


// Oracle pour l'étape 3 ( PrintELFSectionNum et PrintELFSectionNom dans le fichier elf.c )
void oracleEtape3 (char *filename, char numSection){
/* On execute la commande readelf -x nbsection filename et on crée un header avec le résultat */
    char command[STR_SIZE] = "readelf -x ";
    strcat(command, &numSection);
    strcat(command, filename);
    FILE *resultCommand = popen(command, "r");
    Elf32_Ehdr headerCommand;
// Chaine de caractères pour lire les lignes de resultCommand
    size_t tailleLigne = sizeof(char) * STR_SIZE;
    char *ligne = malloc(tailleLigne);
// Token utilisé lorsqu'on découpé une ligne en tableau
    char *token;

    // On récupere les valeurs de la commande readelf -x nbsection filename
    // lireLigne(resultCommand, ligne, tailleLigne); pour lire une ligne et l'interpréter
    // passerNLignes(resultCommand, x); pour passer x lignes


/* On exécute la fonction ReadELFSectionNum pour le fichier en paramètre */
    FILE *file = fopen(filename, "r");
    Elf32_Ehdr header;
    ReadELFHeader(file, &header);
    Elf32_Shdr *sectionTable = create_ELFTableSections(header);
    ReadELFTableSections(file, header, sectionTable);

    //PrintELFSectionNum(file, header, sectionTable, numSection);
    char name[STR_SIZE];
    getSectionName(name, file, header, sectionTable, numSection);
    //PrintELFSectionNom(file, header, sectionTable, name);
    fclose(file);

/* On compare les résultats */

}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Il faut au moins un fichier de test\n");
    } else {
        for (int i = 1 ; i < argc ; i++) {
            printf("Tests avec le fichier '%s'\n", argv[i]);
            //oracleEtape1(argv[i]);
            //oracleEtape2(argv[i]);
            oracleEtape3(argv[i], 13);
        }
    }

    return 0;
}
