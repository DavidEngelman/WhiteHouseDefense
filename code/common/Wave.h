

#ifndef PROJET_WAVE_H
#define PROJET_WAVE_H

#include <vector>
#include "PNJ.hpp"


class Wave {

private:
    std::vector<PNJ> pnjs;
    int quandrant;
public:
    int getQuadrant() const;

    std::string serialize();

    Wave() = default; //not sure
    Wave(int nb_of_pnj);

    std::vector<PNJ> &getPnjs();
};


#endif //PROJET_WAVE_H