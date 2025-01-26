#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	pid_t pid = fork();

	if (pid == 0)
	{
		puts("Hi, I am a child proccess");
	}
	else
	{
		printf("Child Process Id: %d \n", pid);
		sleep(10);
	}

	if (pid == 0)
		puts("End Child Process");
	else
		puts("End Parent Process");
	return (0);
}
