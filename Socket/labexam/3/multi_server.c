#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define PORT 6000
#define PORT2 7000

int main(int argc, char *argv[])
{
	struct sockaddr_in client1, client2, server,server2;
	char msg[100];
	int mm[3][3];
	int fd, fd2, len, addr_len;
	memset(&client1, 0, sizeof(client1));
	memset(&client2, 0, sizeof(client2));
	memset(&server, 0, sizeof(server));
	memset(&server2, 0, sizeof(server2));
	
	//setting for client
	client1.sin_family = AF_INET;
	client1.sin_port = htons(4000);

	client2.sin_family = AF_INET;
	client2.sin_port = htons(5000);
	
	inet_pton(AF_INET, "127.0.0.1", &client1.sin_addr);
	inet_pton(AF_INET, "127.0.0.1", &client2.sin_addr);

	fd = socket(AF_INET, SOCK_DGRAM, 0);
	fd2 = socket(AF_INET, SOCK_DGRAM, 0);

	if(fd < 0){
		printf("socket error\n");
	}
	if(fd2 < 0){
		printf("socket2 error\n");
	}
	// fixig one server port for client1
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);	
	server.sin_port = htons(PORT);
	
	server2.sin_family = AF_INET;
	server2.sin_addr.s_addr = htonl(INADDR_ANY);	
	server2.sin_port = htons(PORT2);
	
	if(bind(fd, (struct sockaddr*)&server, sizeof(server)) < 0){
		printf("bind error\n");
		exit(0);
	}
	if(bind(fd2, (struct sockaddr*)&server2, sizeof(server2)) < 0){
		printf("bind error\n");
		exit(0);
	}
	
	while(1){
		addr_len = sizeof(client1);
		if((len = recvfrom(fd, msg, 99, 0, (struct sockaddr *)&client1, &addr_len)) < 0){
			perror("recvfrom");
			exit(0);
		}
		printf("\nMessage received: \n");
		int i, j;
		int ii = 0, jj = 0;
		i = 0;
		for (ii = 0; ii < 3; ii++) {
			for (jj = 0; jj < 3; jj++) {
				mm[ii][jj] = msg[i]-48;
				i += 2;
			}
		}
		for (i = 0; i < 3; i++) {
			for (j = 0; j < 3; j++) {
				printf("%d ", mm[j][i]);
			}
			printf("\n");
		}
		int x1 = mm[0][0]*(mm[1][1]*mm[2][2] - mm[1][2]*mm[2][1]);
		int x2 = mm[0][1]*(mm[1][0]*mm[2][2] - mm[1][2]*mm[2][0]);
		int x3 = mm[0][2]*(mm[1][0]*mm[2][1] - mm[1][1]*mm[2][0]);
		int det = x1-x2+x3;
		if (det == 0) {
			printf("Singular\n");
		} else {
			printf("Non-singular\n");
		}
		/*//strcat(msg, "Mr.");
		if((len = sendto(fd2, msg, strlen(msg)+1, 0, (struct sockaddr*)&client2, sizeof(client2))) < 0){	
			perror("sendto");
			exit(0);
		}*/
	}
	return 0;
}
