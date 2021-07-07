#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int cstatus;
    pid_t child1 = fork();
    int pipefd[2];
    char buffer[128];

   if (pipe(pipefd) == -1) {
	perror("pipe");
	exit(-1);
    } 

    if (child1 == 0)
    {
	close(pipefd[0]); 
        printf("child1\n");
	if (dup2(STDOUT_FILENO, pipefd[1]) == -1) {
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	fprintf(stdout, "hello parent!\n");
	close(pipefd[1]);
        exit(0);
    } else
    {
	close(pipefd[1]);
	for (int n = 0; (n = read(pipefd[0], buffer, 1)> 0);) {
		printf("Received %d from child\n", n);
		write(STDOUT_FILENO, buffer, 1);
		printf("\n");
	}
	close(pipefd[0]);
	waitpid(child1, &cstatus, 0);
	printf("child status was %d\n", cstatus);
	printf("Goodbye");
    }
		return 0;
}
