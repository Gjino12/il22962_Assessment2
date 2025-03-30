#include "IsingModel1D.h"
#include <iostream>
#include <numeric>
#include <cmath>
#include <fstream>

// Constructor; initializes the number of spins, beta, RNG, and distribution, then sets up the spin configuration
IsingModel1D::IsingModel1D(int n, double beta_val, int seed): num_spins(n), beta(beta_val), rng(seed), dist(0.0, 1.0) {
    
    // Resize the spins vector to the number of spins
    spins.resize(num_spins);
    // Initialize spins to random values (-1 or 1)
    initialize_spins();
    spins.resize(num_spins);
    initialize_spins();
}

// Initializes each spin randomly to either -1 or 1
void IsingModel1D::initialize_spins() {
    
    // Define a uniform integer distribution that returns either 0 or 1
    std::uniform_int_distribution<int> spin_dist(0, 1);
    for (int i = 0; i < num_spins; ++i) {
        // Map 0 to -1, and 1 to +1.
        spins[i] = spin_dist(rng) == 0 ? -1 : 1;
    }
}

// Calculates the change in energy if the spin at the given index is flipped
double IsingModel1D::energy_change(int index) {
    
    // Apply periodic boundary conditions
    // left neighbor: (index - 1) with wrap-around
    int left = spins[(index - 1 + num_spins) % num_spins];
    // right neighbor: (index + 1) with wrap-around
    int right = spins[(index + 1) % num_spins];
    
    // The energy change (ΔE) is given by: ΔE = 2 * spin[index] * (left + right)
    double dE = 2.0 * spins[index] * (left + right);
    return dE;
}

// Performs a single Monte Carlo step
void IsingModel1D::monte_carlo_step() {
    
    // Randomly select a spin index from the available spins
    std::uniform_int_distribution<int> spin_index(0, num_spins - 1);
    int idx = spin_index(rng);
    
    // Calculate the energy change that would result from flipping this spin
    double dE = energy_change(idx);
    
    // Compute the acceptance probability using the Boltzmann factor
    double probability = std::exp(-beta * dE);
    
    // Flip the spin if energy decreases (dE <= 0) or with probability 'probability'
    if (dE <= 0.0 || dist(rng) < probability) {
        
        // Flip the spin by multiplying by -1
        spins[idx] *= -1;  
    }
}

// Computes the total energy of the spin configuration
double IsingModel1D::total_energy() {
    double E = 0.0;
    // Sum over all pairs of neighboring spins using periodic boundary conditions
    for (int i = 0; i < num_spins; ++i) {
        E -= spins[i] * spins[(i + 1) % num_spins];
    }
    return E;
}

// Computes the total magnetization by summing all the spins
double IsingModel1D::magnetization() {
    return std::accumulate(spins.begin(), spins.end(), 0);
}

// Sets the spin configuration to the one provided in 'config' and checks if configuration has correct size
void IsingModel1D::setSpins(const std::vector<int>& config) {
    
    if (config.size() == spins.size()) {
        spins = config;
    } else {
        std::cerr << "Error: spin configuration size mismatch!" << std::endl;
    }
}

// Returns the number of spins in the system.
int IsingModel1D::size() const {
    return num_spins;
}

// Runs the simulation:
// 1. Performs a burn-in period to let the system equilibrate
// 2. Collects energy and magnetization samples at regular intervals
// 3. Outputs average energy and magnetization per spin to the specified file
void IsingModel1D::simulate(int steps, int burn_in, int sample_interval, const std::string& filename) {
    // Open file in append mode to record the simulation data.
    std::ofstream file(filename, std::ios::app);

    // Burn-in: run several Monte Carlo steps without taking measurements
    for (int i = 0; i < burn_in; ++i)
        monte_carlo_step();

    double energy_sum = 0.0;
    double mag_sum = 0.0;
    int samples_taken = 0;

    // Main simulation loop: perform Monte Carlo steps and record data at intervals
    for (int i = 0; i < steps; ++i) {
        monte_carlo_step();
        if (i % sample_interval == 0) {
            // Accumulate total energy and magnetization for averaging
            energy_sum += total_energy();
            mag_sum += magnetization();
            ++samples_taken;
        }
    }

    // Calculate average energy and magnetization per spin
    double avg_energy = energy_sum / samples_taken / num_spins;
    double avg_magnetization = mag_sum / samples_taken / num_spins;

    // Write the results in CSV format: Temperature (1/β), average energy, average magnetization
    file << (1.0 / beta) << "," 
         << avg_energy << "," 
         << avg_magnetization << "\n";

    // Close the file
    file.close();
}