#ifndef ISINGMODEL1D_H
#define ISINGMODEL1D_H

#include <vector>
#include <random>
#include <string>

// Class for simulating a 1D Ising Model using the Monte Carlo algorithm
class IsingModel1D {
    public:
    // Vector to store spin states (-1 or 1)
    std::vector<int> spins;
    
    // Total number of spins in the system
    int num_spins;
    
    // Inverse temperature (β = 1/kT)
    double beta;
    
    // Random number generator
    std::mt19937 rng;
    
    // Uniform distribution between 0 and 1 for acceptance probability checks
    std::uniform_real_distribution<double> dist;

    // Constructor; initializes the model with a given number of spins, inverse temperature and RNG seed
    IsingModel1D(int n, double beta_val, int seed);
    
    // Initializes the spins to random values (-1 or 1)
    void initialize_spins();
    
    // Calculates the energy change (ΔE) when flipping the spin at the given index
    double energy_change(int index);
    
    // Performs one Monte Carlo step 
    void monte_carlo_step();
    
    // Calculates the total energy of the current spin configuration
    double total_energy();
    
    // Calculates the total magnetization (sum of spins) of the current configuration
    double magnetization();
    
    // Sets the spin configuration from an external vector
    void setSpins(const std::vector<int>& config);
    
    // Returns the number of spins in the model
    int size() const;
    
    // Simulates the system and writes results in a file
    void simulate(int steps, int burn_in, int sample_interval, const std::string& filename);
};

#endif
