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

// Este codigo es del servidor, abre el socket y espera las solicitudes del cliente

int main(){
  int serverSocket = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP); //# Creacion del socket con IPv6
  struct sockaddr_in6 serverAddress; //Structura para IPv6
  memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin6_family = AF_INET6;
  serverAddress.sin6_addr = in6addr_any;
  serverAddress.sin6_port = htons(5000); //htons especifica el puerto a usar 
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
