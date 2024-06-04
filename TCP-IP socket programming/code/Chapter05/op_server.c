#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *message);

void reverse(char str[], int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

char* itoa(int num) {
    static char str[20];  // 정적 배열로 문자열 관리
    int i = 0;
    int isNegative = 0;
    int base = 10;

    // 0을 처리
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // 음수일 경우
    if (num < 0 && base == 10) {
        isNegative = 1;
        num = -num;
    }

    // 나머지 숫자들을 처리
    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }

    // 음수일 경우 '-' 추가
    if (isNegative) {
        str[i++] = '-';
    }

    str[i] = '\0';

    // 문자열 뒤집기
    reverse(str, i);

    return str;
}

int main(int argc, char *argv[])
{
	int		serv_sock, clnt_sock;
	char	message[BUF_SIZE];
	int		str_len, i;

	struct sockaddr_in	serv_adr, clnt_adr;
	socklen_t			clnt_adr_sz;

	if (argc != 2)
	{
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (serv_sock == -1)
		error_handling("socket() error");

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	if (bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
		error_handling("bind() error");

	if (listen(serv_sock, 5) == -1)
		error_handling("listen() error");

	clnt_adr_sz = sizeof(clnt_adr);
	clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
	if (clnt_sock == -1)
		error_handling("accept() error");

	int	n_number;
	int	number[10];
	char operator;
	int result = 0;

	read(clnt_sock, message, BUF_SIZE);
	n_number = atoi(message);

	for (int i = 0; i < n_number; i++)
	{
		read(clnt_sock, message, BUF_SIZE);
		number[i] = atoi(message);
	}

	read(clnt_sock, message, BUF_SIZE);
	operator = message[0];

	if (operator == '+')
	{
		for (int i = 0; i < n_number; i++)
			result += number[i];
	}
	else if (operator == '-')
	{
		for (int i = 0; i < n_number; i++)
			result -= number[i];
	}
	else if (operator == '*')
	{
		for (int i = 0; i < n_number; i++)
			result *= number[i];
	}
	else if (operator == '/')
	{
		for (int i = 0; i < n_number; i++)
			result /= number[i];
	}
	write(clnt_sock, itoa(result), strlen(itoa(result)) + 1);

	close(clnt_sock);
	close(serv_sock);
	return (0);
}

void	error_handling(char *msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit (1);
}
