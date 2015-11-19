#include <fcntl.h>
#include <sys/uio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VECTOR_SIZE 3

void fatal(char* str){
	perror(str);
	exit(0);
}

ssize_t kreadv(int fd, const struct iovec* iov, int iovcnt){
	printf("KREADV\n");
}

ssize_t kwritev(int fd, const struct iovec* iov, int iovcnt){
	int i;
	char* buff = NULL;
	size_t buff_size = 0;

	for(i = 0; i < iovcnt; i++){
		printf("%d\n", i);
		struct iovec v = iov[i];

		size_t new_buff_size = buff_size + v.iov_len;
		buff = realloc(buff, new_buff_size);
		printf("Buff_size %d \n", buff_size);
		buff + buff_size;
		buff_size = new_buff_size;
		memcpy(buff, v.iov_base, v.iov_len);
		buff -= 
	}

	write(fd, buff, buff_size);

	free(buff);
}

int main(int argc, char** argv){
	int fd = open("file5_7.txt", O_CREAT | O_TRUNC | O_RDWR, 0777);
	struct iovec iov[VECTOR_SIZE];
	int a = 1, b = 2, c = 3;
	size_t expected_bytes = sizeof(a) + sizeof(b) + sizeof(c);

	iov[0].iov_base = &a;
	iov[0].iov_len = sizeof(a);
	iov[1].iov_base = &b;
	iov[1].iov_len = sizeof(b);
	iov[2].iov_base = &c;
	iov[2].iov_len = sizeof(c);

	// ssize_t st = writev(fd, iov, VECTOR_SIZE);
	ssize_t st = kwritev(fd, iov, VECTOR_SIZE);
	if(st < 0){
		fatal("Writeev");
	}

	if(st != expected_bytes) {
		printf("Write not ok! Expected %d bytes, write %d bytes\n");
	} else {
		printf("Write OK! (%d) bytes\n", expected_bytes);
	}

	
}