#include <iostream>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <error.h>
#define MAXLINE 4096
using namespace::std;

class Client{
    private:
        int port;
        sockaddr_in *cli_addr;
        int cli_fd;
    public:
        Client(int port);
        ~Client();
        int init();
        int establish();
        int send(string message);
};

int main(int argc, char* argv[]){
    cout << "client starts" << endl;

    

    string message("Hello World!");

    Client client(8099);
    client.init();
    client.establish();
    client.send(message);

    cout << "client ends" << endl;

    return 0;

}



Client::Client(int port){
    this->port = port;
}

int Client::init(){

    /** create a sockaddr_in  **/
    this->cli_addr = new sockaddr_in; 

    /** initialize sockaddr **/
    cli_addr->sin_family = AF_INET;
    cli_addr->sin_port = htons(this->port);
    cli_addr->sin_addr.s_addr = inet_addr("127.0.0.1");
    return 0;
}

int Client::establish(){
    cli_fd = socket(AF_INET,SOCK_STREAM,0);

    if (cli_fd == -1) return cli_fd;

    int err = connect(cli_fd,(sockaddr*)cli_addr,sizeof(sockaddr));
 
    return err;
}

int Client::send(string message){
    int num = ::send(cli_fd,message.c_str(),message.length(),1);
    return num;
}

Client::~Client(){
    shutdown(cli_fd,SHUT_RDWR);
    if (cli_addr != NULL){
        delete(cli_addr);
    }
}
