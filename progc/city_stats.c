#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NoeudAVL {
    char nomVille[50];
    int totalTrajets;
    int trajetsDepart;
    struct NoeudAVL* gauche;
    struct NoeudAVL* droite;
    int hauteur;
} NoeudAVL;

int hauteur(NoeudAVL* noeud) {
    if (noeud == NULL)
        return 0;
    return noeud->hauteur;
}

int equilibre(NoeudAVL* noeud) {
    if (noeud == NULL)
        return 0;
    return hauteur(noeud->gauche) - hauteur(noeud->droite);
}

NoeudAVL* nouveauNoeud(char nomVille[]) {
    NoeudAVL* noeud = (NoeudAVL*)malloc(sizeof(NoeudAVL));
    strcpy(noeud->nomVille, nomVille);
    noeud->totalTrajets = 0;
    noeud->trajetsDepart = 0;
    noeud->hauteur = 1;
    noeud->gauche = NULL;
    noeud->droite = NULL;
    return noeud;
}

NoeudAVL* rotationDroite(NoeudAVL* y) {
    NoeudAVL* x = y->gauche;
    NoeudAVL* T2 = x->droite;

    x->droite = y;
    y->gauche = T2;

    y->hauteur = 1 + ((hauteur(y->gauche) > hauteur(y->droite)) ? hauteur(y->gauche) : hauteur(y->droite));
    x->hauteur = 1 + ((hauteur(x->gauche) > hauteur(x->droite)) ? hauteur(x->gauche) : hauteur(x->droite));

    return x;
}

NoeudAVL* rotationGauche(NoeudAVL* x) {
    NoeudAVL* y = x->droite;
    NoeudAVL* T2 = y->gauche;

    y->gauche = x;
    x->droite = T2;

    x->hauteur = 1 + ((hauteur(x->gauche) > hauteur(x->droite)) ? hauteur(x->gauche) : hauteur(x->droite));
    y->hauteur = 1 + ((hauteur(y->gauche) > hauteur(y->droite)) ? hauteur(y->gauche) : hauteur(y->droite));

    return y;
}

NoeudAVL* insertion(NoeudAVL* noeud, char nomVille[]) {
    if (noeud == NULL)
        return nouveauNoeud(nomVille);

    if (strcmp(nomVille, noeud->nomVille) < 0)
        noeud->gauche = insertion(noeud->gauche, nomVille);
    else if (strcmp(nomVille, noeud->nomVille) > 0)
        noeud->droite = insertion(noeud->droite, nomVille);
    else
        return noeud;

    noeud->hauteur = 1 + ((hauteur(noeud->gauche) > hauteur(noeud->droite)) ? hauteur(noeud->gauche) : hauteur(noeud->droite));

    int equilibreNoeud = equilibre(noeud);

    if (equilibreNoeud > 1 && strcmp(nomVille, noeud->gauche->nomVille) < 0)
        return rotationDroite(noeud);

    if (equilibreNoeud < -1 && strcmp(nomVille, noeud->droite->nomVille) > 0)
        return rotationGauche(noeud);

    if (equilibreNoeud > 1 && strcmp(nomVille, noeud->gauche->nomVille) > 0) {
        noeud->gauche = rotationGauche(noeud->gauche);
        return rotationDroite(noeud);
    }

    if (equilibreNoeud < -1 && strcmp(nomVille, noeud->droite->nomVille) < 0) {
        noeud->droite = rotationDroite(noeud->droite);
        return rotationGauche(noeud);
    }

    return noeud;
}

void parcoursInfixe(NoeudAVL* racine) {
    if (racine != NULL) {
        parcoursInfixe(racine->gauche);
        printf("%s - Total: %d, Départs: %d\n", racine->nomVille, racine->totalTrajets, racine->trajetsDepart);
        parcoursInfixe(racine->droite);
    }
}

void libererArbreAVL(NoeudAVL* racine) {
    if (racine != NULL) {
        libererArbreAVL(racine->gauche);
        libererArbreAVL(racine->droite);
        free(racine);
    }
}

int main() {
    FILE* fichier = fopen("data/data.csv", "r");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    char ligne[255];
    fgets(ligne, sizeof(ligne), fichier);

    NoeudAVL* racine = NULL;

    while (fgets(ligne, sizeof(ligne), fichier)) {
        char* token = strtok(ligne, ";");
        char nomVille[50];

        token = strtok(NULL, ";");
        token = strtok(NULL, ";");
        token = strtok(NULL, ";");

        if (token != NULL) {
            sscanf(token, "%s", nomVille);
        }

        racine = insertion(racine, nomVille);
    }

    fclose(fichier);

    parcoursInfixe(racine);

    FILE* fichierDonnees = fopen("temp/sortie.txt", "w");
    if (fichierDonnees == NULL) {
        fprintf(stderr, "Erreur lors de la création du fichier de données pour gnuplot.\n");
        return 1;
    }

    NoeudAVL* courant = racine;
    while (courant != NULL) {
        fprintf(fichierDonnees, "%s %d %d\n", courant->nomVille, courant->totalTrajets, courant->trajetsDepart);
        courant = courant->droite;
    }

    fclose(fichierDonnees);

    libererArbreAVL(racine);

    return 0;
}
