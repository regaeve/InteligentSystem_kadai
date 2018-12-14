/*
 *  GA 
 *
 *  comment  :
 *
 *  Copyright (C) by Shinichi OEDA.
 *  All rights reserved.
 *  大枝 真一 <oeda@j.kisarazu.ac.jp>
 *
 */

/*--------------------------------------------------------------------
        Include Header
--------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "knapsack.h"
#include "GA.h"
#include "MT.h"
/*--------------------------------------------------------------------
        Function
--------------------------------------------------------------------*/
void GAmain(struct item *itemData, int itemNum, char *gene[], int maxWeight);
void calcFitness(struct item *itemData, int itemNum, char *gene[],
		 int fitness[], int maxWeight);
void makePopulation(char *gene[], int itemNum);
void dispGene(char *gene[], int itemNum);
void dispGeneIndividual(char *gene[], int itemNum, int individualNo);
void dispFitness(int fitness[]);
int calcMaxFitness(int fitness[]);
void selection(int fitness[], int parents[]);
void crossover(char *gene[],char *nextGene[],int parents[]);
void mutation(char *nextGene[],int parents[]);

/*--------------------------------------------------------------------
        Function  : GAメイン関数
        Comment   :
--------------------------------------------------------------------*/
void GAmain(struct item *itemData, int itemNum, char *gene[], int maxWeight)
{
  int i, j;
  int fitness[POPULATION];	// 適合度
  int maxFitness;		// 最大適合度
  int maxFitnessAll;		// 全世代を通じた最大適合度
  char *nextGene[POPULATION];	// 次世代の遺伝子の並び
  int parents[2];		// 選択される親2個体
  int popNum;			// 次世代に残す個体数のカウンタ
  int generation;		// 世代数
  
  init_genrand(10);
  /* 次世代の遺伝子の並びのメモリを確保 */
  for(i=0; i<POPULATION; i++) {
    nextGene[i] = (char *)malloc(sizeof(char)*itemNum);
  }

  /* 初期集団を生成 */
  makePopulation(gene, itemNum);

  maxFitnessAll = 0;
  for(generation=0; generation<GENERATION; generation++) {

    /* 適合度を算出 */
    calcFitness(itemData, itemNum, gene, fitness, maxWeight);
    maxFitness = calcMaxFitness(fitness);

    /* 全世代を通じた最大値を算出 */
    if(maxFitnessAll<maxFitness) {
      maxFitnessAll = maxFitness;
    }
    printf("%d %d\n", generation, maxFitnessAll);

    for(popNum=0; popNum<POPULATION; popNum+=2) {
      /* 選択(ルーレット選択) */
      selection(fitness, parents);
      
      /* 交叉 */
      crossover(gene,nextGene,parents);
      
      /* 突然変異 */
      mutation(nextGene,parents);
      
    }

    /* 生成した次世代の遺伝子の並びをコピーする */
    for(i=0; i<POPULATION; i++) {
      for(j=0; j<itemNum; j++) {
        gene[i][j] = nextGene[i][j];
      }
    }
        
  }

  /* 事後処理 */
  for(i=0; i<POPULATION; i++) {
    free(nextGene[i]);
  }

}

/*--------------------------------------------------------------------
        Function  : 初期集団を生成
        Comment   :
--------------------------------------------------------------------*/
void makePopulation(char *gene[], int itemNum)
{
  int i, j;

  for(i=0; i<POPULATION; i++) {
    for(j=0; j<itemNum; j++) {

      if(genrand_int32()%2 == 0) {
	gene[i][j] = 0;
      }
      else {
	gene[i][j] = 1;
      }

    }
  }

}
/*--------------------------------------------------------------------
        Function  : 遺伝子を標準出力
        Comment   :
--------------------------------------------------------------------*/
void dispGene(char *gene[], int itemNum)
{
  int i, j;

  for(i=0; i<POPULATION; i++) {

    printf("pop[%2d] = [", i);

    for(j=0; j<itemNum; j++) {
      printf("%d", gene[i][j]);
    }
    printf("]\n");
    
  }

}
/*--------------------------------------------------------------------
        Function  : 特定の個体の遺伝子を標準出力
        Comment   :
--------------------------------------------------------------------*/
void dispGeneIndividual(char *gene[], int itemNum, int individualNo)
{
  int i;

  printf("pop[%2d] = [", individualNo);
  
  for(i=0; i<itemNum; i++) {
    printf("%d", gene[individualNo][i]);
  }
  printf("]\n");
  
}
/*--------------------------------------------------------------------
        Function  : 適合度を標準出力
        Comment   :
--------------------------------------------------------------------*/
void dispFitness(int fitness[])
{
  int i;

  for(i=0; i<POPULATION; i++) {
    printf("fitness[%2d] = %d\n", i, fitness[i]);
  }

}
/*--------------------------------------------------------------------
        Function  : 選択(ルーレット選択)
        Comment   : 
--------------------------------------------------------------------*/
void selection(int fitness[], int parents[])
{
  int i;
  double val;
  int sum;			// 適合度の合計
  int parentNo;			// 親番号(取り得る値は0, 1)
  int num;			// 個体番号のカウンタ
  double rr;			// 取得した乱数値
  double border;		// 基準

  sum = 0;
  for(i=0; i<POPULATION; i++){
    sum += fitness[i];
  }
  
  do {
    for(parentNo=0; parentNo<2; parentNo++){

      rr = (double)rand()/RANDMAX; // 0.0 - 1.0の値      
      border = sum * rr;	// 基準決定

      num = 0;
      val = fitness[num];
      while(val<border){	// 基準borderを越えるまで適合度を足す
        num++;
        val = val + fitness[num];
      }
      parents[parentNo] = num;
     /* 
      printf("parents_number[%d] = %d, fitness = %d\n",
	    parentNo, parents[parentNo], fitness[parents[parentNo]]);
     */
    }
  } while(parentNo == num);

}
/*--------------------------------------------------------------------
        Function  : 交叉
        Comment   : 
--------------------------------------------------------------------*/
void crossover(char* gene[],char *nextGene[],int parents[2])
{

  int i;
  int randomPoint;

  randomPoint = genrand_int32() % POPULATION;
  for(i=0;i<POPULATION;i++){
    if(i > randomPoint){
      nextGene[parents[0]][i] = gene[parents[0]][i]; 
      nextGene[parents[1]][i] = gene[parents[1]][i];
    }else{
      nextGene[parents[0]][i] = gene[parents[1]][i];
      nextGene[parents[1]][i] = gene[parents[0]][i]; 
    }
  }
}

/*--------------------------------------------------------------------
        Function  : 突然変異
        Comment   : 
--------------------------------------------------------------------*/
void mutation(char* nextGene[],int parents[2])
{
  int random;
  int i,j;
  int p = 10;
  
  for(i=0;i<2;i++){
   for(j=0;j<POPULATION;j++){
     random = genrand_int32()%100;
     if(random < p){
       /*0を1に1を0にする*/
      nextGene[parents[i]][j]+=1;
      nextGene[parents[i]][j]%=2;
     }
   }
  }
}
