#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main() {
	//string to hold data we are gonna send to clients.
	char server_message[256] = "Say hi to MR. Server";
	// 1.create the server socket
	int server_socket;
	server_socket = socket(AF_INET,SOCK_STREAM,0);

	// define the server address.
	struct sockaddr_in server_address,client_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY; // any ip on local machine
	unsigned int len = sizeof(server_address);

	// 2.bind the socket to out specified ip and port
	bind(server_socket , (struct sockaddr *)&server_address,len);
	// 3. listen
	listen(server_socket , 5);
	// 4. accept
	int count = 5;
	while(count--) {
		// client_address stores the client addr.
		int client_socket = accept(server_socket,(struct sockaddr *)&client_address,&len);
		// send the message
		int sent = send(client_socket,server_message,sizeof(server_message),0);
		//printf("Sent %d bytes to client %s : \n",sent,inet_ntoa(client_address.sin_addr) );
		//close the socket
		close(client_socket);
	}
	close(server_socket);

	return 0;
}