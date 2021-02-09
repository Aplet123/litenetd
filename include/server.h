#ifndef ND_SERVER_H
#define ND_SERVER_H
#include <stdint.h>
#include <sys/socket.h>
#include <stdbool.h>
#include <arpa/inet.h>

struct server_info {
    struct sockaddr* addr;
    unsigned short timeout;
    unsigned short backlog;
    bool pipe_stderr;
    bool show_dc_msg;
    char* const* argv;
};

void start_server(struct server_info* info);

#endif
