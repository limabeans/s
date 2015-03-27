#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>

int main() {
  struct addrinfo hints, *res;
  int sockfd;

  memset(&hints, 0, sizeof hints);
  
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  getaddrinfo(NULL, "5999", &hints, &res);
  //STEP 1 socket
  sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  int i = 1;

  //step 1a
  if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &i, sizeof i) == -1) {
    printf("rekt\n");
    perror(NULL);
    exit(-1);
  }

  //step 2 bind
  if(bind(sockfd, res->ai_addr, res->ai_addrlen) == -1) {
    perror(NULL);
    exit(-1);
  } 

  //step 3 listen
  if(listen(sockfd, 1) == -1) {
    perror(NULL);
    exit(-1);

  }

  struct sockaddr_storage their_addr;
  socklen_t addr_size = sizeof their_addr;
  printf("ha\n");

  //step 4 accept
  int new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);

  char *lel = "hi i am angel\n";
  int bytes_sent = send(new_fd, lel, strlen(lel), 0);

  char lel2[20];
  recv(new_fd, lel2, sizeof lel2, 0);
  
  printf("%s\n", lel2);
  
  printf("ho\n");
 
  

  return 0;
}
