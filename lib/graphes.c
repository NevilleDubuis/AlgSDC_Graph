//
//  graphes.c
//  Exo1
//
//  Created by Jean-Claude on 01.03.15.
//  Copyright (c) 2015 Jean-Claude. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

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
    for(i = 0; i < pGraphe->nbSommets; i++)
    {
        j=nbElements(pGraphe->listeAdj[i]);
        printf("Sommet %2c, degré = %2d : ", NOM_SOMMET(i), j);

        noeud = premierElt(pGraphe->listeAdj[i]);
        if (noeud) { // si la liste n'est pas vide
            while(j--) {
                printf("%2c ", NOM_SOMMET(VAL_SOMMET(noeud)));
                noeud = suivantElt(noeud);
            };
        }
        printf("\n");
    }


    printf("\n\nAffichage de la matrice :\n");

    printf("------------");
    for (i=0;i<pGraphe->nbSommets;i++) printf( "%2c ",NOM_SOMMET(i)); // affiche de l'entête du tableau avec la liste des noeuds
    printf("\n");


    for (i=0;i<pGraphe->nbSommets;i++)
    {
        printf("Sommet %2c : ", 'A'+i);
        for (j=0;j<pGraphe->nbSommets;j++)
            printf("%2d ", pGraphe->matrice[i][j]); // on affiche le poids de l'arete entre les noeuds i et j
        printf("\n");
    }

    return(0);
}

/* ---------------------------------------------------------
 *
 *
 * creerListeAdjacence : création de la matrice d'adjacence
 *
 *
 * ----------------------------------------------------------
 */
void creerListeAdjacence(idGraph * pGraphe)
{
    int i,j;
    idElt noeud;

    for (i = 0;i < pGraphe->nbSommets; i++) {

        for (j = pGraphe->nbSommets-1; j >= 0; j--)
            // on explore la matrice en partant des sommets d'indice les plus élevés
        {
            if (pGraphe->matrice[i][j] !=0) {
                // l'arête existe entre les noeuds i et j

                // on rajoute le noeud j dans la liste d'adjacence du noeud i, avec son poids
                noeud = creerElt(REF_OBJET(j,pGraphe->matrice[i][j]));

                // puis on insere les sommets adjacents dans la liste du sommet i
                insereElt(pGraphe->listeAdj[i], NULL, noeud);

                // printf("Insertion sommet : %2c, adjacent de %2c - sommet : %2c, poids : %2d\n", NOM_SOMMET(j), NOM_SOMMET(i), NOM_SOMMET(VAL_SOMMET(noeud)), VAL_POIDS(noeud));
            }
        }
    }
    return;
}

/* ---------------------------------------------------------
 *
 *
 * lireMatriceGraphe() : lire un nouveau graphe via sa matrice
 *                      dans un fichier
 *
 *
 * ----------------------------------------------------------
 */
int lireMatriceGraphe(idGraph * pGraphe)
{
    FILE * fichier;
    char nomfichier[30];
    char buffer[100], *ptr=buffer;
    int i, j;

    // saisie du fichier contenant la matrice
    printf ("Entrer le nom du fichier contenant la matrice du graphe : ");
    fgets (nomfichier, 30, stdin);

    fichier = fopen(nomfichier, "r");
    if (!fichier) {
        printf("erreur sur accès en lecture au fichier : %s\n", nomfichier);
        return (-1); // erreur d'accès au fichier
    }

    // on va réutiliser la structure déjà allouée
    // du graphe courant (probablement graphe par défaut)
    // On commence par libérer les listes d'adjacence
    // et on réinitialise le nombre d'arêtes

    for (i=0;i <pGraphe->nbSommets;i++)
        detruireListe(pGraphe->listeAdj[i]);
    pGraphe->nbAretes=0;

    // On lit la première ligne du fichier qui contient dans l'ordre :
    // 1) le nombre de sommets
    // 2) 1 si le graphe est pondéré, 0 sinon
    // 3) 1 si le graphe est orienté, 0 sinon
    //
    fgets(buffer, 100, fichier);
    ptr = buffer;
    while (*ptr==' ') ptr++; // on passe les caractères espaces
    sscanf(ptr,"%d", &pGraphe->nbSommets);
    while (isdigit(*ptr)) ptr++; // Sauter les digits
    while (*ptr==' ') ptr++; // on passe les caractères espaces
    sscanf(ptr,"%d", &pGraphe->graphePondere);
    while (isdigit(*ptr)) ptr++; // Sauter les digits
    while (*ptr==' ') ptr++; // on passe les caractères espaces
    sscanf(ptr,"%d", &pGraphe->grapheOriente);

    // on lit maintenant chacune des lignes du fichier qui
    // représente une ligne de la matrice avec
    // le poids de chacune des arêtes
    //
    for (i=0; i<pGraphe->nbSommets; i++) {
        fgets(buffer, 100, fichier); // on lit une ligne de la matrice
        ptr=buffer;

        pGraphe->listeAdj[i]=creerListe();

        for (j=0; j<pGraphe->nbSommets;j++) {
            while (*ptr==' ') ptr++; // on passe les caractères espaces
            sscanf(ptr,"%d", &pGraphe->matrice[i][j]);
            if (pGraphe->matrice[i][j]) pGraphe->nbAretes++;
            while (isdigit(*ptr)) ptr++; // Sauter les digits
        }
    }
    if (!pGraphe->grapheOriente)
        // si le graphe est non orienté, on divise le nombre d'aretes
        // par 2 puisqu'on les a compté deux fois
        pGraphe->nbAretes >>= 1;

    creerListeAdjacence(pGraphe);

    printf("Création du graphe terminée avec succès !!\n");

    fclose(fichier);

    return (0);
}

/* ---------------------------------------------------------
 *
 * detruireArete(): on enleve une arete du graphe
 *
 * ----------------------------------------------------------
 */
int detruireArete(idGraph *pGraphe, int s1, int s2)
{
    idElt noeud;
    idListe listeAdj;
    int nbAdjacents;

    // on met le poids de cette arete dans la matrice à zéro
    pGraphe->matrice[s1][s2]=0;

    // puis on va enlever le sommet s2 adjacanet de la liste de s1
    listeAdj=pGraphe->listeAdj[s1];
    noeud=premierElt(listeAdj);
    nbAdjacents=nbElements(listeAdj);

    while (noeud && nbAdjacents--){
        if (VAL_SOMMET(noeud) == s2) {
            // on a trouvé notre sommet dans la liste des adjacents
            // ce sommet s2 est enlevé de la liste car plus adjacent
            enleverElt(listeAdj,noeud);
            detruireElt(noeud);
            break;
        }
        noeud=suivantElt(noeud);
    }

    if (! pGraphe->grapheOriente && pGraphe->matrice[s2][s1]!=0) {
        // si c'est un graphe non orienté
        // il faut enlever l'arete symétrique dans le tableau
        // et dans la liste d'adjacence
        // on rappelle donc la fonction courante
        // en inversant l'ordre des deux sommets
        return(detruireArete(pGraphe, s2, s1));
    } else {
        // on décrémente le compteur d'arêtes
        pGraphe->nbAretes--;
    }
   return(0);
}
/* ---------------------------------------------------------
 *
 * enleverArete(): on enleve une arete du graphe
 *
 * ----------------------------------------------------------
 */
int enleverArete(idGraph *pGraphe)
{
    int s1, s2;

    afficheBanniere("Suppression d'une arête");

    printf("Entrer le sommet source de l'arête (de A à %c) : ", NOM_SOMMET(pGraphe->nbAretes-1));
    s1 = saisieCaractere()-'A';

    printf("Entrer le sommet destination de l'arête (de A à %c) : ", NOM_SOMMET(pGraphe->nbAretes-1));

    s2 = saisieCaractere()-'A';

    if (pGraphe->matrice[s1][s2] == 0) {
        printf("Cette arête n'existe pas ! difficile de la supprimer ...\n");
        return(-1);
    } else {
        return(detruireArete(pGraphe, s1, s2));
    }
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

    pGraphe->matrice[s1][s2]=poids;

    // on rajoute le noeud s2 dans la liste d'adjacence du noeud s1, avec son poids
    noeud = creerElt(REF_OBJET(s2,poids));

    if (noeud)
        insereElt(pGraphe->listeAdj[s1], NULL, noeud);
    else {
        printf("Erreur sur la création d'un élément de liste\n");
        return(-1);
    }

    if (!pGraphe->grapheOriente && pGraphe->matrice[s2][s1]==0) {
        // si le graphe est non orienté
        // on doit créer l'arête symétrique dans la matrice
        // et la liste d'adjacence

        return(creerArete(pGraphe, s2, s1, poids));
    } else {
        pGraphe->nbAretes++;
    }

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
 *                  lire un fichier matrice d'un nouveau graphe
 *                  ajouter/retirer un sommet
 *                  ajouter/retirer une arete
 *
 * ----------------------------------------------------------
 */
int gererGraphe(idGraph * pGraphe)
{
    static typeMenu menuGerer[] = {
        { "Afficher le graphe courant", &afficheGraphe },
        { "Lire un fichier matrice d'un nouveau graphe", &lireMatriceGraphe },
        { "Ajouter un sommet", &fnVide },
        { "Supprimer un sommet", &fnVide},
        { "Ajouter une arete", &ajouterArete },
        { "Supprimer une arete", &enleverArete},
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
    int i, j;

    pGraphe = (idGraph *) malloc(sizeof(idGraph));

    if (pGraphe) {
        pGraphe->nbSommets = nbSommets;
        pGraphe->nbComposantesConnexes = 0;
        pGraphe->nbCycles = 0;
        pGraphe->nbAretes = 0;
        pGraphe->grapheOriente = oriente;
        pGraphe->graphePondere = pondere;

        for(i=0;i<nbSommets;i++) {
            for (j=0;j<nbSommets;j++)
                pGraphe->matrice[i][j]=0;
            pGraphe->listeAdj[i] = creerListe();
        }
     }

    return(pGraphe);
}
/* ---------------------------------------------------------
 *
 *
 * creerDefaultGraphe() : alloue une structure de graphe et renvoie
 *              le pointeur vers le descripteur
 *              null si erreur
 *
 *
 * ----------------------------------------------------------
 */
idGraph * creerDefaultGraphe()
{
    idGraph *pGraphe;
    int i, j;


    // on cree la structure graphe, non orienté, pondéré
    pGraphe = creerGraphe(NB_SOMMETS_DEFAUT, false, true);

    if (pGraphe) {

        // on charge la matrice par défaut
        // et on incremente le nombre d'aretes selon la présence d'une valeur
        for (i = 0; i < NB_SOMMETS_DEFAUT;i++) {

            for (j = 0; j < NB_SOMMETS_DEFAUT;j++) {

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
