#include <stdlib.h>
#include <stdio.h>
#include "struct.h"
#include "utile.h"


#define DGAP 2
#define DXY 3

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
      /*if (S->tab[0][i]==S->tab[1][j])
	F[i][j]=min(F[i-1][j-1], F[i-1][j]+DGAP, F[i][j-1]+DGAP);
	else*/
	//F[i][j]=min(F[i-1][j-1]+DXY, F[i-1][j]+DGAP, F[i][j-1]+DGAP);
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
    //printf("i %d j %d\n",i,j);
    if (F[i][j]==F[i-1][j-1] && S->tab[0][i-1]==S->tab[1][j-1]){   //Si provenance diagonale et lettres simillaires
      //printf("diag c: %c %c\n",S->tab[0][i-1],S->tab[1][j-1]);
      ajout_nucleo(S,0,S->tab[0][i-1],S->tab[1][j-1]);   //On ajoute la paire concordante à l'alignement
      ajout_nucleo(S,1,S->tab[0][i-1],S->tab[1][j-1]);
      SOL1(S,F,i-1,j-1);
    }
    else {if (F[i][j]==F[i-1][j-1]+DXY){   //Si provenance diagonale et lettres non-simillaires
	//printf("diag nc: %c %c\n",S->tab[0][i-1],S->tab[1][j-1]);
	ajout_nucleo(S,1,S->tab[0][i-1],S->tab[1][j-1]);
	ajout_nucleo(S,0,S->tab[0][i-1],S->tab[1][j-1]);  //On ajoute la paire non-concordante à l'alignement
	SOL1(S,F,i-1,j-1);
      }
      else{
	if (F[i][j]==F[i-1][j]+DGAP){   //Si provenance case au dessus
	  //printf("c up: %c -\n",S->tab[0][i-1]);
	  ajout_nucleo(S,1,S->tab[0][i-1],'-');
	  SOL1(S,F,i-1,j);
	}
	else{
	  if (F[i][j]==F[i][j-1]+DGAP){   //Si provenance case a gauche
	    //printf("c down:- %c\n",S->tab[1][j-1]);
	    ajout_nucleo(S,1,'-',S->tab[1][j-1]);
	    SOL1(S,F,i,j-1);
	  }
	}
      }
    }
  }
  else{
    //printf("%c %c\n",S->tab[0][i],S->tab[1][j]);
    //printf("i %d j %d\n",i,j);
    if (S->tab[0][i-1]==S->tab[1][j-1])
      ajout_nucleo(S,0,S->tab[0][i-1],S->tab[1][j-1]);   //On ajoute derniere paire concordante à l'alignement
    if (i==0 && j==0)
      ajout_nucleo(S,1,S->tab[0][i-1],S->tab[1][j-1]);
    if (i==0 && j!=0){
      //printf("i=0 c=%c\n",S->tab[1][j-1]);
      ajout_nucleo(S,1,'-',S->tab[1][0]);}
    if (j==0 && i!=0){
      //printf("j=0\n");
	ajout_nucleo(S,1,S->tab[0][i-1],'-');
      }
  }
}
