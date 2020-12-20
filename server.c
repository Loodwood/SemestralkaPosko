#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int sockfd, newsockfd;
    socklen_t cli_len;
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    char buffer[256];

    //skontrolujeme si ci mame dost argumentov
    if (argc < 2)
    {
        fprintf(stderr,"usage %s port\n", argv[0]);
        return 1;
    }
// vynulujeme si a inicializujeme si sietovu adresu
    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(atoi(argv[1]));

    // vytvorenie TCP/iP socketu
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Error creating socket");
        return 1;
    }

    // priradime sietovu adresu nasmu socketu pre spojenie
    if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Error binding socket address");
        return 2;
    }

    //socket pripravime na pocuvanie sprav od klientov dlzka fronty je 5 max
    listen(sockfd, 5);

    cli_len = sizeof(cli_addr);

    // pockame na nadviazanie spojenia s klientom
    newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &cli_len);
    if (newsockfd < 0)
    {
        perror("ERROR on accept");
        return 3;
    }

    // vynuluejeme buffer pred ziskanim spravy
    bzero(buffer,256);
    // nacita spravu co dostal cez socket do buffra ju dame
    n = read(newsockfd, buffer, 255);
    if (n < 0)
    {
        perror("Error reading from socket");
        return 4;
    }
    printf("Here is the message: %s\n", buffer);

    const char* msg = "I got your message";
    //vypiseme ked sme prijali spravu nejaku odozvu zo servera, odpoved
    n = write(newsockfd, msg, strlen(msg)+1);
    if (n < 0)
    {
        perror("Error writing to socket");
        return 5;
    }

    close(newsockfd);
    close(sockfd);

    return 0;
}