
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Objet{

  int id_trajet;
  char villeA[100];

  int nmb;

}Objet;


typedef struct Noeud{

  Objet* obj; 
  struct Noeud* Fg;
  struct Noeud* Fd;
  int eq;

} Noeud;

typedef Noeud* pNoeud;

pNoeud creerNoeud(Objet* val){


pNoeud noeud;
noeud=malloc(sizeof(Noeud));

  if(noeud==NULL){
    exit(1);
  }
  noeud->obj=NULL;
  noeud->obj=malloc(sizeof(Objet));
  if(noeud->obj==NULL){
    exit(1);
  }
  noeud->obj->id_trajet = val->id_trajet;
      strcpy(noeud->obj->villeA, val->villeA);
  noeud->obj->nmb=1;
  noeud->Fg=NULL;
  noeud->Fd=NULL;
  noeud->eq=0;

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

init->Fg = rotationDroite(init->Fg);
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

pNoeud insertionNoeud(pNoeud init, Objet* val){


  if(init==NULL){

    return creerNoeud(val);
  }else if(strcmp(init->obj->villeA, val->villeA)>0){
    init->Fg=insertionNoeud( init->Fg, val,h);
    init->eq = hauteur(init->Fd) - hauteur(init->Fg);

  }else if(strcmp(init->obj->villeA, val->villeA)<0){
    init->Fd=insertionNoeud( init->Fd, val,h);init->eq = hauteur(init->Fd) - hauteur(init->Fg);
  } else {
  if(init->obj->id_trajet==val->id_trajet){

    return init;
  }else if(init->obj->id_trajet!=val->id_trajet){
    init->obj->nmb++;
    return init;	
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

void parcoursinfixe(pNoeud new){


if(new!=NULL ){


/* printf("m%dm", new->obj->nmb);*/
parcoursinfixe(new->Fg);printf("%s-", new->obj->villeA);printf("%d\n",new->obj->nmb);parcoursinfixe(new->Fd);
}

}

int main(){

char* nul;
  pNoeud new=NULL;

FILE* fichier = fopen("new", "r");

    if (fichier == NULL) {
        fprintf(stderr, "Impossible d'ouvrir le fichier.\n");
        return 1;
    }

 //   fscanf(fichier, "%*s %*s"); 

Objet* val=NULL;

while (fgets(nul, 100, fichier) != NULL) { 
       val=malloc(sizeof(Objet));
if(val==NULL){
  exit(1);
}


       if( sscanf(nul, "%d;%39[^\n]", &(val->id_trajet), val->villeA)==2){
    new=insertionNoeud(new, val);  new=equilibrerAVL(new);  
      // printf("%d\n", val->id_trajet); 

    } free(val);
         }parcoursinfixe(new);// 
           //


//
   fclose(fichier);

  

return 0;
}





