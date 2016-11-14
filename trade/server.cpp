#include <stdio.h>
#include <math.h>
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

Server::Server() {
  srand(time(NULL));
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    perror("ERROR opening socket");
    exit(1);
  }
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(5001);
  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    perror("ERROR binding");
    exit(1);
  }
  
  price = (double) (rand() % 100) / 100;
  map = (char *) mmap(NULL, 8, PROT_READ | PROT_WRITE,
              MAP_SHARED | MAP_ANONYMOUS, 0, 0);
  bzero(buffer, sizeof(buffer));
  sprintf(buffer, "%.2f", price);
  strncpy(map, buffer, 4);

  /* First 4 bytes of memory map are used for price
   * while the last 4 bytes are for the number of buy
   * requests (which means the max value is 9999)
   */
  bzero(buffer, sizeof(buffer));
  sprintf(buffer, "%d", 0);
  strncpy(&map[4], buffer, 4);
}

Server::~Server() {
  close(sockfd);
  munmap(map, 8);
}

int Server::sock() {
  return sockfd;
}

void Server::gen_price(int newsockfd) {
  sleep(1);
  time(&curtime);
  if ((curtime % 10) == 0) {
    char pricestr[4];
    double tprice;
    strncpy(pricestr, map, 4);
    tprice = strtod(pricestr, NULL);
    // Since up to 5 server objects will attempt to update
    // price every 10th seconds, this checks if the price is
    // already updated by another server object.
    if (tprice == price) {
      price = 0.00;
      while (price == 0.00) price = (double) (rand() % 100) / 100;
      sprintf(pricestr, "%.2f", price);
      strncpy(map, pricestr, 4);
    }
  }
  bzero(buffer, sizeof(buffer));
  strncpy(buffer, map, 4);
  price = strtod(buffer, NULL);
  sprintf(buffer, "$%.2f %s", price, ctime(&curtime));
  n = write(newsockfd, buffer, sizeof(buffer));
  if (n < 0) {
    perror("ERROR writing to socket");
    exit(1);
  }
  printf("%s", buffer);
}

void Server::process_buy_request(int newsockfd) {
  double client_price = 0.00;
  char cli_msg[256];
  char substr[4];
  int num;

  bzero(cli_msg, sizeof(cli_msg));
  n = read(newsockfd, cli_msg, sizeof(cli_msg));
  if (n < 0) {
    perror("ERROR reading from socket");
    exit(1);
  }
  strncpy(substr, &cli_msg[16], 4);
  client_price = strtod(substr, NULL);
  bzero(buffer, sizeof(buffer));
  sprintf(buffer, "from client: %s", cli_msg);

  sleep(1);
  n = write(newsockfd, buffer, sizeof(buffer));
  if (n < 0) {
    perror("ERROR processing request");
    exit(1);
  }

  time(&curtime);
  bzero(buffer, sizeof(buffer));
  strncpy(buffer, map, 4);
  price = strtod(buffer, NULL);
  bzero(buffer, sizeof(buffer));
  sprintf(buffer, "%sserver sell at $%.2f at %sall times approx\n", cli_msg, price, ctime(&curtime));
  if (client_price == price)
    strcat(buffer, "buy SUCCESSFUL from server!\n\n");
  else
    strcat(buffer, "buy FAILED from server!\n\n");

  sleep(1);
  n = write(newsockfd, buffer, sizeof(buffer));
  if (n < 0) {
    perror("ERROR finishing request");
    exit(1);
  }
  
  bzero(buffer, sizeof(buffer));
  strncpy(buffer, &map[4], 4);
  num = atoi(buffer);
  num++;
  printf("num buy attempts = %d\n", num);
  bzero(buffer, sizeof(buffer));
  sprintf(buffer, "%d", num);
  strncpy(&map[4], buffer, 4);
}
