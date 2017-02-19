#ifndef PROJET_PLAYERCONNECTION_HPP
#define PROJET_PLAYERCONNECTION_HPP

class PlayerConnection{

private:
    int player_id;
    int socket_fd;

public:
    int getPlayer_id() const;

    int getSocket_fd() const;

    void setPlayer_id(int player_id);

    void setSocket_fd(int socket_fd);

    ~PlayerConnection();

    bool operator==(const PlayerConnection &rhs) const;

    bool operator!=(const PlayerConnection &rhs) const;
};

#endif