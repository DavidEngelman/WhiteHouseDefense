#ifndef PROJET_COMMAND_HPP
#define PROJET_COMMAND_HPP

#include <string>
#include "Message.hpp"

/*
 * Convention: pour les commandes simples, la fin du string de la commande est marqué par un ;.
 */
class Command: public Message {

protected:
    std::string action;
public:

    std::string getAction() const;

    Command();

    virtual int extractAction(char *data);
    virtual void parse(char* data);

    virtual ~Command()= default;
};


#endif //PROJET_COMMAND_HPP
