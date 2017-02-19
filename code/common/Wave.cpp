#include "Wave.h"

Wave::Wave(int nb_of_pnj)  : my_wave(nb_of_pnj){}

void Wave::remove_pnj(int pnj_id) {
    /*Retire un pnj de la wave si il meurt*/
    my_wave.erase(pnj_id);
}

std::string Wave::serialize() {
    /*
     * fill a string like this : Wave,serialized(PNJ1),serialized(PNJ2),...;
     */

    std::string serialized_me;
    serialized_me += "Wave,";
    for (PNJ pnj: my_wave){
        serialized_pnj = pnj.serialize();
        str += serialized_pnj;
    }
    str += ";";

    return str;
}