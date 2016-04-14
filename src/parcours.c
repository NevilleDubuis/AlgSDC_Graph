//
//  parcours.c
//  Exo1
//
//  Created by Jean-Claude on 01.03.15.
//  Copyright (c) 2015 Jean-Claude. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "../lib/utils.h"
#include "../lib/graphes.h"

static bool visited[MAX_S];

/* ---------------------------------------------------------
 *
 *
 * dfs_r() : fait le parcours en profondeur récursif depuis le
 *          sommet passé en paramètre
 *          1- on marque le sommet visité
 *          2- on regarde combien de sommets sont adjacents (nbElements)
 *          3- s'il y a des adjacents, on prend le premier
 *          4- s'il n'a pas été visité, on rappelle cette même fonction
 *              avec le nouveau sommet
 *          5 - on passe au sommet suivant
 *
 *
 * ----------------------------------------------------------
 */
void dfs_r(idGraph *pGraphe, int sommet)
{
    idElt element;
    int nbAdjacents;

    visited[sommet]=true;

    printf("  On visite : %C\n",NOM_SOMMET(sommet));

    nbAdjacents=nbElements(pGraphe->listeAdj[sommet]); // nb sommets adjacents au courant

    if (nbAdjacents) { // S'il y a des sommets adjacents

        // on prend le premier sommet adjacent et s'il n'a pas été visite, on le visite
        element=premierElt(pGraphe->listeAdj[sommet]);

        while(nbAdjacents--) {

            sommet=VAL_SOMMET(element);

            if(!visited[sommet]) // si non visité, on le visite
                dfs_r(pGraphe, sommet);

            // puis on passe au sommet voisin
            element=suivantElt(element);
        }
    }
}

/* ---------------------------------------------------------
 *
 *
 * dfs : parcours en profondeur depuis un sommet
 *         1- on initialise le tableau des sommets visités
 *         2- on appelle la fonction de parcours en profondeur
 *              récursif depuis le sommet A
 *
 *
 * ---------------------------------------------------------
 */
int dfs(idGraph * pGraphe)
{
    int i;

    for (i = 0; i<pGraphe->nbSommets;i++) visited[i]=false;

    afficheBanniere("Parcours en profondeur depuis le sommet A");
    pGraphe->nbComposantesConnexes=0;

    for (i = 0; i<pGraphe->nbSommets;i++)
        if (!visited[i]) {
            printf("On visite le graphe depuis le sommet %c\n", NOM_SOMMET(i));
            pGraphe->nbComposantesConnexes++;
            dfs_r(pGraphe, i);
        }
    return(0);
}
