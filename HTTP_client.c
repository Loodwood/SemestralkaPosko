#include<stdio.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include <netdb.h>
#include "stdlib.h"

// http client reaguje na spravy typu :
//GET HEAD POST PUT DELETE CONNECT OPTIONS TRACE PATCH


int main(int argc , char *argv[])
{
    int socket_desc;
    // struktura ktora obsahuje vssetky potrebne informacie ako port adresu
    struct sockaddr_in serv_addr;
    // takze potrebujemee nasu strutkuru http requestu a teraz buffer co dostaneme z requeastu tak tam ulozime
    char *message , server_reply[2000];
    struct hostent* server;

    //Create socket
    // AF_INET ipv4
    // SOCK_STREAM oreinted to TCP protocol -> FTP or HTTP protocol
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    // convert ip addrees to long format, google ip
    // we need to know the IP address of the remote server you are connecting to.
    //serv_addr.sin_addr.s_addr = inet_addr("74.125.235.20");
    //serv_addr.sin_family = AF_INET;
    //serv_addr.sin_port = htons( 80 );
    //vynulujeme a inicializujeme

     //dostaneme nas server
    server = gethostbyname("www.google.com"); //Použijeme funkciu gethostbyname na získanie informácii o počítači, ktorého hostname je v prvom argumente.
    if (server == NULL)
    {
        fprintf(stderr, "Error, no such host\n");
        return 2;
    }


    printf("server %d", server->h_length);


    bzero((char*)&serv_addr, sizeof(serv_addr));
//Vynulujeme a zinicializujeme adresu, na ktorú sa budeme pripájať.
    serv_addr.sin_family = AF_INET;
    // skopiruje adresu z domeny na server ip
    bcopy(
            (char*)server->h_addr,
            (char*)&serv_addr.sin_addr.s_addr,
            server->h_length
    );
    serv_addr.sin_port = htons(80);

    //Connect to remote server
    if (connect(socket_desc , (struct sockaddr *)&serv_addr , sizeof(serv_addr)) < 0)
    {
        puts("connect error");
        return 1;
    }

    puts("Connected\n");

    //Send some data
    // spravime si nas request na http server
    // HTTP/1.1 -> for returning homepage
    message = "GET / HTTP/1.1\r\n\r\n";
    // send posleme jednoducho data na server cez socket
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
