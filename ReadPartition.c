#include <stdio.h>

int main(int argc, char** argv)
{
  FILE* fp = NULL;
  char buffer[512];
  size_t numread = 0;
  
  fp = fopen("//dev//sda", "r");
  if (fp == NULL)
  {
    printf("read //dev//sda0 error!\n");
    return -1;
  }
  numread = fread((void*)buffer, 1, 512, fp);
  if (numread == 0)
  {
    printf("can't read data from //dev//sda0!\n");
    return -1;
  }
  
  return 0;
}
