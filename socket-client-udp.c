#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
char var1;
int var2;
}mystruct;

int main(int argc, char **argv){

  char *ip = "10.0.0.2";
  int port = 8080;
  int yes = 1;
  int sockfd;
  struct sockaddr_in addr;
  mystruct tosend;
  tosend.var1 = 'A';
  tosend.var2 = 29;
  socklen_t addr_size;
  mystruct torecv;

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  
  int ret = setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, (char*)&yes, sizeof(yes));
  if (ret == -1) {
    perror("setsockopt error");
    return 0;
  }
  
  memset(&addr, '\0', sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = inet_addr(ip);

  sendto(sockfd, (mystruct *)&tosend, sizeof(tosend), 0, (struct sockaddr*)&addr, sizeof(addr));
  printf("Sending data.\n");


  addr_size = sizeof(addr);
  recvfrom(sockfd, (mystruct *)&torecv, sizeof(torecv), 0, (struct sockaddr*)&addr, &addr_size);
  printf("Data recv: %c %d\n", torecv.var1, torecv.var2);

  return 0;
}
