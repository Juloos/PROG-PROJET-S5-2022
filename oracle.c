#include "ELF.h"


void oracleEtape1(char *filename, ELF *elf) {
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
    if (!fgets(ligne, STR_SIZE, resultCommand))
        fprintf(stderr, "Read error : (oracleEtape1) Magic\n");
    // Découpage de la ligne avec l'espace comme délimiteur
    token = strtok(ligne, ":");
    // On ignore le premier mot
    token = strtok(NULL, " ");
    // Champ e_ident
    for (int i = 0; i < EI_NIDENT; i++) {
        headerCommand.e_ident[i] = (unsigned char) strtol(token, NULL, 16);
        token = strtok(NULL, " ");
    }

    // On ignore les 5 prochaines lignes
    passerNLignes(resultCommand, 5);

    // Ligne Type
    if (!fgets(ligne, STR_SIZE, resultCommand))
        fprintf(stderr, "Read error : (oracleEtape1) Type\n");
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
    else
        headerCommand.e_type = ET_NONE;

    // Ligne Machine
    if (!fgets(ligne, STR_SIZE, resultCommand))
        fprintf(stderr, "Read error : (oracleEtape1) Machine\n");
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
    else
        headerCommand.e_machine = ET_NONE;

    // Ligne Version
    if (!fgets(ligne, STR_SIZE, resultCommand))
        fprintf(stderr, "Read error : (oracleEtape1) Version\n");
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_version = strtol(token, NULL, 16);

    // Entry point address
    if (!fgets(ligne, STR_SIZE, resultCommand))
        fprintf(stderr, "Read error : (oracleEtape1) Address\n");
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_entry = strtol(token, NULL, 16);

    // Start of program headers
    if (!fgets(ligne, STR_SIZE, resultCommand))
        fprintf(stderr, "Read error : (oracleEtape1) Start of program header\n");
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_phoff = strtol(token, NULL, 16);

    // Start of section headers
    if (!fgets(ligne, STR_SIZE, resultCommand))
        fprintf(stderr, "Read error : (oracleEtape1) Start of section headers\n");
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_shoff = atoi(token);

    // Flags
    if (!fgets(ligne, STR_SIZE, resultCommand))
        fprintf(stderr, "Read error : (oracleEtape1) Flags\n");
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_flags = strtol(token, NULL, 16);

    // Size of this header
    if (!fgets(ligne, STR_SIZE, resultCommand))
        fprintf(stderr, "Read error : (oracleEtape1) Size\n");
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_ehsize = atoi(token);

    // Size of program headers
    if (!fgets(ligne, STR_SIZE, resultCommand))
        fprintf(stderr, "Read error : (oracleEtape1) Size of program headers\n");
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_phentsize = atoi(token);

    // Number of program headers
    if (!fgets(ligne, STR_SIZE, resultCommand))
        fprintf(stderr, "Read error : (oracleEtape1) Number of program headers\n");
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_phnum = atoi(token);

    // Size of section headers
    if (!fgets(ligne, STR_SIZE, resultCommand))
        fprintf(stderr, "Read error : (oracleEtape1) Size of program headers\n");
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_shentsize = atoi(token);

    // Number of section headers
    if (!fgets(ligne, STR_SIZE, resultCommand))
        fprintf(stderr, "Read error : (oracleEtape1) Number of section headers\n");
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_shnum = atoi(token);

    // Section header string table index
    if (!fgets(ligne, STR_SIZE, resultCommand))
        fprintf(stderr, "Read error : (oracleEtape1) String table of section headers\n");
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_shstrndx = atoi(token);

    pclose(resultCommand);

    /* On compare les deux headers */
    int echec = 0;
    // Champ e_ident
    int i = 0;
    while (i < EI_NIDENT && elf->ehdr.e_ident[i] == headerCommand.e_ident[i])
        i++;

    if (i < EI_NIDENT) {
        fprintf(stderr, "Erreur sur le champ e_ident\n");
        fprintf(stderr, "  e_ident obtenu avec la commande readelf -h : ");
        for (int i = 0; i < EI_NIDENT; i++)
            fprintf(stderr, "%d ", headerCommand.e_ident[i]);
        fprintf(stderr, "\n  e_ident obtenu avec la fonction ReadELFHeader : ");
        for (int i = 0; i < EI_NIDENT; i++)
            fprintf(stderr, "%d ", headerCommand.e_ident[i]);
        fprintf(stderr, "\n");
        echec = 1;
    }

    // Champ e_type
    if (elf->ehdr.e_type != headerCommand.e_type) {
        fprintf(stderr, "Erreur sur le champ e_type\n");
        fprintf(stderr, "  e_type obtenu avec la commande readelf -h : %d\n", headerCommand.e_type);
        fprintf(stderr, "  e_type obtenu avec la fonction ReadELFHeader : %d\n\n", elf->ehdr.e_type);
        echec = 1;
    }

    // Champ e_machine
    if (elf->ehdr.e_machine != headerCommand.e_machine) {
        fprintf(stderr, "Erreur sur le champ e_machine\n");
        fprintf(stderr, "  e_machine obtenu avec la commande readelf -h : %d\n", headerCommand.e_machine);
        fprintf(stderr, "  e_machine obtenu avec la fonction ReadELFHeader : %d\n\n", elf->ehdr.e_machine);
        echec = 1;
    }

    // Champ e_version
    if (elf->ehdr.e_version != headerCommand.e_version) {
        fprintf(stderr, "Erreur sur le champ e_version\n");
        fprintf(stderr, "  e_version obtenu avec la commande readelf -h : 0x%.2x\n", headerCommand.e_version);
        fprintf(stderr, "  e_version obtenu avec la fonction ReadELFHeader : 0x%.2x\n\n", elf->ehdr.e_version);
        echec = 1;
    }

    // Champ e_entry
    if (elf->ehdr.e_entry != headerCommand.e_entry) {
        fprintf(stderr, "Erreur sur le champ e_entry\n");
        fprintf(stderr, "  e_entry obtenu avec la commande readelf -h : 0x%.2x\n", headerCommand.e_entry);
        fprintf(stderr, "  e_entry obtenu avec la fonction ReadELFHeader : 0x%.2x\n\n", elf->ehdr.e_entry);
        echec = 1;
    }

    // Champ e_phoff
    if (elf->ehdr.e_phoff != headerCommand.e_phoff) {
        fprintf(stderr, "Erreur sur le champ e_phoff\n");
        fprintf(stderr, "  e_phoff obtenu avec la commande readelf -h : %d\n", headerCommand.e_phoff);
        fprintf(stderr, "  e_phoff obtenu avec la fonction ReadELFHeader : %d\n\n", elf->ehdr.e_phoff);
        echec = 1;
    }

    // Champ e_shoff
    if (elf->ehdr.e_shoff != headerCommand.e_shoff) {
        fprintf(stderr, "Erreur sur le champ e_shoff\n");
        fprintf(stderr, "  e_shoff obtenu avec la commande readelf -h : %d\n", headerCommand.e_shoff);
        fprintf(stderr, "  e_shoff obtenu avec la fonction ReadELFHeader : %d\n\n", elf->ehdr.e_shoff);
        echec = 1;
    }

    // Champ e_flags
    if (elf->ehdr.e_flags != headerCommand.e_flags) {
        fprintf(stderr, "Erreur sur le champ e_flags\n");
        fprintf(stderr, "  e_flags obtenu avec la commande readelf -h : 0x%.2x\n", headerCommand.e_flags);
        fprintf(stderr, "  e_flags obtenu avec la fonction ReadELFHeader : 0x%.2x\n\n", elf->ehdr.e_flags);
        echec = 1;
    }

    // Champ e_ehsize
    if (elf->ehdr.e_ehsize != headerCommand.e_ehsize) {
        fprintf(stderr, "Erreur sur le champ e_ehsize\n");
        fprintf(stderr, "  e_ehsize obtenu avec la commande readelf -h : %d\n", headerCommand.e_ehsize);
        fprintf(stderr, "  e_ehsize obtenu avec la fonction ReadELFHeader : %d\n\n", elf->ehdr.e_ehsize);
        echec = 1;
    }

    // Champ e_phentsize
    if (elf->ehdr.e_phentsize != headerCommand.e_phentsize) {
        fprintf(stderr, "Erreur sur le champ e_phentsize\n");
        fprintf(stderr, "  e_phentsize obtenu avec la commande readelf -h : %d\n", headerCommand.e_phentsize);
        fprintf(stderr, "  e_phentsize obtenu avec la fonction ReadELFHeader : %d\n\n", elf->ehdr.e_phentsize);
        echec = 1;
    }

    // Champ e_phnum
    if (elf->ehdr.e_phnum != headerCommand.e_phnum) {
        fprintf(stderr, "Erreur sur le champ e_phnum\n");
        fprintf(stderr, "  e_phnum obtenu avec la commande readelf -h : %d\n", headerCommand.e_phnum);
        fprintf(stderr, "  e_phnum obtenu avec la fonction ReadELFHeader : %d\n\n", elf->ehdr.e_phnum);
        echec = 1;
    }

    // Champ e_shentsize
    if (elf->ehdr.e_shentsize != headerCommand.e_shentsize) {
        fprintf(stderr, "Erreur sur le champ e_shentsize\n");
        fprintf(stderr, "  e_shentsize obtenu avec la commande readelf -h : %d\n", headerCommand.e_shentsize);
        fprintf(stderr, "  e_shentsize obtenu avec la fonction ReadELFHeader : %d\n\n", elf->ehdr.e_shentsize);
        echec = 1;
    }

    // Champ e_shnum
    if (elf->ehdr.e_shnum != headerCommand.e_shnum) {
        fprintf(stderr, "Erreur sur le champ e_shnum\n");
        fprintf(stderr, "  e_shnum obtenu avec la commande readelf -h : %d\n", headerCommand.e_shnum);
        fprintf(stderr, "  e_shnum obtenu avec la fonction ReadELFHeader : %d\n\n", elf->ehdr.e_shnum);
        echec = 1;
    }

    // Champ e_shstrndx
    if (elf->ehdr.e_shstrndx != headerCommand.e_shstrndx) {
        fprintf(stderr, "Erreur sur le champ e_shstrndx\n");
        fprintf(stderr, "  e_shstrndx obtenu avec la commande readelf -h : %d\n", headerCommand.e_shstrndx);
        fprintf(stderr, "  e_shstrndx obtenu avec la fonction ReadELFHeader : %d\n\n", elf->ehdr.e_shstrndx);
        echec = 1;
    }

    if (echec)
        printf("\033[0;31mEchec\033[0m pour l'etape 1\n");
    else
        printf("\033[0;32mSucces\033[0m pour l'etape 1\n");
}

void oracleEtape2(char *filename, ELF *elf) {
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
    for (int i = 0; i < strlen(buffer); i++) {
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
    char names[imax][STR_SIZE];
    char type[STR_SIZE];
    char flags[imax][STR_SIZE];
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

    char name[STR_SIZE];
    char flag[STR_SIZE];
    char beforecmp[2];
    int echec = 0;
    for (i = 0; i < imax; i++) {
        getSectionName(name, elf->file, elf->ehdr, elf->shdrTable, i);
        if (strcmp(names[i], name) != 0) {
            beforecmp[0] = names[i][colonnes[0] - 6];  // - 5 (pour '[...]') - 1 (pour le décalage entre colonnes)
            beforecmp[1] = name[colonnes[0] - 6];
            names[i][colonnes[0] - 6] = 0;
            name[colonnes[0] - 6] = 0;
            if (strcmp(names[i], name) != 0) {
                names[i][colonnes[0] - 6] = beforecmp[0];
                name[colonnes[0] - 6] = beforecmp[1];
                fprintf(stderr, "Erreur sur le nom de la section %d\n", i);
                fprintf(stderr, "  nom obtenu avec la commande readelf -S : '%s'\n", names[i]);
                fprintf(stderr, "  nom obtenu avec la fonction ReadELFTableSections : '%s'\n\n", name);
                echec = 1;
            }
        }
        if (shdr[i].sh_type != elf->shdrTable[i].sh_type) {
            fprintf(stderr, "Erreur sur le champ sh_type de la section %d\n", i);
            fprintf(stderr, "  sh_type obtenu avec la commande readelf -S : %x\n", shdr[i].sh_type);
            fprintf(stderr, "  sh_type obtenu avec la fonction ReadELFTableSections : %x\n\n", elf->shdrTable[i].sh_type);
            echec = 1;
        }
        if (shdr[i].sh_addr != elf->shdrTable[i].sh_addr) {
            fprintf(stderr, "Erreur sur le champ sh_addr de la section %d\n", i);
            fprintf(stderr, "  sh_addr obtenu avec la commande readelf -S : %x\n", shdr[i].sh_addr);
            fprintf(stderr, "  sh_addr obtenu avec la fonction ReadELFTableSections : %x\n\n", elf->shdrTable[i].sh_addr);
            echec = 1;
        }
        if (shdr[i].sh_offset != elf->shdrTable[i].sh_offset) {
            fprintf(stderr, "Erreur sur le champ sh_offset de la section %d\n", i);
            fprintf(stderr, "  sh_offset obtenu avec la commande readelf -S : %x\n", shdr[i].sh_offset);
            fprintf(stderr, "  sh_offset obtenu avec la fonction ReadELFTableSections : %x\n\n", elf->shdrTable[i].sh_offset);
            echec = 1;
        }
        if (shdr[i].sh_size != elf->shdrTable[i].sh_size) {
            fprintf(stderr, "Erreur sur le champ sh_size de la section %d\n", i);
            fprintf(stderr, "  sh_size obtenu avec la commande readelf -S : %x\n", shdr[i].sh_size);
            fprintf(stderr, "  sh_size obtenu avec la fonction ReadELFTableSections : %x\n\n", elf->shdrTable[i].sh_size);
            echec = 1;
        }
        if (shdr[i].sh_entsize != elf->shdrTable[i].sh_entsize) {
            fprintf(stderr, "Erreur sur le champ sh_entsize de la section %d\n", i);
            fprintf(stderr, "  sh_entsize obtenu avec la commande readelf -S : %x\n", shdr[i].sh_entsize);
            fprintf(stderr, "  sh_entsize obtenu avec la fonction ReadELFTableSections : %x\n\n", elf->shdrTable[i].sh_entsize);
            echec = 1;
        }
        getSectionFlags2(flag, elf->shdrTable[i]);
        if (strcmp(flags[i], flag) != 0) {
            fprintf(stderr, "Erreur sur le champ sh_flags de la section %d\n", i);
            fprintf(stderr, "  sh_flags obtenu avec la commande readelf -S : %s\n", flags[i]);
            fprintf(stderr, "  sh_flags obtenu avec la fonction ReadELFTableSections : %s\n\n", flag);
            echec = 1;
        }
        if (shdr[i].sh_link != elf->shdrTable[i].sh_link) {
            fprintf(stderr, "Erreur sur le champ sh_link de la section %d\n", i);
            fprintf(stderr, "  sh_link obtenu avec la commande readelf -S : %x\n", shdr[i].sh_link);
            fprintf(stderr, "  sh_link obtenu avec la fonction ReadELFTableSections : %x\n\n", elf->shdrTable[i].sh_link);
            echec = 1;
        }
        if (shdr[i].sh_info != elf->shdrTable[i].sh_info) {
            fprintf(stderr, "Erreur sur le champ sh_info de la section %d\n", i);
            fprintf(stderr, "  sh_info obtenu avec la commande readelf -S : %x\n", shdr[i].sh_info);
            fprintf(stderr, "  sh_info obtenu avec la fonction ReadELFTableSections : %x\n\n", elf->shdrTable[i].sh_info);
            echec = 1;
        }
        if (shdr[i].sh_addralign != elf->shdrTable[i].sh_addralign) {
            fprintf(stderr, "Erreur sur le champ sh_addralign de la section %d\n", i);
            fprintf(stderr, "  sh_addralign obtenu avec la commande readelf -S : %x\n", shdr[i].sh_addralign);
            fprintf(stderr, "  sh_addralign obtenu avec la fonction ReadELFTableSections : %x\n\n", elf->shdrTable[i].sh_addralign);
            echec = 1;
        }
    }
    if (echec)
        printf("\033[0;31mEchec\033[0m pour l'etape 2\n");
    else
        printf("\033[0;32mSucces\033[0m pour l'etape 2\n");
}

void oracleEtape3(char *filename, ELF *elf) {
    char command[2 * STR_SIZE];
    char ligne[STR_SIZE];
    FILE *resultCommand;
    uint8_t *resultProgram;
    uint8_t octet;
    int k;
    int echec = 0;
    for (int i = 1; i < elf->ehdr.e_shnum; i++) {
        sprintf(command, "readelf -x %d %s", i, filename);
        resultCommand = popen(command, "r");

        if (!fgets(ligne, STR_SIZE, resultCommand))
            fprintf(stderr, "Read error : (oracleEtape3) fgets\n");

        if (elf->shdrTable[i].sh_size)
            resultProgram = getSectionContent(elf->file, elf->shdrTable[i]);
        else {
            char name[STR_SIZE] = "";
            getSectionName(name, elf->file, elf->ehdr, elf->shdrTable, i);
            char nodata[2 * STR_SIZE];
            sprintf(nodata, "Section '%s' has no data to dump.\n", name);
            if (strcmp(nodata, ligne) != 0) {
                fprintf(stderr, "Erreur sur la section %d\n", i);
                fprintf(stderr, "  contenu obtenue avec readelf -x : %s\n", ligne);
                fprintf(stderr, "  est vide avec le programme\n\n");
                echec = 1;
            }
            pclose(resultCommand);
            continue;
        }

        passerNLignes(resultCommand, 1);  // On passe la ligne "Hex dump of section '...':"
        if (!fgets(ligne, STR_SIZE, resultCommand))
            fprintf(stderr, "Read error : (oracleEtape3) fgets\n");

        if (strcmp(" NOTE: This section has relocations against it, but these have NOT been applied to this dump.\n",
                   ligne) == 0) {
            if (!fgets(ligne, STR_SIZE, resultCommand))
                fprintf(stderr, "Read error : (oracleEtape3) fgets\n");
        }

        k = 0;
        do {
            for (int j = 13; j < 48; j++)
                ligne[j - 13] = ligne[j];  // On supprime l'adresse
            ligne[36] = 0;

            for (int j = 0; j < 35; j += 2) {
                if (ligne[j] == ' ') {
                    if (ligne[j - 1] == ' ')
                        break;
                    j--;
                } else {
                    sscanf(ligne + j, "%2hhx", &octet);
                    if (octet != resultProgram[k]) {
                        fprintf(stderr, "Erreur sur la section %d (offset 0x%.8x)\n", i, k);
                        fprintf(stderr, "  octet obtenu avec readelf -x : %.2x\n", octet);
                        fprintf(stderr, "  octet obtenu avec le programme : %.2x\n\n", resultProgram[k]);
                        echec = 1;
                        break;
                    }
                    k++;
                }
            }
        } while (fgets(ligne, STR_SIZE, resultCommand) && ligne[0] != '\n' && echec == 0);

        pclose(resultCommand);
        free(resultProgram);
    }

    if (echec)
        printf("\033[0;31mEchec\033[0m pour l'etape 3\n");
    else
        printf("\033[0;32mSucces\033[0m pour l'etape 3\n");
}

void oracleEtape4(char *filename, ELF *elf) {
    char command[STR_SIZE] = "readelf -sW ";
    FILE *resultCommand = popen(strcat(command, filename), "r");

    int imax;
    passerNLignes(resultCommand, 1);
    if (fscanf(resultCommand, "Symbol table '%*[^']' contains %d", &imax) != 1)
        fprintf(stderr, "Erreur de lecture du nombre d'entrées\n");
    passerNLignes(resultCommand, 1);

    Elf32_Sym st[imax];

    // lecture de la taille de chaque colonne
    char buffer[STR_SIZE];
    if (fgets(buffer, STR_SIZE, resultCommand) == NULL)
        fprintf(stderr, "Erreur de lecture de la ligne des titres\n");
    int espaces[8];
    int iespaces = 0;
    int nb_espace = 0;
    for (int i = 0; i < strlen(buffer); i++) {
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
    char names[imax][STR_SIZE];
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

    char name[STR_SIZE];
    int echec = 0;
    for (i = 0; i < imax; i++) {
        getSymbolName(name, elf->file, elf->ehdr, elf->shdrTable, elf->symTable[i]);
        if (strcmp(names[i], name) != 0) {
            fprintf(stderr, "Erreur sur le nom de l'entrée %d\n", i);
            fprintf(stderr, "  nom obtenu avec la commande readelf -s : '%s'\n", names[i]);
            fprintf(stderr, "  nom obtenu avec la fonction ReadELFTableSymbols : '%s'\n\n", name);
            echec = 1;
        }
        if (st[i].st_value != elf->symTable[i].st_value) {
            fprintf(stderr, "Erreur sur le champ st_value de l'entrée %d\n", i);
            fprintf(stderr, "  st_value obtenu avec la commande readelf -s : %x\n", st[i].st_value);
            fprintf(stderr, "  st_value obtenu avec la fonction ReadELFTableSymbols : %x\n\n", elf->symTable[i].st_value);
            echec = 1;
        }
        if (st[i].st_size != elf->symTable[i].st_size) {
            fprintf(stderr, "Erreur sur le champ st_size de l'entrée %d\n", i);
            fprintf(stderr, "  st_size obtenu avec la commande readelf -s : %x\n", st[i].st_size);
            fprintf(stderr, "  st_size obtenu avec la fonction ReadELFTableSymbols : %x\n\n", elf->symTable[i].st_size);
            echec = 1;
        }
        if (st[i].st_info != elf->symTable[i].st_info) {
            fprintf(stderr, "Erreur sur le champ st_info de l'entrée %d\n", i);
            fprintf(stderr, "  st_info obtenu avec la commande readelf -s : %x\n", st[i].st_info);
            fprintf(stderr, "  st_info obtenu avec la fonction ReadELFTableSymbols : %x\n\n", elf->symTable[i].st_info);
            echec = 1;
        }
        if (st[i].st_other != elf->symTable[i].st_other) {
            fprintf(stderr, "Erreur sur le champ st_other de l'entrée %d\n", i);
            fprintf(stderr, "  st_other obtenu avec la commande readelf -s : %x\n", st[i].st_other);
            fprintf(stderr, "  st_other obtenu avec la fonction ReadELFTableSymbols : %x\n\n", elf->symTable[i].st_other);
            echec = 1;
        }
        if (st[i].st_shndx != elf->symTable[i].st_shndx) {
            fprintf(stderr, "Erreur sur le champ st_shndx de l'entrée %d\n", i);
            fprintf(stderr, "  st_shndx obtenu avec la commande readelf -s : %x\n", st[i].st_shndx);
            fprintf(stderr, "  st_shndx obtenu avec la fonction ReadELFTableSymbols : %x\n\n", elf->symTable[i].st_shndx);
            echec = 1;
        }
    }
    if (echec)
        printf("\033[0;31mEchec\033[0m pour l'etape 4\n");
    else
        printf("\033[0;32mSucces\033[0m pour l'etape 4\n");
}

void oracleEtape5(char *filename, ELF *elf) {
    char command[STR_SIZE] = "readelf -r ";
    FILE *resultCommand = popen(strcat(command, filename), "r");

    char ligne[STR_SIZE];
    char name[STR_SIZE];
    int index = 0;
    int k = 0;
    Elf32_Addr r_offset;
    Elf32_Word r_info;
    int echec = 0;
    while (fgets(ligne, STR_SIZE, resultCommand)) {
        if (strcmp(ligne, "\n") == 0)
            continue;
        else if (strcmp(ligne, "There are no relocations in this file.\n") == 0) {
            for (int i = 0; i < elf->ehdr.e_shnum; i++) {
                if (elf->relTables[i] != NULL && elf->shdrTable[i].sh_size) {
                    fprintf(stderr, "Erreur sur la table des relocation\n");
                    fprintf(stderr, "  pas de relocation avec la commande readelf -r\n");
                    fprintf(stderr, "  section %d contient des relocations avec la fonction ReadELFRelocationTable\n\n", i);
                    echec = 1;
                }
            }
            continue;
        } else if (strncmp(ligne, "Relocation section", 18) == 0) {
            sscanf(ligne, "Relocation section '%[^']s'", name);
            index = sectionName2Index(name, elf->file, elf->ehdr, elf->shdrTable);
            passerNLignes(resultCommand, 1);
            k = 0;
            continue;
        }
        sscanf(ligne, "%8x %8x", &r_offset, &r_info);
        if (elf->relTables[index] != NULL) {
            if (r_offset != elf->relTables[index][k].r_offset) {
                fprintf(stderr, "Erreur sur l'entrée %d de la table des relocations %s\n", k, name);
                fprintf(stderr, "  r_offset obtenu avec la commande readelf -r : %.8x\n", r_offset);
                fprintf(stderr, "  r_offset obtenu avec la fonction ReadELFRelocationTable : %.8x\n\n", elf->relTables[index][k].r_offset);
                echec = 1;
            }
            if (r_info != elf->relTables[index][k].r_info) {
                fprintf(stderr, "Erreur sur l'entrée %d de la table des relocations %s\n", k, name);
                fprintf(stderr, "  r_info obtenu avec la commande readelf -r : %.8x\n", r_info);
                fprintf(stderr, "  r_info obtenu avec la fonction ReadELFRelocationTable : %.8x\n\n", elf->relTables[index][k].r_info);
                echec = 1;
            }
        } else {
            fprintf(stderr, "Erreur sur la table des relocation\n");
            fprintf(stderr, "  section %d contient des relocations avec la commande readelf -r\n", index);
            fprintf(stderr, "  pas de relocation avec la fonction ReadELFRelocationTable\n\n");
            echec = 1;
        }
        k++;
    }

    if (echec)
        printf("\033[0;31mEchec\033[0m pour l'etape 5\n");
    else
        printf("\033[0;32mSucces\033[0m pour l'etape 5\n");

    pclose(resultCommand);
}


void oracleEtape6(char *filename1, char *filename2, ELF *elf1, ELF *elf2) {
    FusionELF_Etape6 *res = LinkELFRenumSections(elf1, elf2);

    uint8_t *buff;
    int echec = 0;
    int local_echec;
    int k;
    int i = 0;
    int cat_offset;
    while (i < elf1->nbsh) {
        if (elf1->shdrTable[i].sh_size) {
            local_echec = 0;
            buff = getSectionContent(elf1->file, elf1->shdrTable[i]);
            for (int j = 0; j < elf1->shdrTable[i].sh_size; j++) {
                if (res->contents[i][j] != buff[j] && local_echec == 0) {
                    fprintf(stderr, "Erreur sur la section %d du premier fichier ELF (offset 0x%.8x)\n", i, j);
                    fprintf(stderr, "  octet obtenu apres la fonction LinkELFRenumSections : %.2x\n", res->contents[i][j]);
                    fprintf(stderr, "  octet obtenu dans la section correspondante : %.2x\n\n", buff[j]);
                    echec = 1;
                    local_echec = 1;
                }
            }
            free(buff);
        }
        if (elf1->shdrTable[i].sh_type == SHT_PROGBITS) {
            for (k = 0; k < res->size; k++) {
                if (res->renum[k] == i)
                    break;
            }
            if (k < res->size && elf2->shdrTable[k].sh_size) {
                local_echec = 0;
                buff = getSectionContent(elf2->file, elf2->shdrTable[k]);
                cat_offset = elf1->shdrTable[i].sh_size;
                for (int j = 0; j < elf2->shdrTable[k].sh_size; j++) {
                    if (res->contents[i][j + cat_offset] != buff[j] && local_echec == 0) {
                        fprintf(stderr, "Erreur sur la section %d du second fichier ELF (offset 0x%.8x)\n", k, j);
                        fprintf(stderr, "  octet obtenu apres la fonction LinkELFRenumSections : %.2x\n", res->contents[i][j + cat_offset]);
                        fprintf(stderr, "  octet obtenu dans la section correspondante : %.2x\n\n", buff[j]);
                        echec = 1;
                        local_echec = 1;
                    }
                }
                free(buff);
            }
        }
        i++;
    }
    while (i < res->snb) {
        for (k = 0; k < res->size; k++) {
            if (res->renum[k] == i)
                break;
        }
        if (k < res->size && elf2->shdrTable[k].sh_size) {
            local_echec = 0;
            buff = getSectionContent(elf2->file, elf2->shdrTable[k]);
            for (int j = 0; j < elf2->shdrTable[k].sh_size; j++) {
                if (res->contents[i][j] != buff[j] && local_echec == 0) {
                    fprintf(stderr, "Erreur sur la section %d du second fichier ELF (offset 0x%.8x)\n", k, j);
                    fprintf(stderr, "  octet obtenu apres la fonction LinkELFRenumSections : %.2x\n", res->contents[i][j]);
                    fprintf(stderr, "  octet obtenu dans la section correspondante : %.2x\n\n", buff[j]);
                    echec = 1;
                    local_echec = 1;
                }
            }
            free(buff);
        }
        i++;
    }

    if (echec)
        printf("\033[0;31mEchec\033[0m pour l'etape 6\n");
    else
        printf("\033[0;32mSucces\033[0m pour l'etape 6\n");

    free_fusion6(res);
}

void oracleEtape7(char *filename1, char *filename2, ELF *elf1, ELF *elf2) {
    FusionELF_Etape6 *fusion6 = LinkELFRenumSections(elf1, elf2);

    // Fusion des tables des symboles des deux fichiers en entrées
    ELF *elfRes = LinkELFSymbols(elf1, elf2, fusion6);
    free_fusion6(fusion6);

    int i = 0;
    int j = 0;
    int error = 0;

    // Si la fusion a réussi
    if (elfRes != NULL) {
        // On vérifie que tout les symboles locaux des deux fichiers en entrée sont dans la table des symboles finale
        i = 0;
        while (i < elf1->nbsym && !error) {
            if (ELF32_ST_BIND(elf1->symTable[i].st_info) == STB_LOCAL) {
                j = 0;
                while (j < elfRes->nbsym && elf1->symTable[i].st_name != elfRes->symTable[j].st_name)
                    j++;
                error = (j == elfRes->nbsym);
            }
            i++;
        }

        i = 0;
        while (i < elf2->nbsym && !error) {
            if (ELF32_ST_BIND(elf2->symTable[i].st_info) == STB_LOCAL) {
                j = 0;
                while (j < elfRes->nbsym && elf2->symTable[i].st_name != elfRes->symTable[j].st_name)
                    j++;
                error = j == elfRes->nbsym;
            }
            i++;
        }
    }

    // Dans tout les cas on vérifie que les deux fichiers en entrée n'ont aucun symbole global défini avec le même nom
    i = 0;
    while (i < elf1->nbsym && !error) {
        j = i + 1;
        while (j < elf2->nbsym && !error) {
            error = elf1->symTable[i].st_name == elf2->symTable[j].st_name
                    && ELF32_ST_BIND(elf1->symTable[i].st_info) == STB_GLOBAL
                    && ELF32_ST_BIND(elf2->symTable[j].st_info) == STB_GLOBAL
                    && ELF32_ST_TYPE(elf1->symTable[i].st_info) != STT_NOTYPE
                    && ELF32_ST_TYPE(elf2->symTable[j].st_info) != STT_NOTYPE;
            j++;
        }
        i++;
    }

    if ((elfRes == NULL && error) || (elfRes != NULL && !error))
        printf("\033[0;32mSucces\033[0m pour l'etape 7\n");
    else
        printf("\033[0;31mEchec\033[0m pour l'etape 7\n");

    if (elfRes != NULL)
        free_ELF(elfRes);
}

void oracleEtape8(char* filename1, char* filename2, ELF* elf1, ELF* elf2){
    FusionELF_Etape6 *fusion6 = LinkELFRenumSections(elf1, elf2);

    // Fusion des tables des symboles des deux fichiers en entrées
    ELF *elfRes = LinkELFSymbols(elf1, elf2, fusion6);

    LinkELFTableRelocation(elfRes,fusion6,elf1,elf2);



    free_fusion6(fusion6);

    if (elfRes != NULL)
        free_ELF(elfRes);
}

int main(int argc, char *argv[]) {
    if (argc < 2)
        fprintf(stderr, "Il faut au moins un fichier de test\n");
    else {
        FILE *file1, *file2;
        ELF *elf1, *elf2;
        for (int i = 1; i < argc; i++) {
            file1 = fopen(argv[i], "r");
            if (!file1) {
                printf("File not found : '%s'\n", argv[i]);
                exit(1);
            }
            elf1 = ReadELF(file1);

            printf("\nTests Phase 1 avec le fichier '%s'\n", argv[i]);
            oracleEtape1(argv[i], elf1);
            oracleEtape2(argv[i], elf1);
            oracleEtape3(argv[i], elf1);
            //oracleEtape4(argv[i], elf1);
            oracleEtape5(argv[i], elf1);

            fclose(file1);
            free_ELF(elf1);
        }
        if (argc == 3) {
            file1 = fopen(argv[1], "r");
            file2 = fopen(argv[2], "r");
            if (!file1) {
                printf("File not found : '%s'\n", argv[1]);
                exit(1);
            }
            if (!file2) {
                printf("File not found : '%s'\n", argv[2]);
                exit(1);
            }
            elf1 = ReadELF(file1);
            elf2 = ReadELF(file2);

            printf("\nTests Phase 2 avec la fusion des fichiers '%s' et '%s'\n", argv[1], argv[2]);
            oracleEtape6(argv[1], argv[2], elf1, elf2);
            oracleEtape7(argv[1], argv[2], elf1, elf2);
            //oracleEtape8(argv[1], argv[2], elf1, elf2);
            printf("\033[0;33mOracle incomplet\033[0m pour l'etape 8\n");

            fclose(file1);
            fclose(file2);
            free_ELF(elf1);
            free_ELF(elf2);
        }
    }
    return 0;
}
