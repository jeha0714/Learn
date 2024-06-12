#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(const char *message);
void read_routine(int sock);
void write_routine(int sock);

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;

	pid_t pid;
	socklen_t adr_sz;
	int str_len, state;
	char buf[BUF_SIZE];
	if (argc != 2)
	{
		printf("Usage : %s <port>\n", argv[0]);
		exit (1);
	}

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	if (bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
		error_handling("bind() error");
	if (listen(serv_sock, 5) == -1)
		error_handling("listen() error");

	while (1)
	{
		adr_sz = sizeof(clnt_adr);
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz);
		if (clnt_sock == -1)
			continue;
		else
			puts("new client connected...");
		pid = fork();
		if (pid == -1)
		{
			close(clnt_sock);
			continue;
		}
		if (pid == 0)
		{
			read_routine(clnt_sock);
		}
		else
			write_routine(clnt_sock);
	}
	close(serv_sock);
	return (0);
}

void read_routine(int sock)
{
	char buf[BUF_SIZE];
	int	result;

	dprintf(2, "Come here!\n");
	sleep(3);
	while(1)
	{
		dprintf(2, "Before Write!\n");
		result = write(sock, "Hello 42Seoul webserv!\n", strlen("Hello 42Seoul webserv!\n"));
		dprintf(2, "write return value : %d \n", result);
		sleep(1);
	}
	sleep(10);
	//while (1)
	//{
	//	int str_len = read(sock, buf, BUF_SIZE);
	//	if (str_len == 0)
	//		return ;

	//	buf[str_len] = 0;
	//	printf("Message from server: %s", buf);
	//}
}

void write_routine(int sock)
{
	char buf[BUF_SIZE];

	shutdown(sock, SHUT_WR);
	sleep(100);
	//while (1)
	//{
	//	fgets(buf, BUF_SIZE, stdin);
	//	if (!strcmp(buf, "q\n") || !strcmp(buf, "Q\n"))
	//	{
	//		shutdown(sock, SHUT_WR);
	//		return ;
	//	}
	//	write(sock, buf, strlen(buf));
	//}
}

void error_handling(constchar *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit (1);
}
