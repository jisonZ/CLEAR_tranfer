#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	int fd;
printf("Warm it up.exe\n");
	fd = open("/dev/meschar", O_RDWR);      // Capital o, not zero
	char testStr[20];
	printf("Enter a String:\n");
	scanf("%19s",testStr);
       int tmp = write(fd, testStr, 20);	
	return 0;
}
