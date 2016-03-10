//
//  utils.c
//  Exo1
//
//  Created by Jean-Claude on 01.03.15.
//  Copyright (c) 2015 Jean-Claude. All rights reserved.
//

/* ce fichier contient des fonctions utilitaires pour les graphes */

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"


// message utilisé pour l'accueil de chacun des menus et sous-menus

static char accueil[5][100] = {
    "*------------------------------------------------------------------*",
    "*                                                                  *",
    "*  Le texte de la bannière est ici                                 *",
    "*                                                                  *",
    "*------------------------------------------------------------------*",
};


/* ---------------------------------------------------------
 *
 *
 * Fonction vide : pour les algorithmes non encore implémentés
 *
 *
 * ----------------------------------------------------------
 */

int fnVide()
{
    printf("\n\nFonction pas encore implémentée !!!! \n\n");

    return(0);
}

/* ---------------------------------------------------------
 *
 *
 * affiche_banniere : affichage d'une banniere
 *                     on passe en paramètre la chaine de caractères
 *                     correspondante au titre
 *
 * ----------------------------------------------------------
 */
int afficheBanniere(char *chaine)
{
    int i, nb_espaces;

    for (i = 0; i < 2; i++) printf("%s\n", accueil[i]);


    // on affiche le texte de la bannière en la centrant
    // dans le cadre = calculdu nombre d'espaces avant et après
    // en tenant compte de la longueur impaire du texte

    nb_espaces = (strlen(accueil[0]) - strlen (chaine))/2-1;

    printf("*");
    for (i=0;i<nb_espaces;i++) printf(" "); // espaces avant

    printf("%s", chaine);

    for (i=0;i<nb_espaces;i++) printf(" "); // espaces après
    if (strlen(chaine)&1) printf(" "); // cas de longueur impaire

    printf("*\n");

    for (i = 3; i < 5; i++) printf("%s\n", accueil[i]);
    printf("\n");

    return(0);
}

/* ---------------------------------------------------------
 *
 *
 * afficheMenu : affiche le menu passé en paramètre
 *              et renvoie le choix de l'utilisateur
 *
 *
 * ----------------------------------------------------------
 */

int afficheMenu(typeMenu * pMenu)
{
    int choix=0,i;

    for ( i = 0; (pMenu+i)->fn != NULL; i++) {
        printf("     < %d > - %s\n", i + 1, (pMenu+i)->texte);
    }

    do {
        printf("\nEntrez votre choix (0 pour quitter ce menu) : ");

        choix = saisieEntier();

        if (choix > i || choix < 0)
            printf("\n!! -------> un nombre compris entre 0 et %d, svp !!\n", i );
    } while (choix >i || choix < 0);

    return(choix);
}

/* ---------------------------------------------------------
 *
 *
 * saisieEntier : Saisie d'une valeur numériqueentière au clavier
 *
 *
 * ----------------------------------------------------------
 */

int saisieEntier()
{
    int n, val;
    char ligne[100];

    fgets(ligne, 100, stdin);
    n = sscanf(ligne, "%d", &val);
    while (n != 1) {
        printf("Entrer une valeur entiere : ");
        fgets(ligne, 100, stdin);
        n = sscanf(ligne, "%d", &val);
    }
    return (val);
}
/* ---------------------------------------------------------
 *
 *
 * saisieCaractere : Saisie d'un caractère A à Z au clavier
 *
 *
 * ----------------------------------------------------------
 */

char saisieCaractere()
{
    int n;char val;
    char ligne[100];

    fgets(ligne, 100, stdin);
    n = sscanf(ligne, "%c", &val);
    while ((n != 1) || (val <'A') || (val>'Z')) {
        printf("Entrer un caractère de A à Z : ");
        fgets(ligne, 100, stdin);
        n = sscanf(ligne, "%c", &val);
    }
    return (val);
}
