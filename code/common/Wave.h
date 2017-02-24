#ifndef PROJET_WAVE_H
#define PROJET_WAVE_H

#include <vector>
#include "PNJ.hpp"


class Wave {

private:
    std::vector<PNJ> pnjs;
    int quandrant;
    int number_of_pnjs;
    int number_of_added_pnjs;
public:
    int getQuadrant() const;

    bool isEmpty();

    std::string serialize();

    Wave(int nb_of_pnj);

    std::vector<PNJ> &getPnjs();
};


#endif //PROJET_WAVE_H