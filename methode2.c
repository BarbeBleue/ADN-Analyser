#include <stdlib.h>
#include <stdio.h>
#include "struct.h"
#include "utile.h"


#define DGAP 2
#define DXY 3

int COUT2(Seq* S,int **F,int m, int n){
  int tY=S->tY+1;
  int i,j;
  
  
  for (i=0;i<2;i++)  //Initialisation première colonne
    F[i][0]=i*DGAP;
  for (j=0;j<tY;j++)   //Initialisation première ligne
    F[0][j]=j*DGAP;

  for(j=1;j<tY;j++){  //Calcul deuxième ligne
    /*if (S->tab[0][0]==S->tab[1][j-1])
	F[1][j]=min(F[0][j-1], F[0][j]+DGAP, F[1][j-1]+DGAP);
	else*/
	F[1][j]=min(F[0][j-1]+dxy(S->tab[0][0],S->tab[1][j-1]), F[0][j]+DGAP, F[1][j-1]+DGAP);
  }
      
  for (i=2;i<m;i++){  //Calcul des lignes jusqu'à m
    F[0][0]=F[1][0];  //On monte le 1er élément de la deuxième ligne sur la 1ere
    F[1][0]=F[0][0]+DGAP; //On incrémente de la valeur DGAP la valeur du premier element de la 2eme ligne
    for(j=1;j<tY;j++){ 
      //printf("i=%d j=%d\n",i,j);
      F[0][j]=F[1][j]; //On monte la valeur sur la ligne sup
      /*if (S->tab[0][i-1]==S->tab[1][j-1]){
	F[1][j]=min(F[0][j-1], F[0][j]+DGAP, F[1][j-1]+DGAP);
	
	else*/
      F[1][j]=min(F[0][j-1]+dxy(S->tab[0][i-1],S->tab[1][j-1]), F[0][j]+DGAP, F[1][j-1]+DGAP);
    }
  }
  //print_F(F,2,tY);
  return(F[1][n]); // Retourne F[m][n]
} 


int COUT2BIS(Seq* S,int **F,int m, int n){
  int tY=S->tY+1;
  int tX=S->tX+1;
  int i,j;
  
  
  for (i=0;i<2;i++)//Initialisation dernière colonne
    F[1-i][tY-1]=i*DGAP;
  for (j=0;j<tY;j++)   //Initialisation dernière ligne
    F[1][tY-1-j]=j*DGAP;

  //print_F(F,1,tY-1);

  for(j=1;j<tY;j++){  //Calcul deuxième ligne
    //printf("X: %c Y: %c\n",S->tab[0][tX-2],S->tab[1][tY-1-j]);
    /*if (S->tab[0][tX-1]==S->tab[1][tY-1-j]){
      F[0][tY-1-j]=min(F[1][tY-j], F[0][tY-j]+DGAP, F[1][tY-j-1]+DGAP);
      //printf("paire concordante F[0][%d]=%d\n",tY-j-1,F[0][tY-1-j]);
    }
    else{*/
      
    F[0][tY-1-j]=min(F[1][tY-j]+dxy(S->tab[0][tX-i],S->tab[1][tY-j]), F[0][tY-j]+DGAP, F[1][tY-j-1]+DGAP);
      //printf("paire non-concordante F[0][%d]=%d\n",tY-j-1,F[0][tY-1-j]);
    
  }
  //printf("Calcul 2e ligne\n");
  //print_F(F,1,tY-1);

  // OK
      
  for (i=2;i<m;i++){  //Calcul des lignes jusqu'à m
    F[1][tY-1]=F[0][tY-1];  //On descend le dernier élément de la 1ere ligne sur la 2eme
    //printf("On descend le dernier élément de la 1ere ligne sur la 2eme\n");
    print_F(F,1,tY);
    F[0][tY-1]=F[1][tY-1]+DGAP; //On incrémente de la valeur DGAP la valeur du dernier element de la 1ere ligne
    //print_F(F,2,tY);
    for(j=1;j<tY;j++){ 
      //printf("i=%d j=%d\n",i,j);
      F[1][tY-1-j]=F[0][tY-1-j]; //On descend la valeur sur la ligne inf
      
      //printf("j= %d %d -> %d\n",j,F[1][tY-1-j],F[0][tY-1-j]);
      //print_F(F,2,tY);
      /*if (S->tab[0][tX-1-i]==S->tab[1][tY-1-j]){
        F[0][tY-1-j]=min(F[1][tY-j], F[0][tY-j]+DGAP, F[1][tY-j-1]+DGAP);
	//printf("paire concordante F[0][%d]=%d\n",tY-j-1,F[0][tY-1-j]);
      }
      else{
	//printf("F[1][tY-j]+DXY=%d\n",F[1][tY-j]+DXY);
	//printf("F[0][tY-j]+DGAP=%d\n",F[0][tY-j]+DGAP);	
	//printf("F[1][tY-j-1]+DGAP=%d\n",F[1][tY-j-1]+DGAP);	
	F[0][tY-1-j]=min(F[1][tY-j]+DXY, F[0][tY-j]+DGAP, F[1][tY-j-1]+DGAP);*/
      F[0][tY-1-j]=min(F[1][tY-j]+dxy(S->tab[0][tX-i],S->tab[1][tY-j]), F[0][tY-j]+DGAP, F[1][tY-j-1]+DGAP);
	//printf("paire non-concordante F[0][%d]=%d\n",tY-j-1,F[0][tY-1-j]);
      
    }
  }
  //print_F(F,2,tY);
  return(F[1][n]); // Retourne F[m][n]
}
 
