#ifndef PROJET_COMMAND_HPP
#define PROJET_COMMAND_HPP

#include <string>

class Command {

protected:

    std::string action;


public:

    std::string getAction() const;
    Command() = default;

    virtual int extract_action(char* data);

    virtual void parse(char* data);

    virtual ~Command()= default;



};


#endif //PROJET_COMMAND_HPP
