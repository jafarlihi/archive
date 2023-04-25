dates = ['2023-03', '2023-02', '2023-01', '2022-12', '2022-11', '2022-10', '2022-09', '2022-08', '2022-07', '2022-06', '2022-05', '2022-04', '2022-03', '2022-02', '2022-01', '2021-12', '2021-11', '2021-10', '2021-09', '2021-08', '2021-07', '2021-06', '2021-05', '2021-04', '2021-03', '2021-02', '2021-01']

symbols = ['ETH', 'MATIC', 'THETA', 'UNI', 'LINK', 'NEAR', 'GRT', 'FTM', 'SAND', 'SNX', 'CHZ', 'MKR', 'INJ', 'ZIL', '1INCH', 'ENJ', 'BAT', 'SUSHI']

from keras.metrics import BinaryAccuracy
import pandas
import sklearn.preprocessing

fname = '{symbol}USDT-15m-{date}.csv'
path = '/home/user/dldata/data/'

allData = []
eth = pandas.DataFrame()
for symbol in symbols:
    spath = path + symbol
    data = pandas.DataFrame()
    for date in dates:
        datum = pandas.read_csv(spath + '/' + fname.format(symbol=symbol, date=date), usecols=[0,1], names=['timestamp', symbol])
        data = pandas.concat([data, datum], axis=0)
    #print(data.shape)
    if symbol == 'ETH':
        eth = data
    allData.append(data)

symbols = symbols.remove('ETH')

allData = pandas.concat(allData, axis=1)
allData = allData.loc[:,~allData.columns.duplicated()].copy()
allData = allData.iloc[::-1]
#print(allData)
del allData[allData.columns[0]]
#print(allData)
scaler = sklearn.preprocessing.MinMaxScaler()
allData = scaler.fit_transform(allData)
import joblib
joblib.dump(scaler, 'scaler.save')
#print(allData.shape)
#print(allData)
allData = allData[:len(allData) - 1]
#print(allData.shape)
#print(allData)

eth = eth.iloc[::-1]
#print(eth.shape)
#print(eth)
del eth[eth.columns[0]]
eth = eth.iloc[51: , :]
print(eth.shape)
print(eth)

eth['UPDOWN'] = eth.ETH < eth.ETH.shift()
eth['UPDOWN'] = eth['UPDOWN'].shift(-1)
eth.UPDOWN.fillna(1, inplace=True)
eth['UPDOWN'] = eth['UPDOWN'].astype(int)
del eth[eth.columns[0]]
print(eth)

train_data = allData
train_label = eth

from keras.models import Sequential
from keras.layers import Dense
from keras.layers import LSTM
from keras.layers import Dropout
import numpy as np

n_steps = 50 # number of time steps
n_features = 18 # number of features

# split the data into samples
samples = list()
for i in range(n_steps, len(train_data)):
    sample = train_data[i-n_steps:i, :]
    samples.append(sample)
samples = np.array(samples)

# reshape the samples into a 3D tensor
X = samples.reshape(samples.shape[0], n_steps, n_features)

import keras

model = Sequential()

#Adding the first LSTM layer and some Dropout regularisation
model.add(LSTM(units = 36, return_sequences = True))

# Adding a second LSTM layer and some Dropout regularisation
model.add(LSTM(units = 100, return_sequences = True))
model.add(Dropout(0.1))

model.add(LSTM(units = 36, return_sequences=False))

# Adding the output layer
model.add(Dense(units = 1, activation='sigmoid'))

opt = keras.optimizers.Adam(learning_rate=0.05)
# Compiling the RNN
model.compile(optimizer = opt, loss = 'binary_crossentropy', metrics=[BinaryAccuracy()])

# Fitting the RNN to the Training set
history = model.fit(X, train_label, epochs = 50, batch_size = 32, validation_split=0.1)

model.save('./model6')

import matplotlib.pyplot as plt

plt.plot(history.history['mean_squared_error'])
plt.plot(history.history['val_mean_squared_error'])
plt.legend(['mean_squared_error','validation mean_squared_error'])
plt.show()
