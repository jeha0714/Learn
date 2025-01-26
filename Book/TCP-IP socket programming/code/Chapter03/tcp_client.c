#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void	error_handling(char *message);

int main(int argc, char *argv[])
{
	int	sock;
	struct sockaddr_in	serv_addr;
	char message[30];
	int	str_len;
	int	idx = 0, read_len = 0;

	if (argc != 3)
	{
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit (1);
	}

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		error_handling("socket() error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
		error_handling("connect() error!");

	//while (1)
	//{
	//	read_len=read(sock, &message[idx++], 1);
	//	if (read_len == 0)
	//		break ;
	//	else if (read_len == -1)
	//		error_handling("read() error!");

	//	str_len += read_len;
	//}

	char recieve_message[100];
	char send_message[100];
	while (1)
	{
		scanf("%s", send_message);
		write(sock, send_message, strlen(send_message));

		str_len = read(sock, recieve_message, 99);
		write(STDOUT_FILENO, recieve_message, str_len);
		write(STDOUT_FILENO, "\n", 2);
	}

	printf("Message from server : %s \n", message);
	printf("Function read call count: %d \n", str_len);
	close(sock);

	return (0);
}

void	error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
