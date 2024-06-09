#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void	error_handling(char *message)
{
	write(STDERR_FILENO, message, strlen(message));
	write(STDERR_FILENO, "\n", 1);
	exit(1);
}

int	main(int ac, char *av[])
{
	int					serv_socket;
	int					clnt_socket;
	unsigned int		clnt_addr_size;
	unsigned int		test_addr_size;
	int					read_cnt;
	char				message[1024];
	struct sockaddr_in	serv_addr;
	struct sockaddr_in	clnt_addr;
	struct sockaddr_in	test_addr;

	if (ac != 2)
		error_handling("Usage: ./echo_server <port>");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(av[1]));

	serv_socket = socket(PF_INET, SOCK_STREAM, 0);
	if (serv_socket == -1)
		error_handling("socket() error");
	if (bind(serv_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)))
		error_handling("bind() error");
	if (listen(serv_socket, 5))
		error_handling("listen() error");
	clnt_addr_size = sizeof(clnt_addr);
	for (int i = 0; i < 5; i++)
	{
		if ((clnt_socket = accept(serv_socket, (struct sockaddr *)&clnt_addr, &clnt_addr_size)) == -1)
			error_handling("accept() error");
		test_addr_size = sizeof(test_addr);
		getsockname(clnt_socket, (struct sockaddr*)&test_addr, &test_addr_size);
		printf("New socket is created [port: %d]\n", ntohs(test_addr.sin_port));
		printf("<message from %s port: %d>\n", inet_ntoa(clnt_addr.sin_addr), ntohs(clnt_addr.sin_port));
		connect(serv_socket, (struct sockaddr *)&clnt_addr, sizeof(clnt_addr_size));
		read_cnt = read(serv_socket, message, 1024);
		write(STDOUT_FILENO, "\nread from serv_socket: ", 24);
		write(STDOUT_FILENO, message, read_cnt);
		while ((read_cnt = read(clnt_socket, message, 1024)) != 0)
		{
			write(clnt_socket, message, read_cnt);
			write(STDOUT_FILENO, message, read_cnt);
			write(STDOUT_FILENO, "\n", 1);
		}
		write(STDOUT_FILENO, "\n", 1);
		close(clnt_socket);
	}
	close(serv_socket);
}
