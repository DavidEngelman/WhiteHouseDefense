#include "Networking.h"

// Receive

ssize_t receive(int socket_fd, void *message, size_t length) {
    return recv(socket_fd, message, length, 0);
}

char * get_data(int socket_fd, char *buffer, size_t size) {
    ssize_t data_bytes_read = receive(socket_fd, buffer, size);

    if (data_bytes_read == -1) {
        perror("Receive: packet data");
        exit(EXIT_FAILURE);
    }

    return buffer;
}

size_t get_message_length(int socket_fd) {
    size_t length;
    ssize_t length_bytes_read = receive(socket_fd, &length, sizeof(length));

    if (length_bytes_read == -1) {
        perror("Receive: packet length");
        exit(EXIT_FAILURE);
    }
    return length * sizeof(char);
}

/*
 * TODO: est-ce que receive_data et receive_new_data recoivent un buffer et l'utilise en espérant
 * qu'ils soit assez grand, ou font-t-il un malloc/realloc du buffer?
 */


/*
 * Read from the socket and puts the data in the buffer.
 * If the buffer is NULL, it creates a buffer of the appropriate size.
 * If the buffer is too small, it grows it to have enough space for the data.
 * Return value: a pointer to the buffer.
 */
char *receive_data(int socket_fd, char *buffer) {
    size_t length = get_message_length(socket_fd);
//    if (buffer == NULL){
//        buffer = malloc(length);
//    } else if (sizeof(buffer) < length) {
//        buffer = realloc(buffer, length);
//        if (buffer == NULL){
//            perror("Receive_data - Couldn't grow buffer");
//            exit(EXIT_FAILURE);
//        }
//    }
    get_data(socket_fd, buffer, length);
    return buffer;
}

char *receive_new_data(int socket_fd, char * buffer) {
    size_t length = get_message_length(socket_fd);

//    size_t size = min((int) length, MAX_SENTENCE_SIZE) * sizeof(char);
//    char *message = malloc(size);
    get_data(socket_fd, message, length);
    return message;
}


// Send

void send_data(int socket_fd, char *message) {
    size_t length = strlen(message) + 1;
    send(socket_fd, &length, sizeof(length), 0); // Send the length
    send(socket_fd, message, length, 0);         // Send the data
}