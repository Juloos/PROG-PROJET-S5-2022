#include "ELF.h"
#include <stdio.h>

#define PRINT_ALL 0
#define PRINT_HEADER 1
#define PRINT_SECTION_TABLE 2
#define PRINT_SECTION 3
#define PRINT_SYMBOL_TABLE 4
#define PRINT_RELOCATION_TABLE 5

int main(int argc, char* argv[]) {
    // Si le premier arguments n'est pas un nombre alors on affiche tout les contenus des fichiers en paramaètres
    int typeAffichage = atoi(argv[1]);

    // Le nom ou le numéro de la section que l'on veut afficher si on veut afficher une section en particulier
    char* section = argv[2];

    // Pour savoir à partir de quel arguments commmence la liste des fichiers à afficher
    int firstFile = 1;
    if(typeAffichage) {
        firstFile = 2;
    }
    // Si le 2ième argument n'est pas un fichier
    FILE* file = fopen(argv[2], "r");
    if(file == NULL) {
        firstFile = 3;
    }

    for(int i = firstFile; i < argc; i++) {
        FILE* file = fopen(argv[i], "r");
        if (file == NULL) {
            fprintf(stderr, "Error opening file\n");
            exit(EXIT_FAILURE);
        }


        Elf32_Ehdr header;
        ReadELFHeader(file, &header);
        if(typeAffichage == PRINT_ALL || typeAffichage == PRINT_HEADER) {
            PrintELFHeader(header);
        }

        Elf32_Shdr *sectionTable = create_ELFTableSections(header);
        ReadELFTableSections(file, header, sectionTable);
        if(typeAffichage == PRINT_ALL || typeAffichage == PRINT_SECTION_TABLE) {
            PrintELFTableSections(file, header, sectionTable);
        }

        if(typeAffichage == PRINT_ALL) {
            for (int i = 0; i < header.e_shnum; i++) {
                PrintELFSectionNum(file, header, sectionTable, i);
                printf("\n");
            }
        } else if(typeAffichage == PRINT_SECTION) {
            int numSection = atoi(section);
            // Affichage en fonction du nom
            if(!numSection) {
                PrintELFSectionNom(file, header, sectionTable, section);
            }
            // Affichage en fonction du numéro
            else {
                PrintELFSectionNum(file, header, sectionTable, numSection);
            }
        }

        Elf32_Shdr sh_symtab = sectionTable[sectionName2Index(".symtab", file, header, sectionTable)];
        Elf32_Sym *symbolTable = create_ELFTableSymbols(sh_symtab);
        ReadELFTableSymbols(file, symbolTable, sh_symtab);
        if(typeAffichage == PRINT_ALL || typeAffichage == PRINT_SYMBOL_TABLE) {
            PrintELFTableSymbols(file, header, sectionTable, symbolTable);
        }

        printf("\n");

        free(sectionTable);
        free(symbolTable);
    }

    return 0;
}