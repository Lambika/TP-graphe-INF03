#include "fap.h"
#include <stdlib.h>
#include <stdbool.h>

fap creer_fap_vide() { 
    return NULL; 
}

fap inserer(fap f, void* element, int priorite) {
    fap nouveau = (fap)malloc(sizeof(struct maillon)); 
    nouveau->element = element; 
    nouveau->priorite = priorite; 
    nouveau->prochain = NULL; 

    if (f == NULL) { 
        return nouveau; 
    } else { 
        fap courant = f;
        fap precedent = NULL;

        while (courant != NULL && priorite >= courant->priorite) {
            precedent = courant;
            courant = courant->prochain;
        }

        if (precedent == NULL) { 
            nouveau->prochain = f;
            return nouveau;
        } else { 
            precedent->prochain = nouveau;
            nouveau->prochain = courant;
            return f;
        }
    }
}

fap extraire(fap f, void **element, int *priorite) {
    if (f == NULL) {
        *element = NULL;
        return NULL;
    }

    fap extrait = f;
    *element = extrait->element; 
    *priorite = extrait->priorite;

    f = f->prochain;
    free(extrait);
    return f;
}


int est_fap_vide(fap f) {
    return f == NULL; 
}

void detruire_fap(fap f) {
    while (!est_fap_vide(f)) { 
        void* element;
        int priorite;
        f = extraire(f, &element, &priorite);
    }
}
