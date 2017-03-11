#ifndef PROJET_MESSAGE_HPP
#define PROJET_MESSAGE_HPP

#include <string>

/*
 * Convention: pour les commandes simples, la fin du string de la commande est marqué par un ;.
 */
class Message {
protected:
    char *buffer;
    bool _hasReachedEnd;
    int currentPosInBuffer;
public:
    Message();

    virtual std::string getNextToken();

    virtual bool hasReachedEnd();

    virtual void setData(char *data);

    virtual ~Message() = default;


};


#endif //PROJET_MESSAGE_HPP
