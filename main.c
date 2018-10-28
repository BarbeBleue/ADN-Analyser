#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utile.h"
#include "struct.h"
#include "methode1.h"
#include "methode2.h"
#include <time.h>
#include <math.h>



int main(){
  char* filename=(char*)malloc(sizeof(char)*21);
  if (filename==NULL){
	printf("Erreur d'allocation!\n");
      return 1;
      }
  FILE* f = NULL;
  FILE* f2 = NULL;
  srand(time(NULL));
  f = fopen("results.txt","w");  
  f2 = fopen("results2.txt","w");
  clock_t temps_initial,temps_final;
  float temps_cpu1, temps_cpu2;
  int tX, tY;
  int i,j,n;

  for(n=1;n<2;n++){ //1: 13
    switch(n){
    case 0:
      filename="Inst_0000010_44.adn";
      break;
    case 1:
      filename="Inst_sujet.adn";
      break;
    case 2:
      filename="Inst_0001000_2.adn";
      break;
    case 3:
      filename="Inst_0001000_7.adn";
      break;
    case 4:
      filename="Inst_0003000_25.adn";
      break;
    case 5:
      filename="Inst_0005000_32.adn";
      break;
    case 6:
      filename="Inst_0005000_33.adn";
      break;
    case 7:
      filename="Inst_0008000_32.adn";
      break;
    case 8:
      filename="Inst_0008000_54.adn";
      break;
    case 9:
      filename="Inst_0010000_7.adn";
      break;
    case 10:
      filename="Inst_0012000_10.adn";
      break;
    case 11:
      filename="Inst_0015000_20.adn";
      break;
    case 12:
      filename="Inst_0020000_64.adn";
      break;
    case 13: // Limite SOL 1
      filename="Inst_0050000_88.adn";
      break;
    case 14:
      filename="Inst_0100000_11.adn";
      break;
    default:
      printf("Aucune séquence\n");
      break;
      }
    
  //filename="Inst_sujet.adn";

    // Lecture fichier
    
    printf("\nNom du fichier: %s \n\n",filename);
    Seq* S=(Seq*)malloc(sizeof(Seq));
    S->align=NULL;
    S->parcours=NULL;
    if (S==NULL){
      printf("Erreur d'allocation!\n");
      return 1;
    }    
    S->tab=(char**)malloc(2*sizeof(char*)); //allocation mémoire du tableau de récupération des données du fichier
    if (S->tab==NULL){
      printf("Erreur d'allocation!\n");
      return 1;
    }   
    lecture_fichier(filename,S);
    tX=S->tX;
    tY=S->tY;
    print_seq(S); //Affichage des sequences si taille raisonnable 

    printf("\n----------------- SOL 1 ---------------------------\n"); 

    //  Allocation memoire et initialisation de la matrice des couts

    
    int **F=(int**)malloc((tX+1)*sizeof(int*));
    if (F==NULL){
      printf("Erreur d'allocation!\n");
      return 1;
    }
    for (i=0;i<tX+1;i++){
      F[i]=malloc((tY+1)*sizeof(int));
      if (F[i]==NULL){
	printf("Erreur d'allocation!\n");
	return 1;
      }
    }
    for (i=0;i<tX+1;i++){    //Initialisation des valeurs du tableau à 0
      for(j=0;j<tY+1;j++){
	F[i][j]=0;
      }
    }
    
    //   Optimisation
    
    temps_initial=clock();
    COUT1(S,F);
    temps_final=clock();    
    if (tX<100) print_F(F,tX,tY);
    temps_cpu1=(temps_final-temps_initial)*pow(10,-6);
    printf("\nCoût de l'alignement optimal: %d\n",F[tX][tY]);
  
    SOL1(S,F,tX,tY);
    temps_final=clock();
    temps_cpu2=(temps_final-temps_initial)*pow(10,-6);

    fprintf(f,"%d %f %f %f\n",tX,temps_cpu1,temps_cpu2, temps_cpu1+temps_cpu2);
  
    if (tX<100) print_align(S); // Affichage de l'alignement optimal
    
    if (tX<100) print_parcours(S); //Affiche le parcours inverse de F
    
    //print_F(F,tX,tY);
    //printf("1: %d\n",F[4-1][4-1]); // Pour Q4.7

    //   Libération mémoire
    
    free_F(F,tX);
    
    
    //printf("\n----------------- SOL 2 ---------------------------\n");

      //  Allocation memoire et initialisation de la matrice des couts
      
      int **F2=(int**)malloc(2*sizeof(int*));
      if (F2==NULL){
	printf("Erreur d'allocation!\n");
	return 1;
      }
      F2[0]=malloc((tY+1)*sizeof(int));
      if (F2[0]==NULL){
	printf("Erreur d'allocation!\n");
	return 1;
      }
      F2[1]=malloc((tY+1)*sizeof(int));
      if (F2[1]==NULL){
	printf("Erreur d'allocation!\n");
      return 1;
      }
      for (i=0;i<2;i++){    //Initialisation des valeurs du tableau à 0
	for(j=0;j<tY+1;j++){
	F2[i][j]=0;
	}
      }

      //  Optimisation

      temps_initial=clock();
      COUT2(S,F2,4,2);
      temps_final=clock();      
      //print_F(F2,1,tY);
      
      //print_F(F,2,tY);
      temps_cpu1=(temps_final-temps_initial)*pow(10,-6);
      fprintf(f2,"%d %f \n",tX,temps_cpu1);
      for (i=0;i<2;i++){    //Initialisation des valeurs du tableau à 0
	for(j=0;j<tY+1;j++){
	  F2[i][j]=0;
	}
      }
      
      //printf("\nCOUT2BIS\n");
      COUT2BIS(S,F2,2,3);
      //print_F(F2,1,tY);
    

      //  Liberation memoire
      
      free_F(F2,2); 
      free_Seq(S);
  }
  fclose(f);
  fclose(f2);
  //system("gnuplot commande.txt");
  return 0;
}
