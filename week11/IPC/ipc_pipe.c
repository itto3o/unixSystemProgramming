#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char* argv[]) {
	int fd1[2], fd2[2];
	pid_t pid;
	char buf[257];
	int len, status;

	if(pipe(fd1) == -1) {
		perror("pipe error, fd1");
		exit(1);
	}
	if(pipe(fd2) == -1) {
		perror("pipe error, fd2");
		exit(1);
	}

	switch(pid = fork()) {
		case -1 :
			perror("fork error");
			exit(1);
			break;

		case 0 : //child
			close(fd1[1]);
			close(fd2[0]);
			write(1, "Child Process:", 15);
			len = read(fd1[0], buf, 256);
			write(1, buf, len);

			strcpy(buf, "Good\n");
			write(fd2[1], buf, strlen(buf));
			break;

		default :
			close(fd1[0]);
			close(fd2[1]);
			buf[0] = '\0';
			write(fd1[1], "Hello\n", 6);
			waitpid(pid, &status, 0);

			write(1, "Parent Process:", 15);
			len = read(fd2[0], buf, 256);
			write(1, buf, len);
			break;
	}
	return 0;
}
