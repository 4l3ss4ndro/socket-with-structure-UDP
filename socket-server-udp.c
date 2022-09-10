#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct {
char var1;
int var2;
}mystruct;

int main(int argc, char **argv){

  char *ip = "10.0.0.2";
  int port = 8080;

  int sockfd;
  struct sockaddr_in server_addr, client_addr;
  mystruct torecv;
  socklen_t addr_size;
  int n;

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0){
    perror("[-]socket error");
    exit(1);
  }

  memset(&server_addr, '\0', sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = inet_addr(ip);

  n = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if (n < 0) {
    perror("[-]bind error");
    exit(1);
  }

  addr_size = sizeof(client_addr);
  recvfrom(sockfd, (mystruct *)&torecv, sizeof(torecv), 0, (struct sockaddr*)&client_addr, &addr_size);
  printf("Data recv: %c\n", torecv.var1);
  printf("Data recv: %d\n", torecv.var2);

  sendto(sockfd, (mystruct *)&torecv, sizeof(torecv), 0, (struct sockaddr*)&client_addr, sizeof(client_addr));
  printf("Data sent.\n");

  return 0;
}
