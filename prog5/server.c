// Server.c


#include <errno.h>
#include <strings.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <fcntl.h>

#define NOT_CONNECTED 0
#define CONNECTED 1
#define LISTING 2

main() {
    int listener, conn, length, temp, i, fp;
    int state[32];
    int location[32];
    char buf[1024];
    char ch;
    char *file = "server_log";
    struct sockaddr_in s1, s2;
    fd_set mask;

   // sprintf(buf, "test.out");
    //write(fd, buf, strlen(buf));

    memset(state, NOT_CONNECTED, sizeof(state));

    listener = socket(AF_INET, SOCK_STREAM, 0);

    bzero((char *)&s1, sizeof(s1));
    s1.sin_family = AF_INET;
    s1.sin_addr.s_addr=htonl(INADDR_ANY);
    s1.sin_port = htons(0);
    length = sizeof(s1);
    bind(listener, (struct sockaddr *)&s1, length);
    getsockname(listener, (struct sockaddr *)&s1, &length);
    sprintf(buf, "RSTREAM:: assigned port number %d\n", ntohs(s1.sin_port));
    write(1, buf, strlen(buf));

    listen(listener, 1);


    for(;;)
    {
        length = sizeof(s2);
        conn = accept(listener, (struct sockaddr *)&s2, &length);
        state[conn-4] = CONNECTED;
        sprintf(buf, "Log #: ");
        write(conn, buf, strlen(buf));
        memset(buf, 0, sizeof(buf));
        FD_ZERO(&mask); FD_SET(0, &mask); FD_SET(conn, &mask);
        temp = select(conn+1, &mask, NULL, NULL, NULL);
        if(temp >= 0) {
            memset(buf, 0, sizeof(buf));
            while((read(conn, &buf, 1024)) > 0) {
                write(1, buf, strlen(buf));

                if (strncmp(buf, "log", 3) == 0) {
                    fp = open(file, O_CREAT | O_RDWR, 0644);
                    lseek(fp, 0, SEEK_END);
                    memset(buf, 0, sizeof(buf));
                    sprintf(buf, "Log #: Logging\n");
                    write(conn, buf, strlen(buf));
                    memset(buf, 0, sizeof(buf));
                    read(conn, &buf, 1024);
                    write(fp, buf, strlen(buf));
                    memset(buf, 0, sizeof(buf));
                    close(fp);
                }
                if (strncmp(buf, "list", 4) == 0) {
                    sprintf(buf, "Log #: Listing\n");
                    write(conn, buf, strlen(buf));
                    memset(buf, 0, sizeof(buf));
                    fp = open(file, O_CREAT | O_RDWR, 0644);
                    read(fp, &buf, 1024);
                    write(conn, buf, strlen(buf));
                    memset(buf, 0, sizeof(buf));
                    close(fp);
                }

            }

            state[conn-4] = NOT_CONNECTED;
            close(conn);
        }
        else
        {
            sprintf(buf, "No input\n");
            write(1, buf, strlen(buf));
        }

    }


}