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
void flush_buffer(int fd, char* buff, int size){
	if(write(fd, buff, size) < 0){
		fatal("write");
	}		
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
	char* wBuff = malloc(sizeof(char) * BUFFER_SIZE);
	while((nRead = read(fd, buff, BUFFER_SIZE)) > 0){
		int i = 0;
		int wI = 0;// current position in write buffer
		off_t offset = 0;
		for(; i < nRead; i++){
			if( buff[i] == 0){
				flush_buffer(fd2, wBuff, wI);
				wI = 0;
				lseek(fd2, 1, SEEK_CUR);//no hardware used, simple adjust value at kernel structure
			} else {
				wBuff[wI] = buff[i];
				wI++;
			}
		}

		if(wI > 0){
			flush_buffer(fd2, wBuff, wI);
		}
	}

	if(nRead < 0){
		fatal("Read");
	}

	printf("Ending\n");
}
