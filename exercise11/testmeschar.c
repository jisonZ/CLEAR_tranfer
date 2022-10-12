#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
static char receive[256];

int main(){
	int fd;
	int ret;
	char stringtoSend[256];
	printf("Warm it up.exe\n");
	fd = open("/dev/meschar", O_RDWR);      // Capital o, not zero
	printf("say my name\n");
	scanf("%[^\n]%*c", stringtoSend);
	ret = write(fd, stringtoSend, strlen(stringtoSend));
	printf("repeat back what you said hit enter");
	getchar();
	ret = read(fd, receive, 256);
	printf("Repeat message: %s\n", receive);
	return 0;
}
