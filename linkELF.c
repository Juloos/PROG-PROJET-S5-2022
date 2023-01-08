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

    LinkELFRenumSections(input1, input2, output);

    fclose(input1);
    fclose(input2);
    fclose(output);

    return 0;
}
