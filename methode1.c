#include <stdlib.h>
#include <stdio.h>
#include "struct.h"
#include "utile.h"


#define DGAP 2

void COUT1(Seq* S,int **F){
  int tX=S->tX;
  int tY=S->tY;
  int i,j;
  
  for (i=0;i<tX+1;i++)    //Initialisation 1ere colonne
    F[i][0]=i*DGAP;
  for (j=0;j<tY+1;j++)    //Initialisation 1ere ligne
    F[0][j]=j*DGAP;

  for (i=1;i<tX+1;i++){   //Remplissage du tableau
    for(j=1;j<tY+1;j++){
	F[i][j]=min(F[i-1][j-1]+dxy(S->tab[0][i-1],S->tab[1][j-1]), F[i-1][j]+DGAP, F[i][j-1]+DGAP);
    }
  }
} 
  
void free_F(int **F,int tX){
  int i;
  for(i=0;i<tX;i++)
    free(F[i]); 
  free(F);
}

void SOL1(Seq* S, int** F, int i, int j){
  if (i!=0 && j!=0){
    if (F[i][j]==F[i-1][j-1]+dxy(S->tab[0][i-1],S->tab[1][j-1])){   //Si provenance diagonal
      ajout_nucleo(S,1,S->tab[0][i-1],S->tab[1][j-1]);
      ajout_nucleo(S,0,S->tab[0][i-1],S->tab[1][j-1]);  //On ajoute la pair à l'alignement
      SOL1(S,F,i-1,j-1);
    }
    else{
      if (F[i][j]==F[i-1][j]+DGAP){   //Si provenance case au dessus
	ajout_nucleo(S,1,S->tab[0][i-1],'-');
	SOL1(S,F,i-1,j);
      }
      else{
	if (F[i][j]==F[i][j-1]+DGAP){   //Si provenance case a gauche
	  ajout_nucleo(S,1,'-',S->tab[1][j-1]);
	  SOL1(S,F,i,j-1);
	}
      }
    }
  }
  
  else{
    if (i==0 && j==0)
      ajout_nucleo(S,1,S->tab[0][i-1],S->tab[1][j-1]);
    if (i==0 && j!=0){
      //ajout_nucleo(S,1,'-',S->tab[1][j-1]);
      printf("i %d j %d\n",i,j);
      while(j>0){
	ajout_nucleo(S,1,'-',S->tab[1][j-1]);
	j--;}
    }
      //SOL1(S,F,i,j-1);
    if (j==0 && i!=0){
      //ajout_nucleo(S,1,S->tab[0][i-1],'-');
	while(i>0){
	  ajout_nucleo(S,1,S->tab[1][i-1],'-');
	i--;}
	//SOL1(S,F,i-1,j);
      }
  }
}
