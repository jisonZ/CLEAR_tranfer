#include <syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define sys_jz118 448
int main(int argc, char** argv) {

        if (argc <= 2) {
                long res = syscall(sys_jz118, 0, 1);
                return res;
        }
	int arg1 = atoi(argv[1]);
        int arg2 = atoi(argv[2]);

        printf("making system call with arg: %d %d\n", arg1, arg2);
        long res = syscall(sys_jz118, arg1, arg2);
        return res;
}
