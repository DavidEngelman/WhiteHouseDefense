#include "Networking.h"

// Receive

ssize_t receive_data(int socket_fd, void *message, size_t length) {
    return recv(socket_fd, message, length, 0);
}

char *get_data_from_socket(int socket_fd, char *buffer, size_t size) {
    ssize_t data_bytes_read = receive_data(socket_fd, buffer, size);

    if (data_bytes_read == -1) {
        perror("Receive: packet data");
        exit(EXIT_FAILURE);
    }

    return buffer;
}

size_t get_message_length(int socket_fd) {
    size_t length;
    ssize_t length_bytes_read = receive_data(socket_fd, &length, sizeof(length));

    if (length_bytes_read == -1) {
        perror("Receive: packet length");
        exit(EXIT_FAILURE);
    }
    return length * sizeof(char);
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
 * Read from the socket and puts the data in the buffer.
 * If the buffer is NULL, it creates a buffer of the appropriate size.
 * If the buffer is too small, it grows it to have enough space for the data.
 * Return value: a pointer to the buffer.
 */
char *receive_message(int socket_fd, char *buffer) {
    size_t length = get_message_length(socket_fd);  // Gets the length

//    ensure_buffer_is_big_enough(buffer, length);

    get_data_from_socket(socket_fd, buffer, length);  // Gets the data
    return buffer;
}

char *receive_message_with_timeout(int socket_fd, char *buffer, int timeout_val){
    fd_set set;
    struct timeval timeout;
    FD_ZERO(&set);
    FD_SET(socket_fd, &set);

    timeout.tv_sec = timeout_val;
    timeout.tv_usec = 0;
    int rv = select(socket_fd + 1, &set, NULL, NULL, &timeout);

    if (rv == -1){
        perror("select error");
        //TODO:Peut etre faire quelque chose d'autre je sais pas :D
    }
    else if (rv == 0){
        //timeout
        //Je sais pas trop quoi mettre là mais c'est la ou on gère le bordel
    }
    else{
        //receive the message
        return receive_message(socket_fd, buffer);
    }
}

// Send

void send_data(int socket_fd, char *buffer, int length){
    if (send(socket_fd, buffer, sizeof(length), 0) == - 1) {
        perror("Send");
    }
}

void send_message(int socket_fd, const char *message) {
    size_t length = strlen(message) + 1;
    send(socket_fd, &length, sizeof(length), 0); // Send the length
    send(socket_fd, message, length, 0);         // Send the data
    //TODO remmettre send_data mais y avait un probleme
}

