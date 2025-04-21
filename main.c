#include "scanner.h"
#include <stdio.h>

int
main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <subnet prefix>\n", argv[0]);
        printf("Ex: %s 127.0.0\n", argv[0]);
        return 1;
    }

    const char* subnet_prefix_ptr = argv[1];
    int start_ip = 1; 
    int end_ip = 254;

    for (int i = start_ip; i <= end_ip; i++)
    {
        char ip[32];
        snprintf(ip, sizeof(ip), "%s.%d", subnet_prefix_ptr, i);

        if (is_host_alive(ip))
        {
            printf("[+] j5 alive: %s\n", ip);
            scan_ports(ip);
        }
    }
    
    return 0;
}









































