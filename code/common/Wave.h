

#ifndef PROJET_WAVE_H
#define PROJET_WAVE_H

#include <vector>
#include "PNJ.hpp"


class Wave {

private:
    std::vector<PNJ> my_wave;

public:

    std::string serialize();

    Wave() = default; //not sure
    Wave(int nb_of_pnj);

};


#endif //PROJET_WAVE_H