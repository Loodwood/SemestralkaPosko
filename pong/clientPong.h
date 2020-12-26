#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>

#include <netdb.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <iostream>

class clientPong
{

private:
    int idClient;
    int socketClient;
    char direction;
    int clientToSendToID;
    int startX;
    int startY;
    bool canStart;
    int sockfd;
public:
    char getDirection() {
        return direction;
    }
    bool getCanStart() {return canStart;}
    int getStartX() {return startX;}
    int getStartY() {return startY;}
    int clientConnect();
    clientPong();
    void *rcvData(void) {
        char buffer[2];
        int n = read(sockfd, buffer, 2);

        if (n < 0) {
            perror("ERROR reading from socket");
            //exit(1);
        }
        int idFromBuffer = (int)buffer[0];
        idClient = idFromBuffer;
        std::cout << idFromBuffer << std::endl;
        if (idFromBuffer == 0) {
            clientToSendToID = 1;
        } else if (idFromBuffer == 1) {
            clientToSendToID = 0;
        } else {
            std::cout << "clientHadik.h : invalid value in idFromBuffer" << std::endl;
            perror("invalid idFromBuffer variable");
        }
        while (1) {
            n = read(sockfd, buffer, 2);
            if (n < 0) {
                perror("ERROR reading from socket");
                //exit(1);
            }
            char letter = buffer[0];
            if (letter == 'c') {
                std::cout << "Hra pripravena, startujem... " << std::endl;
                canStart = true;
                continue;
            }
           // std::cout << "prisla direction : " << letter << std::endl;
            this->direction = buffer[0];

        }

        /*int clientSocket = socketClient;

        char data[1024];
        int read = recv(clientSocket, data, 1024, 0);
        data[read] = '\0';
        int cislo = (int)data[0];
        //id clienta
       // int idClient;
       //len pre 2 HRACOV !!!
        if (cislo == 0) {
            clientToSendToID = 1;
        } else {
             clientToSendToID = 0;
        }
        idClient = cislo;
        printf("%d\n", cislo);

        while (1) {
            //direction
            read = recv(clientSocket, data, 1024, 0);
            data[read] = '\0';
            printf("%s\n",data);
            if (data[0] == 'c') {
                printf("%c recieve ready -c \n",data);
                canStart = true;
                continue;
            }
            direction = data[0];
            printf("%s\n", data);
        }*/
    }
    static void *rcvHelper(void *context) {
        return ((clientPong *)context)->rcvData();
    }
    void * recieveData(void * sockID);
    int getClientID();
    int sendToClient(char direction);
    /*int sendToClient(int xStart, int yStart) {
        char input[1024];

        input[0] = clientToSendToID;
        //scanf tu nebude, namiesto toho parameter z main.cpp->id klienta
    //scanf("%s", input); // id, index ->1,2
        send(socketClient, input, 1024, 0);

        input[0] = xStart;
        input[1] = yStart;
        //namiesto scanf parameter direction z main.cpp
    //scanf("%[^\n]s", input); //direction
        send(socketClient, input, 1024, 0);
    }*/


    /*static void* recv_wrapper(void* object)
    {
        reinterpret_cast<clientHadik*>(object)->recieveData((void *) &socketClient);
        return 0;
    }*/
};
