#include <stdio.h>
#include <stdint.h>

typedef uint32_t Elf32_Addr;
typedef uint16_t Elf32_Half;
typedef uint32_t Elf32_Off;
typedef int32_t Elf32_Sword;
typedef uint32_t Elf32_Word;

typedef struct {
    Elf32_Word	sh_name;
    Elf32_Word	sh_type;
    Elf32_Word	sh_flags;
    Elf32_Addr	sh_addr;
    Elf32_Off	sh_offset;
    Elf32_Word	sh_size;
    Elf32_Word	sh_link;
    Elf32_Word	sh_info;
    Elf32_Word	sh_addralign;
    Elf32_Word	sh_entsize;
} Elf32_Shdr;

#define EI_NIDENT 16

/**ReadELFFile
 * Paramètres :
 * - un pointeur sur un fichier ELF
 * Résultat : lit et affiche sur la sortie standard le contenu du fichier ELF en paramètre
*/
void ReadELFFile(FILE* file);

/**ReadELFHeader
 * Paramètres :
 * - un pointeur sur un fichier ELF
 * Résultat : lit et affiche sur la sortie standard l'en tête du fichier ELF en paramètre
*/
void ReadELFHeader(FILE* file);


/**init_TabSection
 * Paramètres :
 * - un entier représentant le nombre de sections
 * Résultat : retourne un pointeur sur un tableau de sections initialiser
*/
Elf32_Shdr * init_TabSection(int nbSection);

/**ReadELFTableSection
 * Paramètre : 
 * - un pointeur sur un fichier ELF
 * Résultat : lit et affiche sur la sortie standard la table des sections du fichier ELF en paramètre
*/
void ReadELFTableSection(FILE* file, Elf32_Shdr* tableSection, int nbSection);

/**ReadELFSection
 * Paramètres :
 * - un pointeur sur un fichier ELF
 * - le numéro de la section à afficher
 * Résultat : lit et affiche sur la sortie standard la section numéro numSection dans le fichier ELF en paramètre
*/
void ReadELFSectionNum(FILE* file, int numSection);

/**ReadELFSection
 * Paramètres :
 * - un pointeur sur un fichier ELF
 * - le numéro de la section à afficher
 * Résultat : lit et affiche sur la sortie standard la section nomSection dans le fichier ELF en paramètre
*/
void ReadELFSectionNom(FILE* file, char* nomSection);

/**ReadELFTableSymbols
 * Paramètres :
 * - un pointeur sur un fichier ELF
 * Résultat : lit et affiche sur la sortie standard la table des symboles du fichier ELF en paramètre
*/
void ReadELFTableSymbols(FILE* file);