import pandas as pd
import csv
import copy

ITEM = 100

if __name__ == '__main__':
    filename = "dragonPole" + str(ITEM) + ".dat"

    #一行目取ってくる
    limit = open(filename,'r').readline()
    limit = int(limit[6:])

    df_table = pd.read_csv(filename,header = None,skiprows=2,
                           names = ["number","weight","value"])

    dp_t = [-1 for i in range(limit+1)]
    dp_t2 = copy.deepcopy(dp_t)
    
    for i in range(ITEM):
        
        w = df_table['weight'][i]
        v = df_table['value'][i]

        for j in range(limit+1):
            if dp_t[j] != -1 and j + w <= limit: #入れられるか判定
                dp_t2[j + w] = max(dp_t[j] + v,dp_t[j + w])

            #価値を登録
            dp_t2[w] = max(dp_t2[w],v);
    
        dp_t = copy.deepcopy(dp_t2)
    
    print(dp_t2[limit])
    
    
