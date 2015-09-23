//
// Created by haohanwang on 9/23/15.
//

#ifndef CPPCLIENT_CLIENT_H
#define CPPCLIENT_CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdexcept>
#include <string>
#include <iostream>

using namespace std;


class Client {
private:
    int sockfd, portno, flag;
    struct sockaddr_in serv_addr;
    struct hostent *server;
public:
    Client(char* hostname, int portno){
        server = gethostbyname(hostname);
        this->portno = portno;
    }

    int connect_to_server(){
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0)
            throw std::runtime_error("Error in Openning Socket");
        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *)server->h_addr,
              (char *)&serv_addr.sin_addr.s_addr,
              server->h_length);
        serv_addr.sin_port = htons(portno);
        if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
            throw std::runtime_error("Error in Connecting");
        return 1;
    }

    void write_message(string message){
        char * m = new char [message.length() + 1];
        strcpy(m, message.c_str());
        cout <<  m << endl;
        flag = write(sockfd,m,strlen(m));
        if (flag < 0) {
            throw std::runtime_error("Error in Writing Message");
        }
    }

    char * get_respond(){
        char result[65530];
        bzero(result,65530);
        flag = read(sockfd,result,255);
        if (flag < 0) {
            throw std::runtime_error("Error in reading message");
        }
        return result;
    }
};


#endif //CPPCLIENT_CLIENT_H
