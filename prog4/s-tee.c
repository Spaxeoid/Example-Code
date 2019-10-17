// S-Tee
// Timothy Leach
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>



int main(int argc, char* argv[])
{
      int i;
      char* file = argv[1];
      char* program = argv[2];
      char buf[1024];

      int fd[2], pid;
      pipe(fd);
      int status;

      if((pid = fork()) > 0)
      {
          close(fd[0]);
          close(1);
          close(2);
          dup(fd[1]);
          dup(fd[1]);
          close(fd[1]);
          for(i = 0; i < argc; i++)
          {
              sprintf(buf, "%s ", argv[i]);
              write(1, buf, strlen(buf));
          }

          sprintf(buf, "\n");
          write(1, buf, strlen(buf));

          execv(program, &argv[2]);

          write(1, "Exec failed\n", 12);
          close(1);
          close(2);
          wait(&status);
      }
      else
      {
          close(fd[1]);
          int numRead;
          int fp;
          fp = open(file, O_CREAT | O_RDWR | O_EXCL, 0644);

          if(fp == -1)
          {
            sprintf(buf, "The file already exists\n");
            write(1, buf, strlen(buf));
            exit(1);
          }
          while((numRead = read(fd[0], buf, 1024)) > 0)
          {
              write(1, buf, numRead);
              write(fp, buf, numRead);
          }
      }

}
