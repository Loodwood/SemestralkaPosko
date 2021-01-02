
#include "clientPong.h"

clientPong::clientPong() {
    direction = ' ';
    startX = -1;
    startY = -1;
    clientConnect();
    canStart = false;
}

int clientPong::getClientID() {
    return idClient;
}

int clientPong::clientConnect() {
   int portno, n;
   struct sockaddr_in serv_addr;
   struct hostent *server;
   char buffer[256];
   portno = 8888;

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
   serv_addr.sin_port = htons(portno);

    //connect to the server
   if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR connecting");
      exit(1);
   }

    printf("Connected\n");

    pthread_t thread;
    pthread_create(&thread, NULL, &clientPong::rcvHelper, this);
}

int clientPong::sendToClient(char direction) {

    char buffer[2];
    buffer[0] = direction;
    buffer[1] = '\0';

    // Send message to the server
    int n = write(sockfd, buffer, strlen(buffer));

    if (n < 0) {
        perror("ERROR writing to socket");
        exit(1);
    }
}

