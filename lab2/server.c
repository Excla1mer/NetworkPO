#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void main(int argc, char **argv){
	if(argc != 2){
	printf("Usage: %s <port>\n", argv[0]);
	exit(0);
	}	
	int t = 0, random;
	int port = atoi(argv[1]);
	int sockfd;
	struct sockaddr_in si_me, si_other;
	char buffer[1024];
	socklen_t addr_size;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	memset(&si_me, '\0', sizeof(si_me));
	memset(&si_other, '\0', sizeof(si_other));

	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(port);
	si_me.sin_addr.s_addr = inet_addr("127.0.0.1");
	while(t == 0)
	{
		if((bind(sockfd, (struct sockaddr*)&si_me, sizeof(si_me))) < 0 )
		{
			printf("Port is unavailable\nPlease input new port -> ");
			scanf("%d",&port);
			si_me.sin_port = htons(port);
		}
		else
		{
			t = 1;
		}
	}
	while(1)
	{
		printf("-----------------------------------------------------------------\n");
		addr_size = sizeof(si_other);
		bzero(buffer, 1024);
		recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)& si_other, &addr_size);
		printf("[+]Data Received: %s\n", buffer);
		//printf("[#]From: %s\n", inet_ntoa(si_me.sin_addr));
		random = rand() % 10; 
		if(random >= 7)
		{
			*buffer = "Error message";
			sendto(sockfd, buffer, 1024, 0, (struct sockaddr*)&si_other, sizeof(si_other));
			printf("[+]Data Send: %s\n", buffer);
		}
		else
		{
			sendto(sockfd, buffer, 1024, 0, (struct sockaddr*)&si_other, sizeof(si_other));
			printf("[+]Data Send: %s\n", buffer);
		}
		
	}
	
	
}
