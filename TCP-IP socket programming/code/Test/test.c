#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
	char buf1[100];
	char buf2[100];
	memset(buf1, 0, 100);
	memset(buf2, 0, 100);

	int fd1 = open("server.cpp", O_RDONLY);
	//int fd2 = open("server.cpp", O_RDONLY);
	//int fd2 = open("write.cpp", O_RDONLY);
	int fd2 = fd1 + 1;

	printf("-----------\n");
	printf("%d|%d\n", fd1,fd2);
	//fd2 = dup(fd1);
	dprintf(2, "%d|%d\n", dup2(fd1, fd2), fd2);
	dprintf(2, "-----------\n");

	read(fd1, buf1, 10);
	buf1[10] = '\0';
	dprintf(2, "%s\n", buf1);
	read(fd2, buf2, 10);
	buf2[10] = '\0';
	dprintf(2, "%s\n", buf2);

	memset(buf1, 0, 100);
	memset(buf2, 0, 100);
	dprintf(2, "-----------\n");

	read(fd1, buf1, 10);
	buf1[10] = '\0';
	dprintf(2, "%s\n", buf1);
	read(fd2, buf2, 10);
	buf2[10] = '\0';
	dprintf(2, "%s\n", buf2);

	//close(fd1);
	//close(fd2);
	return (0);
}
