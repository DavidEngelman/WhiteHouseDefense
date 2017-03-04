#ifndef PROJET_COMMAND_HPP
#define PROJET_COMMAND_HPP

#include <string>

/*
 * Convention: pour les commandes simples, la fin du string de la commande est marqué par un ;.
 */
class Command {

protected:

    std::string action;
    char * buffer;
    bool _hasReachedEnd;
    int currentPosInBuffer;


public:

    std::string getAction() const;
    Command();

    virtual int extract_action(char* data);

    virtual void parse(char* data);

    std::string getNextToken();
    bool hasReachedEnd();

    virtual ~Command()= default;


    void setData(char *data);
};


#endif //PROJET_COMMAND_HPP
