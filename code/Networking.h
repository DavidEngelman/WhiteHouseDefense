#ifndef PROJET_NETWORKING_H
#define PROJET_NETWORKING_H

ssize_t receive(int socket_fd, void *message, size_t length);
char * get_data(int socket_fd, char *buffer, size_t size);
size_t get_message_length(int socket_fd);
char *receive_data(int socket_fd, char *buffer);
char *receive_new_data(int socket_fd, char * buffer);


void send_data(int socket_fd, char *message);

#endif //PROJET_NETWORKING_H
