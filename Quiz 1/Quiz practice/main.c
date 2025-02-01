#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>

int main(){
    int fd[2];
    if (pipe(fd)==-1){
        perror("Pipe: ");
        return 1;
    }

    int pid=fork();
    if (pid==0){
        //child
        close(fd[1]);
        char tmp[5][50];
        int rows=0;
        int bytesRead=read(fd[0], &rows, sizeof(int));
        for (int i=0;i<=rows;i++){
            bytesRead=read(fd[0], tmp[i], 50);
            tmp[i][bytesRead]='\0';
        }
        close (fd[0]);
        //tokenizing the string
        char arr[50][3]; //max 2 digit numbers
        char delimeter[]=" ";
        char* token;
        int index=0;
        for (int i=0;i<=rows;i++){
            token=strtok(tmp[i], delimeter);
            while (token!=NULL){
                strncpy(arr[index++], token, 2);
                printf("%s\n", token);
                token=strtok(NULL, delimeter);
            }
        }
        //calculating sum
        printf("%d\n", index);
        int sum=0;
        for (int i=0;i<index;i++){
            if (atoi(arr[i])!=0){
                printf("%d ", atoi(arr[i]));
                sum +=atoi(arr[i]);
            }
            else if (atoi(&arr[i][0])!=0){
                printf("%d ", atoi(&arr[i][0]));
                sum +=atoi(&arr[i][0]);
            } 
            else if (atoi(&arr[i][1])!=0){
                printf("%d ", atoi(&arr[i][1]));
                sum +=atoi(&arr[i][1]);
            }
        }
        printf("\nThe sum is %d.\n", sum);
        exit(0);
    }
    else{
        //parent
        int fd1=open("a.txt", O_RDONLY);
        char c, tmp[5][50];
        int i=0,j=0;
        while (read(fd1, &c, sizeof(char))==1){
            if (c!='\0' && c!='\n'){
                //add into the array
                tmp[i][j++]=c;
            }
            else{
                //read the next line in the next index
                j=0;
                i++; 
            }
        }
        close(fd1);
        // for (int k=0;k<=i;k++){
        //     printf("%s\n", tmp[k]);
        // }
        close(fd[0]);
        int bytesWritten=write(fd[1], &i, sizeof(int));
        for (int k=0;k<=i;k++){
            bytesWritten=write(fd[1], tmp[k], 50);
        }
        close(fd[1]);
        wait(NULL);
    }

    return 0;
}
