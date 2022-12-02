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
typedef struct sockaddr SA;

int main(int argc, char **argv)
{
    char chat[100];
    int listenfd, connfd, n;
    struct sockaddr_in servaddr, clientaddr;
    char buff[MAXLINE];
    char recvline[MAXLINE + 1];
    time_t ticks;
    socklen_t len;
    int port;

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

    for (;;)
    {
        // connfd = accept(listenfd,(SA*)NULL,NULL)'
        // printf("Client connected");
        len = sizeof(clientaddr);
        connfd = accept(listenfd, (SA *)&clientaddr, &len);
        printf("Connection from %s, port %d\n", inet_ntop(AF_INET, &clientaddr.sin_addr, buff, sizeof(buff)), ntohs(clientaddr.sin_port));
        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        write(connfd, buff, strlen(buff));
        if (n = read(connfd, recvline, MAXLINE))
        {
            recvline[n] = 0;
            printf("Client: ");
            if (fputs(recvline, stdout) == EOF)
                printf("fputs error");
            snprintf(buff, sizeof(buff), "%.24s\r\n", recvline);
            // printf("Char is %ld", strlen(buff));
            fflush(stdout);

            write(connfd, buff, strlen(buff));
        }
        printf("Enter a message for client: ");
        fgets(chat, 100, stdin);
        printf("Server: %s", chat);
        write(connfd,chat,strlen(chat));
        close(connfd);
    }
}
