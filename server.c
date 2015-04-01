#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

int main( int argc, char *argv[]) {
  if(argc != 3) {
    printf("Usage: ./server [destination] [port number]\n");
    return 1;
  }
  char *PORT_NUM = argv[2];
  if(atoi(PORT_NUM) < 1023) {
    printf("port number must be greater than 1023\n");
    return 1;
  }
  //char *DEST = argv[1];

  struct addrinfo hints;
  //hints will be passed into getaddrinfo and specify some 
  //criteria for getaddrinfo to return into res.
  memset(&hints, 0, sizeof hints); //Make sure hints is empty
  hints.ai_family = AF_UNSPEC; //I don't care if it is IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE; //bind to the IP of the host I am on

  struct addrinfo *res;
  if(getaddrinfo(NULL, PORT_NUM, &hints, &res) != 0) {
    perror("getaddrinfo");
  }
  
  int sockfd; //socket file descriptor
  //I should error check this in the future
  sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  

  //the port number is used to match the incoming packet to a certain
  //process's file descriptor
  //bind: associate the socket to a port on the machine
  //that port is inside of res->ai_addr
  bind(sockfd, res->ai_addr, res->ai_addrlen);

  listen(sockfd, 1);

  //accept

  int new_fd;
  struct sockaddr_storage their_addr;
  socklen_t addr_size = sizeof their_addr;
  new_fd = accept(sockfd, (struct sockaddr *) &their_addr, &addr_size);
  
  //send something!
  char *msg = "welcome to angels server!\n";
  send(new_fd, msg , strlen(msg),0 );

  //receive something!
  char buffer[20];
  recv(new_fd, buffer, sizeof buffer, 0);
  printf("client>> %s\n", buffer);
 

  return 0;
}
