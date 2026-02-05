#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>

#define UDP_PORT 9009
#define TCP_PORT 8008
#define LOCALHOST "127.0.0.1"
#define BRODCAST "255.255.255.255"

void* udp_broadcast_sender_thread(void* args) {
    (void)args;
    int udp_socket;
    struct sockaddr_in serverAddr, fromAddr;
    char recv_buffer[1024];
    socklen_t fromSize;

    udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_socket == -1) {
        perror("[UDP Thread] socket");
        exit(1);
    }

    int broadcast = 1;
    if (setsockopt(udp_socket, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0) {
        perror("[UDP Thread] setsockopt SO_BROADCAST");
        close(udp_socket);
        exit(1);
    }

    printf("[UDP Thread] Broadcast enabled on UDP socket\n");

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(UDP_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(LOCALHOST);

    printf("[UDP Thread] UDP broadcast sender thread started\n");

    while (1) {
        const char *message = "UDP broadcast message from client";
        

        if (sendto(udp_socket, message, strlen(message), 0,
                   (const struct sockaddr*) &serverAddr, sizeof(serverAddr)) < 0) {
            perror("[UDP Thread] sendto");
            continue;
        }

        printf("[UDP Thread] Sent UDP broadcast message\n");


        fromSize = sizeof(fromAddr);
        int recvSize = recvfrom(udp_socket, recv_buffer, sizeof(recv_buffer), 0,
                                (struct sockaddr*) &fromAddr, &fromSize);
        if (recvSize > 0) {
            recv_buffer[recvSize] = '\0';
            printf("[UDP Thread] Received response: %s\n", recv_buffer);
        }

        sleep(5); 
    }

    close(udp_socket);
    return NULL;
}

int main() {
    pthread_t udp_thread_id;
    int tcp_socket;
    struct sockaddr_in serverAddr;
    char command[256];
    char messageRec[1024];

    printf("[Main] Creating UDP broadcast sender thread...\n");
    if (pthread_create(&udp_thread_id, NULL, udp_broadcast_sender_thread, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }
    printf("[Main] UDP broadcast thread created. Starting TCP client...\n");

    tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_socket == -1) {
        perror("[Main TCP] socket");
        exit(1);
    }


    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(TCP_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(LOCALHOST);

    if (connect(tcp_socket, (const struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("[Main TCP] connect");
        exit(1);
    }

    printf("[Main TCP] Connected to TCP server on port %d\n", TCP_PORT);
    printf("[Main TCP] Type messages to send (type 'exit' to quit):\n");


    while (1) {
        printf("> ");
        if (fgets(command, 256, stdin) == NULL) {
            printf("Error reading input\n");
            continue;
        }

        command[strcspn(command, "\n")] = 0;


        if (send(tcp_socket, command, strlen(command), 0) < 0) {
            perror("[Main TCP] send");
            break;
        }


        int recSize = recv(tcp_socket, messageRec, sizeof(messageRec), 0);
        if (recSize <= 0) {
            printf("[Main TCP] Server closed connection\n");
            break;
        }
        messageRec[recSize] = '\0';
        printf("[Main TCP] Server response: %s\n", messageRec);
    }

    pthread_join(udp_thread_id, NULL);
    close(tcp_socket);
    return 0;
}
