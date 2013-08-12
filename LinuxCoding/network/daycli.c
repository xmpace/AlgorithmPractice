#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#define MAX_BUFFER 80
#define DAYTIME_SERVER_PORT 13
#define SERVER_IP "127.0.0.1"

int main(int argc, char **argv)
{
  int connectFd;
  int ret;

  connectFd = socket(AF_INET, SOCK_STREAM, 0);
  if (connectFd == -1) {
    printf("%s: %s\n", "socket", strerror(errno));
    return -1;
  }

  struct sockaddr_in servAddr;
  memset(&servAddr, 0, sizeof(servAddr));
  servAddr.sin_family = AF_INET;
  servAddr.sin_port = htons(DAYTIME_SERVER_PORT);
  servAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

  ret = connect(connectFd, 
		(const struct sockaddr*)&servAddr, 
		sizeof(servAddr));
  if (ret == -1) {
    printf("%s\n", strerror(errno));
    return -1;
  }

  int nRecv;
  int limit = MAX_BUFFER;
  char recvBuf[MAX_BUFFER+1];
  int index = 0;
  do {
    nRecv = read(connectFd, recvBuf + index, limit);
    if (nRecv == 0) {
      break;
    }
    else {
      index += nRecv;
      limit -= nRecv;
    }
  } while (true);
  recvBuf[index] = '\0';
  printf("%s\n", recvBuf);

  close(connectFd);

  return 0;
}
