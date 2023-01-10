#include "ELF.h"
#include <stdio.h>

#define PRINT_ALL "-a"
#define PRINT_HEADER "-h"
#define PRINT_SECTION_TABLE "-S"
#define PRINT_SECTION "-x"
#define PRINT_SYMBOL_TABLE "-s"
#define PRINT_RELOCATION_TABLE "-r"

int main(int argc, char *argv[]) {
    // Si le premier arguments n'est pas un nombre alors on affiche tout les contenus des fichiers en paramaètres
    char *typeAffichage = argv[1];

    // Le nom ou le numéro de la section que l'on veut afficher si on veut afficher une section en particulier
    char *section = argv[2];

    // Pour savoir à partir de quel arguments commmence la liste des fichiers à afficher
    int firstFile = 2;
    // Si le 2ième argument n'est pas un fichier
    FILE *file = fopen(argv[2], "r");
    if (file == NULL)
        firstFile = 3;

    if (firstFile >= argc) {
        fprintf(stderr, "Aucun fichier en entrée n'a été fourni\n");
        exit(EXIT_FAILURE);
    }

    for (int i = firstFile; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            fprintf(stderr, "Error opening file\n");
            exit(EXIT_FAILURE);
        }

        ELF *elf = ReadELF(file);

        if (!strcmp(typeAffichage, PRINT_ALL) || !strcmp(typeAffichage, PRINT_HEADER))
            PrintELFHeader(elf);

        if (!strcmp(typeAffichage, PRINT_ALL) || !strcmp(typeAffichage, PRINT_SECTION_TABLE))
            PrintELFTableSections(elf);

        if (!strcmp(typeAffichage, PRINT_ALL)) {
            for (int i = 0; i < elf->ehdr.e_shnum; i++) {
                PrintELFSectionNum(elf, i);
                printf("\n");
            }
        } else if (!strcmp(typeAffichage, PRINT_SECTION)) {
            int numSection = atoi(section);
            // Affichage en fonction du nom
            if (!numSection)
                PrintELFSectionNom(elf, section);
                // Affichage en fonction du numéro
            else
                PrintELFSectionNum(elf, numSection);
        }

        if (!strcmp(typeAffichage, PRINT_ALL) || !strcmp(typeAffichage, PRINT_SYMBOL_TABLE))
            PrintELFTableSymbols(elf);

        if (!strcmp(typeAffichage, PRINT_ALL) || !strcmp(typeAffichage, PRINT_RELOCATION_TABLE))
            PrintELFRelocationTable(elf);

        free_ELF(elf);
        fclose(file);
    }

    return 0;
}