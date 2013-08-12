#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

#define HOST_NAME "www.taobao.com"
int main(int argc, char **argv)
{
  char addr[32];
  struct hostent *host;

  host = gethostbyname(HOST_NAME);
  if (host == NULL) {
    printf("%s: %s\n", "gethostbyname", strerror(errno));
    return -1;
  }

  inet_ntop(AF_INET, host->h_addr, addr, sizeof(addr));

  printf("%s: %s\n", host->h_name, addr);

  return 0;
}
