#include <iostream>

#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 

#define PORT 8080 

#include "./sock.h"

Sock::Sock()
{
}


// Demonstrates a working starting point. Able to hit the server once, then program ends.
void Sock::CreateTestSocket(const char* msg)
{

    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 

    // AF_INET == IPv4, SOCK_STREAM == TCP (SOCK_DGRAM for UDP), 0 (protocol) => IP 
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == 0) {
        throw "Failure to create socket";
    }

    // attach socket to port 8080
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) {
        throw "SetSockOpt failure";
    }

    address.sin_family = AF_INET; // IPv4
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT ) ;


    // Forcefully attaching socket to the port 8080 
    if (bind(sockfd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        throw "Failed to bind"; 
    } 
    if (listen(sockfd, 3) < 0) 
    { 
        throw "Failed to listen" 
    } 


    int new_socket;
    int valread;

    if ((new_socket = accept(sockfd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    { 
        throw "Failed to accept new connection"
    } 
    valread = read( new_socket , buffer, 1024); 
    printf("%s\n",buffer ); 
    send(new_socket , msg , strlen(msg) , 0 ); 

}
