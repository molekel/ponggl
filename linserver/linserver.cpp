#include <stdio.h>
#include <io.h>
#include <winsock2.h>
//pragma ws2_32.lib


#define port 5555

typedef struct {int x;int y;} vektor;

	char readstring[30]="";
	
int readfromclient (int filedes)
{
vektor position;
int buffer;
int *bufferp;
bufferp=&buffer;
int nbytes;
nbytes=read(filedes,&position,8);
if (nbytes <0)
{
	exit(1);
}
else if (nbytes ==0)//eof
	return -1;
else
{
int test=888888;
printf("printingint %i",test);
printf("received posx %i",position.x);
printf("received posy %i",position.y);
return 0;
}
}

void main(){

WORD wVersionRequested;
WSADATA wsaData;
int wsaerr;

wVersionRequested = MAKEWORD(2, 2);
wsaerr = WSAStartup(wVersionRequested, &wsaData);

SOCKET m_socket;
m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
sockaddr_in service;


service.sin_family = AF_INET;
service.sin_addr.s_addr = inet_addr("127.0.0.1");
service.sin_port = htons(55555);

 

bind(m_socket, (SOCKADDR*)&service, sizeof(service)) ;
listen(m_socket, 1);
SOCKET AcceptSocket;

//while (1)
//{
//AcceptSocket = SOCKET_ERROR;
//while (AcceptSocket == SOCKET_ERROR)
//{
AcceptSocket = accept(m_socket, NULL, NULL); //akzeptiert alles ... 
//}

 
m_socket = AcceptSocket; 

//break;

//}

 

//int bytesSent;
//int bytesRecv = SOCKET_ERROR;
//char sendbuf[200] = "This string is a test data from server";

char recvbuf[200] = "";
//bytesSent = send(m_socket, sendbuf, strlen(sendbuf), 0);
 
//recv(m_socket, recvbuf, 200, 0);
int socketpointer=0;
UINT_PTR dort;
dort=m_socket;
//socketpointer=*dort;
//printf("sockp%i",socketpointer);

read(dort,&recvbuf,20);	


printf("Server: Received data is: \"%s\"\n", recvbuf);



WSACleanup();





/*
while (1)
{
//select() linux zeug..bzw wer connected
int connection;
int size;
connection=accept(serversocket,NULL,NULL);
	if (connection <0)
		exit(1);
	else 
//	if (readfromclient(i)<0)
	{
		recv(serversocket,readstring,30,0);
		printf("read%s",readstring);
		//	close(serversocket);
		WSACleanup();
		exit(0);
	}
	*/
	}
 




