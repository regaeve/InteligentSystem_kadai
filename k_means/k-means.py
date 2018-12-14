import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import random
#メモ
'''
初期値依存する
クラスタの数が多いと計算量が大変なことになる
データの数が多くても計算量が大変なことになる
'''
#二点間の距離を測る関数
#戻り値は距離
def calc_distance(a,b):
  dist = 0.0
  dist += (a["x"] - b["x"])**2
  dist += (a["y"] - b["y"])**2
  dist = np.sqrt(dist)
  return dist

#重心を計算する関数
#入力はDataFrameを想定
#戻り値は(x,y)で返す  
def calc_center(group):
  sum_x = 0.0
  sum_y = 0.0
  for i in range(len(group)):
    sum_x += group["x"][i]
    sum_y += group["y"][i] 
    sum_x /= len(group)
    sum_y /= len(group)

  return np.c_[center_x,center_y]

if __name__  == '__main__':
  #csvを読み込む
  data = pd.read_csv('data.csv')

  #とりあえず表示してみる
  #print(data)

  #EPS
  EPS = 0

  #想定するクラスタ数
  V = 2

  #Gridを表示する
  plt.grid(True)

  colors = ['red','green','blue']

  #データをプロット
  #plt.scatter(data["x"],data["y"],c = 'blue',marker = 'o',s = 20)

  #plt.legend()

  #表示
  #plt.show()

  end_flag = True

  #クラスタの初期化
  #a[i] = [random.rand(-0.5,0.5),random.rand(-0.5,0.5) for i in range V] 
  a = [[0.0,0.0],[1.0,1.0],[0.5,0.5]]

  cur_cluster = pd.DataFrame(a,columns = ["x","y"])
  prev_cluster = cur_cluster


  dist_cluster = [0.0 for i in range(V)]
  dist = [0.0 for i in range(V)]

  while end_flag :

    #各データの距離を計算し，一番近いクラスタのlabelをつける
    for i in range(len(data)) :
      for j in range(V) : 
        dist_cluster[j] = calc_distance(data[i],cur_cluster[i])
        print('check')
      #距離が最小のインデックスを取得し，それをlabelとする
      data["label"][i] = dist_cluster.index(min(dist_cluster)) 
 
    #重心を計算して，クラスタを更新
    for i in range(V):
      cur_cluster[i] = calc_center(data[data["label"] == i])
  
    #更新前と比べた時の変化量を計算
    for i in range(V):
      dist[i] = calc_distance(cur_cluster[i],prev_cluster[i])
 
    #終了判定 
    if sum(dist) < EPS:
      end_flag = False 

  plt.scatter(data["x"][i],data["y"][i],c = colors[data["label"][i]],marker = 'o',s = 20)

