#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 200

void usage(){
	printf("Incorrect usage\n");
	exit(0);
}
void fatal(char* str){
	perror(str);
	exit(0);
}
int main(int argc, char** argv){
	if(argc < 3){
		usage();
	}
	
	int fd = open(argv[1], O_RDONLY);
	if(fd < 0){
		fatal("Fopen first");
	}

	int fd2 = open(argv[2], O_TRUNC | O_CREAT | O_WRONLY, 0777);
	if(fd2 < 0){
		fatal("Fopen second");
	}

	int nRead;
	char* buff = malloc(sizeof(char) * BUFFER_SIZE);
	while((nRead = read(fd, buff, BUFFER_SIZE)) > 0){
		if(write(fd2, buff, nRead) < 0){
			fatal("write");
		}
	}

	if(nRead < 0){
		fatal("Read");
	}

	printf("Ending\n");
}
