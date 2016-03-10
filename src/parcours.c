//
//  parcours.c
//  Exo1
//
//  Created by Jean-Claude on 01.03.15.
//  Copyright (c) 2015 Jean-Claude. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

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


    // a compléter ....


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

    for (int i = 0; i<pGraphe->nbSommets;i++) visited[i]=false;

    afficheBanniere("Parcours en profondeur depuis le sommet A");

    dfs_r(pGraphe, 0);

    return(0);
}
