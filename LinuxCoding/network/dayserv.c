#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <stdbool.h>

#define DAYTIME_SERVER_PORT 13
#define MAX_CLIENT 1000
#define MAX_LEN 80

int main(int argc, char **argv)
{
  int servFd, ret;
  int clientFd;
  struct sockaddr_in addr;

  servFd = socket(AF_INET, SOCK_STREAM, 0);
  if(servFd == -1) {
    printf("%s: %s\n", "socket", strerror(errno));
    return -1;
  }

  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  addr.sin_port = htons(DAYTIME_SERVER_PORT);

  ret = bind(servFd, (struct sockaddr*)&addr, sizeof(addr));
  if (ret != 0) {
    printf("%s: %s\n", "bind", strerror(errno));
    return -1;
  }

  ret = listen(servFd, MAX_CLIENT);
  if (ret != 0) {
    printf("%s: %s\n", "listen", strerror(errno));
    return -1;
  }

  time_t currentTime;
  char sendBuf[MAX_LEN];

  while (true) {
    clientFd = accept(servFd, (struct sockaddr*)NULL, NULL);
    if (clientFd > 0) {
      currentTime = time(NULL);
      snprintf(sendBuf, MAX_LEN, "%s\n", ctime(&currentTime));
      write(clientFd, sendBuf, strlen(sendBuf));
      close(clientFd);
    }
    else {
      printf("error occuced when client attemp to connect\n");
    }
  }

  return 0;
}
