#include "oracle.h"

void lireNLignes(FILE* file, uint n) {
    char ligne[200];
    for(int i = 0; i < n; i++) {
        if(!fgets(ligne, sizeof(ligne), file)) {
            printf("Erreur lors de la lecture\n");
        }
    }
}

void lireLigne(FILE* file, char* ligne, size_t tailleLigne) {
    if(!fgets(ligne, tailleLigne, file)) {
        printf("Erreur lors de la lecture\n");
    }
}

void oracleEtapeUn(char* fileName) {
    /* On éxecute la commande readelf -h fileName et on crée un header avec le résultat */
    char command[100] = "readelf -h ";
    FILE* resultCommand = popen(strcat(command, fileName), "r");
    Elf32_Ehdr* headerCommand = malloc(sizeof(Elf32_Ehdr));

    // Chaine de caractères pour lire les lignes de resultCommand
    size_t tailleLigne = sizeof(char)*200;
    char* ligne = malloc(tailleLigne);

    // Token utilisé lorsqu'on découpé une ligne en tableau
    char* token;

    // On ignore la première ligne
    lireNLignes(resultCommand, 1);

    // Ligne Magic
    lireLigne(resultCommand, ligne, tailleLigne);
    // Découpage de la ligne avec l'espace comme délimiteur
    token = strtok(ligne, ":");
    // On ignore le premier mot
    token = strtok(NULL, " ");
    // Champ e_ident
    for(int i = 0; i < EI_NIDENT; i++) {
        headerCommand->e_ident[i] = (unsigned char) strtol(token, NULL, 16);
        token = strtok(NULL, " ");
    }

    // On ignore les 5 prochaines lignes
    lireNLignes(resultCommand, 5);

    // Ligne Type
    lireLigne(resultCommand, ligne, tailleLigne);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    if(strcmp(token, "NONE") == 0) {
        headerCommand->e_type = ET_NONE;
    } else if(strcmp(token, "REL") == 0) {
        headerCommand->e_type = ET_REL;
    } else if(strcmp(token, "EXEC") == 0) {
        headerCommand->e_type = ET_EXEC;
    } else if(strcmp(token, "DYN") == 0) {
        headerCommand->e_type = ET_DYN;
    } else if(strcmp(token, "CORE") == 0) {
        headerCommand->e_type = ET_CORE;
    } else if(strcmp(token, "LOPROC") == 0) {
        headerCommand->e_type = ET_LOPROC;
    } else if(strcmp(token, "HIPROC") == 0) {
        headerCommand->e_type = ET_HIPROC;
    }

    // Ligne Machine
    lireLigne(resultCommand, ligne, tailleLigne);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    if(strcmp(token, "NONE\n") == 0) {
        headerCommand->e_machine = ET_NONE;
    } else if(strcmp(token, "M32\n") == 0) {
        headerCommand->e_machine = EM_M32;
    } else if(strcmp(token, "SPARC\n") == 0) {
        headerCommand->e_machine = EM_SPARC;
    } else if(strcmp(token, "386\n") == 0) {
        headerCommand->e_machine = EM_386;
    } else if(strcmp(token, "68K\n") == 0) {
        headerCommand->e_machine = EM_68K;
    } else if(strcmp(token, "860\n") == 0) {
        headerCommand->e_machine = EM_860;
    } else if(strcmp(token, "MIPS\n") == 0) {
        headerCommand->e_machine = EM_MIPS;
    } else if(strcmp(token, "ARM\n") == 0) {
        headerCommand->e_machine = EM_ARM;
    }

    // Ligne Version
    lireLigne(resultCommand, ligne, tailleLigne);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand->e_version = strtol(token, NULL, 16);

    // Entry point address
    lireLigne(resultCommand, ligne, tailleLigne);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand->e_entry = strtol(token, NULL, 16);

    // Start of program headers
    lireLigne(resultCommand, ligne, tailleLigne);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand->e_phoff = strtol(token, NULL, 16);   

    // Start of section headers
    lireLigne(resultCommand, ligne, tailleLigne);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand->e_shoff = atoi(token);

    // Flags
    lireLigne(resultCommand, ligne, tailleLigne);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand->e_flags = strtol(token, NULL, 16);

    // Size of this header
    lireLigne(resultCommand, ligne, tailleLigne);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand->e_ehsize = atoi(token);

    // Size of program headers
    lireLigne(resultCommand, ligne, tailleLigne);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand->e_phentsize = atoi(token);

    // Number of program headers
    lireLigne(resultCommand, ligne, tailleLigne);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand->e_phnum = atoi(token);

    // Size of section headers
    lireLigne(resultCommand, ligne, tailleLigne);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand->e_shentsize = atoi(token);

    // Number of section headers
    lireLigne(resultCommand, ligne, tailleLigne);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand->e_shnum = atoi(token);

    // Section header string table index
    lireLigne(resultCommand, ligne, tailleLigne);
    token = strtok(ligne, ":");
    token = strtok(NULL, " ");
    headerCommand->e_shstrndx = atoi(token);

    pclose(resultCommand);
    free(ligne);

    /* On exécute la fonction readELFHeader pour le fichier en paramètre */
    FILE* file = fopen(fileName, "r");
    Elf32_Ehdr* headerProgram = malloc(sizeof(Elf32_Ehdr));
    ReadELFHeader(file, headerProgram);
    fclose(file);

    /* On compare les deux headers */
    int echec = 0;
    // Champ e_ident
    int i = 0;
    while(i < EI_NIDENT && headerProgram->e_ident[i] == headerCommand->e_ident[i]) {
        i++;
    }

    if(i < EI_NIDENT) {
        printf("Erreur sur le champ e_ident\n");
        printf("e_ident obtenu avec la commande readelf -h : ");
        for(int i = 0; i < EI_NIDENT; i++) {
            printf("%d ", headerCommand->e_ident[i]);
        }
        printf("\ne_ident obtenu avec la fonction readELFHeader : ");
        for(int i = 0; i < EI_NIDENT; i++) {
            printf("%d ", headerCommand->e_ident[i]);
        }
        printf("\n");
        echec = 1;
    }

    // Champ e_type
    if(headerProgram->e_type != headerCommand->e_type) {
        printf("Erreur sur le champ e_type\n");
        printf("e_type obtenu avec la commande readelf -h : %d\n", headerCommand->e_type);
        printf("e_type obtenu avec la fonction readELFHeader : %d\n", headerProgram->e_type);
        echec = 1;
    }

    // Champ e_machine
    if(headerProgram->e_machine != headerCommand->e_machine) {
        printf("Erreur sur le champ e_machine\n");
        printf("e_machine obtenu avec la commande readelf -h : %d\n", headerCommand->e_machine);
        printf("e_machine obtenu avec la fonction readELFHeader : %d\n", headerProgram->e_machine);
        echec = 1;
    }

    // Champ e_version
    if(headerProgram->e_version != headerCommand->e_version) {
        printf("Erreur sur le champ e_version\n");
        printf("e_version obtenu avec la commande readelf -h : 0x%.2x\n", headerCommand->e_version);
        printf("e_version obtenu avec la fonction readELFHeader : 0x%.2x\n", headerProgram->e_version);
        echec = 1;
    }

    // Champ e_entry
    if(headerProgram->e_entry != headerCommand->e_entry) {
        printf("Erreur sur le champ e_entry\n");
        printf("e_entry obtenu avec la commande readelf -h : 0x%.2x\n", headerCommand->e_entry);
        printf("e_entry obtenu avec la fonction readELFHeader : 0x%.2x\n", headerProgram->e_entry);
        echec = 1;
    }

    // Champ e_phoff
    if(headerProgram->e_phoff != headerCommand->e_phoff) {
        printf("Erreur sur le champ e_phoff\n");
        printf("e_phoff obtenu avec la commande readelf -h : %d\n", headerCommand->e_phoff);
        printf("e_phoff obtenu avec la fonction readELFHeader : %d\n", headerProgram->e_phoff);
        echec = 1;
    }

    // Champ e_shoff
    if(headerProgram->e_shoff != headerCommand->e_shoff) {
        printf("Erreur sur le champ e_shoff\n");
        printf("e_shoff obtenu avec la commande readelf -h : %d\n", headerCommand->e_shoff);
        printf("e_shoff obtenu avec la fonction readELFHeader : %d\n", headerProgram->e_shoff);
        echec = 1;
    }

    // Champ e_flags
    if(headerProgram->e_flags != headerCommand->e_flags) {
        printf("Erreur sur le champ e_flags\n");
        printf("e_flags obtenu avec la commande readelf -h : 0x%.2x\n", headerCommand->e_flags);
        printf("e_flags obtenu avec la fonction readELFHeader : 0x%.2x\n", headerProgram->e_flags);
        echec = 1;
    }

    // Champ e_ehsize
    if(headerProgram->e_ehsize != headerCommand->e_ehsize) {
        printf("Erreur sur le champ e_ehsize\n");
        printf("e_ehsize obtenu avec la commande readelf -h : %d\n", headerCommand->e_ehsize);
        printf("e_ehsize obtenu avec la fonction readELFHeader : %d\n", headerProgram->e_ehsize);
        echec = 1;
    }

    // Champ e_phentsize
    if(headerProgram->e_phentsize != headerCommand->e_phentsize) {
        printf("Erreur sur le champ e_phentsize\n");
        printf("e_phentsize obtenu avec la commande readelf -h : %d\n", headerCommand->e_phentsize);
        printf("e_phentsize obtenu avec la fonction readELFHeader : %d\n", headerProgram->e_phentsize);
        echec = 1;
    }

    // Champ e_phnum
    if(headerProgram->e_phnum != headerCommand->e_phnum) {
        printf("Erreur sur le champ e_phnum\n");
        printf("e_phnum obtenu avec la commande readelf -h : %d\n", headerCommand->e_phnum);
        printf("e_phnum obtenu avec la fonction readELFHeader : %d\n", headerProgram->e_phnum);
        echec = 1;
    }

    // Champ e_shentsize
    if(headerProgram->e_shentsize != headerCommand->e_shentsize) {
        printf("Erreur sur le champ e_shentsize\n");
        printf("e_shentsize obtenu avec la commande readelf -h : %d\n", headerCommand->e_shentsize);
        printf("e_shentsize obtenu avec la fonction readELFHeader : %d\n", headerProgram->e_shentsize);
        echec = 1;
    }

    // Champ e_shnum
    if(headerProgram->e_shnum != headerCommand->e_shnum) {
        printf("Erreur sur le champ e_shnum\n");
        printf("e_shnum obtenu avec la commande readelf -h : %d\n", headerCommand->e_shnum);
        printf("e_shnum obtenu avec la fonction readELFHeader : %d\n", headerProgram->e_shnum);
        echec = 1;
    }

    // Champ e_shstrndx
    if(headerProgram->e_shstrndx != headerCommand->e_shstrndx) {
        printf("Erreur sur le champ e_shstrndx\n");
        printf("e_shstrndx obtenu avec la commande readelf -h : %d\n", headerCommand->e_shstrndx);
        printf("e_shstrndx obtenu avec la fonction readELFHeader : %d\n", headerProgram->e_shstrndx);
        echec = 1;
    }

    if(echec) {
        printf("Echec pour l'etape 1\n");
    } else {
        printf("Succes pour l'etape 1\n");
    }

    free(headerCommand);
    free(headerProgram);
}

int main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("Il faut au moins un fichier de test\n");
    } else {
        for(int i = 1; i < argc; i++) {
            oracleEtapeUn(argv[i]);
        }
    }

    return 0;
}