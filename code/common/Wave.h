

#ifndef PROJET_WAVE_H
#define PROJET_WAVE_H

#include "PNJ.hpp"


class Wave {

private:
    std::vector<PNJ> my_wave;

public:

    std::string serialize(std::string& str);

    Wave() = default; //not sure
    Wave(int nb_of_pnj);
    void remove_pnj(int pnj_id);



};


#endif //PROJET_WAVE_H