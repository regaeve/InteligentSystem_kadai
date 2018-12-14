#include <stdio.h>
#include "dragonPole.h"

void dragonpoleMain();
int calcBattlePoint(int *selection);

int main(void)
{
  int i;
  int point;
  int selection[ITEM];

  int *dp_t;
  int *dp_t_plus_one;

  /* システム初期化 */
  dragonpoleMain();

  /* 初期化 (技をすべて0にする) */
  for (i=0; i<ITEM; i++) {
    selection[i] = 0;
  }

  /* 技を選択 (ここでは，0, 4, 8の技を選択した)*/

  /* 戦闘力を計測 (スカウターのこと) */
  point = calcBattlePoint(selection);

  printf("戦闘力は%d\n", point);

  return 0;
}
