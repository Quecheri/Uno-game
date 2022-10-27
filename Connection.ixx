#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <thread>
export module Connection;

export class Connection
{
public:
	~Connection()
	{
		ShutDown();
	}
	/// <summary>
	/// Inicjalizing ddls
	/// </summary>
	void Inicjalize()
	{

#define DEFAULT_BUFLEN 512
#define WIN32_LEAN_AND_MEAN
		// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

	}
	/// <summary>
	/// recive string from external source
	/// </summary>
	/// <returns></returns>
	std::string GetSeed()
	{
		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {

		}
		else if (iResult == 0)
			printf("Connection closing...\n");
		else {
			printf("recv failed with error: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
		}
		std::string res = "";
		for (int i = 0; i < 512; i++)
		{
			if (recvbuf[i] = '$')
			break;
			res = +recvbuf[i];
		}
		return res;
	}
	/// <summary>
/// Opens Client connection
/// </summary>
/// <returns></returns>
	int ClientConnect(std::string ip)
	{
		const char* i = ip.c_str();
		PCSTR IP = i;

		struct addrinfo* result = NULL,
			* ptr = NULL,
			hints;

		// Initialize Winsock
		iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			printf("WSAStartup failed with error: %d\n", iResult);
			return 1;
		}

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		// Resolve the server address and por
		
		
		iResult = getaddrinfo(IP, DEFAULT_PORT, &hints, &result);
		if (iResult != 0) {
			printf("getaddrinfo failed with error: %d\n", iResult);
			WSACleanup();
			return 1;
		}

		// Attempt to connect to an address until one succeeds
		for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

			// Create a SOCKET for connecting to server
			ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
				ptr->ai_protocol);
			if (ConnectSocket == INVALID_SOCKET) {
				printf("socket failed with error: %ld\n", WSAGetLastError());
				WSACleanup();
				return 1;
			}

			// Connect to server.
			iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
			if (iResult == SOCKET_ERROR) {
				closesocket(ConnectSocket);
				ConnectSocket = INVALID_SOCKET;
				continue;
			}
			break;
		}

		freeaddrinfo(result);

		if (ConnectSocket == INVALID_SOCKET) {
			printf("Unable to connect to server!\n");
			WSACleanup();
			return 1;
		}
		ConnectionIsOpen = true;



		return 0;


	}
	/// <summary>
	/// Opens Serwer connection
	/// </summary>
	/// <returns></returns>
	int  OpenServerConnection()
	{

		struct addrinfo* result = NULL;
		struct addrinfo hints;
		// Initialize Winsock
		iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			printf("WSAStartup failed with error: %d\n", iResult);
			return 1;
		}

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		hints.ai_flags = AI_PASSIVE;

		// Resolve the server address and port
		iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
		if (iResult != 0) {
			printf("getaddrinfo failed with error: %d\n", iResult);
			WSACleanup();
			return 1;
		}

		// Create a SOCKET for connecting to server
		ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
		if (ListenSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			freeaddrinfo(result);
			WSACleanup();
			return 1;
		}

		// Setup the TCP listening socket
		iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			printf("bind failed with error: %d\n", WSAGetLastError());
			freeaddrinfo(result);
			closesocket(ListenSocket);
			WSACleanup();
			return 1;
		}

		freeaddrinfo(result);

		iResult = listen(ListenSocket, SOMAXCONN);
		if (iResult == SOCKET_ERROR) {
			printf("listen failed with error: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();
			return 1;
		}

		// Accept a client socket
		ConnectSocket = accept(ListenSocket, NULL, NULL);
		if (ConnectSocket == INVALID_SOCKET) {
			printf("accept failed with error: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();
			return 1;
		}
		closesocket(ListenSocket);
		// No longer need server socket
		ConnectionIsOpen = true;

		return 0;
	}
	/// <summary>
	/// Shuts down connection
	/// </summary>
	/// <returns></returns>
	int ShutDown()
	{
		iResult = shutdown(ConnectSocket, SD_SEND);
		if (iResult == SOCKET_ERROR) {
			printf("shutdown failed with error: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return 1;
		}

		// Receive until the peer closes the connection

		// cleanup
		ConnectionIsOpen = false;
		ClearConnections(ConnectSocket);
	}
	/// <summary>
	/// close sockets and clean connection
	/// </summary>
	/// <param name="socket"></param>
	void ClearConnections(SOCKET socket)
	{
		closesocket(ConnectSocket);
		WSACleanup();
	}
	/// <summary>
	/// sends single messeage through a net
	/// </summary>
	/// <param name="msg"></param>
	/// <returns></returns>
	bool SendString(std::string msg)
	{
		PushMessage(msg);
		if (SendSomething() == 1)return false;
		return true;
	}
	/// <summary>
	/// sends everything from sendbuff through net
	/// </summary>
	/// <returns></returns>
	int SendSomething()
	{
		iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
		if (iResult == SOCKET_ERROR) {
			printf("send failed with error: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return 1;
		}
		printf("Bytes Sent: %ld\n", iResult);
		return 0;
	}
	/// <summary>
	/// clears the reciving buffer
	/// </summary>
	void ClearBuffer()
	{
		for (int i = 0; i < 512; i++)//czyszczenie bufora
		{
			if (recvbuf[i] != '$')  recvbuf[i] = ' ';
			else if (recvbuf[i] == '$')
			{
				recvbuf[i] = ' ';
				break;
			}

		}
	}

	/// <summary>
	/// Stops program and wait for external communication
	/// </summary>
	/// <returns></returns>
	std::string WaitForAnswer()
	{
		ClearBuffer();
		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {

		}
		else if (iResult == 0)
			printf("Connection closing...\n");
		else {
			printf("recv failed with error: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return "ex1";
		}
		return recvbuf;
	}
	/// <summary>
	/// Load send buffer with message
	/// </summary>
	/// <param name="message"></param>
	void PushMessage(std::string message)
	{
		message += "$";
		if (message.length() - 1 < sendbuflen)strcpy_s(sendbuf, message.c_str());
	}
	/// <summary>
	/// Sends seed through net
	/// </summary>
	/// <param name="seed"></param>
	/// <returns></returns>
	int InicjalizeGameRules(std::string seed)
	{
		if (!SendString(seed))
			return -1;

		return 0;
	}
	/// <summary>
	/// Load seed from serwer
	/// </summary>
	/// <returns>seed</returns>
	std::string LoadGameRules()
	{
		std::string seed = WaitForAnswer();
		return seed;
	}
	/// <summary>
	/// Function starts liestening loop
	/// </summary>
	void MonitorCommunication()
	{

		while (ConnectionIsOpen)
		{
			if (IsListening)
			{
				WaitForAnswer();
				StopListening();
				IsLoaded = true;
			}
			else std::this_thread::sleep_for(std::chrono::milliseconds(200));
		}
	}
	/// <summary>
	/// Starts Listenig
	/// </summary>
	void StartListening()
	{
		IsListening = true;
	}
	/// <summary>
	/// Stops Listenig
	/// </summary>
	void StopListening()
	{
		IsListening = false;
	}
	/// <summary>
	/// Returns Last recived message
	/// </summary>
	/// <returns>recvbuf</returns>
	std::string GetLastMessage()
	{
		return recvbuf;
	}
	/// <summary>
	/// Returns true if message is loaded
	/// </summary>
	/// <returns>IsLoaded</returns>
	bool IsAnswerRecived()
	{
		return IsLoaded;
	}
	/// <summary>
	/// clears isLoaded bool
	/// </summary>
	void ClearMessage()
	{
		IsLoaded = false;
	}
	/// <summary>
	/// returns info about connection
	/// </summary>
	/// <returns>ConnectionIsOpen</returns>
	bool GetConnectionInfo()
	{
		return ConnectionIsOpen;
	}
private:

	char sendbuf[DEFAULT_BUFLEN];
	int sendbuflen = DEFAULT_BUFLEN;

	WSADATA wsaData;
	int iSendResult;
	int iResult;

	SOCKET ConnectSocket = INVALID_SOCKET;
	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;


	PCSTR DEFAULT_PORT = "52137";
	int messageCount = 0;

	bool IsLoaded = false;
	bool IsListening = false;
	bool ConnectionIsOpen = false;
};