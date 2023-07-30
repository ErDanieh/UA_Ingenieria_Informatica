import os
import cv2
import argparse
import numpy as np
import pandas as pd

from collections import Counter

from keras.callbacks import Callback
from keras.backend import clear_session
from keras.models import Model, load_model
from keras.layers import Dense, Input, Flatten
from keras.applications import ResNet50, MobileNet, Xception, DenseNet121

from sklearn.metrics import f1_score
from sklearn.model_selection import train_test_split

from keras_model import build_model
import tensorflow as tf
import datetime

# Custom callback para el calculo del F1 Score
def F1_score(y_true, y_pred):
    return f1_score(y_true, y_pred, average='samples')


class ComputeF1(Callback):

    def __init__(self, val_data, batch_size):
        self.best_f1 = -1
        self.validation_data = val_data
        self.batch_size = batch_size

    def on_epoch_end(self, epoch, logs={}):
        val_pred = np.round(self.model.predict(self.validation_data[0]))
        val_f1 = f1_score(self.validation_data[1], val_pred, average='samples')
        print('Validando por media de F1: ', val_f1)

        if val_f1 > self.best_f1:
            print('Mejor F1 Score, Guardando el último modelo...')
            self.model.save('model.h5')
            self.best_f1 = val_f1



#Funcion para cargar las imagenes y las labels de aprendizaje
def load_data(df):

    #Creamos los vectores para guardar los datos
    trainX, testX, valX = [], [], []
    trainY, testY, valY = [], [], []

    for i in range(len(df)):

        #La primera linea del csv tiene el nombre de la carpeta
        item = df.loc[i][0]
        valorNutricional = np.array((df.loc[i])[1:])
        print('analizando:', item)
        path = os.path.join('images', item)
        #Sacamos la lista de imagenes
        list_of_imgs = [os.path.join(path, file) for file in os.listdir(path)]

        #Las primeras 30 imagenes para entrenamiento
        train_set = list_of_imgs[:300]
        #De la 30 a la 40 de validacion
        val_set = list_of_imgs[300:400]
        #De la 40 para adelante de test
        test_set = list_of_imgs[400:]

        #Para cada imagen del conjunto de entrenamiento le damos su valor nutricional
        for file in train_set:
            img = cv2.resize(cv2.cvtColor(cv2.imread(file, 1), cv2.COLOR_BGR2RGB), (224, 224))
            img = img.reshape(224,224,3)
            trainX.append(img)
            trainY.append(valorNutricional)
        #Para cada imagen del conjunto de validación le damos su valor nutricional
        for file in val_set:
            img = cv2.resize(cv2.cvtColor(cv2.imread(file, 1), cv2.COLOR_BGR2RGB), (224, 224))
            img = img.reshape(224,224,3)
            valX.append(img)
            valY.append(valorNutricional)

        #Para cada imagen del conjunto de test le damos su valor nutricional
        for file in test_set:
            img = cv2.resize(cv2.cvtColor(cv2.imread(file, 1), cv2.COLOR_BGR2RGB), (224, 224))
            img = img.reshape(224,224,3)
            testX.append(img)
            testY.append(valorNutricional)

    return (np.array(trainX), np.array(trainY), np.array(testX),
            np.array(testY), np.array(valX), np.array(valY))



#Main para rescatar los argumentos
if __name__ == '__main__':

    #Sacamos el argumento para el profesor elija el modelo
    parser = argparse.ArgumentParser()

    parser.add_argument('--model', choices=['ResNet50', 'Xception', 'DenseNet121', 'MobileNet'],
                        help='Seleccone un modelo para entrenar', required=True)

    args = parser.parse_args()

    print('Cargando imagenes para entrenamiento...')
    #Csv con los datos de las imagenes
    df = pd.read_csv('clean_anno_reduced.csv')
    trainX, trainY, testX, testY, valX, valY = load_data(df)
    print('Imagenes cargadas con exito')

    # Normalizacion de imagenes
    trainX = trainX.astype(np.float32)
    testX = testX.astype(np.float32)
    valX = valX.astype(np.float32)

    trainY = trainY.astype(np.float32)
    testY = testY.astype(np.float32)
    valY = valY.astype(np.float32)

    MEAN = np.mean(trainX, axis=(0, 1, 2))
    STD = np.std(trainX, axis=(0, 1, 2))

    for i in range(3):
        trainX[:, :, :, i] = (trainX[:, :, :, i] - MEAN[i]) / STD[i]
        testX[:, :, :, i] = (testX[:, :, :, i] - MEAN[i]) / STD[i]
        valX[:, :, :, i] = (valX[:, :, :, i] - MEAN[i]) / STD[i]

    f1_score_callback = ComputeF1(val_data=(
        valX, valY), batch_size=16)
    model = build_model('train', model_name=args.model)
    
    log_dir = "logs/fit/" + datetime.datetime.now().strftime("%Y%m%d-%H%M%S")
    tensorboard_callback = tf.keras.callbacks.TensorBoard(log_dir=log_dir, histogram_freq=1)
    
    # Training model.
    model.fit(trainX, trainY, batch_size=16, epochs=50, validation_data=(
        valX, valY), callbacks=[f1_score_callback,tensorboard_callback])

    # Compute test F1 Score
    model = load_model('model.h5')

    score = F1_score(testY, model.predict(testX).round())
    print('F1 Score =', score)
