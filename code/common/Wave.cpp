#include "Wave.h"

Wave::Wave(int nb_of_pnj)  : pnjs(nb_of_pnj){}



std::string Wave::serialize() {
    /*
     * fill a string like this : Wave,serialized(PNJ1),serialized(PNJ2),...;
     */

    std::string serialized_me;
    serialized_me += "Wave,";
    for (PNJ& pnj: pnjs){

        //TODO:Pnj.serialize()
        //std::string serialized_pnj = pnj.serialize();
        //serialized_me += serialized_pnj;
    }
    serialized_me += ";";

    return serialized_me;
}

std::vector<PNJ> &Wave::getPnjs(){
    return pnjs;
}

int Wave::getQuadrant() const {
    return quandrant;
}
