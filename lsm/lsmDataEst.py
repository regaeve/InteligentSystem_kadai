import numpy as np
import math
from matplotlib import pyplot as plt
from numpy.linalg import pinv


# 最小二乗法で多項式フィッティング

def errSumsOfSq(y, t):
    return np.sqrt((np.sum((y - t)**2) / len(y)))

def test(c,x,y):
    c = np.array(c)

   
    return 0

if __name__ == '__main__':
    # ここでデータを作成して、ノイズを乗せる場合
    # ランダムシードを固定
    np.random.seed(0)

    # 元の式の係数
    #c = np.array([4, -5, -10, 1])

    # 0~10の間に100個の等間隔な点のベクトル作成
    #x = np.linspace(0,10,100)

    # 真の値x
    #y_true = c[0] + c[1] * x + c[2] * x**2 + c[3] * x**3 
    #plt.plot(x,y_true,label='true')

    # ノイズの乗った値
    #y_measured = c[0] + c[1] * x + c[2] * x**2 + c[3] * x**3 + np.random.normal(0,10,x.size) 
    #plt.plot(x,y_measured,"ro",label='measured')

    # 任意のデータから読み込む場合
    train_data = np.loadtxt("lsmdata4_train.csv", skiprows=1) #一つ空白を飛ばして次の値を読み込む
    #train_data = np.sort(train_data,axis = 0) #0番目の要素をkeyとして昇順ソート 諸悪の根源

    test_data = np.loadtxt("lsmdata4_test.csv", skiprows=1) #一つ空白を飛ばして次の値を読み込む
    #test_data = np.sort(train_data,axis = 0) #0番目の要素をkeyとして昇順ソート　諸悪の根源

    x = [i[0] for i in train_data]
    x = np.array(x)
    y_measured = [i[1] for i in train_data]
    y_measured = np.array(y_measured)
    
    y_test = [i[1] for i in test_data]
    y_test = np.array(y_test)
    
    plt.plot(x,y_measured,"ro",label='measured')
    #plt.plot(x,y_test,"bo",label='test')
    

    AIC_list = []
    BIC_list = []
    c_est_list = []

    print (len(x))

    # 8次までにとりあえずしておく
    if len(x)>=20:
        n = 20
    else :
        n = len(x)

    for dim in range(1,n):

        # 行列の大きさだけもらって中身全部１にする
        x_mat = x * 0 + 1 

        for i in range(1, dim+1):
            
            # 答えの項を作成 
            x_mat = np.c_[x_mat, x**i] 

        # 擬似逆行列を計算
        c_est = np.linalg.pinv(x_mat).dot(y_measured) 

        c_est_list.append(c_est)

        # 大きさだけもらって中身は全部0
        y_est = x * 0 
        
        for i in range(0, dim+1):
            y_est = y_est + c_est[i] * x**i

        plt.plot(x,y_est,label='fit(dim = ' + str(dim) + ')')
        #print ('y_est = '+ str(y_est))

        # 分散の計算
        sigma = np.sum((y_est - y_measured)**2) / x.size
        #print('sigma = ' + str(sigma))

        # 対数尤度の計算
        p = lambda x,mu,sigma: (math.exp(-(x-mu)**2 / (2*sigma)) / math.sqrt(2*math.pi*sigma))    
        L = 0.0
        for i in range(0, x.size-1):
            L = L + np.log(p(y_measured[i], y_est[i], sigma))

        AIC = -1 * L + (dim+1)
        AIC_list.append(AIC)

        BIC = -1 * L + (dim+1) * np.log(len(x))
        BIC_list.append(BIC)
        

        print('dim = ' + str(dim) +', L = ' + str(L) + ', AIC = ' + str(AIC) + ', BIC = ' + str(BIC))
        print('二乗和誤差(' + str(dim) + '):' + str(errSumsOfSq(y_est,y_measured)))

    # AICが最も小さい時の次数を表示
    i = AIC_list.index(min(AIC_list))
    print ('least AIC dim = ' + str(i+1))
    print (c_est_list[i])

    # BICが最も小さい時の次数を表示
    i = BIC_list.index(min(BIC_list))
    print ('least BIC dim = ' + str(i+1))
    print (c_est_list[i])
    test(c_est_list[i],x,y_measured)

    print(c_est_list[0])

    plt.legend()
    plt.grid()
    plt.show()