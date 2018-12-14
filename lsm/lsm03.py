import numpy as np
import math
from matplotlib import pyplot
from numpy.linalg import pinv


# 最小二乗法で多項式フィッティング

c = np.array([4, -5, -10, 1])
x = np.linspace(0,10,100)
y_measured = c[0] + c[1] * x + c[2] * x**2 + c[3] * x**3 + np.random.normal(0,10,x.size)
pyplot.plot(x,y_measured,label='measured')

for dim in range(1,8):    
    x_mat = x * 0 + 1
    for i in range(1, dim+1):
        x_mat = np.c_[x_mat, x**i] 
    c_est =  np.linalg.pinv(x_mat).dot(y_measured)

    y_est = x * 0
    for i in range(0, dim+1):
        y_est = y_est + c_est[i] * x**i

    pyplot.plot(x,y_est,label='fit(dim = ' + str(dim) + ')')

    # 分散の計算
    sigma = np.sum((y_est - y_measured)**2) / x.size

    # 対数尤度の計算
    p = lambda x,mu,sigma: (math.exp(-(x-mu)**2 / (2*sigma)) / math.sqrt(2*math.pi*sigma))    
    L = 0.0
    for i in range(0, x.size-1):
        L = L + np.log(p(y_measured[i], y_est[i], sigma))
    

    AIC = -2 * L + 2 * (dim+1)
    print('dim = ' + str(dim) +', L = ' + str(L) + ', AIC = ' + str(AIC))

pyplot.legend()
pyplot.grid()
