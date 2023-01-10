#include <windows.networking.sockets.h>
#pragma comment(lib, "Ws2_32.lib")
#include <iostream>
#include <string.h>
#include <string>
using namespace std;

int main()
{
	//starts Winsock DLLs
	WSADATA wsaData;
	if ((WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) {
		return 0;
	}

	//initializes socket. SOCK_STREAM: TCP
	SOCKET ClientSocket;
	ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ClientSocket == INVALID_SOCKET) {
		WSACleanup();
		return 0;
	}

	//Connect socket to specified server
	sockaddr_in SvrAddr;
	SvrAddr.sin_family = AF_INET;						//Address family type itnernet
	SvrAddr.sin_port = htons(27000);					//port (host to network conversion)
	SvrAddr.sin_addr.s_addr = inet_addr("127.0.0.1");	//IP address
	if ((connect(ClientSocket, (struct sockaddr*)&SvrAddr, sizeof(SvrAddr))) == SOCKET_ERROR) {
		closesocket(ClientSocket);
		WSACleanup();
		return 0;
	}
	while (1)
	{
		// Create TxBuffer
		string TxBuffer;
		cout << "Enter a String to transmit" << endl;
		getline(cin, TxBuffer);
		const char* send_Mess = TxBuffer.c_str();
		send(ClientSocket, send_Mess, sizeof(TxBuffer), 0);

		//receives RxBuffer
		char RxBuffer[128] = {};
		recv(ClientSocket, RxBuffer, sizeof(RxBuffer), 0);

		// print out the message
		cout << "Msg Rx: " << RxBuffer << endl;

		// Check if the user want to quit the program
		if (TxBuffer == "Quit" || TxBuffer == "Bye" || TxBuffer == "quit" || TxBuffer == "bye") { break; }
	}

	//closes connection and socket
	closesocket(ClientSocket);

	//frees Winsock DLL resources
	WSACleanup();

	return 1;
}
