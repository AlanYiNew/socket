#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<pthread.h>
#include<vector>
class Server{
    private : 
        int port;
        sockaddr_in *serv_addr; 
        std::vector<pthread_t> accept_thread_pool;
        
    public :
        /** Server class constructor **/
        Server(int port,int accept_thread_num);
        ~Server();

        /** Initialize a server and prepare to set up listening **/
        int init();

        /** starts the server **/
        int starts();

};
