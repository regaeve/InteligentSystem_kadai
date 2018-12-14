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

/*--------------------------------------------------------------------
        Function  : 初期化
        Comment   : 引数チェック, ファイル名の決定, アイテムの数を決定
--------------------------------------------------------------------*/
void initilize(int argc, char *argv[], char filename[], int *itemNum,
	       int *maxWeight)
{
  FILE *fp;
  char tmp[256];
  int num;
  int max;

  if(argc-1 != 1) {
    printf("Error.\n");
    printf("引数は1つです.\n");
    printf("第1引数: ナップサック問題のファイル名\n");
    exit(1);
  }
  strcpy(filename, argv[1]);

  fp = fopen(filename, "r");
  if(fp == NULL) {
    printf("Error.\n");
    printf("%sファイルを開くことができませんでした.\n", filename);
    exit(1);
  }

  fscanf(fp, "limit=%d\n", &max);
  fgets(tmp, 256, fp);
  num = 0;
  while(fgets(tmp, 256, fp)!=NULL) {
    num++;
  }

  *itemNum = num;
  *maxWeight = max;
}

/*--------------------------------------------------------------------
        Function  : ファイルからデータ入力
        Comment   : 
--------------------------------------------------------------------*/
void getData(struct item *itemData, char filename[], int itemNum)
{
  FILE *fp;
  char tmp[256];
  int i;

  if( (fp = fopen(filename, "r"))==NULL) {
    printf("can't open error.\n");
    exit(1);
  }

  fgets(tmp, 256, fp);
  fgets(tmp, 256, fp);
  for (i=0; i<itemNum; i++) {
    fscanf(fp, "%d,%d,%d\n", &itemData[i].number, &itemData[i].weight, &itemData[i].money);
  }
  fclose(fp);

}
/*--------------------------------------------------------------------
        Function  : 読み込んだデータを標準出力
        Comment   : 
--------------------------------------------------------------------*/
void dispData(int itemNum, int limit, struct item *itemData)
{
  int i;

  printf("limit=%d\n", limit);
  printf("number, weight, money\n");
  for (i=0; i<itemNum; i++) {
    printf("%6d,%6d,%6d\n", itemData[i].number, itemData[i].weight, itemData[i].money);
  }

}
