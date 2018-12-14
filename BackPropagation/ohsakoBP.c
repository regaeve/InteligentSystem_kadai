/*
 * NeuralNetwork For XOR
 *
 * Input layer:  2
 * Hidden layer: 2
 * Output layer: 1
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define EPSILON 4.0
#define ETA 0.1
#define TIMES 1000
#define INIT_WEIGHT 0.3

#define SUM_RAW 100
#define TRAIN_RAW 90
#define TEST_RAW 10

void random_access(int iaRandarray[TRAIN_RAW*2]){
  int iCounter; /*ループカウンタ用変数*/
  int iNumRand; /*残り乱数候補数*/
  int key;
  int tmp;
  /*乱数の種を初期化*/

  /*あらかじめ配列に数値を代入しておく*/
  for( iCounter = 0 ; iCounter < TRAIN_RAW*2; iCounter++){
    iaRandarray[ iCounter ] = iCounter;
  }
  //ランダムに並べるなぜか100%を出す！！！！！！
  // for (iCounter = 0 ;iCounter < 10000;iCounter++){
  //   key = rand() % TRAIN_RAW*2;
  //   tmp = iaRandarray[key];
  //   iaRandarray[key] = iaRandarray[0];
  //   iaRandarray[0] = tmp;
  // }

  /*確認用に表示*/
  for (iCounter = 0 ;iCounter < TRAIN_RAW*2; iCounter++){
    printf("%d\n",iaRandarray[iCounter]);
  }

}
//データを読み込む関数　トレインデータ 180個 テストデータ 20個とした
void input_data(double train_data[][3],double test_data[][3])
{
  int i,j,k;
  j = 0;
  k = 0;

  //puts("check"); 
  double val;
  FILE *fp;

  fp = fopen("ohsakoA.train", "r");
  if (fp==NULL) {
    printf("can't open file.\n");
    exit(1);
  }
  for (i=0; i<SUM_RAW; i++) {
    fscanf(fp, "%lf", &val);
    if(i<TRAIN_RAW){
      train_data[j][0] = val;
    }else{
      test_data[k][0] = val;
    }
    fscanf(fp, "%lf", &val);
     if(i<TRAIN_RAW){
      train_data[j][1] = val;
      train_data[j][2] = 0.0;
      j+=1;
    }else{
      test_data[k][1] = val;
      test_data[k][2] = 0.0;
      k+=1;
    }
  }
  fclose(fp);

  fp = fopen("ohsakoB.train", "r");
  if (fp==NULL) {
    printf("can't open file.\n");
    exit(1);
  }
  for (i=0; i<SUM_RAW; i++) {
    fscanf(fp, "%lf", &val);
    if(i<TRAIN_RAW){
      train_data[j][0] = val;
    }else{
      test_data[k][0] = val;
    }
    fscanf(fp, "%lf", &val);
     if(i<TRAIN_RAW){
      train_data[j][1] = val;
      train_data[j][2] = 1.0;
      j+=1;
    }else{
      test_data[k][1] = val;
      test_data[k][2] = 1.0;
      k+=1;
    }
  }
  fclose(fp);
}

void disp_data(double data[][3],int raw)
{
  int i,j;

  for (i=0; i<raw; i++) {
    for (j=0; j<3; j++) {
      printf("%f, ", data[i][j]);
    }
    printf("\n");
  }
}
double randNum(void)
{
  return ((double)rand()/RAND_MAX-0.5)*2.0*INIT_WEIGHT;
}

double sigmoid(double x)
{
  return 1/(1+exp(-1*EPSILON*x));
}

int main(void)
{
  double train_data[TRAIN_RAW*2][3] = {0};
  double test_data[TEST_RAW*2][3] = {0};

  int iaRandarray[TRAIN_RAW*2] = {0}; /*乱数候補収納用変数*/


  double wbd, wbe, wcd, wce, wab, wac;
  double offb, offc, offa;
  double outd, oute, outb, outc, outa;
  double xb, xc, xa;
  double deltab, deltac, deltaa;

  int r;
  int i;
  double error;
  double errorSum;
  int times;
  int seed;

  int count_crrect_answer;
  FILE *fp;

  fp = fopen("error_2.dat", "w");
  if (fp==NULL) {
    printf("can't open file.\n");
    exit(1);
  }

  random_access(iaRandarray);
  //seed = (unsigned int)time(NULL);
  //printf("seed = %d\n", seed);

  input_data(train_data,test_data);
  //disptrain_data(train_data);

  for(i=0;i<10;i++){

    seed = i;

    srand(seed);
    wbd = randNum();
    wbe = randNum();
    wcd = randNum();
    wce = randNum();
    wab = randNum();
    wac = randNum();
    offb = randNum();
    offc = randNum();
    offa = randNum();

    printf("seed:%d\n",seed);
    printf("%lf\n",wbd);
    printf("%lf\n",wbe);
    printf("%lf\n",wcd);
    printf("%lf\n",wce);
    printf("%lf\n",wab);
    printf("%lf\n",wac);

    for(times=0;times<TIMES; times++) {

      errorSum = 0.0;

      for(r=0; r<TRAIN_RAW*2; r++) {

        /* ----------- */
        /* Feedforward */
        /* ----------- */
        
        /* Input layer output */
        outd = train_data[iaRandarray[r]][0];
        oute = train_data[iaRandarray[r]][1];

        /* Hidden layer output */
        xb = wbd*outd + wbe*oute + offb;
        outb = sigmoid(xb);

        xc = wcd*outd + wce*oute + offc;
        outc = sigmoid(xc);

        /* Output layer output */
        xa = wab*outb + wac*outc + offa;
        outa = sigmoid(xa);

        if(times==TIMES-1) {
          //printf("[%d]=%.10f, (%f)\n", r, outa, train_data[r][2]);
        }

        /* ---------------- */
        /* Back Propagation */
        /* ---------------- */

        error = ((outa-train_data[iaRandarray[r]][2])*(outa-train_data[iaRandarray[r]][2]));
        errorSum += error;

        deltaa = EPSILON * (1-outa) * outa * (outa-train_data[iaRandarray[r]][2]);      
        deltab = EPSILON * (1-outb) * outb * wab * deltaa;
        deltac = EPSILON * (1-outc) * outc * wac * deltaa; 

        offa -= ETA * deltaa; 
        offb -= ETA * deltab;
        offc -= ETA * deltac;
        
        wab -= ETA * deltaa * outb;
        wac -= ETA * deltaa * outc;

        wbe -= ETA * deltab * oute;
        wbd -= ETA * deltab * outd;
        
        wce -= ETA * deltac * oute;
        wcd -= ETA * deltac * outd;
      }
      //printf("errorSum = %f\n", errorSum/4.0);
      fprintf(fp, "%f\n", errorSum/4.0);

    }
    count_crrect_answer = 0;
    for(r=0; r<TRAIN_RAW*2; r++) {

      /* ----------- */
      /* Feedforward */
      /* ----------- */

      /* Input layer output */
      outd = train_data[iaRandarray[r]][0];
      oute = train_data[iaRandarray[r]][1];

      /* Hidden layer output */
      xb = wbd*outd + wbe*oute + offb;
      outb = sigmoid(xb);

      xc = wcd*outd + wce*oute + offc;
      outc = sigmoid(xc);

      /* Output layer output */
      xa = wab*outb + wac*outc + offa;
      outa = sigmoid(xa);

      //printf("[%d]=%.10f, (%f)\n", r, outa, train_data[r][2]);

      if (outa*2 >= 1){
        outa = 1.0;
      }else{
        outa = 0.0;
      }
      if(outa == train_data[iaRandarray[r]][2]) count_crrect_answer++;
    }
    printf("seed = %d ,トレインデータ正答率: %d / %d\n",i,count_crrect_answer,TRAIN_RAW*2);

    count_crrect_answer = 0;
    for(r=0; r<TEST_RAW*2; r++) {

      /* ----------- */
      /* Feedforward */
      /* ----------- */

      /* Input layer output */
      outd = test_data[r][0];
      oute = test_data[r][1];

      /* Hidden layer output */
      xb = wbd*outd + wbe*oute + offb;
      outb = sigmoid(xb);

      xc = wcd*outd + wce*oute + offc;
      outc = sigmoid(xc);

      /* Output layer output */
      xa = wab*outb + wac*outc + offa;
      outa = sigmoid(xa);

    //printf("[%d]=%.10f, (%f)\n", r, outa, test_data[r][2]);

      if (outa*2 >= 1){
        outa = 1.0;
      }else{
        outa = 0.0;
      }
      if(outa == test_data[r][2]) count_crrect_answer++;
    }
    printf("seed = %d ,テストデータ正答率: %d / %d\n",i,count_crrect_answer,TEST_RAW*2);
    printf("%lf\n",wbd);
    printf("%lf\n",wbe);
    printf("%lf\n",wcd);
    printf("%lf\n",wce);
    printf("%lf\n",wab);
    printf("%lf\n",wac);
  }
  fclose(fp);
  return 0;
}