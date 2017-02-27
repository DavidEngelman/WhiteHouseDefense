#include <iostream>
#include "Networking.h"

// Receive

ssize_t receive_data(int socket_fd, void *message, int length) {
    return recv(socket_fd, message, (size_t) length, 0);
}

char *get_data_from_socket(int socket_fd, char *buffer, int size) {
    ssize_t data_bytes_read = receive_data(socket_fd, buffer, size);

    if (data_bytes_read == -1) {
        perror("Receive: packet data");
        exit(EXIT_FAILURE);
    }

    return buffer;
}

int get_message_length(int socket_fd) {
    /*
     * Tries to get the length of the message
     * If can't read from the socket, throws an error
     * If the socket is closed, returns -1
     * Otherwise, returns the length of the message
     * */
    size_t length;
    ssize_t length_bytes_read = receive_data(socket_fd, &length, sizeof(length));

    if (length_bytes_read == -1) {
        perror("Receive: packet length");
        exit(EXIT_FAILURE);
    } else if (length_bytes_read == 0){
        // Le client a fermé le socket
        return -1;
    }
    return (int) (length * sizeof(char));
}

/* TODO: y avait un probleme avec cette methode, je l ai mis en comm pour le moment
void ensure_buffer_is_big_enough(char *buffer, int length) {
    if (buffer == NULL) {
        buffer = malloc(length);
    } else if (sizeof(buffer) < length) {
        buffer = realloc(buffer, length);
        if (buffer == NULL) {
            perror("Receive_data - Couldn't grow buffer");
            exit(EXIT_FAILURE);
        }
    }
}
*/


/*
 * TODO: est-ce que receive_data et receive_new_data recoivent un buffer et l'utilise en espérant
 * qu'il soit assez grand, ou font-t-il un malloc/realloc du buffer?
 */

/*
 * Reads from the socket and puts the result in the buffer.
 * If the socket is closed, doesn't modify the buffer and returns -1.
 * Otherwise, puts the message in the buffer and return the length of the message.
 */
int receive_message(int socket_fd, char *buffer) {
    int length = get_message_length(socket_fd);  // Gets the length
    if (length == -1){ // Socket fermé
        std::cout << "Le socket " << socket_fd << " est fermé " << std::endl;
        return -1;
    }

//    ensure_buffer_is_big_enough(buffer, length);

    get_data_from_socket(socket_fd, buffer, length);  // Gets the data
    return length;
}

/*
 * Tries to receive from the socket, but stops after a timeout.
 * Returns True if the read was succesful.
 * Returns False otherwise.
 */
bool receive_message_with_timeout(int socket_fd, char *buffer, int timeout_val){
    fd_set set;
    struct timeval timeout;
    FD_ZERO(&set);
    FD_SET(socket_fd, &set);

    timeout.tv_sec = timeout_val;
    timeout.tv_usec = 0;

    bool success = false;

    int num_ready_descriptors = select(socket_fd + 1, &set, NULL, NULL, &timeout);
    if (num_ready_descriptors > 0){  // There is a readable socket
        int num_bytes_read = receive_message(socket_fd, buffer);

        if (num_bytes_read > 0){
            success = true;
        }
    }
    return success;
}

// Send

void send_data(int socket_fd, char *buffer, int length){
    if (send(socket_fd, buffer, sizeof(length), 0) == - 1) {
        perror("Send");
    }
}

void send_message(int socket_fd, const char *message) {
    size_t length = strlen(message) + 1;
    std::cout << "Sending message of size (including \\0) of " << length << " bytes" << std::endl;
    std::cout << "Message: " << message << std::endl;
    send(socket_fd, &length, sizeof(length), 0); // Send the length
    send(socket_fd, message, length, 0);         // Send the data
    //TODO remmettre send_data mais y avait un probleme
}

