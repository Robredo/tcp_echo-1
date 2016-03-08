#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

void handleTCPEchoClient(int clientSocket){
  char buffer[BUFSIZ];
  ssize_t bytesRcvd = recv(clientSocket, buffer, BUFSIZ, 0);
  send(clientSocket, buffer, bytesRcvd, 0);
  close(clientSocket);
}

void handleTimeClient(){}

int main(){
  int serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  struct sockaddr_in serverAddress;
  memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddress.sin_port = htons(5000);
  bind(serverSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress));
  if(listen(serverSocket, SOMAXCONN) < 0)
    exit(5);
  for(;;){
    struct sockaddr_in clientAddress;
    socklen_t clientAddrLen = sizeof(clientAddress);
    int clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddrLen );
    if(clientSocket < 0)
      exit(5);
    char clientIp[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &clientAddress.sin_addr.s_addr, clientIp, sizeof(clientIp));
    printf("%s %d\n", clientIp, ntohs(clientAddress.sin_port));
    handleTCPEchoClient(clientSocket);
  }
  return 0;
}
