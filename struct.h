#ifndef STRUCT_H
#define STRUCT_H

typedef struct _Nucleotide{
  char c1; //de la sequence X
  char c2; //de la sequence Y
  struct _Nucleotide* suiv;
}Nucleotide;

typedef struct _Seq{
  int tX;
  int tY;
  char **tab; //Tableau à 2 lignes des sequences de nucleotides
  Nucleotide* align; //Liste chainee de l'alignement optimal
  Nucleotide* parcours; //Parcours de la matrice F
}Seq;

#endif

