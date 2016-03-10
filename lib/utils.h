
#define FALSE 0
#define TRUE 1


// Structure utilisée pour les menus utilisateur
typedef struct {
    char texte[100];
    int (* fn) (void *) ;
} typeMenu;


// Les déclarations des fonctions générales

extern int saisieEntier(); // saisie d'un entier
extern char saisieCaractere(); // saisie d'un caractère de 'A' à 'Z', pour les sommets
extern int afficheBanniere(char *p); // affiche un message d'accueil de la fonction appelée
extern int afficheMenu( typeMenu *); // affiche d'un menu à choix

extern int fnVide(); // quand une fonction n'est pas encore implémentée
