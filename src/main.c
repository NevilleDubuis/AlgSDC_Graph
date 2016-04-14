//
//  main.c
//  Exo1
//
//  Created by Jean-Claude on 01.03.15.
//  Copyright (c) 2015 Jean-Claude. All rights reserved.
//

/* ----------------------------------------------------------------------------------------------------------------------------------
 *
 *
 * Structure de fichiers du projet EXO_GRAPHES
 *
 *   main.c :               affichage du menu principal de l'application
 *                          appel de la fonction sélectionnée par l'utilisateur
 *
 *   graphes.h :            ces deux fichiers include contiennent toustes les définitions à usage global pour l'applicatio
 *   liste.h   :            liste.h et liste.c sont issus des cours d'algorithme 1 et possède les définitions de listes chainées
 *   liste.c :              graphes.h contient toutes les définitions de variables et fonctions globales utiles pour les graphes
 *
 *   graphes.c :            contient les fonctions de création et mise à jour de graphes (matrice et liste d'adjacence, affichage)
 *
 *   parcours.c :           contient les fonctions de parcours en profondeur et largeur des graphes, appelées par les autres fonctions
 *
 *   caractéristiques.c :   contient les fonctions permettant de connaitre les caractéristiques générales d'un graphe
 *
 *   chemin.c :             contient l'algorithme de calcul de chemin le plus court entre deux sommets
 *
 *   acpm.c :               contient l'algorithme d'arbre couvrant de plus faible poids
 *
 *   coloration.c :         contient l'algorithme de coloration d'un graphe
 *
 * ----------------------------------------------------------------------------------------------------------------------------------
 */



#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "../lib/utils.h"
#include "../lib/graphes.h"



/*
 * définition du menu principal de l'application
*/


static typeMenu menuPrincipal[] = {
    { "Gestion d'un graphe ", &gererGraphe },
    { "Caracteristiques du graphe ", &fnVide },
    { "Coloration du graphe", &fnVide },
    { "Parcours en profondeur", &dfs },
    { "Parcours en largeur", &fnVide },
    { "Arbre couvrant de poids mimimum", &acpm },
    { "Chemin le plus court entre deux sommets", &fnVide },
    { "", NULL }
};


/* ---------------------------------------------------------
 *
 *
 * Main : affichage du menu principal et appel de la fonction sélectionnée
 *
 *
 * ----------------------------------------------------------
 */
int main(void)
{
    int choix=0, erreur=0;
    idGraph *pGraphe;

    afficheBanniere("Bienvenue dans mon programme de theorie des graphes !!");

    printf("\n\n\n");

    pGraphe = creerDefaultGraphe(); // initialisation du graphe par défaut

    if (pGraphe) {
        do {
            afficheBanniere("MENU PRINCIPAL");

            choix = afficheMenu(menuPrincipal);

            if (choix > 0) {

            // l'utilisateur a sélectionné une option dans le menu
            // on appelle la fonction correspondante a ce choix

                erreur = menuPrincipal[choix - 1].fn(pGraphe);
            }


        } while (choix != 0 && erreur == 0); /* tant qu'on n'a pas demandé a sortir (choix 0) on réaffiche le menu) */
    } else {
        printf("erreur de création du graphe par défaut\n");
    }
    printf("\n\n\nA bientôt !!\n");

    return(0);
}
