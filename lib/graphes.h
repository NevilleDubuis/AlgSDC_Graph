
#define FALSE 0
#define TRUE 1


// La liste d'adjacence d'un graphe utilise une structure de données de type "liste chainée"
// On va donc ré-utiliser les sources du cours d'algo sur ces structures "liste.h et "liste.c"

#include "listedble.h" // inclusion de la définition des listes chainées du cours d'Algo

#define MAX_S 26 //nombre max de sommets supporté
#define NOM_SOMMET(n) ('A'+n) // transformation index sommet en nom de Sommet

// on stocke dans la file le numero de sommet et le poids dans la référence objet
#define VAL_SOMMET(n) ((int)valElt(n) & 0x00ff)
#define VAL_POIDS(n) (((int)valElt(n) & 0xff00)>>8)
#define REF_OBJET(s,p) ((refObjet) ((s&0x00ff) + ((p<<8)&0xff00)))


// Structure descriptive d'un graphe
typedef struct typeGraphe {
    idListe listeAdj[MAX_S];
    int matrice[MAX_S][MAX_S];
    int nbSommets;
    int nbAretes;
    bool graphePondere;
    bool grapheOriente;
    int nbCycles;
    int nbComposantesConnexes;
} idGraph;

typedef idElt typeNoeud; // redefinition d'un élément d'une liste chainée comme étant un noeud/sommet d'un graphe
typedef refObjet IdSommet; // la donnée stockée dans un élément de la liste est le numéro de sommet (commençant par UN)


extern idGraph * creerDefaultGraphe(); // appelée une fois pour initialiser la matrice et la liste d'adjacence du graphe par défaut
extern idGraph * creerGraphe(); // création d'une structure de type graphe
extern void detruireGraphe(); // destruction de la structure graphe

extern int creerArete(); // Création d'un arete dans un graphe existant
extern int detruireArete(); // suppression d'une arete

extern int gererGraphe(); // gestion des aretes et sommets d'un graphe
extern int afficheGraphe(); // affichage matrice et liste d'adjacenec

extern int creerMatrice(); // Saisie d'une nouvelle matrice, remplaçant celle par défaut

// les déclarations des fonctions correspondant à chacun des algorithmes à développer

extern int bfs(); // recherche en profondeur dans parcours.c
extern int dfs(); // recherche en largeurdans parcours.c
extern int coloration(); // coloration d'un graphe
extern int acpm(); // arbre couvrant de poids minimum
extern int pcch(); // chemin le plus court entre deux sommets
extern int caracteristiques(); // fournit les caractéristiques du graphe
