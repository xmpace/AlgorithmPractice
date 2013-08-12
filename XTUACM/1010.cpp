#include <stdio.h>

int main(int argc, char **argv)
{
  int m = 0, n = 0;
  int X[1000], Y[1000];
  int xauxilary[500][500];
  int yauxilary[500][500];

  scanf("%d", &m);
  for (int i = 0; i < m; i++)
    scanf("%d", &X[i]);

  for (int i = 0; i < m; i++)
    for (int j = 0; j < m; j++)
      scanf("%d", &xauxilary[i][j]);
      
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    scanf("%d", &Y[i]);

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      scanf("%d", &yauxilary[i][j]);

  int xindex = 0, yindex = 0;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      if (xauxilary[i][j] == 1 && yauxilary[i][j] == 0) {
	printf("%d", X[xindex++]);
      }
      else if (xauxilary[i][j] == 0 && yauxilary[i][j] == 1) {
	printf("%d", Y[yindex++]);
      }
      else if (xauxilary[i][j] == 1 && yauxilary[i][j] == 1) {
	printf("%d", X[xindex++] + Y[yindex++]);
      }
      if (i == m-1 && j == m-1)
	printf("\n");
      else
	printf(" ");
    }
  }

  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++) {
      printf("%d", xauxilary[i][j] | yauxilary[i][j]);
      if (i == m-1 && j == n-1) {
	printf("\n");
      }
      else {
	printf(" ");
      }
    }

  return 0;
}
