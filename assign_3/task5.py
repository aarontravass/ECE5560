#
#  task5.py
#
#  Created by Angelos Stavrou
#  Python program to explain os.urandom() method
        
# importing os module
import os
import math
import matplotlib.pyplot as plt
import numpy as np

def entropy(string):
    "Calculates the Shannon entropy of a string"

    # get probability of chars in string
    prob = [ float(string.count(c)) / len(string) for c in dict.fromkeys(list(string)) ]

    # calculate the entropy
    entropy = - sum([ p * math.log(p) / math.log(2.0) for p in prob ])

    return entropy


def entropy_ideal(length):
    "Calculates the ideal Shannon entropy of a string with given length"

    prob = 1.0 / length

    return -1.0 * length * prob * math.log(prob) / math.log(2.0)
# Declaring size
 # This is in bytes
  
# Using os.urandom() method
strs = {}
prev_num=0
x = list(range(1,10000))
y=[]
y2=[]
for size in x:
    result = os.urandom(size) 
    # Print the random bytes string
    # Output will be different everytime
    res = entropy(result)
    y.append(res)
    y2.append(res-prev_num)
    prev_num=res
    

x = np.array(x)
y = np.array(y)
y2=np.array(y2)
plt.figure(1, figsize=(20, 4)) # Figure size in inches (size_x, size_y)
plt.plot(x, y)
plt.title('Entropy vs Byte size')
plt.xlabel('Byte size')
plt.ylabel('Entropy')
plt.show()
print("\n")
plt.figure(1, figsize=(20, 4))
plt.plot(x, y2)
plt.title('Entropy variation vs Byte size')
plt.xlabel('Byte size')
plt.ylabel('Entropy variation')
plt.show()