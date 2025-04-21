#include "scanner.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <fcntl.h>

int
is_host_alive(const char* ip_ptr)
{
    int sock;
    struct sockaddr_in addr;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) return 0;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80); //attempt port 80
    inet_pton(AF_INET, ip_ptr, &addr.sin_addr);

    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    int result = connect(sock, (struct sockaddr*)&addr, sizeof(addr));
    close(sock);
    return (result == 0);
}

void
scan_ports(const char* ip_ptr)
{
    int common_ports[] = {22, 80, 443};
    int num_ports = sizeof(common_ports) / sizeof(int);
    
    for (int i = 0; i < num_ports; i++)
    {
        int port = common_ports[i];
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) continue;

        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        inet_pton(AF_INET, ip_ptr, &addr.sin_addr);

        struct timeval timeout;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;
        setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
        
        int result = connect(sock, (struct sockaddr*)&addr, sizeof(addr));
        close(sock);

        if (result == 0)
        {
            printf("    [OPEN] Port %d\n", port);
        }
    }
}
