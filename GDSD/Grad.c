#include <stdio.h>
#include <math.h>
//最急降下法　二変数対応

double f(double x,double y){
  return sin(x) + 2.0 * x * cos(y) + 0.2 * cbrt(x) + cbrt(y);
}

double dx(double x,double y){
  return cos(x) + 2.0 * cos(y) + 0.4 * x;
}

double dy(double x,double y){
  return 2.0 * x * -1.0 * sin(y) + 0.4 * y;
}

int main(void){
  double pre_x,cur_x;
  double pre_y,cur_y;
  double epsilon;
  double eita;
  int count = 0;

  epsilon = 0.00000001;
  eita = 0.01;
  pre_x = 5.0;
  pre_y = 10.0;

  while(1){
    cur_x = pre_x - eita * dx(pre_x,pre_y);
    cur_y = pre_y - eita * dy(pre_x,pre_y);
    if(fabs(cur_x - pre_x) < epsilon && fabs(cur_y - pre_y) < epsilon) break;
    pre_x = cur_x;
    pre_y = cur_y;
    count++;
  }
  printf("pre_x = %f\n",pre_x);
  printf("pre_y = %f\n",pre_y);
  printf("count = %d\n",count);

}
