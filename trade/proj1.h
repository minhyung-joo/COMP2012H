#ifndef PROJ1_H 
#define PROJ1_H

class Server {
public:
	Server();
	~Server();
	int sock();
	void gen_price(int);
	void process_buy_request(int);
private:
	int sockfd, n;
        char* map;
	struct sockaddr_in serv_addr;
	time_t curtime;
	char buffer[256];
	double price;
};

class Client {
public:
	Client(char*, int);
	~Client();
	void get_price();
	void gen_buy_request();
private:
	int sockfd, n;
	char* map;
	struct sockaddr_in serv_addr;
    	struct hostent *server;
	char buffer[256];
};

#endif
