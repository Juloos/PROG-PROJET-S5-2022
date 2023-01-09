#include "ELF.h"


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
    if (!fgets(ligne, STR_SIZE, resultCommand)) {
        fprintf(stderr, "Read error : (oracleEtape1) Magic\n");
    }
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
    if (!fgets(ligne, STR_SIZE, resultCommand)) {
        fprintf(stderr, "Read error : (oracleEtape1) Type\n");
    }
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
    if (!fgets(ligne, STR_SIZE, resultCommand)) {
        fprintf(stderr, "Read error : (oracleEtape1) Machine\n");
    }
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
    if (!fgets(ligne, STR_SIZE, resultCommand)) {
        fprintf(stderr, "Read error : (oracleEtape1) Version\n");
    }
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_version = strtol(token, NULL, 16);

    // Entry point address
    if (!fgets(ligne, STR_SIZE, resultCommand)) {
        fprintf(stderr, "Read error : (oracleEtape1) Address\n");
    }
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_entry = strtol(token, NULL, 16);

    // Start of program headers
    if (!fgets(ligne, STR_SIZE, resultCommand)) {
        fprintf(stderr, "Read error : (oracleEtape1) Start of program header\n");
    }
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_phoff = strtol(token, NULL, 16);

    // Start of section headers
    if (!fgets(ligne, STR_SIZE, resultCommand)) {
        fprintf(stderr, "Read error : (oracleEtape1) Start of section headers\n");
    }
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_shoff = atoi(token);

    // Flags
    if (!fgets(ligne, STR_SIZE, resultCommand)) {
        fprintf(stderr, "Read error : (oracleEtape1) Flags\n");
    }
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_flags = strtol(token, NULL, 16);

    // Size of this header
    if (!fgets(ligne, STR_SIZE, resultCommand)) {
        fprintf(stderr, "Read error : (oracleEtape1) Size\n");
    }
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_ehsize = atoi(token);

    // Size of program headers
    if (!fgets(ligne, STR_SIZE, resultCommand)) {
        fprintf(stderr, "Read error : (oracleEtape1) Size of program headers\n");
    }
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_phentsize = atoi(token);

    // Number of program headers
    if (!fgets(ligne, STR_SIZE, resultCommand)) {
        fprintf(stderr, "Read error : (oracleEtape1) Number of program headers\n");
    }
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_phnum = atoi(token);

    // Size of section headers
    if (!fgets(ligne, STR_SIZE, resultCommand)) {
        fprintf(stderr, "Read error : (oracleEtape1) Size of program headers\n");
    }
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_shentsize = atoi(token);

    // Number of section headers
    if (!fgets(ligne, STR_SIZE, resultCommand)) {
        fprintf(stderr, "Read error : (oracleEtape1) Number of section headers\n");
    }
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand.e_shnum = atoi(token);

    // Section header string table index
    if (!fgets(ligne, STR_SIZE, resultCommand)) {
        fprintf(stderr, "Read error : (oracleEtape1) String table of section headers\n");
    }
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
        fprintf(stderr, "Erreur sur le champ e_ident\n");
        fprintf(stderr, "  e_ident obtenu avec la commande readelf -h : ");
        for (int i = 0; i < EI_NIDENT; i++) {
            fprintf(stderr, "%d ", headerCommand.e_ident[i]);
        }
        fprintf(stderr, "\n  e_ident obtenu avec la fonction ReadELFHeader : ");
        for (int i = 0; i < EI_NIDENT; i++) {
            fprintf(stderr, "%d ", headerCommand.e_ident[i]);
        }
        fprintf(stderr, "\n");
        echec = 1;
    }

    // Champ e_type
    if (headerProgram.e_type != headerCommand.e_type) {
        fprintf(stderr, "Erreur sur le champ e_type\n");
        fprintf(stderr, "  e_type obtenu avec la commande readelf -h : %d\n", headerCommand.e_type);
        fprintf(stderr, "  e_type obtenu avec la fonction ReadELFHeader : %d\n\n", headerProgram.e_type);
        echec = 1;
    }

    // Champ e_machine
    if (headerProgram.e_machine != headerCommand.e_machine) {
        fprintf(stderr, "Erreur sur le champ e_machine\n");
        fprintf(stderr, "  e_machine obtenu avec la commande readelf -h : %d\n", headerCommand.e_machine);
        fprintf(stderr, "  e_machine obtenu avec la fonction ReadELFHeader : %d\n\n", headerProgram.e_machine);
        echec = 1;
    }

    // Champ e_version
    if (headerProgram.e_version != headerCommand.e_version) {
        fprintf(stderr, "Erreur sur le champ e_version\n");
        fprintf(stderr, "  e_version obtenu avec la commande readelf -h : 0x%.2x\n", headerCommand.e_version);
        fprintf(stderr, "  e_version obtenu avec la fonction ReadELFHeader : 0x%.2x\n\n", headerProgram.e_version);
        echec = 1;
    }

    // Champ e_entry
    if (headerProgram.e_entry != headerCommand.e_entry) {
        fprintf(stderr, "Erreur sur le champ e_entry\n");
        fprintf(stderr, "  e_entry obtenu avec la commande readelf -h : 0x%.2x\n", headerCommand.e_entry);
        fprintf(stderr, "  e_entry obtenu avec la fonction ReadELFHeader : 0x%.2x\n\n", headerProgram.e_entry);
        echec = 1;
    }

    // Champ e_phoff
    if (headerProgram.e_phoff != headerCommand.e_phoff) {
        fprintf(stderr, "Erreur sur le champ e_phoff\n");
        fprintf(stderr, "  e_phoff obtenu avec la commande readelf -h : %d\n", headerCommand.e_phoff);
        fprintf(stderr, "  e_phoff obtenu avec la fonction ReadELFHeader : %d\n\n", headerProgram.e_phoff);
        echec = 1;
    }

    // Champ e_shoff
    if (headerProgram.e_shoff != headerCommand.e_shoff) {
        fprintf(stderr, "Erreur sur le champ e_shoff\n");
        fprintf(stderr, "  e_shoff obtenu avec la commande readelf -h : %d\n", headerCommand.e_shoff);
        fprintf(stderr, "  e_shoff obtenu avec la fonction ReadELFHeader : %d\n\n", headerProgram.e_shoff);
        echec = 1;
    }

    // Champ e_flags
    if (headerProgram.e_flags != headerCommand.e_flags) {
        fprintf(stderr, "Erreur sur le champ e_flags\n");
        fprintf(stderr, "  e_flags obtenu avec la commande readelf -h : 0x%.2x\n", headerCommand.e_flags);
        fprintf(stderr, "  e_flags obtenu avec la fonction ReadELFHeader : 0x%.2x\n\n", headerProgram.e_flags);
        echec = 1;
    }

    // Champ e_ehsize
    if (headerProgram.e_ehsize != headerCommand.e_ehsize) {
        fprintf(stderr, "Erreur sur le champ e_ehsize\n");
        fprintf(stderr, "  e_ehsize obtenu avec la commande readelf -h : %d\n", headerCommand.e_ehsize);
        fprintf(stderr, "  e_ehsize obtenu avec la fonction ReadELFHeader : %d\n\n", headerProgram.e_ehsize);
        echec = 1;
    }

    // Champ e_phentsize
    if (headerProgram.e_phentsize != headerCommand.e_phentsize) {
        fprintf(stderr, "Erreur sur le champ e_phentsize\n");
        fprintf(stderr, "  e_phentsize obtenu avec la commande readelf -h : %d\n", headerCommand.e_phentsize);
        fprintf(stderr, "  e_phentsize obtenu avec la fonction ReadELFHeader : %d\n\n", headerProgram.e_phentsize);
        echec = 1;
    }

    // Champ e_phnum
    if (headerProgram.e_phnum != headerCommand.e_phnum) {
        fprintf(stderr, "Erreur sur le champ e_phnum\n");
        fprintf(stderr, "  e_phnum obtenu avec la commande readelf -h : %d\n", headerCommand.e_phnum);
        fprintf(stderr, "  e_phnum obtenu avec la fonction ReadELFHeader : %d\n\n", headerProgram.e_phnum);
        echec = 1;
    }

    // Champ e_shentsize
    if (headerProgram.e_shentsize != headerCommand.e_shentsize) {
        fprintf(stderr, "Erreur sur le champ e_shentsize\n");
        fprintf(stderr, "  e_shentsize obtenu avec la commande readelf -h : %d\n", headerCommand.e_shentsize);
        fprintf(stderr, "  e_shentsize obtenu avec la fonction ReadELFHeader : %d\n\n", headerProgram.e_shentsize);
        echec = 1;
    }

    // Champ e_shnum
    if (headerProgram.e_shnum != headerCommand.e_shnum) {
        fprintf(stderr, "Erreur sur le champ e_shnum\n");
        fprintf(stderr, "  e_shnum obtenu avec la commande readelf -h : %d\n", headerCommand.e_shnum);
        fprintf(stderr, "  e_shnum obtenu avec la fonction ReadELFHeader : %d\n\n", headerProgram.e_shnum);
        echec = 1;
    }

    // Champ e_shstrndx
    if (headerProgram.e_shstrndx != headerCommand.e_shstrndx) {
        fprintf(stderr, "Erreur sur le champ e_shstrndx\n");
        fprintf(stderr, "  e_shstrndx obtenu avec la commande readelf -h : %d\n", headerCommand.e_shstrndx);
        fprintf(stderr, "  e_shstrndx obtenu avec la fonction ReadELFHeader : %d\n\n", headerProgram.e_shstrndx);
        echec = 1;
    }

    if (echec)
        printf("\033[0;31mEchec\033[0m pour l'etape 1\n");
    else
        printf("\033[0;32mSucces\033[0m pour l'etape 1\n");
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
    for (i = 0; i < imax; i++) {
        getSectionName(name, file, header, shdrProgram, i);
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
        if (shdr[i].sh_type != shdrProgram[i].sh_type) {
            fprintf(stderr, "Erreur sur le champ sh_type de la section %d\n", i);
            fprintf(stderr, "  sh_type obtenu avec la commande readelf -S : %x\n", shdr[i].sh_type);
            fprintf(stderr, "  sh_type obtenu avec la fonction ReadELFTableSections : %x\n\n", shdrProgram[i].sh_type);
            echec = 1;
        }
        if (shdr[i].sh_addr != shdrProgram[i].sh_addr) {
            fprintf(stderr, "Erreur sur le champ sh_addr de la section %d\n", i);
            fprintf(stderr, "  sh_addr obtenu avec la commande readelf -S : %x\n", shdr[i].sh_addr);
            fprintf(stderr, "  sh_addr obtenu avec la fonction ReadELFTableSections : %x\n\n", shdrProgram[i].sh_addr);
            echec = 1;
        }
        if (shdr[i].sh_offset != shdrProgram[i].sh_offset) {
            fprintf(stderr, "Erreur sur le champ sh_offset de la section %d\n", i);
            fprintf(stderr, "  sh_offset obtenu avec la commande readelf -S : %x\n", shdr[i].sh_offset);
            fprintf(stderr, "  sh_offset obtenu avec la fonction ReadELFTableSections : %x\n\n", shdrProgram[i].sh_offset);
            echec = 1;
        }
        if (shdr[i].sh_size != shdrProgram[i].sh_size) {
            fprintf(stderr, "Erreur sur le champ sh_size de la section %d\n", i);
            fprintf(stderr, "  sh_size obtenu avec la commande readelf -S : %x\n", shdr[i].sh_size);
            fprintf(stderr, "  sh_size obtenu avec la fonction ReadELFTableSections : %x\n\n", shdrProgram[i].sh_size);
            echec = 1;
        }
        if (shdr[i].sh_entsize != shdrProgram[i].sh_entsize) {
            fprintf(stderr, "Erreur sur le champ sh_entsize de la section %d\n", i);
            fprintf(stderr, "  sh_entsize obtenu avec la commande readelf -S : %x\n", shdr[i].sh_entsize);
            fprintf(stderr, "  sh_entsize obtenu avec la fonction ReadELFTableSections : %x\n\n", shdrProgram[i].sh_entsize);
            echec = 1;
        }
        getSectionFlags2(flag, shdrProgram[i]);
        if (strcmp(flags[i], flag) != 0) {
            fprintf(stderr, "Erreur sur le champ sh_flags de la section %d\n", i);
            fprintf(stderr, "  sh_flags obtenu avec la commande readelf -S : %s\n", flags[i]);
            fprintf(stderr, "  sh_flags obtenu avec la fonction ReadELFTableSections : %s\n\n", flag);
            echec = 1;
        }
        if (shdr[i].sh_link != shdrProgram[i].sh_link) {
            fprintf(stderr, "Erreur sur le champ sh_link de la section %d\n", i);
            fprintf(stderr, "  sh_link obtenu avec la commande readelf -S : %x\n", shdr[i].sh_link);
            fprintf(stderr, "  sh_link obtenu avec la fonction ReadELFTableSections : %x\n\n", shdrProgram[i].sh_link);
            echec = 1;
        }
        if (shdr[i].sh_info != shdrProgram[i].sh_info) {
            fprintf(stderr, "Erreur sur le champ sh_info de la section %d\n", i);
            fprintf(stderr, "  sh_info obtenu avec la commande readelf -S : %x\n", shdr[i].sh_info);
            fprintf(stderr, "  sh_info obtenu avec la fonction ReadELFTableSections : %x\n\n", shdrProgram[i].sh_info);
            echec = 1;
        }
        if (shdr[i].sh_addralign != shdrProgram[i].sh_addralign) {
            fprintf(stderr, "Erreur sur le champ sh_addralign de la section %d\n", i);
            fprintf(stderr, "  sh_addralign obtenu avec la commande readelf -S : %x\n", shdr[i].sh_addralign);
            fprintf(stderr, "  sh_addralign obtenu avec la fonction ReadELFTableSections : %x\n\n", shdrProgram[i].sh_addralign);
            echec = 1;
        }
    }
    if (echec)
        printf("\033[0;31mEchec\033[0m pour l'etape 2\n");
    else
        printf("\033[0;32mSucces\033[0m pour l'etape 2\n");
}

void oracleEtape3(char *filename) {
    FILE *file = fopen(filename, "r");
    Elf32_Ehdr header;
    ReadELFHeader(file, &header);
    Elf32_Shdr *shdr = create_ELFTableSections(header);
    ReadELFTableSections(file, header, shdr);

    char command[2 * STR_SIZE];
    char ligne[STR_SIZE];
    FILE *resultCommand;
    uint8_t *resultProgram;
    uint8_t octet;
    int k;
    int echec = 0;
    for (int i = 1; i < header.e_shnum; i++) {
        sprintf(command, "readelf -x %d %s", i, filename);
        resultCommand = popen(command, "r");

        if (!fgets(ligne, STR_SIZE, resultCommand))
            fprintf(stderr, "Read error : (oracleEtape3) fgets\n");

        if (shdr[i].sh_size)
            resultProgram = getSectionContent(file, shdr[i]);
        else {
            char name[STR_SIZE] = "";
            getSectionName(name, file, header, shdr, i);
            char nodata[2 * STR_SIZE];
            sprintf(nodata, "Section '%s' has no data to dump.\n", name);
            if (strcmp(nodata, ligne) != 0) {
                fprintf(stderr, "Erreur sur la section %d\n", i);
                fprintf(stderr, "  contenu obtenue avec readelf -x : %s\n", ligne);
                fprintf(stderr, "  est vide avec le programme\n\n");
                echec = 1;
            }
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
    fclose(file);

    if (echec)
        printf("\033[0;31mEchec\033[0m pour l'etape 3\n");
    else
        printf("\033[0;32mSucces\033[0m pour l'etape 3\n");
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
    for (i = 0; i < imax; i++) {
        getSymbolName(name, file, header, shdrProgram, stProgram[i]);
        if (strcmp(names[i], name) != 0) {
            fprintf(stderr, "Erreur sur le nom de l'entrée %d\n", i);
            fprintf(stderr, "  nom obtenu avec la commande readelf -s : '%s'\n", names[i]);
            fprintf(stderr, "  nom obtenu avec la fonction ReadELFTableSymbols : '%s'\n\n", name);
            echec = 1;
        }
        if (st[i].st_value != stProgram[i].st_value) {
            fprintf(stderr, "Erreur sur le champ st_value de l'entrée %d\n", i);
            fprintf(stderr, "  st_value obtenu avec la commande readelf -s : %x\n", st[i].st_value);
            fprintf(stderr, "  st_value obtenu avec la fonction ReadELFTableSymbols : %x\n\n", stProgram[i].st_value);
            echec = 1;
        }
        if (st[i].st_size != stProgram[i].st_size) {
            fprintf(stderr, "Erreur sur le champ st_size de l'entrée %d\n", i);
            fprintf(stderr, "  st_size obtenu avec la commande readelf -s : %x\n", st[i].st_size);
            fprintf(stderr, "  st_size obtenu avec la fonction ReadELFTableSymbols : %x\n\n", stProgram[i].st_size);
            echec = 1;
        }
        if (st[i].st_info != stProgram[i].st_info) {
            fprintf(stderr, "Erreur sur le champ st_info de l'entrée %d\n", i);
            fprintf(stderr, "  st_info obtenu avec la commande readelf -s : %x\n", st[i].st_info);
            fprintf(stderr, "  st_info obtenu avec la fonction ReadELFTableSymbols : %x\n\n", stProgram[i].st_info);
            echec = 1;
        }
        if (st[i].st_other != stProgram[i].st_other) {
            fprintf(stderr, "Erreur sur le champ st_other de l'entrée %d\n", i);
            fprintf(stderr, "  st_other obtenu avec la commande readelf -s : %x\n", st[i].st_other);
            fprintf(stderr, "  st_other obtenu avec la fonction ReadELFTableSymbols : %x\n\n", stProgram[i].st_other);
            echec = 1;
        }
        if (st[i].st_shndx != stProgram[i].st_shndx) {
            fprintf(stderr, "Erreur sur le champ st_shndx de l'entrée %d\n", i);
            fprintf(stderr, "  st_shndx obtenu avec la commande readelf -s : %x\n", st[i].st_shndx);
            fprintf(stderr, "  st_shndx obtenu avec la fonction ReadELFTableSymbols : %x\n\n", stProgram[i].st_shndx);
            echec = 1;
        }
    }
    if (echec)
        printf("\033[0;31mEchec\033[0m pour l'etape 4\n");
    else
        printf("\033[0;32mSucces\033[0m pour l'etape 4\n");
}

void oracleEtape5(char *filename) {
    char command[STR_SIZE] = "readelf -r ";
    FILE *resultCommand = popen(strcat(command, filename), "r");

    FILE *file = fopen(filename, "r");
    Elf32_Ehdr ehdr;
    ReadELFHeader(file, &ehdr);
    Elf32_Shdr *shdrTable = create_ELFTableSections(ehdr);
    ReadELFTableSections(file, ehdr, shdrTable);
    Elf32_Shdr sh_symtab = shdrTable[sectionName2Index(".symtab", file, ehdr, shdrTable)];
    Elf32_Sym *symTable = create_ELFTableSymbols(sh_symtab);
    ReadELFTableSymbols(file, symTable, sh_symtab);
    Elf32_Rel **relTables = create_ELFTablesRel(ehdr);
    ReadELFRelocationTable(file, relTables, ehdr, shdrTable, symTable);

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
        else if (strncmp(ligne, "Relocation section", 18) == 0) {
            sscanf(ligne, "Relocation section '%[^']s'", name);
            index = sectionName2Index(name, file, ehdr, shdrTable);
            passerNLignes(resultCommand, 1);
            k = 0;
            continue;
        }
        sscanf(ligne, "%8x %8x", &r_offset, &r_info);
        if (r_offset != relTables[index][k].r_offset) {
            fprintf(stderr, "Erreur sur l'entrée %d de la table de relocation %s\n", k, name);
            fprintf(stderr, "  r_offset obtenu avec la commande readelf -r : %.8x\n", r_offset);
            fprintf(stderr, "  r_offset obtenu avec la fonction ReadELFRelocationTable : %.8x\n\n",
                   relTables[index][k].r_offset);
            echec = 1;
        }
        if (r_info != relTables[index][k].r_info) {
            fprintf(stderr, "Erreur sur l'entrée %d de la table de relocation %s\n", k, name);
            fprintf(stderr, "  r_info obtenu avec la commande readelf -r : %.8x\n", r_info);
            fprintf(stderr, "  r_info obtenu avec la fonction ReadELFRelocationTable : %.8x\n\n", relTables[index][k].r_info);
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


void oracleEtape6(char *filename1, char *filename2) {
    FILE *file1 = fopen(filename1, "r");
    FILE *file2 = fopen(filename2, "r");

    Elf32_Ehdr ehdr1, ehdr2;
    ReadELFHeader(file1, &ehdr1);
    ReadELFHeader(file2, &ehdr2);
    Elf32_Shdr *shdrTable1 = create_ELFTableSections(ehdr1);
    Elf32_Shdr *shdrTable2 = create_ELFTableSections(ehdr2);
    ReadELFTableSections(file1, ehdr1, shdrTable1);
    ReadELFTableSections(file2, ehdr2, shdrTable2);

    FILE *output = fopen("output.tmp", "w");
    FusionELF_Etape6 *res = LinkELFRenumSections(file1, file2, output);
    fclose(output);

    output = fopen("output.tmp", "r");

    uint8_t octet;
    uint8_t *buff;
    int echec = 0;
    int local_echec;
    int k;
    int i = 0;
    while (i < ehdr1.e_shnum) {
        if (shdrTable1[i].sh_size) {
            local_echec = 0;
            buff = getSectionContent(file1, shdrTable1[i]);
            for (int j = 0; j < shdrTable1[i].sh_size; j++) {
                octet = fgetc(output);
                if (octet != buff[j] && local_echec == 0) {
                    fprintf(stderr, "Erreur sur la section %d du premier fichier ELF (offset 0x%.8x)\n", i, j);
                    fprintf(stderr, "  octet obtenu dans le fichier resultat de LinkELFRenumSections : %.2x\n", octet);
                    fprintf(stderr, "  octet obtenu dans la section correspondante : %.2x\n\n", buff[j]);
                    echec = 1;
                    local_echec = 1;
                }
            }
            free(buff);
        }
        if (shdrTable1[i].sh_type == SHT_PROGBITS) {
            for (k = 0; k < res->size; k++) {
                if (res->renum[k] == i)
                    break;
            }
            if (k < res->size && shdrTable2[k].sh_size) {
                local_echec = 0;
                buff = getSectionContent(file2, shdrTable2[k]);
                for (int j = 0; j < shdrTable2[k].sh_size; j++) {
                    octet = fgetc(output);
                    if (octet != buff[j] && local_echec == 0) {
                        fprintf(stderr, "Erreur sur la section %d du second fichier ELF (offset 0x%.8x)\n", k, j);
                        fprintf(stderr, "  octet obtenu dans le fichier resultat de LinkELFRenumSections : %.2x\n",
                                octet);
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
        if (k < res->size && shdrTable2[k].sh_size) {
            local_echec = 0;
            buff = getSectionContent(file2, shdrTable2[k]);
            for (int j = 0; j < shdrTable2[k].sh_size; j++) {
                octet = fgetc(output);
                if (octet != buff[j] && local_echec == 0) {
                    fprintf(stderr, "Erreur sur la section %d du second fichier ELF (offset 0x%.8x)\n", k, j);
                    fprintf(stderr, "  octet obtenu dans le fichier resultat de LinkELFRenumSections : %.2x\n", octet);
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

    fclose(output);
    remove("output.tmp");
    fclose(file2);
    fclose(file1);
}


int main(int argc, char *argv[]) {
    if (argc < 2)
        fprintf(stderr, "Il faut au moins un fichier de test\n");
    else {
        for (int i = 1; i < argc; i++) {
            printf("\nTests Phase 1 avec le fichier '%s'\n", argv[i]);
            oracleEtape1(argv[i]);
            oracleEtape2(argv[i]);
            oracleEtape3(argv[i]);
            oracleEtape4(argv[i]);
            oracleEtape5(argv[i]);
        }
        if (argc == 3) {
            printf("\nTests Phase 2 avec la fusion des fichiers '%s' et '%s'\n", argv[1], argv[2]);
            oracleEtape6(argv[1], argv[2]);
        }
    }
    return 0;
}
