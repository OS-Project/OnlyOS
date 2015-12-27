# -*- coding: utf-8 -*-
import os
import sys

def extract_hw(ligne):
    l = ligne.split("hw_")
    l2 = l[1].split('"')
    l3 = "hw_" + l2[0]
    return l3.replace('\n','')

path = "/media/thibault/Programmation et sites/Programmation/TIPE/OnlyOS"
hw_path = path + "/include/arch/arm/hal/hw"

liste_hw = []
chaine = '#include "hw_' # Texte à rechercher
dossier_exclu = [".git", ".idea"]
fichier_exclu = ["CMakeLists.txt"]
hw_exclus = ["soc_AM335x.h"]

for k in range(len(dossier_exclu)):
    dossier_exclu[k] = path + "/" + dossier_exclu[k]

for dossier, sous_dossiers, fichiers in os.walk(path):
    new_hw = []
    progress = True
    for dir in dossier_exclu:
        if dir in dossier:
            progress = False

    if progress:
        print('%s' % dossier)

        for nom_fichier in fichiers:
            if nom_fichier not in fichier_exclu:
                fichier = open(dossier + "/" + nom_fichier,"r")
                for ligne in fichier:
                    if chaine in ligne:
                        print(nom_fichier)
                        new_hw.append(extract_hw(ligne))
                fichier.close()

    print("Les nouveaux hw : %s" % new_hw)
    liste_hw += new_hw
    print("Total hw : %s" % liste_hw)


print("\nFin du traitement, detection des hw inutiles\n")
hw_inutiles = []

for dossier, sous_dossiers, fichiers in os.walk(hw_path):
    for nom_fichier in fichiers:
        if nom_fichier not in liste_hw:
            if nom_fichier not in hw_exclus:
                hw_inutiles.append(nom_fichier)
                print(nom_fichier)


print ("\nSupprimer ces fichiers ? (y/n)")
line = sys.stdin.readline()
if "y" in line:
    for fichier in hw_inutiles:
        print("Suppression de " + fichier)
        os.remove(hw_path + "/" + fichier)

