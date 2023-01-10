//
// Created by bossyr on 09/01/23.
//

#include <stdio.h>
#include "oracle_fusion.h"
#include "ELF.h"
#include "utils.h"

void oracleEtape7(FILE* input1, FILE* input2) {
    // Récupération de la table des symboles de input1
    SymbolsTable * symsTableInput1 = GetSymbolsTable(input1);

    // Récupération de la table des symboles de input2
    SymbolsTable* symsTableInput2 = GetSymbolsTable(input2);

    // Fusion des tables des symboles des deux fichiers en entrées
    SymbolsTable* symsTableResult = LinkELFSymbols(input1, input2);

    int i = 0;
    int j = 0;
    int error = 0;

    // Si la fusion a réussi
    if(symsTableResult != NULL) {
        // On vérifie que tout les symboles locaux des deux fichiers en entrée sont dans la table des symboles finale
        i = 0;
        while(i < symsTableInput1->nbElems && !error) {
            if(getSymbolBindValue(symsTableInput1->symbols[i]) == STB_LOCAL) {
                j = 0;
                while(j < symsTableResult->nbElems && SymbolCmp(symsTableInput1->symbols[i], symsTableResult->symbols[j])) {
                    j++;
                }
                error = j == symsTableResult->nbElems;
            }
            i++;
        }

        i = 0;
        while(i < symsTableInput2->nbElems && !error) {
            if(getSymbolBindValue(symsTableInput2->symbols[i]) == STB_LOCAL) {
                j = 0;
                while(j < symsTableResult->nbElems && SymbolCmp(symsTableInput2->symbols[i], symsTableResult->symbols[j])) {
                    j++;
                }
                error = j == symsTableResult->nbElems;
            }
            i++;
        }
    }

    // Dans tout les cas on vérifie que les deux fichiers en entrée n'ont aucun symbole global défini avec le même nom
    i = 0;
    while(i < symsTableInput1->nbElems && !error) {
        j = i+1;
        while(j < symsTableInput2->nbElems && !error) {
            error = symsTableInput1->symbols[i].st_name == symsTableInput2->symbols[j].st_name
                    && getSymbolBindValue(symsTableInput1->symbols[i]) == STB_GLOBAL
                    && getSymbolBindValue(symsTableInput2->symbols[j]) == STB_GLOBAL
                    && ELF32_ST_TYPE(symsTableInput1->symbols[i].st_info) != STT_NOTYPE
                    && ELF32_ST_TYPE(symsTableInput2->symbols[j].st_info) != STT_NOTYPE;
            j++;
        }
        i++;
    }

    if((symsTableResult == NULL && error) || (symsTableResult != NULL && !error)) {
        fprintf(stderr, "Succès pour l'étape 7\n");
    } else {
        fprintf(stderr, "Echec pour l'étape 7\n");
    }

    free(symsTableInput1->symbols);
    free(symsTableInput1);
    free(symsTableInput2->symbols);
    free(symsTableInput2);
    if(symsTableResult != NULL) {
        free(symsTableResult->symbols);
        free(symsTableResult);
    }
}

int main(int argc, char* argv[]) {

    FILE* input1 = fopen(argv[1], "r");
    FILE* input2 = fopen(argv[2], "r");

    oracleEtape7(input1, input2);

    fclose(input1);
    fclose(input2);

    return 0;
}
