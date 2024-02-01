#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int nmb;
  char* nom;
}Node;

typedef struct Arbre{
Node elmt;
struct Arbre* Fg;
struct Arbre* Fd;
}Arbre;
typedef Arbre* pArbre;

pArbre createArbre(node* val){

pArbre new=malloc(sizeof(Arbre));
if(new==NULL){
exit(1);
}
new->node->nmb=val->nmb;
strcpy(val->nom,new->node->nom);
new->Fg=NULL;
new->Fd=NULL;
return new;
}

int isempty(pArbre new){

return new==NULL;
}

pArbre addArbreFg(pArbre new, int elmt, char n){

if (!hasFg){
exit(3);
}
new->Fg=createArbre(elmt);

return new;
}

pArbre addArbreFd(pArbre new, int elmt){

if (!hasFd){
exit(3);
}
new->Fd=createArbre(elmt);

return new;
}

void treat(pArbre new){

printf("%d-", get(new));

}

typedef struct File{
      Node* tete;
      Node* queue;
      int taille;
}File;

File* creationfile(){

        File* head=malloc(sizeof(File));

   head->tete=NULL;
       head->queue=NULL;
  head->taille=0;
        return head;
}

void enfiler(File* file, Node* val){
    node* nouveau= val;
    if(file->queue==NULL && file->tete==NULL){
        file->tete=nouveau;
        file->queue=nouveau;
    }
    else{
        file->queue->suiv=nouveau;
        file->queue = nouveau;
    }
  fille->taille++;
}

void defiler(File* file){
  int result=0;
  if(file->tete==file->queue+1){
    result=1;
  }
  else {

    file->tete=file->tete->suiv;
  }
  file->taille--;

}

void parcoursinfixe(pArbre new){

if(!isempty(new)){
parcoursinfixe(new->Fg);
  enfiler(file,new->node);
 
  if(file->taille>10){
     defiler(file);
  }
parcoursinfixe(new->Fd);
}

}


pArbre insertArbre(pArbre new, node elmt){

if (isempty(new)){
new=createArbre(elmt);
}
else if(new->elmt<elmt){
new->Fd=insertArbre(new->Fd,elmt);
}
else if(new->elmt>elmt){
new->Fg=insertArbre(new->Fg,elmt);
}
return new;
}

int main(){

pArbre new= NULL, 

parcoursinfixe(new);




return 0;
}