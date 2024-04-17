#ifndef FILE_H
#define FILE_H

#include "graphe.h" 

typedef struct file {
    psommet_t sommet;
    struct file *suivant;
} File;

File *creer_file(psommet_t sommet);
void enfiler(File **file, psommet_t sommet);
psommet_t defiler(File **file);
int est_vide(File *file);

#endif
