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

  printf("\nParcours en largeur\n");
  afficher_graphe_largeur(g,g->label);
  printf("\nParcours en profondeur\n");
  afficher_graphe_profondeur(g,g->label);

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

  chemin_t c = creer_chemin(g); 
  // afficher_chemin(c);
  if (elementaire(g, c)) {
        printf("Le chemin est élémentaire.\n");
    } else {
        printf("Le chemin n'est pas élémentaire.\n");
    }
  if (simple(g, c)) {
        printf("Le chemin est simple.\n");
    } else {
        printf("Le chemin n'est pas simple.\n");
    }
  if (eulerien(g, c)) {
        printf("Le chemin est eulrien.\n");
    } else {
        printf("Le chemin n'est pas eulrien.\n");
    }
  if (graphe_hamiltonien(g)) {
        printf("Le chemin est hamiltonien.\n");
  } else {
        printf("Le chemin n'est pas hamiltonien.\n");
    }

      printf("\n                                  distance et excentricité et diametre :\n");

    int x, y;
    printf("donnez le sommet source : ");
    scanf("%d", &x);
    printf("donnez le sommet destination : ");
    scanf("%d", &y);

    int dist = distance(g, x, y);
    printf("La distance entre %d et %d est : %d\n", x, y, dist);

    int n;
    printf("Entrez le sommet pour l'excentricciité : ");
    scanf("%d", &n);

    int excentricite_n = excentricite(g, n);
    printf("L'excentriccité du sommet %d est : %d\n", n, excentricite_n);
    int diam = diametre(g);
    printf("Le diamètre du graphe est : %d\n", diam);
  

}