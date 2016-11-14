#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <time.h>
#include "proj1.h"

Client::Client(char * serv, int portno) {
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) { 
    perror("ERROR opening socket");
    exit(1);
  }
  server = gethostbyname(serv);
  if (server == NULL) {
      fprintf(stderr,"ERROR, no such host\n");
      exit(0);
  }
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, 
       (char *)&serv_addr.sin_addr.s_addr,
       server->h_length);
  serv_addr.sin_port = htons(portno);
  if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) { 
    perror("ERROR connecting");
    exit(1);
  }
  map = (char*) mmap(NULL, 4, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS,0,0);
}

Client::~Client() {
  close(sockfd);
  munmap(map, 4);
}

void Client::get_price() {
  bzero(buffer, sizeof(buffer));
  n = read(sockfd, buffer, sizeof(buffer));
  if (n < 0) {
    perror("ERROR reading from socket");
    exit(1);
  }
  printf("%s", buffer);
  strncpy(map, &buffer[1], 4);
}

void Client::gen_buy_request() {
  time_t buy_t;
  char c = 0;
  double price = 0.00;
  while (c != '\n') c = getchar();
  
  bzero(buffer, sizeof(buffer));
  price = strtod(map, NULL);
  if (price == 0.00) return;
  time(&buy_t);
  sprintf(buffer, "client buy  at $%.2f at %s", price, ctime(&buy_t));
  n = write(sockfd, buffer, sizeof(buffer));
  if (n < 0) {
    perror("ERROR sending request");
    exit(1);
  }

  bzero(buffer, sizeof(buffer));
  n = read(sockfd, buffer, sizeof(buffer));
  if (n < 0) {
    perror("ERROR receiving reply");
    exit(1);
  }
  printf("%s", buffer);

  bzero(buffer, sizeof(buffer));
  n = read(sockfd, buffer, sizeof(buffer));
  if (n < 0) {
    perror("ERROR receiving result");
    exit(1);
  }
  printf("%s", buffer);
}
