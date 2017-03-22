
#include "../pnj/MexicanPNJ.h"
#include "../pnj/MuslimPNJ.h"
#include "../pnj/CommunistPNJ.h"

Wave::Wave(int number_of_pnjs, int quadrant) :
        number_of_pnjs(number_of_pnjs),
        quadrant(quadrant),
        number_of_added_pnjs(0) {}


Wave::Wave(int quadrant) : Wave(0, quadrant) {}

std::string Wave::serialize() {
    /*
     * fill a string like this : Wave,quadrant,serialized(PNJ1),serialized(PNJ2),...;
     */

    std::string serialized_me;
    serialized_me += "Wave," + std::to_string(quadrant) + "|";
    for (auto pnj: pnjs) {

        std::string serialized_pnj = pnj->serialize();
        serialized_me += serialized_pnj;
    }
    serialized_me += ";";

    return serialized_me;
}

std::vector<PNJ *> &Wave::getPnjs() {
    return pnjs;
}

int Wave::getQuadrant() const {
    return quadrant;
}

bool Wave::isComplete() { return number_of_added_pnjs == number_of_pnjs && pnjs.empty(); }

void Wave::removeDeadPNJs() {
    std::vector<PNJ *>::iterator it;
    for (it = pnjs.begin(); it != pnjs.end();) {
        if ((*it)->isDead()) {
            it = pnjs.erase(it);
        } else {
            it++;
        }
    }
}

int Wave::getNumber_of_pnjs() const {
    return number_of_pnjs;
}

int Wave::getNumber_of_added_pnjs() const {
    return number_of_added_pnjs;
}

void Wave::addPNJ(int typeOfPnj) {
    PNJ *pnj;
    if (typeOfPnj == 0) {
        pnj = new MexicanPNJ(quadrant);
    } else if (typeOfPnj == 1) {
        pnj = new MuslimPNJ(quadrant);
    } else {
        pnj = new CommunistPNJ(quadrant);
    }
    pnjs.push_back(pnj);
    number_of_added_pnjs += 1;
}

void Wave::addPNJ(PNJ &pnj) {
    pnjs.push_back(&pnj);
    number_of_added_pnjs += 1;
}

Wave::~Wave() {
    /*
    for (auto pnj: pnjs) {
        delete pnj;
    }
     */
}

void Wave::freeze() {
    for (auto &&pnj : pnjs) {
        pnj->freeze();
    }
}
