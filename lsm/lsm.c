#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct dataset
{
  double x;
  double y;
};

double calc_n(int dataNumber)
{
  double i = dataNumber;
  double data = 1;

  while (i > 0)
  {
    data = data * i;
    i--;
  }
}

void calc_sam(struct dataset source[], int dataNumber, double *x_sam, double *y_sam)
{
  int i;
  for (i = 0; i < dataNumber; i++)
  {
    *x_sam += source[i].x;
    *y_sam += source[i].y;
  }
}

void inputData(struct dataset data[], int dataNumber, char filename[256])
{
  FILE *fp;
  int i;

  fp = fopen(filename, "r");
  if (fp == NULL)
  {
    printf("Error.\n");
    printf("Can't open file.\n");
    exit(1);
  }

  for (i = 0; i < dataNumber; i++)
  {
    fscanf(fp, "%lf", &data[i].x);
    fscanf(fp, "%lf", &data[i].y);
  }

  fclose(fp);
}

void dispData(struct dataset data[], int dataNumber)
{
  int i;

  for (i = 0; i < dataNumber; i++)
  {
    printf("%lf %lf\n", data[i].x, data[i].y);
  }
}

void lsm(struct dataset data[], int dataNumber)
{
  dispData(data, dataNumber);


  /* $B$3$3$+$i:G>.Fs>hK!$N%W%m%0%i%`$r=q$/(B */
}

int main(int argc, char *argv[])
{
  struct dataset *data;
  int dataNumber;
  char filename[256];

  if (argc - 1 != 2)
  {
    printf("Error.\n");
    printf("Usage: ./a.out [Data Number] [Filename]\n");
    exit(1);
  }

  dataNumber = atoi(argv[1]);
  strcpy(filename, argv[2]);

  data = (struct dataset *)malloc(sizeof(struct dataset) * dataNumber);

  inputData(data, dataNumber, filename);

  lsm(data, dataNumber);

  return 0;
}
