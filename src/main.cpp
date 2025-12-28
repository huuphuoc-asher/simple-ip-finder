#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  int status;
  struct addrinfo hints, *res, *p;
  char ipstr[INET6_ADDRSTRLEN];

  if(argc != 2) {
    fprintf(stderr, "usage: showip hostname \n");
  }

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  if ((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0) {
    fprintf(stderr, "gai error: %s\n",gai_strerror(status));
    return(2);
  }

  printf("IP address for %s:\n\n", argv[1]);

  for(p = res; p != NULL; p = p->ai_next) {
    void *addr;
    std::string ipver;
    struct sockaddr_in *ipv4;
    struct sockaddr_in6 *ipv6;

    if(p->ai_family == AF_INET) {
      ipv4 = (struct sockaddr_in *) p->ai_addr;
      addr = &(ipv4->sin_addr);
      ipver = "IPv4";
    }

    if (p->ai_family == AF_INET6) {
      ipv6 = (struct sockaddr_in6 *)p->ai_addr;
      addr = &(ipv6->sin6_addr);
      ipver = "IPv6";
    }

   inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr) ;
    printf("%s: %s\n", ipver.c_str(), ipstr);
  }

  freeaddrinfo(res);
  return 0;
}
