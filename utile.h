#ifndef UTILE
#define UTILE
#include "struct.h"

void lecture_fichier(char* f, Seq* S);

void print_seq(Seq* S);

void free_Seq(Seq* S);

int min(int x, int y, int z);

void ajout_nucleo(Seq* S,int n, char c1, char c2);

void print_align(Seq* S);

void print_parcours(Seq* S);

void print_F(int **F, int tX, int tY); // Pour debugage

int dxy(char x, char y);

#endif
