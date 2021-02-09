#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "server.h"
#include "util.h"

void start_server(struct server_info* info) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        error_and_exit("Could not create socket.\n");
    }
    socklen_t addrlen = sizeof(struct sockaddr);
    if (bind(sock, info->addr, addrlen) == -1) {
        error_and_exit("Could not bind to port.\n");
    }
    if (listen(sock, info->backlog) == -1) {
        error_and_exit("Could not listen on port.\n");
    }
    while(1) {
        struct sockaddr_in clientaddr;
        int conn = accept(sock, (struct sockaddr*) &clientaddr, &addrlen);
        int pid = fork();
        if (pid == -1) {
            // fork failed, print error message and ignore connection
            fputs("Fork failed.\n", stderr);
            close(conn);
            continue;
        } else if (pid != 0) {
            // parent, close connection since it belongs to the child
            close(conn);
            continue;
        } else {
            // child, handle connection
            dup2(conn, 0);
            dup2(conn, 1);
            if (info->pipe_stderr) {
                dup2(conn, 2);
            }
            if (info->timeout && fork() == 0) {
                sleep(info->timeout);
                if (info->show_dc_msg) {
                    puts("\nYour connection has been timed out.");
                }
                close(conn);
                kill(getppid(), SIGKILL);
                break;
            }
            execvp(info->argv[0], info->argv);
            close(conn);
            break;
        }
    }
}
