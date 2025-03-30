#include "IsingModel2d.h"
#include <iostream>
#include <numeric>
#include <cmath>
#include <fstream>

// Constructor; initializes the 2D Ising model with a square lattice of dimensions size x size, inverse temperature (beta) and random seed
// Inherits from IsingModel1D by setting the total number of spins to size*size
IsingModel2D::IsingModel2D(int s, double beta_val, int seed): IsingModel1D(s * s, beta_val, seed), size(s) {
    
    // Resize the 2D spins vector to create a square lattice
    spins.resize(size, std::vector<int>(size));
    // Initialize the 2D spins randomly to -1 or 1
    initialize_spins();
}

// Initializes each spin in the 2D lattice randomly to either -1 or 1
void IsingModel2D::initialize_spins() {
    
    // Define a uniform integer distribution that returns either 0 or 1
    std::uniform_int_distribution<int> spin_dist(0, 1);
    // Loop over each lattice site
    for (int x = 0; x < size; ++x)
        for (int y = 0; y < size; ++y)
            // Map 0 to -1 and 1 to +1
            spins[x][y] = spin_dist(rng) == 0 ? -1 : 1;
}

// Calculates the change in energy if the spin at position (x, y) is flipped
double IsingModel2D::energy_change(int x, int y) {
    
    // Apply periodic boundary conditions:
    // Get the spin of the neighbor above (up), below (down), left and right
    int up = spins[(x - 1 + size) % size][y];
    int down = spins[(x + 1) % size][y];
    int left = spins[x][(y - 1 + size) % size];
    int right = spins[x][(y + 1) % size];

    // Compute the energy change: ΔE = 2 * spin(x,y) * (up + down + left + right)
    double dE = 2.0 * spins[x][y] * (up + down + left + right);
    return dE;
}

// Performs a single Monte Carlo step using the algorithm for the 2D lattice
void IsingModel2D::monte_carlo_step() {

    // Randomly select lattice coordinates (x, y) within the lattice dimensions
    std::uniform_int_distribution<int> spin_index(0, size - 1);
    int x = spin_index(rng);
    int y = spin_index(rng);

    // Calculate the energy change for flipping the spin at (x, y)
    double dE = energy_change(x, y);
    // Calculate the acceptance probability using the Boltzmann factor
    double probability = std::exp(-beta * dE);
    // Flip the spin if energy decreases or with the computed acceptance probability
    if (dE <= 0.0 || dist(rng) < probability)
        spins[x][y] *= -1;
}

// Computes the total energy of the 2D spin configuration
double IsingModel2D::total_energy() {

    double E = 0.0;
    // Loop over each lattice site and sum interactions with right and down neighbors
    for (int x = 0; x < size; ++x)
        for (int y = 0; y < size; ++y) {

            // Right neighbor (with wrap-around).
            int right = spins[x][(y + 1) % size];
            // Down neighbor (with wrap-around).
            int down = spins[(x + 1) % size][y];
            // Update total energy.
            E -= spins[x][y] * (right + down);
        }
    return E;
}

// Computes the total magnetization of the 2D spin configuration
double IsingModel2D::magnetization() {
    
    double M = 0.0;
    // Sum over each row in the lattice
    for (const auto& row : spins)
        M += std::accumulate(row.begin(), row.end(), 0.0);
    return M;
}

// Saves the current 2D spin configuration to a file
void IsingModel2D::save_spins_to_file(const std::string& filename) {
    
    // Open the file for writing
    std::ofstream file(filename);
    // Write each spin value with a space separator
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            file << spins[i][j] << " ";
        }
        file << "\n";
    }
    // Close the file
    file.close();
}

// Runs the simulation for the 2D Ising model:
// 1. Performs a burn-in period to equilibrate the system
// 2. Collects energy and magnetization samples at specified intervals
// 3. Computes the average energy and magnetization per spin
// 4. Writes the results to a file in CSV format
void IsingModel2D::simulate(int steps, int burn_in, int sample_interval, const std::string& filename) {
    
    // Open the file in append mode to record simulation results
    std::ofstream file(filename, std::ios::app);

    // Perform Monte Carlo 
    for (int i = 0; i < burn_in; ++i)
        monte_carlo_step();

    double energy_sum = 0.0;
    double mag_sum = 0.0;
    int samples_taken = 0;

    // Main simulation loop: perform Monte Carlo steps and record data at intervals
    for (int i = 0; i < steps; ++i) {
        monte_carlo_step();
        if (i % sample_interval == 0) {
            // Accumulate total energy and magnetization
            energy_sum += total_energy();
            mag_sum += magnetization();
            ++samples_taken;
        }
    }

    // Calculate average energy and magnetization per spin
    double avg_energy = energy_sum / samples_taken / (size * size);
    double avg_magnetization = mag_sum / samples_taken / (size * size);

    // Write the results in CSV format: Temperature (1/β), average energy, average magnetization
    file << (1.0 / beta) << ","
         << avg_energy << ","
         << avg_magnetization << "\n";

    // Close the file
    file.close();

    // Output the average values to the console
    std::cout << "Average Energy per spin: " << avg_energy << '\n';
    std::cout << "Average Magnetization per spin: " << avg_magnetization << '\n';
}
