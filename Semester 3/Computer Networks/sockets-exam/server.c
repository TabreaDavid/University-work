#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define TCP_PORT 8008
#define UDP_PORT 9009

void *udp_broadcast_server_thread(void *arg) {
    (void)arg;
    int udp_socket;
    struct sockaddr_in server, client;
    char recv_buf[1024];
    socklen_t client_len;

    udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_socket == -1) {
        perror("[UDP Thread] socket");
        return NULL;
    }

    int broadcast = 1;
    if (setsockopt(udp_socket, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0) {
        perror("[UDP Thread] setsockopt SO_BROADCAST");
        close(udp_socket);
        return NULL;
    }

    printf("[UDP Thread] Broadcast enabled on UDP socket\n");

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(UDP_PORT);

    if (bind(udp_socket, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("[UDP Thread] bind");
        close(udp_socket);
        return NULL;
    }

    printf("[UDP Thread] UDP broadcast server listening on port %d...\n", UDP_PORT);

    while (1) {
        client_len = sizeof(client);
        ssize_t res = recvfrom(udp_socket, recv_buf, sizeof(recv_buf), 0, 
                               (struct sockaddr *) &client, &client_len);

        if (res < 0) {
            perror("[UDP Thread] recvfrom");
            continue;
        }

        recv_buf[res] = '\0';
        printf("[UDP Thread] Received broadcast from %s: %s\n", 
               inet_ntoa(client.sin_addr), recv_buf);

        const char *response = "Broadcast message received by server";
        if (sendto(udp_socket, response, strlen(response), 0, 
                   (struct sockaddr *) &client, client_len) < 0) {
            perror("[UDP Thread] sendto");
        }
    }

    close(udp_socket);
    return NULL;
}

int main() {
    pthread_t udp_thread_id;
    fd_set master;
    fd_set read_fds;
    int fdmax;
    int newfd;
    int listener_fd;
    char buf[1024];
    struct sockaddr_in client_addr, server_addr;
    socklen_t client_len;

    printf("[Main] Creating UDP broadcast server thread...\n");
    if (pthread_create(&udp_thread_id, NULL, udp_broadcast_server_thread, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }
    printf("[Main] UDP broadcast thread created. Starting TCP server...\n");

    listener_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listener_fd == -1) {
        perror("socket");
        exit(1);
    }

    int opt = 1;
    if (setsockopt(listener_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        close(listener_fd);
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(TCP_PORT);

    if (bind(listener_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(listener_fd);
        exit(1);
    }

    if (listen(listener_fd, 15) < 0) {
        perror("listen");
        close(listener_fd);
        exit(1);
    }

    printf("[Main] TCP server listening on port %d...\n", TCP_PORT);


    FD_ZERO(&master);
    FD_ZERO(&read_fds);
    FD_SET(listener_fd, &master);
    fdmax = listener_fd;
    
    while (1) {
        read_fds = master;
        
        if (select(fdmax + 1, &read_fds, NULL, NULL, NULL) == -1) {
            perror("select");
            close(listener_fd);
            exit(1);
        }

        for (int i = 0; i <= fdmax; i++) {
            if (FD_ISSET(i, &read_fds)) {
                if (i == listener_fd) {
                    client_len = sizeof(client_addr);
                    newfd = accept(listener_fd, (struct sockaddr *) &client_addr, &client_len);
                    if (newfd == -1) {
                        perror("accept");
                        continue;
                    }
                    FD_SET(newfd, &master);
                    if (newfd > fdmax)
                        fdmax = newfd;
                    printf("[Main TCP] New connection from %s on socket %d\n",
                           inet_ntoa(client_addr.sin_addr), newfd);
                } else {
                    int res = recv(i, buf, sizeof(buf), 0);
                    if (res <= 0) {
                        if (res == 0) {
                            printf("[Main TCP] Connection closed on socket %d\n", i);
                        } else {
                            perror("recv");
                        }
                        
                        close(i);
                        FD_CLR(i, &master);
                    } else {
                        buf[res] = '\0';
                        printf("[Main TCP] Received from socket %d: %s\n", i, buf);
                        
                        const char *response = "TCP message received";
                        if (send(i, response, strlen(response), 0) < 0) {
                            perror("send");
                        }
                    }
                }
            }
        }
    }

    pthread_join(udp_thread_id, NULL);
    close(listener_fd);
    return 0;
}
