import numpy as np

def activation_func(x):
    return x * 0.5

def calc_NN(w1,w2,theta1,theta2,inputs):

    x1 = np.dot(w1,inputs)+theta1
    y1 = activation_func(x1)

    x2 = np.dot(w2,y1)+theta2
    y2 = activation_func(x2)

    return y2

if __name__ == "__main__":

    inputs = np.array([0.0,0.0],[0.0,1.0],[1.0,0.0],[1.0,1.0])

    w1 = np.array([[0.5,0.1],[-0.3,0.6]])
    w2 = np.array([0.4,0.3])

    theta1 = np.array([0.4,-0.2])
    theta2 = -0.5 

    output = [i for in range(inputs) calc_NN(w1,w2,theta1,theta2,inputs[i])]

    print(inputs)
    print(output)
    
