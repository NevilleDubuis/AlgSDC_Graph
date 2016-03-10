//
//  graphes.c
//  Exo1
//
//  Created by Jean-Claude on 01.03.15.
//  Copyright (c) 2015 Jean-Claude. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "graphes.h"


#define NB_SOMMETS_DEFAUT 13
static int defaultMatrice[NB_SOMMETS_DEFAUT][NB_SOMMETS_DEFAUT] = {
    // la matrice d'adjacence du graphe de test par défaut, pondéré, non orienté
    {0,2,3,0,0,4,5,0,0,0,0,0,0}, // A
    {2,0,0,0,0,0,0,0,0,0,0,0,0}, // B
    {3,0,0,0,0,0,0,0,0,0,0,0,0}, // C
    {0,0,0,0,2,6,0,0,0,0,0,0,0}, // D
    {0,0,0,2,0,2,1,0,0,0,0,0,0}, // E
    {4,0,0,6,2,0,0,0,0,0,0,0,0}, // F
    {5,0,0,0,1,0,0,0,0,0,0,0,0}, // G
    {0,0,0,0,0,0,0,0,4,0,0,0,0}, // H
    {0,0,0,0,0,0,0,4,0,0,0,0,0}, // I
    {0,0,0,0,0,0,0,0,0,0,3,5,1}, // J
    {0,0,0,0,0,0,0,0,0,3,0,0,0}, // K
    {0,0,0,0,0,0,0,0,0,5,0,0,1}, // L
    {0,0,0,0,0,0,0,0,0,1,0,1,0}, // M
};


/* ---------------------------------------------------------
 *
 *
 * afficheGraphe() : affichage de la matrice et de la liste d'adjacence
 *
 *
 * ----------------------------------------------------------
 */
int afficheGraphe(idGraph *pGraphe)
{
    int i,j;
    idElt noeud;

    afficheBanniere("Affichage du contenu du graphe");

    printf("Nombre de sommets = %d\n", pGraphe->nbSommets);
    printf("Nombre d'arêtes   = %d\n", pGraphe->nbAretes);
    printf("Graphe pondéré    = %s\n", (pGraphe->graphePondere) ? "VRAI" : "FAUX");
    printf("Graphe orienté    = %s\n", (pGraphe->grapheOriente) ? "VRAI" : "FAUX");

    printf("\n\nAffichage de la liste d'adjacence : \n");

    // a compléter ....

    printf("\n\nAffichage de la matrice :\n");

    printf("------------");
    for (i=0;i<pGraphe->nbSommets;i++) printf( "%2c ",NOM_SOMMET(i)); // affiche de l'entête du tableau avec la liste des noeuds
    printf("\n");


    // a compléter ....


    return(0);
}

/* ---------------------------------------------------------
 *
 *
 * creerListeAdjacence : création de la liste
 *      d'adjacence du graphe à partir de la matrice
 *
 *
 * ----------------------------------------------------------
 */
void creerListeAdjacence(idGraph * pGraphe)
{
    int i,j;
    idElt noeud;

    // a compléter ....

    return;
}
/* ---------------------------------------------------------
 *
 *
 * creerMatrice : création de la matrice d'adjacence
 *
 A COMPLETER, car pas adapté à la refonte
 *
 * ----------------------------------------------------------
 */

int creerMatrice(idGraph * pGraphe)
{
    int i,j, s1,s2, poids;

    afficheBanniere("Saisie d'un nouveau graphe");

    printf("Entrez le nbre de sommets : ");
    pGraphe->nbSommets=saisieEntier();

    printf("Entrez le nbre d'arêtes : ");
    pGraphe->nbAretes=saisieEntier();

    printf("Entrez le poids maximum d'une arête (0 si graphe non pondéré et non orienté)  : ");
    poids=saisieEntier();
    if (poids>0)
        pGraphe->graphePondere=true;
    else
    {
        poids=1;
        pGraphe->graphePondere=false;
    }

    printf("nb sommets = %d, nb Aretes = %d\n",pGraphe->nbSommets,pGraphe->nbAretes);
    if (pGraphe->nbSommets > MAX_S) {
        printf("----> Ereur : Nombre maximal de sommets = %d\n", MAX_S);
        return (1);
    }

    /*
     * initialisation de la matrice
     */

    for (i=0;i<pGraphe->nbSommets;i++)
        for (j=0;j<pGraphe->nbSommets;j++)
            pGraphe->matrice[i][j]=0;

    /*
     * remplissage de la matrice
     */

    for (j=0;j<pGraphe->nbAretes;j++)
    {
        printf("Entrer le premier sommet de l'arête No %d sur %d : ", j+1, pGraphe->nbAretes);
        s1 = saisieCaractere()-'A';

        printf("Entrer le deuxième sommet de l'arête No %d sur %d : ", j+1, pGraphe->nbAretes);
        s2 = saisieCaractere()-'A';

        if (pGraphe->graphePondere)
        {
            printf("Entrer le poids de cette arête : ");
            poids = saisieEntier();
        }
 //       printf("%d %d\n", s1, s2);
        pGraphe->matrice[s1][s2]=poids;

        if (!pGraphe->grapheOriente)
            pGraphe->matrice[s2][s1]=poids;

    }

    creerListeAdjacence(pGraphe);

    return(0);
}
/* ---------------------------------------------------------
 *
 * detruireArete(): on enleve une arete du graphe
 *
 * ----------------------------------------------------------
 */
void detruireArete(idGraph *pGraphe, int s1, int s2)
{
    idElt noeud;
    idListe listeAdj;
    int nbAdjacents;

// à compléter

    return;
}
/* ---------------------------------------------------------
 *
 * enleverArete(): on enleve une arete du graphe
 *
 * ----------------------------------------------------------
 */
void enleverArete(idGraph *pGraphe)
{
    idElt noeud;
    idListe listeAdj;
    int nbAdjacents;

// à compléter

    return;
}
/* ---------------------------------------------------------
 *
 *
 * creerArete(): ajoute une arete à un graphe existant
 *              1- saisie des sommets source et destination
 *              2- mise à jour de la matrice
 *              3- mise à jour de la liste d'adjacence
 *
 * ----------------------------------------------------------
 */
int creerArete(idGraph *pGraphe, int s1, int s2, int poids)
{
    idElt noeud;

    if (pGraphe->matrice[s1][s2]) {
        printf("arête déjà existante : %c -> %c, poids = %d !!\n", NOM_SOMMET(s1), NOM_SOMMET(s2), poids);
        return(-1);
    }


    // a compléter ....


    return(0);
}
/* ---------------------------------------------------------
 *
 *
 * ajouterArete(): ajoute une arete à un graphe existant
 *              1- saisie des sommets source et destination
 *              2- mise à jour de la matrice
 *              3- mise à jour de la liste d'adjacence
 *
 * ----------------------------------------------------------
 */
static int ajouterArete(idGraph * pGraphe){
    int s1, s2, poids=1;

    afficheBanniere("Ajout d'une arête");
    printf("Entrer le sommet source de l'arête (de A à %c) : ", NOM_SOMMET(pGraphe->nbAretes-1));
    s1 = saisieCaractere()-'A';
    printf("Entrer le sommet destination de l'arête (de A à %c) : ", NOM_SOMMET(pGraphe->nbAretes-1));
    s2 = saisieCaractere()-'A';

    if (pGraphe->graphePondere)
    {
        printf("Entrer le poids de cette arête : ");
        poids = saisieEntier();
    }

    if (creerArete(pGraphe, s1, s2, poids))
        return(-1);
    else
        return(0);
}
/* ---------------------------------------------------------
 *
 *
 * gérerGraphe() : sous-menu permettant de créer un graphe
 *                  afficher le graphe
 *                  ajouter/retirer un sommet
 *                  ajouter/retirer une arete
 *
 * ----------------------------------------------------------
 */
int gererGraphe(idGraph * pGraphe)
{
    static typeMenu menuGerer[] = {
        { "Creer un nouveau graphe", &creerMatrice },
        { "Afficher le graphe", &afficheGraphe },
        { "Ajouter un sommet", &fnVide },
        { "Supprimer un sommet", &fnVide},
        { "Ajouter une arête", &ajouterArete },
        { "Supprimer une arête", &enleverArete},
        { "", NULL }
    };
    int choix, erreur =0;

    do {
        afficheBanniere("Gestion d'un graphe");

        choix = afficheMenu(menuGerer);

        if (choix > 0) {
            // l'utilisateur a sélectionné une option dans le menu
            // on appelle la fonction correspondante a ce choix

            erreur = menuGerer[choix - 1].fn(pGraphe);
        }


    } while (choix != 0 && erreur == 0); /* tant qu'on n'a pas demandé a sortir (choix 0) on réaffiche le menu) */


    return(0);
}

/* ---------------------------------------------------------
 *
 *
 * creerGraphe() : alloue une structure de graphe et renvoie
 *              le pointeur vers le descripteur
 *              null si erreur
 *
 *
 * ----------------------------------------------------------
 */
idGraph * creerGraphe(int nbSommets, int oriente, int pondere)
{
    idGraph *pGraphe;

    pGraphe = (idGraph *) malloc(sizeof(idGraph));

    if (pGraphe) {
        pGraphe->nbSommets = nbSommets;
        pGraphe->nbComposantesConnexes = 0;
        pGraphe->nbCycles = 0;
        pGraphe->nbAretes = 0;
        pGraphe->grapheOriente = oriente;
        pGraphe->graphePondere = pondere;

        for(int i=0;i<nbSommets;i++) {
            for (int j=0;j<nbSommets;j++)
                pGraphe->matrice[i][j]=0;
            pGraphe->listeAdj[i] = creerListe();
        }
     }

    return(pGraphe);
}
/* ---------------------------------------------------------
 *
 *
 * creerDefaultGraphe() :
 *              alloue une structure de graphe et charge
 *              le graphe par défaut dans la matrice
 *              puis créé la liste d'adjacence
 *              renvoie null si erreur
 *
 *
 * ----------------------------------------------------------
 */
idGraph * creerDefaultGraphe()
{
    idGraph *pGraphe;


    // on cree la structure graphe, non orienté, pondéré
    pGraphe = creerGraphe(NB_SOMMETS_DEFAUT, false, true);

    if (pGraphe) {

        // on charge la matrice par défaut
        // et on incremente le nombre d'aretes selon la présence d'une valeur
        for (int i = 0; i < NB_SOMMETS_DEFAUT;i++) {

            for (int j = 0; j < NB_SOMMETS_DEFAUT;j++) {

                pGraphe->matrice[i][j] = defaultMatrice[i][j];

                if (pGraphe->matrice[i][j])
                    pGraphe->nbAretes++;
            }
        }
        pGraphe->nbAretes >>=1; // non orienté, nb Arètes divisé par 2

        creerListeAdjacence(pGraphe);
    }

    return(pGraphe);
}

/* ---------------------------------------------------------
 *
 *
 * detruireGraphe() : libere la memoire allouée pour les
 *                  données d'un graphe passé en paramètre
 *
 * ----------------------------------------------------------
 */
void detruireGraphe(idGraph *pGraphe)
{
    int i;

    for (i=0;i<pGraphe->nbSommets;i++) {
        detruireListe(pGraphe->listeAdj[i]);
    }

    free(pGraphe);

    return;
}
