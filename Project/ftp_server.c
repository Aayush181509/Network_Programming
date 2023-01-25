#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

#define MAXLINE 1024
#define LISTENQ 10
#define SIZE 1024
typedef struct sockaddr SA;

void write_file(int sockfd)
{
    int n;
    FILE *fp;
    char *filename = "recv.txt";
    char buffer[SIZE];

    fp = fopen(filename, "w");
    while (1)
    {
        n = recv(sockfd, buffer, SIZE, 0);
        if (n <= 0)
        {
            break;
            return;
        }
        fputs(buffer, stdout);
        fprintf(fp, "%s",buffer);
        bzero(buffer, SIZE);
    }
    return;
}

int main(int argc, char **argv)
{
    int listenfd, connfd;
    struct sockaddr_in servaddr, clientaddr;
    char recvline[MAXLINE + 1];

    char buff[MAXLINE];
    time_t ticks;
    socklen_t len;
    int port, n;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("The Value of listenfd is: %d\n", listenfd);
    port = atoi(argv[1]);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port); /* day time server*/

    bind(listenfd, (SA *)&servaddr, sizeof(servaddr));
    printf("Server is waiting connection at port %d\n", port);
    listen(listenfd, LISTENQ);

    printf(" New Connection Establishment :");
    // connfd = accept(listenfd,(SA*)NULL,NULL)'
    // printf("Client connected");
    len = sizeof(clientaddr);
    connfd = accept(listenfd, (SA *)&clientaddr, &len);
    printf("Connection from %s, port %d\n", inet_ntop(AF_INET, &clientaddr.sin_addr, buff, sizeof(buff)), ntohs(clientaddr.sin_port));
    write_file(connfd);
    return 0;
}