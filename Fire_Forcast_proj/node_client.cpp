

// Client side C++ program 

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
#include <sstream>
using namespace std;
#define PORT 8080
 static int seconds=0;
 static int count=0;
 static float sum=0;
 bool isNumeric(string str) {
   for (int i = 0; i < str.length(); i++){
      if (isdigit(str[i]) == false)
      return false; 
   return true;}
}
int main(int argc, char const* argv[])
{
    int sock = 0, valread, client_fd;
    struct sockaddr_in serv_addr;
    char* hello = "Hello from client";
    char buffer[1024] = { 0 };
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        cout<<"Socket creation error"<<endl;
        return -1;
    }
 cout << "\n=> Socket client has been created..." << endl;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
 
    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
        <= 0) {
        cout<<"Invalid address/ Address not supported"<<endl;
        return -1;
    }
 
    if ((client_fd
         = connect(sock, (struct sockaddr*)&serv_addr,
                   sizeof(serv_addr)))
        < 0) {
        cout<<"Connection Failed"<<endl;
        return -1;
    }cout << "=> Connection to the server port number: " << PORT << endl;
   while(1)
    {
     cout<<"ready to read"<<endl;
    valread=recv(sock, buffer, 1024,0);
   
    if(valread){
     seconds++;
    
    count++;
     cout<<count<<endl;
      if(!(isNumeric(buffer))){
     cout<<"Wrong Temperature Input!"<<endl;
     }
     cout<<"buffer is"<<buffer;
     stringstream strValue;
     strValue << buffer;
     unsigned int intValue;
     strValue >> intValue;
     cout<<intValue<<endl;
     sum+=intValue;
     cout<<"sum is"<<sum<<endl;
    if(seconds==5){
 
     
     cout<<"Average is:"<<(sum/count)<<endl;
     cout<<"Accumulation is:"<<sum<<endl;
     seconds=0;
    }
  
 }
 }
    // closing the connected socket
    close(client_fd);
    return 0;
}


