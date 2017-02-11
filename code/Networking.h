#ifndef PROJET_NETWORKING_H
#define PROJET_NETWORKING_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cstdlib>


ssize_t receive_data(int socket_fd, void *message, size_t length);
char *get_data_from_socket(int socket_fd, char *buffer, size_t size);
size_t get_message_length(int socket_fd);
void ensure_buffer_is_big_enough(char *buffer, int length);
char *receive_message(int socket_fd, char *buffer);


void send_data(int socket_fd, char *buffer, int length);
void send_message(int socket_fd, char *message);

#endif //PROJET_NETWORKING_H
