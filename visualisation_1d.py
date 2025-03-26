import matplotlib.pyplot as plt
import csv

temperatures = []
energy_per_spin = []
magnetization_per_spin = []

with open('ising_1d_results.csv', 'r') as file:
    reader = csv.reader(file)
    next(reader)
    for row in reader:
        temperatures.append(float(row[0]))
        energy_per_spin.append(float(row[1]))
        magnetization_per_spin.append(float(row[2]))

data = sorted(zip(temperatures, energy_per_spin, magnetization_per_spin))
temperatures, energy_per_spin, magnetization_per_spin = zip(*data)

plt.figure(figsize=(8, 5))
plt.plot(temperatures, energy_per_spin, marker='o', linestyle='-', color='blue')
plt.xlabel('Temperature (1/beta)')
plt.ylabel('Energy per Spin')
plt.title('1D Ising Model: Energy per Spin vs Temperature')
plt.grid(True)
plt.savefig('energy_vs_temperature.png')
plt.show()

plt.figure(figsize=(8, 5))
plt.plot(temperatures, magnetization_per_spin, marker='o', linestyle='-', color='red')
plt.xlabel('Temperature (1/beta)')
plt.ylabel('Magnetization per Spin')
plt.title('1D Ising Model: Magnetization per Spin vs Temperature')
plt.grid(True)
plt.savefig('magnetization_vs_temperature.png')
plt.show()