/* server */

//a file trans run in linux 
//write by  6520874@163.com 
#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <errno.h>

#define PORT 8848
#define BACKLOG 10

int main(void)
{
	int sockfd, conn_fd;
	struct sockaddr_in my_addr;
	struct sockaddr_in their_addr;
	int sin_size;
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		fprintf(stderr, "socket error!\n");
		return 0;
	}
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(PORT);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(my_addr.sin_zero), 8);
	if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
	{
		fprintf(stderr, "bind error!\n");
		return 0;
	}
	if (listen(sockfd, BACKLOG) == -1)
	{
		fprintf(stderr, "listen error!\n");
		return 0;
	}

	FILE *fp = fopen("wow.jpg","wb+");
	if(fp  == NULL)
	{
		printf("fopen error\n");
		return -1;
	}

	int i = 0;

	while (1)
	{
		sin_size = sizeof(struct sockaddr_in);
		if ((conn_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1)
		{
			fprintf(stderr, "accept error!\n");
			continue;
		}
		printf("server: got connection from %s\n", inet_ntoa(their_addr.sin_addr));
		if (!fork())
		{
			while(1)
			{

				char buf[1024] ={0};
				int in =   recv(conn_fd,buf,1024,0);
				if(in <= 0){ break;}
				fwrite(buf,1,in,fp);
				i++;
				printf("receive len = %d i = %d\n",in,i);
			}
		}
		close(conn_fd);
		while(waitpid(-1, NULL, WNOHANG) > 0);
	}
}
