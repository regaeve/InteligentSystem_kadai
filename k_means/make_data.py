
import numpy as np
import pandas as pd

# 2次元プロットデータ(3クラス)を作成する import numpy as np
# 各データの個数
NUM = 30

np.random.seed(seed = 810)
# クラスター中心 
cluster1 = [0,0] 
cluster2 = [0.5,0.5] 
cluster3 = [0,1]

# データを正規乱数で生成
x1 = np.random.normal(cluster1[0], 0.2, NUM) 
y1 = np.random.normal(cluster1[1], 0.2, NUM)
x2 = np.random.normal(cluster2[0], 0.3, NUM)
y2 = np.random.normal(cluster2[1], 0.1, NUM) 
x3 = np.random.normal(cluster3[0], 0.15, NUM) 
y3 = np.random.normal(cluster3[1], 0.15, NUM)

# データを結合
xx = [] 
xx.extend(x1) 
xx.extend(x2) 
xx.extend(x3)

yy = [] 
yy.extend(y1) 
yy.extend(y2) 
yy.extend(y3)

data = np.c_[xx, yy]
df = pd.DataFrame(data, columns=["x","y"])

#ファイル出力
df.to_csv("data.csv")

# ファイル出力
#np.savetxt("data.csv", data, delimiter=",")
