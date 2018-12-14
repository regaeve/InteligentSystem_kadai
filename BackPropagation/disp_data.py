import matplotlib.pyplot as plt
import numpy as np

# plt.use('tkagg')
# print(matplotlib.matplotlib_fname())
# x = np.arange(0,1000)
# plt.title(u"二次元座標にデータをプロットしたもの",fontdict = {"fontproperties": fontprop})
plt.xlabel("input 1")
plt.ylabel("input 2")
plt.grid(True)

a = np.loadtxt('ohsakoA.csv',delimiter = ' ')
b = np.loadtxt('ohsakoB.csv',delimiter = ' ')
# x = np.arange(-3, 3, 0.1)
# y = np.sin(x)

plt.plot(a[:,0],a[:,1],"ro",label = "ohsakoA")
plt.plot(b[:,0],b[:,1],"bo",label = 'ohsakoB')

plt.legend()
plt.show()
