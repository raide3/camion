#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct etape {

  int id_trajet;
  float distance;
  double max;
  double min;
  double moy;
  double premierNombre;
} Etape;

typedef struct Noeud{

  Etape* obj; 
  struct Noeud* Fg;
  struct Noeud* Fd;
  int eq;
  int som;
  int nbEtapes;

} Noeud;

typedef Noeud* pNoeud;

pNoeud creerNoeud(Etape* val){


pNoeud noeud;
noeud=malloc(sizeof(Noeud));

  if(noeud==NULL){
    exit(1);
  }
  noeud->obj=NULL;
  noeud->obj=malloc(sizeof(Etape));
  if(noeud->obj==NULL){
    exit(1);
  }
  noeud->obj->distance = val->distance;
  noeud->obj->id_trajet = val->id_trajet;
      noeud->nbEtapes=1;
  noeud->obj->max=0;
  noeud->obj->min=0;
  noeud->obj->moy=0;
  noeud->obj->premierNombre=1;
  noeud->Fg=NULL;
  noeud->Fd=NULL;
  noeud->eq=0;
  noeud->som=0;

return noeud; 
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int maxi(int a, int b, int c) {
    int maxAB = max(a, b);
    return (maxAB > c) ? maxAB : c;
}

int min(int a, int b) {
    return (a > b) ? a : b;
}
int mini(int a, int b, int c) {
    return (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c);
}

pNoeud rotationGauche(pNoeud init){

pNoeud pivot;
pivot=malloc(sizeof(pNoeud));
int eq_a, eq_p;

pivot = init->Fd;
init->Fd = pivot->Fg;
pivot->Fg = init;
eq_a = init->eq;
eq_p = pivot->eq;
init->eq = eq_a - max(eq_p, 0) - 1;
pivot->eq = mini( eq_a-2, eq_a+eq_p-2, eq_p-1 );
init = pivot;
return init;
}

pNoeud rotationDroite(pNoeud init){

pNoeud pivot;
pivot=malloc(sizeof(pNoeud));
int eq_a, eq_p;

pivot = init->Fg;
init->Fg =pivot->Fd;
pivot->Fd = init;
eq_a =init->eq;
eq_p =pivot->eq;
init->eq =eq_a - min(eq_p, 0) + 1;
pivot->eq =maxi( eq_a+2, eq_a+eq_p+2, eq_p+1 );
init =pivot;
return init;
}

pNoeud doubleRotationGauche(pNoeud init){

init->Fd = rotationDroite(init->Fd);
return rotationGauche(init);
}

pNoeud doubleRotationDroite(pNoeud init){

init->Fg = rotationGauche(init->Fg);
return rotationDroite(init);
}

int hauteur(pNoeud n) {
    if (n == NULL) {
        return 0;
    }
    int hauteurG = hauteur(n->Fg);
    int hauteurD = hauteur(n->Fd);
    return 1 + (hauteurG > hauteurD ? hauteurG : hauteurD);
}

pNoeud insertionNoeud(pNoeud init, Etape* val, int* h){

h=NULL;
h=malloc(sizeof(int));
if(h==NULL){
  exit(1);
}
  if(init==NULL){
  *h=1;
    return creerNoeud(val);
  }else if(init->obj->id_trajet> val->id_trajet){
    init->Fg=insertionNoeud( init->Fg, val,h);
    init->eq = hauteur(init->Fd) - hauteur(init->Fg);

  }else if(init->obj->id_trajet < val->id_trajet){
    init->Fd=insertionNoeud( init->Fd, val,h);init->eq = hauteur(init->Fd) - hauteur(init->Fg);
  } else {

 init->som += val->distance;
init->nbEtapes++;

// Mise à jour de la moyenne
init->obj->moy = init->som / init->nbEtapes;

    if (init->obj->premierNombre) {
        // Traiter le premier nombre correctement
      init->obj->max= init->obj->min = val->distance;
        init->obj->premierNombre = 0;
    } else {
        // Mettre à jour le maximum et le minimum
        if (val->distance > init->obj->max) {
          init->obj->max= val->distance;
        }

       if (val->distance < init->obj->min) {
    init->obj->min = val->distance;

}
    }


    *h=0;
    return init;

  }
  if(*h!=0){
    init->eq=init->eq+*h;
    if(init->eq==0){
      *h=0;
    }
    else{*h=1;}
  }
return init;
}

pNoeud equilibrerAVL(pNoeud init){

if (init->eq>=2){
  if(init->Fd->eq>=0){
    return rotationGauche(init);
  }else{
    return doubleRotationGauche(init);
  }
}else if(init->eq<=-2){
  if(init->Fg->eq<=0){
    return rotationDroite(init);
  }
  else{
    return doubleRotationDroite(init);
  }
}
return init;
}

void parcoursinfixep(pNoeud new,int cmp){


if(new!=NULL && cmp<1 ){


/* printf("m%dm", new->obj->nmb);*/
parcoursinfixep(new->Fg,cmp);printf("%d-", new->obj->id_trajet);printf("%lf/",new->obj->max);
  printf("%lf/",new->obj->moy);
  printf("%lf\n",new->obj->min);cmp++;parcoursinfixep(new->Fd,cmp);
}

}

void parcoursinfixe(pNoeud new){


if(new!=NULL  ){


/* printf("m%dm", new->obj->nmb);*/
parcoursinfixe(new->Fg);printf("%d;", new->obj->id_trajet);printf("%lf;",new->obj->max);
  printf("%lf;",new->obj->moy);
  printf("%lf\n",new->obj->min);parcoursinfixe(new->Fd);
}

}
int main(){

char* nul,*mul;
  pNoeud new=NULL; 
 int* h,*h1;int cmp=0;
FILE* fichier = fopen("stat.p", "r");

    if (fichier == NULL) {
        fprintf(stderr, "Impossible d'ouvrir le fichier.\n");
        return 1;
    }

 //   fscanf(fichier, "%*s %*s"); 

Etape* val=NULL;

while (fgets(nul, 100, fichier) != NULL) { 
       val=malloc(sizeof(Etape));

       if( sscanf(nul, "%d;%f\n", &(val->id_trajet), &(val->distance))==2){
    new=insertionNoeud(new, val, h);  new=equilibrerAVL(new);  
      // printf("%d\n", val->id_trajet); 

    } free(val);
         }parcoursinfixe(new);// 
           //


//
   fclose(fichier);




return 0;
}
