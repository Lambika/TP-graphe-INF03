/*
  Structures de type graphe
  Structures de donnees de type liste
  (Pas de contrainte sur le nombre de noeuds des  graphes)
*/


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "fap.h"
#include "graphe.h"
#include "stdbool.h"


psommet_t chercher_sommet (pgraphe_t g, int label)
{
  psommet_t s ;

  s = g ;

  while ((s!= NULL) && (s->label != label))
    {
      s = s->sommet_suivant ;
    }
  return s ;
}

parc_t existence_arc (parc_t l, psommet_t s)
{
  parc_t p = l ;

  while (p != NULL)
    {
      if (p->dest == s)
	return p ;
      p = p->arc_suivant ;
    }
  return p ;
  
}


void ajouter_arc (psommet_t o, psommet_t d, int distance)
{
  parc_t parc ;

  parc = (parc_t) malloc (sizeof(arc_t)) ;

  if (existence_arc (o->liste_arcs, d) != NULL)
    {
      fprintf(stderr, "ajout d'un arc deja existant\n") ;
      exit (-1) ;
    }
  
  parc->poids = distance ;
  parc->dest = d ;
  parc->arc_suivant = o->liste_arcs ;
  o->liste_arcs = parc ;
  return ;
}



// ===================================================================

int nombre_sommets (pgraphe_t g)
{
  psommet_t p = g ;
  int nb = 0 ;

  while (p != NULL)
    {
      nb = nb + 1 ;
      p = p->sommet_suivant ;
    }

  return nb ;
}

int nombre_arcs (pgraphe_t g)
{

  psommet_t p = g ;
  int nb_arcs = 0 ;

  while (p != NULL)
    {
      parc_t l = p->liste_arcs ;

      while (l != NULL)
	{
          nb_arcs = nb_arcs + 1 ;
	  l = l->arc_suivant ;
	}
      
      p = p->sommet_suivant ;
    }
  return nb_arcs ;
}

void init_couleur_sommet (pgraphe_t g)
{
  psommet_t p = g ;

  while (p != NULL)
    {
      p->couleur = 0 ; // couleur indefinie
      p = p->sommet_suivant ; // passer au sommet suivant dans le graphe
    }
  
  return ;
}

int colorier_graphe (pgraphe_t g)
{
  /*
    coloriage du graphe g
    
    datasets
    graphe data/gr_planning
    graphe data/gr_sched1
    graphe data/gr_sched2
  */

  psommet_t p = g ;
  parc_t a ;
  int couleur ;
  int max_couleur = INT_MIN ; // -INFINI
  
  int change ;

  init_couleur_sommet (g) ;
  
  while (p != NULL)
    {
      couleur = 1 ; // 1 est la premiere couleur

      // Pour chaque sommet, on essaie de lui affecter la plus petite couleur

      // Choix de la couleur pour le sommet p
      
      do
	{
	  a = p->liste_arcs ;
	  change = 0 ;
      
	  while (a != NULL)
	    {
	      if (a->dest->couleur == couleur)
		{
		  couleur = couleur + 1 ;
		  change = 1 ;
		} 
	      a = a->arc_suivant ; 
	    }

	} while (change == 1) ;

      // couleur du sommet est differente des couleurs de tous les voisins
      
      p->couleur = couleur ;
      if (couleur > max_couleur)
	max_couleur = couleur ;

      p = p->sommet_suivant ;
    }
  
  return max_couleur ;
}

void afficher_graphe_largeur (pgraphe_t g, int r)
{
  /*
    afficher les sommets du graphe avec un parcours en largeur
  */
  
  return ;
}


void afficher_graphe_profondeur (pgraphe_t g, int r)
{
  /*
    afficher les sommets du graphe avec un parcours en profondeur
  */
  
  return ;
}

void initialiser_distance_racine(pgraphe_t graphe, int infini) {
    psommet_t sommet = graphe;
    while (sommet != NULL) {
        sommet->distance_racine = infini;
        sommet = sommet->sommet_suivant;
    }
}

void algo_dijkstra(pgraphe_t g, int r) {
    if (!g) 
        return;

    init_couleur_sommet(g);
    initialiser_distance_racine(g, INT_MAX); 

    fap file = creer_fap_vide(); 
    psommet_t sommet_depart = chercher_sommet(g, r); 
    if (!sommet_depart) 
        return;

    sommet_depart->distance_racine = 0;

    file = inserer(file, sommet_depart, sommet_depart->distance_racine); 

    while (!est_fap_vide(file)) { 
        int distance;
        psommet_t sommet_courant;
        file = extraire(file, (void **)&sommet_courant, &distance); 

        sommet_courant->couleur = 1; 

        for (parc_t arc = sommet_courant->liste_arcs; arc != NULL; arc = arc->arc_suivant) {
            
            if (arc->dest->couleur == 0 || arc->dest->distance_racine > distance + arc->poids) {
                arc->dest->couleur = 1; 
                arc->dest->distance_racine = distance + arc->poids; 
                file = inserer(file, arc->dest, arc->dest->distance_racine); 
            }
        }
    }
}

void afficher_dijkstra(pgraphe_t g) {
    bool aucun_chemin_trouve = true;
    for (psommet_t s = g; s != NULL; s = s->sommet_suivant) {
        if (s->distance_racine != INT_MAX) { 
            aucun_chemin_trouve = false; 
            printf("Le sommet %d est accessible à une distance de %d\n", s->label, s->distance_racine);
        }
    }
    if (aucun_chemin_trouve) { 
        printf("Aucun chemin trouvé dans le graphe.\n");
    }
}





// ======================================================================




int degre_sortant_sommet  (pgraphe_t g, psommet_t s) {
    int degre = 0;
    parc_t arc = s->liste_arcs;
    while (arc != NULL) {
        degre++; 
        arc = arc->arc_suivant; 
    }
    return degre; 
    }

int degre_entrant_sommet  (pgraphe_t g, psommet_t s) {
    int degre = 0;
    for (psommet_t sommet = g; sommet != NULL; sommet = sommet->sommet_suivant) {
        parc_t arc = sommet->liste_arcs;
        while (arc != NULL) {

            if (arc->dest == s) {
                degre++;
            }
            arc = arc->arc_suivant;
        }
    }

    return degre;
}


int degre_maximal_graphe  (pgraphe_t g) {
    int degre_maximal = 0; 

    for (psommet_t sommet = g; sommet != NULL; sommet = sommet->sommet_suivant) {
        int degre = degre_sortant_sommet(g, sommet);
        if (degre > degre_maximal) {
            degre_maximal = degre; 
        }
    }

    return degre_maximal;
}

int degre_minimal_graphe  (pgraphe_t g) {
    int degre_minimal = INT_MAX; 

    for (psommet_t sommet = g; sommet != NULL; sommet = sommet->sommet_suivant) {
        int degre = degre_sortant_sommet(g, sommet); 
        if (degre < degre_minimal) {
            degre_minimal = degre; 
        }
    }
    return degre_minimal;
}


int independant (pgraphe_t g)
{
    return degre_maximal_graphe(g) <= 1;// si c'est plus cad  que directement y'a des sommets en communs 
} 



int complet (pgraphe_t g) {
    for (psommet_t sommet1 = g; sommet1 != NULL; sommet1 = sommet1->sommet_suivant) {
        for (psommet_t sommet2 = sommet1->sommet_suivant; sommet2 != NULL; sommet2 = sommet2->sommet_suivant) {
            int a_relie = 0;
            for (parc_t arc = sommet1->liste_arcs; arc != NULL; arc = arc->arc_suivant) {
                if (arc->dest == sommet2) {
                    a_relie = 1;
                    break;
                }
            }
            if (!a_relie) {
                return 0;
            }
        }
    }
    return 1; 
}


int regulier(pgraphe_t g) {
    int degre = degre_sortant_sommet(g, g);

    for (psommet_t sommet = g->sommet_suivant; sommet != NULL; sommet = sommet->sommet_suivant) {
        if (degre_sortant_sommet(g, sommet) != degre) {
            return 0;
        }
    }
    return 1; 
}


int elementaire(pgraphe_t g, chemin_t c) {
    psommet_t sommet = chercher_sommet(g, c.permier_sommet->label);
    if (sommet == NULL) {
        printf("Le sommet initial n'existe pas dans le graphe.\n");
        return 0;
    }

    psommet_t sommet_precedent = NULL;
    for (parc_t arc = c.liste_arcs; arc != NULL; arc = arc->arc_suivant) {
        if (sommet_precedent != NULL && sommet_precedent == arc->dest) {
            printf("Le chemin n'est pas élémentaire. Il passe deux fois par le sommet %d.\n", arc->dest->label);
            return 0;
        }
        sommet_precedent = arc->dest;

        if (existence_arc(sommet->liste_arcs, arc->dest) == NULL) {
            printf("Le chemin n'est pas élémentaire. Il n'y a pas d'arc entre les sommets %d et %d.\n", sommet->label, arc->dest->label);
            return 0;
        }

        sommet = arc->dest;
    }

    return 1;
}



/*
  placer les fonctions de l'examen 2017 juste apres
*/
