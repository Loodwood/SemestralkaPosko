
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
#include "Ball.h"

using namespace std;

class clientPong
{

private:
    int clientID;
    
    char direction;
    int sendToclient;
    //float startX;             na posielanie suradnic lopticky
    //float startY;
    bool canStart;
    bool canStartGame;
    int sockfd;                 // descriptor socket 
    int clientSocket;
public:
    char getDirection() {
        return direction;
    }
    float *direc;
    bool getCanStart() {return canStart;}
    bool getStartGame() {return canStartGame;}
    //float getStartX() {return startX;}
    //float getStartY() {return startY;}
    int connectClient();
    clientPong();
    // vlakno na spustenie hry a ziskavanie vstupov od hracov cez sockety
    void *recieveDataFromServer(void) {
        char buffer[2];
        void *tmp = malloc((sizeof(char)*4 + sizeof(float)*3));
        int n = read(sockfd, buffer, 2);

        if (n < 0) {
            perror("ERROR reading from socket");
            //exit(1);
        }
        int idFromBuffer = (int)buffer[0];
        clientID = idFromBuffer;
        std::cout << idFromBuffer << std::endl;
        if (idFromBuffer == 0) {
            sendToclient = 1;
        } else if (idFromBuffer == 1) {
            sendToclient = 0;
        } else {
            std::cout << "clientPong.h : invalid value in idFromBuffer" << std::endl;
            perror("invalid idFromBuffer variable");
        }
        // cita co pride 
        while (1) {
            n = recv( sockfd , tmp,((sizeof(char)*4)+(sizeof(float)*3)) ,0);
            if (n < 0) {
                perror("ERROR reading from socket");
                //exit(1);
            }
            char *tmp_c = (char*)tmp;
            float *tmp_f = (float*)tmp;
            if(tmp_f[3] == 1) {
                direc = tmp_f;
            }else {
                char letter = tmp_c[0];
            if (letter == 'c') {
                std::cout << "Hra pripravena, startujem...stlac Tab pre Start " << std::endl;
                
                canStart = true;
                continue;
            }
            
            if (letter == 'e') {
                std::cout << "spustena hra : " << std::endl;
                canStartGame = true;
                continue;
            }
           
            std::cout << "prisla direction : " << letter << std::endl;
            this->direction = tmp_c[0]; 
            }
        }
        free(tmp);
    }
    static void *recievePomocnik(void *context) {
        return ((clientPong *)context)->recieveDataFromServer();
    }
    void * recieveData(void * sockID);
    int getClientID();
    int sendToC(char direction);
    int sendToClientBallPosition(Ball lopta);
};

