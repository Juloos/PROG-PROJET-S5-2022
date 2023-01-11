#include "ELF.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <input1> <input2> <output>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    FILE *input1 = fopen(argv[1], "r");
    FILE *input2 = fopen(argv[2], "r");
    FILE *output = fopen(argv[3], "w");

    ELF *elf1 = ReadELF(input1);
    ELF *elf2 = ReadELF(input2);

    FusionELF_Etape6 *res = LinkELFRenumSections(elf1, elf2, output);

    ELF *resultat = LinkELFSymbols(elf1, elf2, res);

    printf("Offsets de concaténation du deuxième fichiers : \n  ");
    for (int j = 0; j < res->size; j++)
        printf("%3d ", res->offsets[j]);
    printf("\nRenumérotation des sections du deuxième fichier : \n  ");
    for (int j = 0; j < res->size; j++)
        printf("%3d ", res->renum[j]);
    printf("\n");

    WriteELFFile("resultat.o", *elf1);

    printf("Fin écriture\n");

    free_fusion6(res);
    free_ELF(resultat);
    free_ELF(elf1);
    free_ELF(elf2);
    fclose(output);

    return 0;
}
