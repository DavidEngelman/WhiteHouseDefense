

#include "Wave.h"


Wave::Wave(int nb_of_pnj)  {
    //TODO initialisé le vecteur wave avec nb_of_pnj PNJ
}

void Wave::remove_pnj(int pnj_id) {
    /*Retire un pnj de la wave si il meurt*/
    wave.erase(pnj_id);
}