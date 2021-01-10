
#include "clientPong.h"

clientPong::clientPong() {
    direction = ' ';
    //startX = -1;
    //startY = -1;
    connectClient();
    canStart = false;
    canStartGame = false;
}

int clientPong::getClientID() {
    return clientID;
}

int clientPong::connectClient() {
    // zakladne premenne pre pripojenie client socketu 
   int portNumber, n;
   struct sockaddr_in serv_addr;
   struct hostent *server;
   char buffer[256];
   portNumber = 8888;

   // Create a socket point
   sockfd = socket(AF_INET, SOCK_STREAM, 0);

   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }

   server = gethostbyname("127.0.0.1");
   if (server == NULL) {
      fprintf(stderr,"ERROR, no such host\n");
      exit(0);
   }

   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
   serv_addr.sin_port = htons(portNumber);

    //connect to the server
   if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR connecting");
      exit(1);
   }

    printf("Connected\n");

    pthread_t thread;
    pthread_create(&thread, NULL, &clientPong::recievePomocnik, this);
    
    return 0;
}

int clientPong::sendToC(char direction) {

    char buffer[4];
    buffer[0] = direction;
    buffer[1] = '\0';
   
    
  
    
    

    // Send message to the server
    int n = write(sockfd, buffer, strlen(buffer));

    if (n < 0) {
        perror("ERROR writing to socket");
        exit(1);
    }
    return 0;
}

int clientPong::sendToClientBallPosition(char x, char y) {

    char buffer[4];
    buffer[0] = x;
    buffer[1] = '\0';
    buffer[2] = y;
    buffer[4] = '\0';

    // Send message to the server
    int n = write(sockfd, buffer, strlen(buffer));

    if (n < 0) {
        perror("ERROR writing to socket");
        exit(1);
    }
    return 0;
}

