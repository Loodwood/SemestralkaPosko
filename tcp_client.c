//
// Created by janho on 20.12.2020.
//
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    //
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent* server;

    char buffer[256];

    if (argc < 3)
    {
        fprintf(stderr,"usage %s hostname port\n", argv[0]);
        return 1;
    }

    server = gethostbyname(argv[1]); //Použijeme funkciu gethostbyname na získanie informácii o počítači, ktorého hostname je v prvom argumente.
    if (server == NULL)
    {
        fprintf(stderr, "Error, no such host\n");
        return 2;
    }

    bzero((char*)&serv_addr, sizeof(serv_addr));
//Vynulujeme a zinicializujeme adresu, na ktorú sa budeme pripájať.
    serv_addr.sin_family = AF_INET;
    bcopy(
            (char*)server->h_addr,
            (char*)&serv_addr.sin_addr.s_addr,
            server->h_length
    );
    serv_addr.sin_port = htons(atoi(argv[2]));

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    //Vytvoríme si socket v doméne
    if (sockfd < 0)
    {
        perror("Error creating socket");
        return 3;
    }
 //Pripojíme sa na zadanú sieťovú adresu
    if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Error connecting to socket");
        return 4;
    }

    printf("Please enter a message: "); //Vyzveme používateľa aby zadal text správy pre server
    bzero(buffer,256);
    fgets(buffer, 255, stdin);//Načítame správu od používateľa zo štandardného vstupu do buffra.

    n = write(sockfd, buffer, strlen(buffer));//Pošleme správu cez socket servru.
    if (n < 0)
    {
        perror("Error writing to socket");
        return 5;
    }

    bzero(buffer,256);
    n = read(sockfd, buffer, 255);//Načítame odpoveď od servra do buffra.
    if (n < 0)
    {
        perror("Error reading from socket");
        return 6;
    }

    printf("%s\n",buffer);//Vypíšeme odpoveď z buffra na štandardný výstup.
    close(sockfd);

    return 0;
}


#include<stdio.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include <netdb.h>
#include "stdlib.h"

int main(int argc , char *argv[])
{
    int socket_desc;
    // struktura ktora obsahuje vssetky potrebne informacie ako port adresu
    struct sockaddr_in serv_addr;
    char *message , server_reply[2000];
    struct hostent* server;

    //Create socket
    // AF_INET ipv4
    // SOCK_STREAM oreinted to TCP protocol -> FTP or HTTP protocols
    //
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    // convert ip addrees to long format, google ip
    // we need to know the IP address of the remote server you are connecting to.
    // server.sin_addr.s_addr = inet_addr("74.125.235.20");
    // server.sin_family = AF_INET;
    // server.sin_port = htons( 80 );
    //vynulujeme a inicializujeme

    // dostaneme nas server
    server = gethostbyname("www.google.com"); //Použijeme funkciu gethostbyname na získanie informácii o počítači, ktorého hostname je v prvom argumente.
    if (server == NULL)
    {
        fprintf(stderr, "Error, no such host\n");
        return 2;
    }


    bzero((char*)&serv_addr, sizeof(serv_addr));
//Vynulujeme a zinicializujeme adresu, na ktorú sa budeme pripájať.
    serv_addr.sin_family = AF_INET;
    bcopy(
            (char*)server->h_addr,
            (char*)&serv_addr.sin_addr.s_addr,
            server->h_length
    );
    serv_addr.sin_port = htons(80);

    //Connect to remote server
    if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("connect error");
        return 1;
    }

    puts("Connected\n");

    //Send some data
    message = "GET / HTTP/1.1\r\n\r\n";
    if( send(socket_desc , message , strlen(message) , 0) < 0)
    {
        puts("Send failed");
        return 1;
    }
    puts("Data Send\n");

    //Receive a reply from the server
    if( recv(socket_desc, server_reply , 2000 , 0) < 0)
    {
        puts("recv failed");
    }
    puts("Reply received\n");
    puts(server_reply);

    return 0;
}
