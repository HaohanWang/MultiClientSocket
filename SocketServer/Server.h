//
// Created by haohanwang on 9/23/15.
//

#ifndef SOCKETSERVER_SERVER_H
#define SOCKETSERVER_SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdexcept>


class Server {

private:
    int sockfd, newsockfd; //file descriptors
    int portno; //port number on which the server accepts connections
    socklen_t clilen; //size of the address of the client
    char buffer[256]; //server reads characters from the socket connection into this buffer.
    struct sockaddr_in serv_addr, cli_addr; //structures containing an internet address
    int flag;

public:
    Server(int protno) { this->portno = protno; }

    void setSockfd(int sockfd) {
        Server::sockfd = sockfd;
    }

    void setNewsockfd(int newsockfd) {
        Server::newsockfd = newsockfd;
    }

    void setPortno(int portno) {
        Server::portno = portno;
    }

    void setClilen(socklen_t clilen) {
        Server::clilen = clilen;
    }

    void setServ_addr(const sockaddr_in &serv_addr) {
        Server::serv_addr = serv_addr;
    }

    void setCli_addr(const sockaddr_in &cli_addr) {
        Server::cli_addr = cli_addr;
    }

    int serve() {
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0)
            throw std::runtime_error("ERROR opening socket");
        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(portno);
        if (bind(sockfd, (struct sockaddr *) &serv_addr,
                 sizeof(serv_addr)) < 0){
            throw std::runtime_error( "ERROR on binding" );
        }
        listen(sockfd,5);
        clilen = sizeof(cli_addr);
        newsockfd = accept(sockfd,
                           (struct sockaddr *) &cli_addr,
                           &clilen);
        if (newsockfd < 0)
            throw std::runtime_error( "ERROR on accept" );
        bzero(buffer,256);
        flag = read(newsockfd,buffer,255);
        if (flag < 0) throw std::runtime_error( "ERROR reading from socket" );
        printf("Here is the message: %s\n",buffer);
        flag = write(newsockfd,"I got your message",18);
        if (flag < 0) throw std::runtime_error( "ERROR writing to socket" );
        close(newsockfd);
        close(sockfd);
    }
};


#endif //SOCKETSERVER_SERVER_H
