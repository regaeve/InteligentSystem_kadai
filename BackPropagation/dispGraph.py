import matplotlib.pyplot as plt
import numpy as np

# plt.use('tkagg')
# print(matplotlib.matplotlib_fname())
# x = np.arange(0,1000)
datanum = 1000
source = np.loadtxt('error_2.dat')
y = []
x = np.arange(0,datanum)

for i in range(5):
    y = source[i*datanum:i*datanum+datanum].tolist()    
    plt.plot(x, y,label = "seed:" + str(i))
plt.legend()
plt.show()

