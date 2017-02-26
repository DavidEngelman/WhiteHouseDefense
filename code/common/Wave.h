#ifndef PROJET_WAVE_H
#define PROJET_WAVE_H

#include <vector>
#include "PNJ.hpp"

class PNJ;

class Wave {

private:
    std::vector<PNJ> pnjs;

    const int quadrant;
    int number_of_pnjs;
    int number_of_added_pnjs;
public:

    Wave(int number_of_pnjs, int quadrant);
    bool isEmpty();
    int getQuadrant() const;

    void setNumber_of_pnjs(int number_of_pnjs);

    int getNumber_of_pnjs() const;

    int getNumber_of_added_pnjs() const;

    std::vector<PNJ> &getPnjs();

    std::string serialize();

    void addPNJ();

    void removeDeadPNJs();
};


#endif //PROJET_WAVE_H