#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main(int x, char *argv[]){
  int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  struct sockaddr_in server_address;
  memset(&server_address, 0, sizeof(server_address));
  int ip = inet_pton(AF_INET, "148.201.210.36", &server_address.sin_addr.s_addr);
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(4999);
  bind(sock, (struct sockaddr*) &server_address, sizeof(server_address));
  server_address.sin_port = htons(5000);
  if(connect(sock, (struct sockaddr *) &server_address, sizeof(server_address))<0)
    exit(5);
  char *echoString = "hi";
  size_t echoStringLength = strlen(echoString);
  ssize_t numBytes = send(sock, echoString, echoStringLength, 0);
  if(numBytes != echoStringLength)
    exit(2);
  char buffer[BUFSIZ];
  int counter = 0;
  while(counter < echoStringLength){
    numBytes = recv(sock, buffer, BUFSIZ -1, 0);
    counter += numBytes;
    if(numBytes != echoStringLength)
      exit(3);
    buffer[numBytes] = '\0';
    fputs(buffer, stdout);
  }
  close(sock);
  printf("\n");
  return 0; 
}
