#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>


int main(int argc, char* argv[]){
      int fd[2];
      int fd1[2];
      if (pipe(fd)==-1){
            perror("Pipe: ");
            return 1;
      }
      if (pipe(fd1)==-1){
            perror("Pipe: ");
            return 1;
      }
      if (argc!=3){
            printf("Insufficient parameters.\n");
      }
      else{
            int pid=fork();
            if (pid==0){
                  //child process
                  //lap time
                  close(fd[0]);
                  close(fd1[1]);
                  int laps=atoi(argv[1]), lapTime=atoi(argv[2]);
                  int count=0, timePassed=0;
                  while (count< laps){
                        sleep(1);
                        timePassed++;
                        //the next line sets the stdout to line buffered(default behavior)
                        //that is set to full buffered(i.e. print contents after the program executes) when using pipes
                        setvbuf(stdout, NULL, _IONBF, 0);
                        printf("%d ", timePassed);
                        int bytesWritten=write(fd[1], &timePassed, sizeof(int));
                        if (timePassed==lapTime){
                              int bytesRead=read(fd1[0], &count, sizeof(int));
                              timePassed=0;
                        }
                  }
            }
            else {
                  //parent process
                  //total time
                  close(fd[1]);
                  close(fd1[0]);
                  int laps=atoi(argv[1]), lapTime=atoi(argv[2]);
                  int timePassed=0, count=0;
                  while (count < laps){
                        int bytesRead=read(fd[0], &timePassed, sizeof(int));
                        if (timePassed==lapTime){
                              printf("\nLap %d completed.\n", count);
                              count++;
                              int bytesWritten=write(fd1[1], &count, sizeof(int));
                        }
                  }

            }
      }

      return 0;
}