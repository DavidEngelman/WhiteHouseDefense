#ifndef PROJET_NETWORKING_H
#define PROJET_NETWORKING_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cstdlib>

int init_connection_to_server(char* server_ip_address, int port);
int create_socket();
int connect_to_server(int socket, int port, struct hostent *addr);

ssize_t receive_data(int socket_fd, void *message, int length);
char *get_data_from_socket(int socket_fd, char *buffer, int size);
int get_message_length(int socket_fd);
void ensure_buffer_is_big_enough(char *buffer, int length);
int receive_message(int socket_fd, char *buffer);
bool receive_message_with_timeout(int socket_fd, char *buffer, int timeout);

void send_data(int socket_fd, char *buffer, int length);
int send_message(int socket_fd, const char *message);

#endif //PROJET_NETWORKING_H
