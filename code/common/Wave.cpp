#include "Wave.h"

Wave::Wave(int number_of_pnjs, int quadrant) :
        number_of_pnjs(number_of_pnjs), quadrant(quadrant), number_of_added_pnjs(0) {}



std::string Wave::serialize() {
    /*
     * fill a string like this : Wave,serialized(PNJ1),serialized(PNJ2),...;
     */

    std::string serialized_me;
    serialized_me += "Wave,";
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
    return quadrant;
}

bool Wave::isEmpty() { return pnjs.empty(); }

void Wave::removeDeadPNJs() {
    std::vector<PNJ>::iterator it;
    for (it = pnjs.begin(); it != pnjs.end();) {
        if ((*it).isDead()) {
            it = pnjs.erase(it);
        } else {
            it++;
        }
    }
}