import matplotlib.pyplot as plt

import pandas as pd

data = pd.read_csv('plot.csv',sep=',')
x = data['n']

plt.figure()
plt.plot(x, data['insArray'], 'bo-', label='remove TrieArray')
plt.plot(x, data['insMap'], 'ro-', label='remove TrieMap')
plt.xlabel('n')
plt.ylabel('t(n)')
plt.title('Algoritmo remove')
plt.xlabel('n')
plt.ylabel('t(n)')
plt.legend()

# plt.figure()
# plt.plot(x, data['SelectionSort'], 'bo-', label='SelectionSort')
# plt.xlabel('n')
# plt.ylabel('t(n)')
# plt.title('Analisis experimental algoritmos ordenamiento')
# plt.xlabel('n')
# plt.ylabel('t(n)')
# plt.legend()
#
# plt.figure()
# plt.plot(x, data['HeapSort'], 'ro-', label='HeapSort')
# plt.xlabel('n')
# plt.ylabel('t(n)')
# plt.title('Analisis experimental algoritmos ordenamiento')
# plt.xlabel('n')
# plt.ylabel('t(n)')
# plt.legend()

plt.show()
