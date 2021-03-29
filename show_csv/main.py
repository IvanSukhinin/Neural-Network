#! /usr/bin/python3

import numpy
import matplotlib.pyplot 

data_file = open("./mnist_test_10.csv", "r")
data_list = data_file.readlines()

print(data_list[0]);

all_values = data_list[0].split(',')
image_array = numpy.asfarray(all_values[1:]).reshape((28,28))
matplotlib.pyplot.imshow(image_array, cmap="Greys", interpolation="None")
matplotlib.pyplot.show()
data_file.close();
