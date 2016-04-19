#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>


// Este codigo es el del cliente, inicia la comunicacion con el server, le envia un string e imprime la respuesta del server
int main(int argc, char *argv[]){
  int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //# Creacion del socket con IPv4
  struct sockaddr_in server_address;
  memset(&server_address, 0, sizeof(server_address));
  int ip = inet_pton(AF_INET, "10.0.1.4", &server_address.sin_addr.s_addr);
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(4999);
  int x = bind(sock, (struct sockaddr*) &server_address, sizeof(server_address));
  if(x == -1){
    printf("%s", strerror(errno));
  }
  printf("%d", x);
  ip = inet_pton(AF_INET, "10.0.1.2", &server_address.sin_addr.s_addr);
  server_address.sin_port = htons(5000); //Puerto a utilizar
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
  printf("%d", close(sock));
  printf("\n");
  return 0; 
}
