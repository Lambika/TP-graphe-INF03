#include <stdio.h>
#include <stdlib.h>
#include "file.h"


File *creer_file(psommet_t sommet) {
    File *nouveau = (File *)malloc(sizeof(File));
    if (nouveau == NULL) {
        fprintf(stderr, "Erreur : Impossible de créer une nouvelle file\n");
        exit(EXIT_FAILURE);
    }
    nouveau->sommet = sommet;
    nouveau->suivant = NULL;
    return nouveau;
}

void enfiler(File **file, psommet_t sommet) {
    File *nouveau = creer_file(sommet);
    if (*file == NULL) {
        *file = nouveau;
    } else {
        File *tmp = *file;
        while (tmp->suivant != NULL) {
            tmp = tmp->suivant;
        }
        tmp->suivant = nouveau;
    }
}

psommet_t defiler(File **file) {
    if (*file == NULL) {
        fprintf(stderr, "Erreur : Tentative de défiler une file vide\n");
        exit(EXIT_FAILURE);
    }
    File *tmp = *file;
    psommet_t sommet = tmp->sommet;
    *file = (*file)->suivant;
    free(tmp);
    return sommet;
}

int est_vide(File *file) {
    return (file == NULL);
}