#ifndef ISINGMODEL2D_H
#define ISINGMODEL2D_H

#include "IsingModel1D.h"
#include <vector>
#include <string>

// Class for simulating a 2D Ising Model using Monte Carlo 
// Inherits from IsingModel1D to leverage some common functionality
class IsingModel2D : public IsingModel1D {
public:
    // Constructor; initializes the 2D Ising model with a lattice of dimensions size x size, given inverse temperature (beta) and a random seed
    IsingModel2D(int size, double beta, int seed);
    
    // Runs the simulation:
    // - Performs a burn-in period,
    // - Samples energy and magnetization at specified intervals,
    // - Writes the results to a file
    void simulate(int steps, int burn_in, int sample_interval, const std::string& filename);
    
    // Saves the current 2D spin configuration to a file
    void save_spins_to_file(const std::string& filename);
    
private:
    // The length of one side of the 2D square lattice
    int size;
    
    // 2D vector to store spin states (-1 or 1) for each lattice site
    std::vector<std::vector<int>> spins;

    // Initializes the spins in the 2D lattice randomly to either -1 or 1
    void initialize_spins();
    
    // Calculates the change in energy (ΔE) if the spin at position (x, y) is flipped
    double energy_change(int x, int y);
    
    // Performs a single Monte Carlo step using the Metropolis algorithm for the 2D lattice
    void monte_carlo_step();
    
    // Computes the total energy of the 2D spin configuration
    double total_energy();
    
    // Computes the total magnetization (sum of all spins) of the 2D configuration
    double magnetization();
};

#endif