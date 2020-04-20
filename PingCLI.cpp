#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netinet/ip_icmp.h>
#include <netinet/ip.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <ctime>
using namespace std;

int main(){

  //Variables 
  string input;
  string ip_add; //if hostname given
  char str[input.size()+1];
  int sock;
  struct hostent *host;
  struct icmphdr *icm = new icmphdr;
  struct sockaddr_in out;
  struct sockaddr_in in;
  int packetsSent = 0;
  int packetsRecv = 0;


  //Prompt User
  cout<<"Enter IP Address or Hostname: ";
  cin>>input;
  strcpy(str,input.c_str()); //Parse string to C-String


  //Open RAW Socket
  sock = socket(AF_INET,SOCK_RAW,IPPROTO_ICMP);



  //Get DNS Address
  host = gethostbyname(str);
  ip_add=inet_ntoa(*(struct in_addr*)host->h_addr);




  //Setting up icm & out
   icm->type = ICMP_ECHO;
   icm->code = 0;
   icm->un.echo.id = 0; //random() or 0
   icm->un.echo.sequence = 0;
   icm->checksum =0;
   out.sin_family = AF_INET;
   out.sin_addr.s_addr = inet_addr(host->h_addr);


   //Continuously pinging
   while(1){
     clock_t start;
     if(sendto(sock,icm,sizeof(struct iphdr)+sizeof(struct icmphdr),0,(struct sockaddr *) &out, sizeof(struct sockaddr))>0){
       start = clock();
       packetsSent++;
     }

    unsigned int addrl = sizeof(in);
     if(recvfrom(sock,icm,sizeof(struct iphdr)+sizeof(struct icmphdr),0,(struct sockaddr *) &in, &addrl)>0){
	if(in->type == 0){
       	   packetsRecv++;
       	   double loss = ((packetsSent+packetsRecv)-packetsRecv)/(packetsSent+packetsRecv)*100.0;
       	   double duration = (clock()-start)/CLOCKS_PER_SEC;
       	   cout<<"Packet number: "<<packetsRecv<<"   Packet Loss: "<<loss<<"    " << "Time Elapsed: " <<duration <<endl;
	}
     }

     usleep(2000000);
   }
}


