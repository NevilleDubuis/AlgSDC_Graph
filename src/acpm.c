//
//  acpm.c
//  Exo1
//
//  Created by Jean-Claude on 02.03.15.
//  Copyright (c) 2015 Jean-Claude. All rights reserved.
//
// Algorithme Arbre Couvrant de Poids Minimum selon KRUSKAL
// ---------------------------------------------------------
#include <stdio.h>

#include "../lib/utils.h"
#include "../lib/graphes.h"

#define DEBUG false

// définition d'un tableau des arêtes qui va être utilisé pour trier
// les arêtes en ordre croissant de poids pour l'algo KRUSKAL

typedef struct {
    int poids;
    int s1;
    int s2;
} aretesTriees;

static aretesTriees tabAretes[MAX_S*MAX_S];
static int composanteConnexe[MAX_S];

// déclaration des fonctions statiques internes de ce module
static void swapAretes(int a1, int a2);
static void joindreComposantesConnexes (int c1, int c2);

/* ---------------------------------------------------------
 *
 * acpm : arbre couvrant de poids minimum, algorithme de kruskal
 *      (suppose que le graphe est pondéré, connexe)
 *
 *      1- trier les arêtes du graphe par ordre de poids croissant
 *          (créer une tableau ordonnée)
 *      2- créer un graphe vide du même type (pondéré,...) que celui
 *          que l'on veut étudier
 *      3- mettre chacun des sommets dans une composante connexe
 *          différente (tableau composanteConnexe[]
 *      4- boucle tant que l'on n'a pas vu toutes les aretes
 *          4.1- si les deux sommets sont dans différentes composantes
 *              4.1.1- on ajoute l'arete à l'arbre
 *              4.1.2- on joint les deux composantes connexes
 *          4.2- on passe à l'arête suivante
 *
 * ----------------------------------------------------------
 */

int acpm(idGraph *pGraphe)
{
    int s1, s2, c1, c2, indexArete, poids;
    int poidsArbre=0; // poids de l'arbre couvrant
    idGraph *pGrapheACPM; // graphe de l'arbre

    afficheBanniere("Algorithme de kruskal : arbre couvrant de poids minimum");

    // on récupère tous les arêtes du graphe via la matrice
    // et on met les infos sur ces aretes dans le tableau

    // ... a compléter

    // trions ce tableau dans l'ordre croissant de poids


    // ... a compléter



    // on créé le graphe vierge dans lequel on va insérer les
    // arêtes dans leur ordre croissant de poids

    pGrapheACPM = creerGraphe(pGraphe->nbSommets,
                              pGraphe->grapheOriente,
                              pGraphe->graphePondere);

    // on initialise le tableau des composantes connexes
    // de telle manière que chaque sommet est dans une composante
    // connexe différente, puisque pas encore d'arête



    // ... a compléter



    // on a notre arbre couvrant de poids minimum
    //
    // quelques printf à faire pour l'afficher
    // et c'est fini !!


    printf("Arbre de poids couvrant minimum, poids = %d\n", poidsArbre);

    afficheGraphe(pGrapheACPM);

    detruireGraphe(pGrapheACPM);

    return(0);
}
/* ---------------------------------------------------------
 *
 * swapAretes : inverse deux arêtes dans le tableau des arêtes
 *              triées par ordre de poids croissant
 *
 * ---------------------------------------------------------
 */
static void swapAretes(int a1, int a2)
{
    int s1, s2, poids;

    s1=tabAretes[a1].s1;
    s2=tabAretes[a1].s2;
    poids=tabAretes[a1].poids;

    tabAretes[a1].s1=tabAretes[a2].s1;
    tabAretes[a1].s2=tabAretes[a2].s2;
    tabAretes[a1].poids=tabAretes[a2].poids;

    tabAretes[a2].s1=s1;
    tabAretes[a2].s2=s2;
    tabAretes[a2].poids=poids;

    return ;
}

/* ---------------------------------------------------------
 *
 * joindreComposantesConnexes : réunit deux composantes
 *                              connexes en une seule
 *
 * ---------------------------------------------------------
 */
static void joindreComposantesConnexes(int c1, int c2)
{
    for (int i=0; i<MAX_S;i++)
        if (composanteConnexe[i]==c2)
            composanteConnexe[i]=c1;

    return ;
}
