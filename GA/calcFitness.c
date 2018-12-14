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
#include "knapsack.h"
#include "GA.h"

/*--------------------------------------------------------------------
        Function  : 適合度を算出
        Comment   :
--------------------------------------------------------------------*/
void calcFitness(struct item *itemData, int itemNum, char *gene[],
		 int fitness[], int maxWeight)
{
  int i, j;
  int money, weight;

  for(i=0; i<POPULATION; i++) {

    money = weight = 0;
    for(j=0; j<itemNum; j++) {
      if(gene[i][j]==1) {
	money += itemData[j].money;
	weight += itemData[j].weight;
      }
    }

    if(maxWeight<weight) {
      money = 0;
    }
    fitness[i] = money;
  }
  
}
/*--------------------------------------------------------------------
        Function  : 最大適合度を算出
        Comment   :
--------------------------------------------------------------------*/
int calcMaxFitness(int fitness[])
{
  int i;
  int max;

  max = fitness[0];

  for(i=1; i<POPULATION; i++) {

    if(max<fitness[i]) {
      max = fitness[i];
    }

  }

  return max;
}
