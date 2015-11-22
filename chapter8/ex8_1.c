#include <pwd.h>
#include <stdio.h>
#include <string.h>


struct passwd* kgetpwnam(const char* name){
	struct passwd* pwd;
	while((pwd = getpwent()) != NULL) {
		if(strcmp(name, pwd->pw_name) == 0){
			return pwd;
		}
	}

	return NULL;
}

int main(int argc, char** argv){
	// we assume that 'vagrant' user exist
	struct passwd* pwd = kgetpwnam("vagrant");
	printf("PWD33 %s\n", pwd->pw_name);
}