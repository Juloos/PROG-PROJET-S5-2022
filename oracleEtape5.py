from sys import argv
from re import findall, split

class RelocationSection:
    def __init__(self, name, offset):
        self.name = name
        self.offset = offset
        self.inputs = []

    def __str__(self):
        return str(self.name) + " " + str(self.offset) + "\n" + str(self.inputs)

    def __eq__(self, other):
        if self.name != other.name:
            return False
        elif self.offset != other.offset:
            return False
        elif len(self.inputs) != len(other.inputs):
            return False
        else:
            i = 0
            while (i < len(self.inputs) and self.inputs[i] == other.inputs[i]):
                i += 1
            return i == len(self.inputs)

def lire_fichier(fichier, relocation_sections):
    for ligne in fichier.readlines():
        if "Relocation section" in ligne:
            contenu_ligne = ligne.split('\'')
            relocation_sections.append(RelocationSection(name=contenu_ligne[1], offset=findall('0x[0-9]+', contenu_ligne[2])))
        elif ligne != "\n" and "Offset" not in ligne:
            ligne = ligne.replace("\n", "")
            contenu_ligne = split(' +', ligne.strip())
            relocation_sections[-1].inputs = contenu_ligne

# Premier argument le fichier texte du résultat de la commande : readelf -r
# Deuxième argument le fichier texte du résultat de la fonction pour lire les tables de réimplantation du même fichier que celui utilisé avec la fonction readelf -r
if __name__ == '__main__':
    resultat_commande = open(argv[1], 'r')
    relocation_sections_commandes = []
    lire_fichier(resultat_commande, relocation_sections_commandes)

    resultat_programme = open(argv[2], 'r')
    relocation_sections_programme = []
    lire_fichier(resultat_programme, relocation_sections_programme)

    resultat_programme.close()
    resultat_commande.close()

    if len(relocation_sections_programme) != len(relocation_sections_commandes):
        print("Le programme de l'étape 5 ne trouve pas le même nombre de tables de réimplantation que la commande readelf -r")
        exit(1)

    # for section in relocation_sections_programme:
    #     print(section)
    #
    # print("")
    #
    # for section in relocation_sections_commandes:
    #     print(section)

    i = 0
    while i < len(relocation_sections_commandes) and relocation_sections_programme[i] == relocation_sections_commandes[i]:
        i += 1

    if i == len(relocation_sections_commandes):
        print("Succès pour l'étape 5")
        exit(0)
    else:
        print("Echec pour l'étape 5")
        exit(1)
