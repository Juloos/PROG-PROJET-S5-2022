#include "ELF.h"
#include <elf.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    for(int i = 1; i < argc; i++) {
        FILE* file = fopen(argv[i], "r");
        Elf32_Ehdr* header = malloc(sizeof(Elf32_Ehdr));

        ReadELFHeader(file, header);
    }

    return 0;
}