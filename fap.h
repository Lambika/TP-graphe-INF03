#ifndef __FAP_H__
#define __FAP_H__

struct maillon;

typedef struct maillon *fap;

struct maillon {
    void* element;
    int priorite;
    fap prochain;
};

fap creer_fap_vide();


fap inserer(fap f, void* element, int priorite);

fap extraire(fap f, void* *element, int *priorite);


int est_fap_vide(fap f);


void detruire_fap(fap f);

#endif
