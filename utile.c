#include <stdlib.h>
#include <stdio.h>
#include "struct.h"



void print_seq(Seq* S){
  int i;
  printf("taille sequence X: %d taille sequence Y:%d\n\n",S->tX,S->tY);
  if(S->tX<100){
    printf("Sequence X:\n[ ");
    for (i=0;i<S->tX;i++)
      printf("%c  ",S->tab[0][i]);
    printf("]\nSequence Y:\n[ ");
    for (i=0;i<S->tY;i++)
      printf("%c  ",S->tab[1][i]);
    printf("]\n");
  }
}

void lecture_fichier(char* nom_fichier, Seq* S) {
	FILE *f = fopen(nom_fichier, "r");
        if (f!=NULL){
	  int tX,tY;
	  fscanf(f,"%d %d",&tX,&tY);
	  S->tX=tX;   //Affectation valeurs associées aux sequences
	  S->tY=tY;
	  S->tab[0]=malloc(sizeof(char)*(tX));  //Allocation mémoire du tableau des sequences de nucleotides
	  if (S->tab[0]==NULL){
	    printf("Erreur d'allocation!\n");
	    //exit;
	  }
	  S->tab[1]=malloc(sizeof(char)*(tY));
	  if (S->tab[1]==NULL){
	    printf("Erreur d'allocation!\n");
	    //exit;
	  }
	  int i,k=0;
	  
	  for (i=0;i<tX;i++){   //Lecture sequence X
	    fgetc(f);
	    S->tab[0][i]=fgetc(f);
	    
	  }
	  while(fgetc(f)!='\n'){
	    //printf("%d ",k);
	      k++;
	  }
	  for (i=0;i<tY;i++){   //Lecture sequence Y
	    
	    S->tab[1][i]=fgetc(f);
	    fgetc(f);
	    }
	}
	fclose(f);
}
	  
void free_Seq(Seq* S){
  Nucleotide* N=S->align;
  Nucleotide* temp;
  free(S->tab[0]);
  free(S->tab[1]);
  free(S->tab);
  while (N!=NULL){
    temp=N;
    N=N->suiv;
    free(temp);
    }
  free(S);
}

int min(int x, int y, int z){
  if (x<y){
    if (x<z)
      return x;
  }
  else{ 
    if (z<y)
      return z;
  }
  return y;
}

void ajout_nucleo(Seq* S,int n, char c1, char c2){ //n = mode -> 0= align autre= parcours
  Nucleotide *n_new = malloc (sizeof(Nucleotide));
   if (n_new != NULL)
   {
     n_new->c1 = c1;   //Affectation de données
     n_new->c2 = c2;
     //printf("ajout: %c %c\n",c1,c2);
     if (n==0){
       n_new->suiv=S->align;  //Ajout en début de liste
       S->align=n_new;
     }
     else{
       n_new->suiv=S->parcours;
       S->parcours=n_new;
     }
   }
}


void print_align(Seq* S){
  Nucleotide *n = S->align;
  printf("\nAlignement\n+-------+\n");
  while (n!=NULL){
    printf("%c %c\n",n->c1,n->c2);
    n=n->suiv;
  }  
  printf("+-------+\n");
}

void print_parcours(Seq*S){
  Nucleotide *n = S->parcours;
  printf("\nParcours\n+-------+\n");
  while (n!=NULL){
    printf("%c %c\n",n->c1,n->c2);
    n=n->suiv;
  }  
  printf("+-------+\n");
}

void print_F(int **F,int tX, int tY){
  //Affiche la matrice F
  int i,j;
  printf("\nMatrice coûts: F\n+-------+\n");
  for (i=0;i<tX+1;i++){   
    for(j=0;j<tY+1;j++){
      printf("%d ",F[i][j]);
    }
    printf("\n");
  }
  printf("+-------+\n");
}

int dxy(char x,char y){
  //printf("x= %c y= %c\n",x,y);
  if (x==y){
    //printf("c=0\n");
    return 0;
  }
  if ((x=='T'|| y=='A') && (y=='A' && x=='T')){
    //printf("c=3\n");
    return 3;
  }
  if ((x=='C'|| y=='G') && (y=='C' && x=='G')){
    //printf("c=3\n");
    return 3;
  }
  else{
    //printf("c=4\n");
    return 4;
  }
}
      
