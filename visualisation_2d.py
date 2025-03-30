import matplotlib.pyplot as plt
import csv

# Initialize empty lists to store temperature, energy per spin and magnetization per spin values
temperatures = []
energy_per_spin = []
magnetization_per_spin = []

# Open the CSV file containing the 2D simulation results
with open('ising_2d_results.csv', 'r') as file:

    # Create a CSV reader object
    reader = csv.reader(file)
    next(reader)

    # Iterate over each row in the CSV file
    for row in reader:
        
        # Append the temperature (1/beta) value as a float
        temperatures.append(float(row[0]))
        # Append the energy per spin value as a float
        energy_per_spin.append(float(row[1]))
        # Append the magnetization per spin value as a float
        magnetization_per_spin.append(float(row[2]))

# Sort the data by temperature to ensure proper plotting
data = sorted(zip(temperatures, energy_per_spin, magnetization_per_spin))
# Unzip the sorted data back into separate lists
temperatures, energy_per_spin, magnetization_per_spin = zip(*data)

# Plot energy per spin against temperature
plt.figure(figsize=(8, 5))
plt.plot(temperatures, energy_per_spin, marker='o', linestyle='-', color='blue')
plt.xlabel('Temperature (1/beta)')
plt.ylabel('Energy per Spin')
plt.title('2D Ising Model: Energy per Spin vs Temperature')
plt.grid(True)
plt.savefig('energy_vs_temperature.png')
plt.show()

# Plot magnetization per spin against temperature
plt.figure(figsize=(8, 5))
plt.plot(temperatures, magnetization_per_spin, marker='o', linestyle='-', color='red')
plt.xlabel('Temperature (1/beta)')
plt.ylabel('Magnetization per Spin')
plt.title('2D Ising Model: Magnetization per Spin vs Temperature')
plt.grid(True)
plt.savefig('magnetization_vs_temperature.png')
plt.show()