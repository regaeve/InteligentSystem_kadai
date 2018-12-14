#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define CHECK 1 //ガウスの消去法における三角行列のチェック用

struct dataset
{
  double x;
  double y;
};

void gauss(int dimNumber,double **a,double *p);

void inputData(struct dataset data[],int dataNumber, char filename[256])
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

void sai(struct dataset data[], int dimNumber,int dataNumber)
{
        int i,j,k;
        double X,Y;

/*動的確保*/
        double **A;
        A = (double**)malloc(sizeof(double*)*dimNumber);
        for (i=0;i<dimNumber+1;i++){
                A[i]=(double*)malloc(sizeof(double)*dimNumber+1);
        }

        double *xx;
        xx = (double*)malloc(sizeof(double)*dimNumber); 

            FILE *output1;
            FILE *output2;
            output1=fopen("output1.data","w");
            output2=fopen("output2.data","w");

/*初期化*/
        for(i=0;i<dimNumber;i++) {
                for(j=0;j<dimNumber+1;j++) {
                        A[i][j]=0.0;
                }
        }

/*ガウスの消去法で解く行列の作成*/
        for(i=0;i<dimNumber;i++) {
                for(j=0;j<dimNumber;j++) {
                        for(k=0;k<dataNumber;k++) {
                                A[i][j]+=pow(data[k].x,i+j);
                        }
                }
        }
        for(i=0;i<dimNumber;i++) {
                for(k=0;k<dataNumber;k++) {
                        A[i][n]+=pow(data[k].x,i)*data[k].y;
                }
        }
/*ガウスの消去法の実行（配列xxは解、すなわち多項式の係数を入れるためのもの）*/
        gauss(dimNumber,A,xx);

/*GNUPLOTで表示するために最小２乗法による関数のデータをファイル保存*/
        for(X=data[0].x-10.0;X<data[dataNumber].x+10.0;X+=0.01) {
                Y=0.0;
                for(i=0;i<dimNumber;i++) {
                        Y+=xx[i]*pow(X,i);
                }
                fprintf(output1,"%f %f\n",X,Y);
        }

/*GNUPLOTで表示するために、最小２乗法に使われたデータを保存*/
        for(i=0;i<dataNumber;i++) {
                fprintf(output2,"%f %f\n",data[i].x,data[i].y);
        }

        fclose(output1);
        fclose(output2);

/*メモリ解放*/
        for (i=0;i<dimNumber;i++) {
	        free(A[i]);
        }
        free(A);
        free(xx);

}

void gauss(int dimNumber,double **a,double *xx)
{
        int i,j,k,l,pivot;
        double p,q,m;

/*動的確保*/
        double *x;
        x = (double*)malloc(sizeof(double)*dimNumber);

        double **b;
        b = (double**)malloc(sizeof(double*)*1);
        for(i = 0;i<dimNumber+1;i++){
                b[i]=(double*)malloc(sizeof(double));
        }

        for(i=0;i<dimNumber;i++) {
                m=0;
                pivot=i;

                for(l=i;l<dimNumber;l++) {
                        if(fabs(**(a+l*dimNumber+i))>m) {   //i列の中で一番値が大きい行を選ぶ
                                m=fabs(a[l][i]);
                                pivot=l;
                        }
                }

                if(pivot!=i) {                          //pivotがiと違えば、行の入れ替え
                        for(j=0;j<dimNumber+1;j++) {
                                b[0][j]=a[i][j];        
                                a[i][j]=a[pivot][j];
                                a[pivot][j]=b[0][j];
                        }
                }
        }

        for(k=0;k<dimNumber;k++) {
                p=**(a+k*dimNumber+k);              //対角要素を保存
                a[k][k]=1;              //対角要素は１になることがわかっているから

                for(j=k+1;j<dimNumber+1;j++) {
                        a[k][j]/=p;
                }

                for(i=k+1;i<dimNumber;i++) {
                        q=a[i][k];
                        for(j=k+1;j<dimNumber+1;j++) {
                                a[i][j]-=q*a[pivot][j];
                        }
                a[i][k]=0;              //０となることがわかっているところ
                }
        }

//解の計算
        for(i=dimNumber-1;i>=0;i--) {
                x[i]=a[i][dimNumber];
                for(j=dimNumber-1;j>i;j--) {
                        x[i]-=a[i][j]*x[j];
                }
        }

//行列が最後どうなったか見たいときに実行
#if CHECK==1
        for(i=0;i<dimNumber;i++) {
                for(j=0;j<dimNumber+1;j++) {
                        printf("%10.3f",a[i][j]);
                }
                printf("\n");
                
        }
#endif

        printf("解は\n");
        for(i=0;i<dimNumber;i++) {
                printf("%f\n",x[i]);
                xx[i]=x[i];
        }

/*メモリ解放*/
        free(x);
        free(b[1]);
        free(b);

}

int main(int argc, char *argv[])
{
  struct dataset *data;
  int dataNumber;
  int dimNumber;
  char filename[256];

  if (argc - 1 != 3)
  {
    printf("Error.\n");
    printf("Usage: ./a.out [Data Number] [dimNumber] [Filename]\n");
    exit(1);
  }

    dataNumber = atoi(argv[1]);
    dimNumber = atoi(argv[2]);
    strcpy(filename, argv[3]);

    data = (struct dataset *)malloc(sizeof(struct dataset) * dataNumber);

    inputData(data, dataNumber, filename);

    /*double x[S]={1.0,2.0,3.0,4.0,5.0},y[S]={7.987,2.986,1.998,2.224,5.678};*/

/*データの横軸に値する数値を配列xに小さい順に入れ、
それぞれの横軸の値における縦軸の値を配列yに入れ関数saiに渡す*/
    sai(data,dimNumber,dataNumber);

    return 0;
}