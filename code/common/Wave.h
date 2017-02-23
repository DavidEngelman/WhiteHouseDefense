

#ifndef PROJET_WAVE_H
#define PROJET_WAVE_H

#include <vector>
#include "PNJ.hpp"


class Wave {

private:
    std::vector<PNJ> my_pnjs;
    int id;

public:
    int getId() const;

    std::string serialize();

    Wave() = default; //not sure
    Wave(int nb_of_pnj);

    std::vector<PNJ> &getMy_pnjs();
};


#endif //PROJET_WAVE_H