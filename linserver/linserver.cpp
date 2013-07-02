#include <stdlib.h>

#include <stdio.h>
#include <io.h>
#include <winsock2.h>
//pragma ws2_32.lib


#define port 5555

typedef struct {int x;int y;} vektor;

	char readstring[30]="";


int main(){

WORD wVersionRequested;
WSADATA wsaData;
int wsaerr;

 

// Using MAKEWORD macro, Winsock version request 2.2
wVersionRequested = MAKEWORD(2, 2);
wsaerr = WSAStartup(wVersionRequested, &wsaData);

SOCKET m_socket;

m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);



sockaddr_in service;


service.sin_family = AF_INET;
// "127.0.0.1" is the local IP address to which the socket will be bound.
service.sin_addr.s_addr = inet_addr("127.0.0.1");
// 55555 is the port number to which the socket will be bound.
service.sin_port = htons(55555);

 

// Call the bind function, passing the created socket and the sockaddr_in structure as parameters.
// Check for general errors.

if (bind(m_socket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) 
{
    printf("Server: bind() failed: %ld.\n", WSAGetLastError());
    closesocket(m_socket);
    return 0;
}
else 
{
    printf("Server: bind() is OK!\n");
}

// Call the listen function, passing the created socket and the maximum number of allowed
// connections to accept as parameters. Check for general errors.

if (listen(m_socket, 10) == SOCKET_ERROR)
{
	printf("Server: listen(): Error listening on socket %ld.\n", WSAGetLastError());
}
else
{
printf("Server: listen() is OK, I'm waiting for connections...\n");

}

 

// Create a temporary SOCKET object called AcceptSocket for accepting connections.
/*schleife umbauen*/
SOCKET AcceptSocket;

 

// Create a continuous loop that checks for connections requests. If a connection
// request occurs, call the accept function to handle the request.

printf("Server: Waiting for a client to connect...\n" );

printf("***Hint: Server is ready...run your client program...***\n");

// Do some verification...

while (1)

{
AcceptSocket = SOCKET_ERROR;
while (AcceptSocket == SOCKET_ERROR)
{
AcceptSocket = accept(m_socket, NULL, NULL);
}

 

// else, accept the connection...
// When the client connection has been accepted, transfer control from the
// temporary socket to the original socket and stop checking for new connections.

printf("Server: Client Connected!\n");

m_socket = AcceptSocket; 

break;

}

 

int bytesSent;

int bytesRecv = SOCKET_ERROR;

char sendbuf[200] = "9123456789";

// initialize to empty data...

char recvbuf[200] = "";

 

// Send some test string to client...
printf("Server: Sending some test data to client...\n");
int sender=543210;
//bytesSent = send(m_socket, &sender,sizeof(int), 0);
	   vektor testcoord;
testcoord.x=98765;
testcoord.y=44444;
static vektor* vektorpointer=&testcoord;

bytesSent = send(m_socket,(char *)vektorpointer, sizeof(vektor), 0);

//bytesSent = write(&m_socket,&sender,sizeof(int));
 

if (bytesSent == SOCKET_ERROR)
       printf("Server: send() error %ld.\n", WSAGetLastError());
else
{
       printf("Server: send() is OK.\n");
       printf("Server: Bytes Sent: %ld.\n", bytesSent);
}

 

// Receives some test string from client...and client
// must send something lol...

bytesRecv = recv(m_socket, recvbuf, 200, 0);

 

if (bytesRecv == SOCKET_ERROR)

       printf("Server: recv() error %ld.\n", WSAGetLastError());

else

{
     printf("Server: recv() is OK.\n");

       printf("Server: Received data is: \"%s\"\n", recvbuf);

       printf("Server: Bytes received: %ld.\n", bytesRecv);

}

 

WSACleanup();

return 0;

}
 




