#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "common.h"
#include <string.h>

int main(int argc, char** argv){
	int fd = open("file5_2.txt", O_WRONLY | O_APPEND);
	if (fd < 0){
		fatal("open");
	}

	if(lseek(fd, 0, SEEK_SET) < 0){
		fatal("lseek");
	}

	char* buff = "THIS IS BUFFER=)";
	int buff_size = strlen(buff);// don`t write \0
	if(write(fd, buff, buff_size) < 0){
		fatal("write");
	}
}