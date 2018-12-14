import numpy as np
import math
from matplotlib import pyplot as plt
from numpy.linalg import pinv

if __name__ == '__main__':
    
    # 0~10の間に100個の等間隔な点のベクトル作成
    x = np.linspace(-1.5,1.5,100)

    # 真の値x
    y = (x-1.0)**2 * (x+1.0)**2
    plt.plot(x,y,label='kadai1')

    a = 6.0
    sigma = 0.01

    for i in range(0,10):
        a -= sigma * (4 * a**3 - 4 * a)
        print(a)
    
    # ノイズの乗った値
    #y_measured = c[0] + c[1] * x + c[2] * x**2 + c[3] * x**3 + np.random.normal(0,10,x.size) 
    #plt.plot(x,y_measured,"ro",label='measured')

    # 任意のデータから読み込む場合

    plt.legend()
    plt.grid()
    plt.show()
