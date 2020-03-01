#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
void main(int argc, char **argv){
	if(argc != 2){
	printf("Usage: %s <port>\n", argv[0]);
	exit(0);
	}

	int port = atoi(argv[1]);
	int sockfd;
	struct sockaddr_in serverAddr, clientAddr;
	char buffer[1024];
	char check_buff[1024];

	socklen_t addr_size;

	sockfd = socket(PF_INET, SOCK_DGRAM, 0);
	memset(&serverAddr, '\0', sizeof(serverAddr));
	memset(&clientAddr, '\0', sizeof(clientAddr));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	while(1)
	{
		printf("--------------------------------\n");
		bzero(buffer, 1024);
		bzero(check_buff, 1024);
		fgets(buffer, 1024, stdin);
		sendto(sockfd, buffer, 1024, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
		printf("[+]Data Send: %s\n", buffer);
		recvfrom(sockfd, check_buff, 1024, 0, (struct sockaddr*)&serverAddr, &addr_size);
		printf("[+]Data Resieved: %s\n", check_buff);
		if(strcmp(buffer, check_buff) == 0) 
		{
			printf("Ok\n");
		}
		else
		{
			printf("Message error\n");
		}
		
	}
	

}
