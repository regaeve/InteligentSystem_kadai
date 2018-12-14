#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "dragonPole.h"

void dragonpoleMain();
int calcBattlePoint(int *selection);

int main(void)
{
  int i,j;
  int point;
  int selection[ITEM];
  int max_point = 0;
  int count = 1000000;
  int random_selector = 0;

  srand((unsigned)time(NULL));

  /* システム初期化 */
  dragonpoleMain();

  /* 初期化 (技をすべて0にする) */
  for (i=0; i<ITEM; i++) {
    selection[i] = 0;
  }

  /* 技を選択 */
  for(i=0; i<count; i++){
    for(j=0;j<ITEM ;j++){
      selection[j] = rand() % 2;
    }
    /* 戦闘力を計測 (スカウターのこと) */
    point = calcBattlePoint(selection);
    if(point > max_point){
      max_point = point;
      printf("%d\n",max_point);
    }

  }

  printf("戦闘力は%d\n", max_point);

  return 0;
}
