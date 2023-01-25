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


void send_file(FILE *fp, int sockfd){
  int n;
  char data[SIZE] = {0};
 
  while(fgets(data, SIZE, fp) != NULL) {
    fputs(data, stdout);
    if (send(sockfd, data, sizeof(data), 0) == -1) {
      perror("[-]Error in sending file.");
      exit(1);
    }
    bzero(data, SIZE);
  }
}

int main(int argc, char **argv)
{
    int sockfd, n;
    char buff[MAXLINE];

    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;
    int port;
    FILE *fp;
    char *filename="sendfile.txt";
    int val;
    if (argc != 3)
        printf("usage:a.out<IPaddress><port>");
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        printf("socket error");
    port = atoi(argv[2]);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
        printf("inet_pton error for %s", argv[1]);

    val = connect(sockfd, (SA *)&servaddr, sizeof(servaddr));
    printf("value= %d \n", val);
    fp=fopen(filename,"r");
    if(fp==NULL){
        perror("[-] Error in reading file");
        exit(1);
    }
    send_file(fp,sockfd);
    printf("Data Successfully sent");

    close(sockfd);
    exit(0);
}