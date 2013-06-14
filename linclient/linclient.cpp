#include <stdio.h>
#include <io.h>
#include <winsock2.h>
//pragma ws2_32.lib
/*
WinSock2.h ln 119
typedef UINT_PTR        SOCKET;
einstweilen würd ich mal die pointer gleichsetzen problem :vorzeichenlose darstellung.. das könnte schiefgehen
*/
typedef struct {int x;int y;} vektor;

	char sendstr[30]="bla";


void writetoserver(int filedes){
vektor position;
position.x=111;
position.y=999;
int nbytes;

nbytes=write(filedes,&position,8);//sizeof(int*2)
if (nbytes<0)
	exit(1);
}

int main(){
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    SOCKET msocket;
    msocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in clientService;

 

    clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = inet_addr("127.0.0.1");
	clientService.sin_port = htons(55555);

 

    connect(msocket, (SOCKADDR*)&clientService, sizeof(clientService));

    int bytesSent;

    //int bytesRecv = SOCKET_ERROR;

    // Be careful with the array bound, provide some checking mechanism...

    char sendbuf[200] = "This is a test string from client";

    //char recvbuf[200] = "";

 

    //       bytesRecv = recv(msocket, recvbuf, 200, 0);

      //        printf("Client: Received data is: \"%s\"\n", recvbuf);

       bytesSent = send(msocket, sendbuf, strlen(sendbuf), 0);


    WSACleanup();

    return 0;


}