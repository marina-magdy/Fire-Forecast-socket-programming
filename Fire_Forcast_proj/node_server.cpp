// Server side C++ program 

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <netdb.h>

using namespace std;
#define PORT 8080



//string temp[10] = {"38","39","40","41","42","43","44","45","46","47"};
//char* temperature=temp[0];
int main(int argc, char const* argv[])
{
    int client, server, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = { 0 };
    char* hello = "Hello from server";
    client = socket(AF_INET, SOCK_STREAM, 0);
    // Creating socket file descriptor
    if (client < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    cout<<"Socket server has been created..." << endl;
 
    // Forcefully attaching socket to the port 8080, it helps in reuse of address and port. Prevents error such as: “address already in use”.
    if (setsockopt(client, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
 
    // Forcefully attaching socket to the port 8080
    if (bind(client, (struct sockaddr*)&address,
             sizeof(address))
        < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
     cout << "Listening for clients..." << endl;
    if (listen(client, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
     
    if ((server
         = accept(client, (struct sockaddr*)&address,
                  (socklen_t*)&addrlen))
        < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    cout<<"the connection is established between client and server, and they are ready to transfer data"<< endl;
    
    while (server > 0) 
    { 
        //(temp[i]).c_str(), strlen((temp[i]).c_str()),
    	//for(int i=0;i<(sizeof(temp)/sizeof(temp[0]));i++){
       	//char* temperature = get_temp();
          string s = to_string(rand()%(50 + 1) +10);
    char const *temperature = s.c_str();
       	send(server, temperature, strlen(temperature), 0);
       	cout<<"Temperature sent "<<temperature <<endl;
       	//cout<<"Temperature sent "<<temp[i] <<endl;
    
    		// Sleep for 1 second
    		sleep(1);
    
}
   
 
    // closing the connected socket
    close(server);
    // closing the listening socket
    shutdown(client, SHUT_RDWR);
    return 0;
}

