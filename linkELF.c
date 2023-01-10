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

    FusionELF_Etape6 *res = LinkELFRenumSections(input1, input2, output);

    printf("Offsets de concaténation du deuxième fichiers : \n  ");
    for (int j = 0; j < res->size; j++)
        printf("%3d ", res->offsets[j]);
    printf("\nRenumérotation des sections du deuxième fichier : \n  ");
    for (int j = 0; j < res->size; j++)
        printf("%3d ", res->renum[j]);
    printf("\n");

    free_fusion6(res);

    fclose(input1);
    fclose(input2);
    fclose(output);

    return 0;
}
