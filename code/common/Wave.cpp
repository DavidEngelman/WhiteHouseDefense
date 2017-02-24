#include "Wave.h"

Wave::Wave(int number_of_pnjs)  : number_of_pnjs(number_of_pnjs), number_of_added_pnjs(0) {}



std::string Wave::serialize() {
    /*
     * fill a string like this : Wave,quandrant,x,y,heathpoints,x,y,healthpoints,....;
     */

    std::string serialized_me;
    serialized_me += "Wave," + std::to_string(quandrant);
    for (PNJ& pnj: pnjs){
        std::string serialized_pnj = pnj.serialize();
        serialized_me += serialized_pnj;
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
