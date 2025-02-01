#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[]){
    int sum=0;
    for (int i=1;i<argc;i++){
        if (atoi(argv[i])!=0){
            sum +=atoi(argv[i]);
        }
    }
    printf("The sum is %d.\n", sum);
    return 0;
}