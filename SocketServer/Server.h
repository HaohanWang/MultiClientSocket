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
#include <iostream>
#include <algorithm>
#include <pthread.h>

#include "json/json.h"
#include "JsonEncoder.h"

using namespace std;


class Server {

private:
    int sockfd, newsockfd; //file descriptors
    int portno; //port number on which the server accepts connections
    socklen_t clilen; //size of the address of the client
//    char buffer[65535]; //server reads characters from the socket connection into this buffer.
    struct sockaddr_in serv_addr, cli_addr; //structures containing an internet address
    int flag;

public:
    Server(int protno) { this->portno = protno; }

    int serve(int times) {
        pthread_t thread;
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0)
            throw std::runtime_error("ERROR opening socket");
        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(portno);
        if (bind(sockfd, (struct sockaddr *) &serv_addr,
                 sizeof(serv_addr)) < 0) {
            throw std::runtime_error("ERROR on binding");
        }
        listen(sockfd, 5);
        clilen = sizeof(cli_addr);

        int i = 0;
        while (i < times) {
            /* accept incoming connections */
            newsockfd = accept(sockfd,
                               (struct sockaddr *) &cli_addr,
                               &clilen);
            if (newsockfd < 0)
                throw std::runtime_error("ERROR on accept");
            else {
                /* start a new thread but do not wait for it */
                cout << "This is process # " << to_string(i+1) << endl;
                pthread_create(&thread, 0, Server::process, &newsockfd);
                pthread_detach(thread);
            }
            i++;
        }
        close(sockfd);
    }

    static void *process(void *ptr) {
        int len;
        int *conn;
        long addr = 0;
        char buffer[65535];
        if (!ptr) pthread_exit(0);

        conn = (int*) ptr;
        bzero(buffer, 65535);
        int flag;
        flag = read(*conn, buffer, 65535);
        if (flag < 0) throw std::runtime_error("ERROR reading from socket");
        vector<float> v = JsonEncoder<float>::decode_vector_main(buffer);
        std::sort(v.begin(), v.end());
        string m = JsonEncoder<float>::encode(v);
        const char *r = m.c_str();
        flag = write(*conn, r, 65535);
        if (flag < 0) throw std::runtime_error("ERROR writing to socket");
        close(*conn);

        pthread_exit(0);
    }

};


#endif //SOCKETSERVER_SERVER_H
