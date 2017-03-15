#ifndef PROJET_ABSTRACTUI_HPP
#define PROJET_ABSTRACTUI_HPP

#include <iostream>

class AbstractUI {
public:
    // Utile dans le cas terminal; reimplementé dans le cas GUI dans la classe AbstractGUI
    virtual void destroy() = 0;


    // NE PAS ENLEVER. FONDAMENTAL POUR ASSURER LA DESTRUCTION CORRECTE DES OBJETS;
    virtual ~AbstractUI() = default;
};


#endif //PROJET_ABSTRACTUI_HPP
