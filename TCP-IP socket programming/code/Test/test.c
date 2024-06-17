#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "apple,grape$ banana$,cherry";
    char *token;

	printf("%s|", str);
    token = strtok(str, "$, ");
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, "$ ,");
		printf("%s|", str);
    }

    return 0;
}
