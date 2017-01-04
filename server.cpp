#include <iostream>
#include <string.h>
#include <vector>
#include <exception>
#include <unistd.h>
#include "server.h"
#include <pthread.h>
#define MAXLINE 4096
using namespace::std;
Server::Server(int port,int accept_thread_num){
    this->port = port;
    this->accept_thread_pool.reserve(accept_thread_num);
}

int Server::init(){
    /** declare a socketaddr_in **/       
    this->serv_addr = new sockaddr_in;
       
    /** set protocol family ipv4 **/
    this->serv_addr->sin_family=AF_INET;
    
    /** set address accepting any in_addr using host to network address 
    transalation **/
    this->serv_addr->sin_addr.s_addr=htonl(INADDR_ANY);
    
    /** set input port **/
    serv_addr->sin_port=htons(this->port);

    return 0;
}

int Server::starts(){
    /** create a socket **/
    int fd = socket(AF_INET,SOCK_STREAM,0);
    
    /** buff **/
    char buff[MAXLINE+1];
   
    
 
    try {
    
        int err = bind(fd,(sockaddr*)(serv_addr),sizeof(sockaddr_in));
        
        err =  listen(fd,accept_thread_pool.capacity());        

        int i = 0;
       
        socklen_t len = sizeof(sockaddr_in); 

        while (true){
            
            int connfd = accept(fd,(struct sockaddr*)serv_addr,&len);

            if (connfd == -1) continue;
            
            int n = recv(connfd,buff,MAXLINE,0);

            buff[n] = '\0'; 
 
            cout << "running " << i << "rounds:" << buff << endl;

        }
    }   catch (exception& e){

        cout << e.what() << endl; 

        return -1;
    }
    
    return 0;
}

Server::~Server(){
    if (serv_addr != NULL){
       delete(serv_addr); 
    }
}
