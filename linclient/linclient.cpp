#include <stdio.h>
#include <io.h>
#include <winsock2.h>
//pragma ws2_32.lib
typedef struct {int x;int y;} vektor;


	char sendstr[30]="bla";


int main(){

    WSADATA wsaData;

    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);

    if (iResult != NO_ERROR)

              printf("Client: Error at WSAStartup().\n");

    else

              printf("Client: WSAStartup() is OK.\n");

 

    // Create a socket.

    SOCKET msocket;

    msocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

 

    if (msocket == INVALID_SOCKET)

    {

        printf("Client: socket() - Error at socket(): %ld\n", WSAGetLastError());

        WSACleanup();

        return 0;

    }

   else

       printf("Client: socket() is OK.\n");

 

    // Connect to a server.

    sockaddr_in clientService;

 

    clientService.sin_family = AF_INET;

    // Just test using the localhost, you can try other IP address

    clientService.sin_addr.s_addr = inet_addr("127.0.0.1");

    clientService.sin_port = htons(55555);

 

    if (connect(msocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR)

    {

        printf("Client: connect() - Failed to connect.\n");

        WSACleanup();

        return 0;

    }

    else

    {

       printf("Client: connect() is OK.\n");

       printf("Client: Can start sending and receiving data...\n");

    }

 

    // Send and receive data.

    int bytesSent;

    int bytesRecv = SOCKET_ERROR;

    // Be careful with the array bound, provide some checking mechanism...

    char sendbuf[200] = "This is a test string from client";

    char recvbuf[200] = "";

 

       // Receives some test string from server...

       while(bytesRecv == SOCKET_ERROR)

       {
		   vektor testcoord;
testcoord.x=22;
testcoord.y=33;

		   static vektor* datapointer=&testcoord;
           bytesRecv = recv(msocket,(char *)datapointer, sizeof(vektor), 0);
		  printf("%i",testcoord.x);
       printf("%i",testcoord.y);
		  if (bytesRecv == 0 || bytesRecv == WSAECONNRESET)

        {

             printf("Client: Connection Closed.\n");

            break;

        }

 

        if (bytesRecv < 0)

            return 0;

       else

       {

              printf("Client: recv() is OK.\n");

              printf("Client: Received data is: \"%s\"\n", recvbuf);

              printf("Client: Bytes received is: %ld.\n", bytesRecv);

       }

    }

 

       // Sends some test data to server...bytesSent = send(msocket, sendbuf, strlen(sendbuf), 0);
	   
	   bytesSent = send(msocket,(char *)sendbuf, strlen(sendbuf), 0);

       if(bytesSent == SOCKET_ERROR)

              printf("Client: send() error %ld.\n", WSAGetLastError());

       else

       {

              printf("Client: send() is OK - Bytes sent: %ld\n", bytesSent);

              printf("Client: The test string sent: \"%s\"\n", sendbuf);

       }

 

    WSACleanup();

    return 0;

}