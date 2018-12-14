import numpy as np
import math
from matplotlib import pyplot as plt
from numpy.linalg import pinv

def f(x,y):
    return np.sin(x) + 2 * x * np.cos(y) + 0.2 * x**2 + 0.2 * y**2

def dfdy(x,y):
    delta = 0.00001
    return (f(x,y)/delta)-(f(x,y-delta)/delta)

def dfdx(x,y):
    delta = 0.00001
    return (f(x,y)/delta)-(f(x-delta,y)/delta)

if __name__ == '__main__':

    a = 2 
    b = 2
    sigma = 0.1

    for i in range(0,1000):
        a -= sigma * dfdy(a,b)
        b -= sigma * dfdx(a,b)
        print(f(a,b))
    