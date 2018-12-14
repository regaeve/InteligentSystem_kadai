   # 任意のデータから読み込む場合
    data = np.loadtxt("lsmdata1_train.csv", skiprows=1) #一つ空白を飛ばして次の値を読み込む
    data = np.sort(data,axis = 0) #0番目の要素をkeyとして昇順ソート

    x = [i[0] for i in data] #xのデータのみ取得
    x = np.array(x) #リスト内包表記で取得したデータはint型なのでarrayにキャスト
    y_measured = [i[1] for i in data] 
    y_measured = np.array(y_measured)
