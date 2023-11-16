#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int main() {
    struct sockaddr_in sa;
    struct sockaddr_in cli;
    int sockfd, conntfd;
    char str[100];
    time_t tick;
    socklen_t clilen;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error in socket");
        exit(EXIT_FAILURE);
    } else {
        printf("Socket opened\n");
    }

    // Initialize sockaddr_in structure
    bzero(&sa, sizeof(sa));
    sa.sin_port = htons(5600);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind the socket
    if (bind(sockfd, (struct sockaddr*)&sa, sizeof(sa)) < 0) {
        perror("Error in binding");
        exit(EXIT_FAILURE);
    } else {
        printf("Binded Successfully\n");
    }

    // Listen for incoming connections
    listen(sockfd, 50);

    for (;;) {
        clilen = sizeof(cli);
        // Accept a connection
        conntfd = accept(sockfd, (struct sockaddr*)&cli , &clilen);
        if (conntfd < 0) {
            perror("Error in accepting connection");
            exit(EXIT_FAILURE);
        }

        printf("Accepted\n");

        // Get current time
        tick = time(NULL);
        snprintf(str, sizeof(str), "%s", ctime(&tick));
        printf("%s", str);

        // Send time to the client
        send(conntfd, str, strlen(str),0);

        // Close the connection
    }



    return 0;
}
