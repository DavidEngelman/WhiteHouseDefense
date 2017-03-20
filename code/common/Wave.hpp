#ifndef PROJET_WAVE_H
#define PROJET_WAVE_H

#include <vector>
#include "PNJ.hpp"

class PNJ;

class Wave {

private:
    std::vector<PNJ> pnjs;

    int quadrant;
    int number_of_pnjs;
    int number_of_added_pnjs;
public:

    Wave(int quadrant); // Version client
    Wave(int number_of_pnjs, int quadrant);

    bool isComplete();
    int getQuadrant() const;

    void setNumber_of_pnjs(int number_of_pnjs);

    int getNumber_of_pnjs() const;

    int getNumber_of_added_pnjs() const;

    std::vector<PNJ> &getPnjs();

    std::string serialize();

    void addPNJ();
    void addPNJ(PNJ &pnj);

    void removeDeadPNJs();
};


#endif //PROJET_WAVE_H