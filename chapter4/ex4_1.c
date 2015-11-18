#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define RBUFFER_LEN 200

void fatal(char* str){
	perror(str);
	exit(0);
}
void usage(){
	printf("Wrong usage\n");
	exit(0);
}
int main(int argc, char** argv){
	size_t nRead;
	int fd;
	int flags = O_CREAT | O_WRONLY;
	char* rBuffer = malloc(sizeof(char) * RBUFFER_LEN);

	if(argc < 2){
		usage();
	} else if(argc > 2){
		if(strcmp(argv[2], "-a") == 0){
			flags |= O_APPEND;
		} else {
			usage();
		}
	} else {
		flags |= O_TRUNC;
	}

	mode_t mode = 0777;
	
	fd = open(argv[1], flags, mode);
	if(fd < 0){
		fatal("Open");
	}

	while((nRead = read(STDIN_FILENO, rBuffer, RBUFFER_LEN)) > 0){
		if(write(STDOUT_FILENO, rBuffer, nRead) != nRead){
			fatal("stdout write");
		}

		if(write(fd, rBuffer, nRead) != nRead){
			fatal("file write");
		}
	}

	if(nRead == -1){
		fatal("read");
	}
	
	if(close(fd) < 0){
		perror("close");
	}
}
