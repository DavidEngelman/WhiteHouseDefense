#include "Server.hpp"

Server::Server(int portNumber) : socket_fd(0), port(portNumber) {
    init();
    std::cout << "server created with success!" << std::endl;
}

void Server::init() {
    struct sockaddr_in my_address;

    socket_fd = create_socket();

    my_address = build_address();
    struct sockaddr *address = (struct sockaddr *) &my_address;

    bind_socket_to_address(address);
}

void Server::bind_socket_to_address(struct sockaddr *address) {
    int result = bind(socket_fd, address, sizeof(struct sockaddr));
    if (result == -1) {
        perror("Bind");
        exit(EXIT_FAILURE);
    }
}

int Server::create_socket() {
    int socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_descriptor == -1) {
        perror("Error during socket creation");
        exit(1);
    }

//  Permet de reutiliser l'addresse
    int yes = 1;
    setsockopt(socket_descriptor, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

    return socket_descriptor;
}

/*
 * Accepts a new connection and returns the new socket descriptor (or -1 if there is an error).
 */
int Server::accept_connection() {
    struct sockaddr_in client_addr;
    socklen_t sin_size = sizeof(struct sockaddr_in);

    int new_socket = accept(socket_fd, (struct sockaddr *) &client_addr, &sin_size);
    if (new_socket == -1) {
        perror("Accept: ");
    }
    return new_socket;
}

//void Server::add_new_client(int his_socket) {
//    client_sockets.push_back(his_socket);
//}

struct sockaddr_in Server::build_address() {
    struct sockaddr_in my_address;
    my_address.sin_family = AF_INET;
    my_address.sin_port = htons((uint16_t) port);
    my_address.sin_addr.s_addr = INADDR_ANY;

    // On met sin_zero à 0
    memset(&(my_address.sin_zero), 0, 8);
    return my_address;
}


void Server::start_socket_listen() {
    int error_code = listen(socket_fd, BACKLOG);
    if (error_code == -1) {
        perror("Listen");
        exit(1);
    }

    //Cette méthode est pas appellée dans le init comme ça on peut créer un server sans commencer directement
    //a listen, je sais pas si c'est une bonne idée ou pas -_-

    // On peut laisser ça comme ça pour l'instant, sinon on fait un appel à start_socket_listen
    // à la fin du constructeur si on se rend compte que c'est une bonne idée
}

/*
* Takes in a list of sockets, waits until one is readable, then returns the
* index of the readable socket in the array.
*/
int Server::get_readable_socket_index(int *sockets, int num_sockets) {
    fd_set read_socket_fds;
    FD_ZERO(&read_socket_fds);

    int max = sockets[0];
    for (int i = 0; i < num_sockets; ++i) {
        int socket_fd = sockets[i];
        FD_SET(socket_fd, &read_socket_fds);
        max = (max < socket_fd ? socket_fd : max);
    }

    int error_code = select(max + 1, &read_socket_fds, NULL, NULL, NULL);
    std::cout << "The error code from select is : " << error_code << std::endl;

    int socket_num = 0;
    while (!FD_ISSET(sockets[socket_num], &read_socket_fds)) {
        socket_num++;
    }
    return socket_num;
}

int Server::get_readable_socket_index_with_timeout(int *sockets, int num_sockets, int timeout_val){
    struct timeval timeout;
    timeout.tv_sec = timeout_val;
    timeout.tv_usec = 0;

    fd_set read_socket_fds;
    FD_ZERO(&read_socket_fds);

    int max = sockets[0];
    for (int i = 0; i < num_sockets; ++i) {
        int socket_fd = sockets[i];
        FD_SET(socket_fd, &read_socket_fds);
        max = (max < socket_fd ? socket_fd : max);
    }

    int num_readable_sockets = select(max + 1, &read_socket_fds, NULL, NULL, &timeout);
    std::cout << "num_readable_socket: "<<num_readable_sockets << std::endl;

    if (num_readable_sockets == 0) return -1;

    int socket_num = 0;
    while (!FD_ISSET(sockets[socket_num], &read_socket_fds)) {
        socket_num++;
    }
    std::cout << "after while"<< std::endl;
    return socket_num;
}


std::string Server::get_command_type(char* data){

    /*
     * Determine le type de commande (login/register, ranking, profile,...)
     */

    int i = 0;
    std::string command_type;


    while ((data[i] != ',') && (data[i] != ';')) { // comme ça une commande peut etre juste par ex: "ranking;"
        command_type += data[i];                        // au lieu de "ranking," c'est un peu plus clean
        i++;
    }

    return command_type;

}

Server::~Server() {
    close(socket_fd);
}

int Server::getPort() const {
    return port;
}
