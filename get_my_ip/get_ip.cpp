#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>

#include <cstdio>
#include <iostream>
#include <string>

#include <net/if.h>
#include <ifaddrs.h>
#include <errno.h>

#define MAX_HOST 256

static int get_my_ip(void)
{
    int    s, retval = 0;
    char   myhost[MAX_HOST] = {0};
    char   str[INET6_ADDRSTRLEN] = {0};
    struct addrinfo *addr_result = NULL;
    struct addrinfo *piter;
    struct addrinfo hints;
   
    gethostname(myhost, MAX_HOST);

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM; /* Datagram socket */

    s = getaddrinfo(myhost, NULL, &hints, &addr_result);
    if (s != 0) {
        std::cerr << "getaddrinfo: " << gai_strerror(s);
        retval = -1;
        goto EARLY_OUT;
    }
   
    std::cout << "Using getaddrinfo-------" << std::endl;
    for (piter = addr_result; piter != NULL; piter = piter->ai_next) {
        const void *paddr = NULL;
        if (piter->ai_family == AF_INET) {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)piter->ai_addr;
            paddr = &(ipv4->sin_addr);
        }
        else {
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)piter->ai_addr;
            paddr = &(ipv6->sin6_addr);
        }
       
        inet_ntop(piter->ai_family, paddr, str, sizeof(str));
        std::cout << "....address from gethostname/getaddrinfo is " << str << std::endl;
    }
    
    freeaddrinfo(addr_result);

    /* alternative impl. -- could use getifaddrs if getaddrinfo is not sufficient or correct */
    std::cout << "Using getifaddrs-------" << std::endl;
    struct ifaddrs *myaddrs;
    if(getifaddrs(&myaddrs) != 0) {
        std::cerr << "getifaddrs failed: " << strerror(errno) << std::endl;
    }
    else {
        char str[INET6_ADDRSTRLEN];
        struct ifaddrs *ifa;
        for (ifa = myaddrs; ifa != NULL; ifa = ifa->ifa_next) {
            const void *paddr = NULL;
            if (ifa->ifa_addr == NULL) {
                continue;
            }
            if (!(ifa->ifa_flags & IFF_UP)) {
                continue;
            }
            
            if (ifa->ifa_addr->sa_family == AF_INET) {
                struct sockaddr_in *ipv4 = (struct sockaddr_in *)ifa->ifa_addr;
                paddr = &(ipv4->sin_addr);
            }
            else if (ifa->ifa_addr->sa_family == AF_INET6) {
                struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)ifa->ifa_addr;
                paddr = &(ipv6->sin6_addr);
            }
            else {
                std::cerr << "got unsupported sa_family type: " << ifa->ifa_addr->sa_family << std::endl;
                continue;
            }

            if (NULL != inet_ntop(ifa->ifa_addr->sa_family, paddr, str, sizeof(str))) {
                std::cout << "....address from getifaddrs is " << str << std::endl;
            }
            else {
                std::cerr << "inet_ntop failed: " << strerror(errno) << std::endl;
            }
        }
        freeifaddrs(myaddrs);
    }

EARLY_OUT:
    std::cout << "return value :" << retval << std::endl;
    return retval;
}

int main(void) 
{
    return get_my_ip();
}
