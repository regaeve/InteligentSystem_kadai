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

/*--------------------------------------------------------------------
        Function
--------------------------------------------------------------------*/
void initilize(int argc, char *argv[], char filename[], int *itemNum,
	       int *maxWeight);
void getData(struct item *itemData, char filename[], int itemNum);
void dispData(int itemNum, int limit);
void GAmain(struct item *itemData, int itemNum, char *gene[], int maxWeight);

/*--------------------------------------------------------------------
        Function  : メイン関数
        Comment   :
--------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
  int i;
  char filename[256];		// データ読み込みのためのファイル名
  
  struct item *itemData;	// アイテムの情報(重量，価値)
  int itemNum;			// アイテムの数
  char *gene[POPULATION];	// 遺伝子の並び
  int maxWeight;		// 重量の最大制限

  /* 初期化 */
  srand(0);
  initilize(argc, argv, filename, &itemNum, &maxWeight);
  itemData = (struct item *)malloc(sizeof(struct item)*itemNum);
  for(i=0; i<POPULATION; i++) {
    gene[i] = (char *)malloc(sizeof(char)*itemNum);
  }
  getData(itemData, filename, itemNum);


  /* GA */
  GAmain(itemData, itemNum, gene, maxWeight);
      
 
  /* 事後処理 */
  free(itemData);
  for(i=0; i<POPULATION; i++) {
    free(gene[i]);
  }

  return 0;
}
