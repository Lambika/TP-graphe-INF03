#include <stdio.h>
#include <stdlib.h>

#include "graphe.h"

int main (int argc, char **argv)
{
  pgraphe_t g ;
  
  if (argc != 2)
    {
      fprintf (stderr, "erreur parametre \n") ;
      exit (-1) ;
    }

  /*
    la fonction lire_graphe alloue le graphe (matrice,...) 
    et lit les donnees du fichier passe en parametre
  */
  
  
  lire_graphe (argv [1], &g) ;

  /*
    la fonction ecrire_graphe affiche le graphe a l'ecran
  */  
  
  printf ("nombre de sommets du graphe %d nombre arcs %d \n", nombre_sommets (g), nombre_arcs (g)) ;
  fflush (stdout) ;
  
  ecrire_graphe (g) ;      
  int nc ;
  nc = colorier_graphe (g) ;
  
  printf ("nombre chromatique graphe = %d\n", nc) ;
  
  ecrire_graphe_colorie (g) ;


  printf("\n                                    Algo Dijkstra: \n");
  algo_dijkstra(g,g->label);
  afficher_dijkstra(g);

  printf("\n                                    Degrés sortants des sommets :\n");
  psommet_t sommet = g;
  while (sommet != NULL) {
      int degre_sortant = degre_sortant_sommet(g, sommet);
      printf("Le degré sortant du sommet %d est : %d\n", sommet->label, degre_sortant);
      sommet = sommet->sommet_suivant;
  }

  printf("\n                                    Degrés entrants des sommets :\n");
  sommet = g;
  while (sommet != NULL) {
      int degre_entrant = degre_entrant_sommet(g, sommet);
      printf("Le degré entrant du sommet %d est : %d\n", sommet->label, degre_entrant);
      sommet = sommet->sommet_suivant;
  }
  printf("\n                                    Degré maximal/minimal :");

  int degre_maximal = degre_maximal_graphe(g);
  printf("\nLe degré maximal du graphe est : %d\n", degre_maximal);

  int degre_minimal = degre_minimal_graphe(g);
  printf("Le degré minimal du graphe est : %d\n\n", degre_minimal);

  printf("\n                                  Propriété du graphe :\n");

  printf("Independant? : %s\n", independant(g) ? "OUI" : "NON");
  printf("Complet ? : %s\n", complet(g) ? "OUI" : "NON");
  printf("Régulier: %s\n", regulier(g) ? "OUI" : "NON");


}