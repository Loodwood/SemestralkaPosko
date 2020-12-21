#include<stdio.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include <netdb.h>
#include "stdlib.h"
#include <limits.h>
#include <unistd.h>

// http client reaguje na spravy typu :
//GET HEAD POST PUT DELETE CONNECT OPTIONS TRACE PATCH

int http_socket_connetct(char *host, in_port_t port) {

    struct hostent* server;
    int socket_desc;
    struct sockaddr_in serv_addr;
    int on=1, sock;

    if((server = gethostbyname(host)) == NULL){
        herror("gethostbyname");
        exit(1);
    }
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }

    serv_addr.sin_family = AF_INET;
    bcopy(
            (char*)server->h_addr,
            (char*)&serv_addr.sin_addr.s_addr,
            server->h_length
    );
    serv_addr.sin_port = htons(port);

    if (connect(socket_desc , (struct sockaddr *)&serv_addr , sizeof(serv_addr)) < 0)
    {
        puts("connect error");
        return 1;
    }
    puts("Connected\n");


    return socket_desc;
}

#define MAXLINE = 10000;

int main(int argc , char *argv[])
{
    int socket_desc = http_socket_connetct("www.facebook.com",80);
    char* message, server_reply[1000000];

    //Send some data
    // spravime si nas request na http server
    // HTTP/1.1 -> for returning homepage

    //file options
    char *filename = "test.png";
    int total_len = 0;
    int file_len = 1000000;

    int len;

    FILE *file = NULL;


    // building http request host:port/string
    //message = "GET /wp-content/uploads/2020/04/easter-5001093_1920-800x445.jpg HTTP/1.1\r\n"
              "Host: www.snv24.sk\r\n\r\n"
              " Connection: keep-alive\r\n\r\n"
              " Keep-Alive: 300\r\n";

    /*char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working dir: %s\n", cwd);
    } else {
        perror("getcwd() error");
        return 1;
    }
     */

    message = "GET / HTTP/1.1\r\n\r\n";
   // message = "GET / HTTP/1.1\r\n"
              //   "Host: www.facebook.com\r\n\r\n "
              // "Connection: keep-alive\r\n\r\n"
    //" Keep-Alive: 300\r\n";

    // send posleme jednoducho data na server cez socket
    if( send(socket_desc , message , strlen(message) , 0) < 0)
    {
        puts("Send failed");
        return 1;
    }
    puts("Data Send\n");

    file = fopen(filename, "wb");

    if(file == NULL){
        printf("File could not opened");
    }
    printf("Idem nacitat\n");
    /*
    while(1)
    {

        int received_len = recv(socket_desc, server_reply , sizeof server_reply, 0);

        if( received_len < 0 ){
            puts("recv failed");
            break;
        }else if (received_len == 0)
        {
            puts("end of loading..\n");
            break;
        }
//
        total_len += received_len;

        //puts(server_reply);
        fwrite(server_reply , received_len , 1, file);

        printf("\nReceived byte size = %d\nTotal lenght = %d", received_len, total_len);

        if( total_len >= file_len ){
            break;
        }
    }

    puts("Reply received\n");
    puts(server_reply);

    fclose(file);
    printf("File created and saved successfully. :) \n");

    return 0;
     */
    //Receive a reply from the server
    if( recv(socket_desc, server_reply , 2000 , 0) < 0)
    {
        puts("recv failed");
    }
    puts("Reply received\n");
    puts(server_reply);



    return 0;

}
