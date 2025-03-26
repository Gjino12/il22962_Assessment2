import matplotlib.pyplot as plt
import numpy as np

spins_2d = np.loadtxt('spins_output.txt')

plt.figure(figsize=(6, 6))
plt.imshow(spins_2d, cmap='coolwarm', interpolation='none')
plt.colorbar(label='Spin Value')
plt.title('2D Ising Model Spin Configuration')
plt.xlabel('X Index')
plt.ylabel('Y Index')
plt.grid(False)
plt.show()