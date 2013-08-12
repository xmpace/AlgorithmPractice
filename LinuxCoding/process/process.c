#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  pid_t myPid, myParentPid;
  gid_t myGid;
  uid_t myUid;

  myPid = getpid();
  myParentPid = getppid();

  myGid = getgid();
  myUid = getuid();

  printf("pid: %d\n", myPid);
  printf("parent pid: %d\n", myParentPid);
  printf("group id: %d\n", myGid);
  printf("user id: %d\n", myUid);

  return 0;
}
