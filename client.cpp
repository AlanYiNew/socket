#include <iostream>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <vector>
#include <cerrno>
#define MAXLINE 4096
using namespace::std;
static int count = 0;
static pthread_mutex_t mutex;
static void *run_client(void* ptr);

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
        int shutdown();
};

int main(int argc, char* argv[]){
    int NUM_THREADS = 4; 
    vector<pthread_t> tids;
    tids.reserve(NUM_THREADS);
    
    try {
        for( int i = 0; i < NUM_THREADS; i++ ){
            int ret = ::pthread_create( &(tids[i]), NULL, run_client, NULL );
            if( ret != 0 ){
                cout << "pthread_create error:error_code=" << ret << endl;
            }
        }
    }   catch (exception& e){
        cout << e.what() << endl;
    }
    
    while (count < NUM_THREADS);
 
    /** make a long enough terminating signal **/
    Client cliente(8099); 
    cliente.init();
    cliente.establish();
    string endMessage("tttttttttttttttttttttttttttttttttttttt");
    cliente.send(endMessage);
    cliente.shutdown();
    return 0;

}

static void *run_client(void * ptr){
    string message("Hello World!\n");
    for (int j = 0; j < 1000; j++){
        Client client(8099);
        client.init();
       
        int errt = 0; 
        while (errt=client.establish());
        
        for (int i = 0; i < 10000; i++){
            client.send(message);
        }
    }
    pthread_mutex_lock(&mutex);
    count++;
    pthread_mutex_unlock(&mutex);
}

Client::Client(int port){
    this->port = port;
}

int Client::init(){

    /** create a sockaddr_in  **/
    this->cli_addr = new sockaddr_in; 

    if (this->cli_addr == NULL) exit(-1);

    /** initialize sockaddr **/
    cli_addr->sin_family = AF_INET;
    cli_addr->sin_port = htons(this->port);
    cli_addr->sin_addr.s_addr = inet_addr("127.0.0.1");
    return 0;
}

int Client::establish(){
    cli_fd = socket(AF_INET,SOCK_STREAM,0);

    if (cli_fd <=0) return -1;

    int err = connect(cli_fd,(sockaddr*)cli_addr,sizeof(sockaddr));
 
    return err;
}

int Client::send(string message){
    int num = ::send(cli_fd,message.c_str(),message.length(),1);
    return num;
}

int Client::shutdown(){
    ::shutdown(cli_fd,SHUT_RDWR);
    ::close(cli_fd);
    
}

Client::~Client(){
    ::shutdown(cli_fd,SHUT_RDWR);
    ::close(cli_fd);
    if (cli_addr != NULL){
        delete(cli_addr);
    }
}
