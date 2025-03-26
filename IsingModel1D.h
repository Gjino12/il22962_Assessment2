#ifndef ISINGMODEL1D_H
#define ISINGMODEL1D_H

#include <vector>
#include <random>

class IsingModel1D {
    public:
    std::vector<int> spins;
    int num_spins;
    double beta;
    std::mt19937 rng;
    std::uniform_real_distribution<double> dist;
    IsingModel1D(int n, double beta_val);
    void initialize_spins();
    double energy_change(int index);
    void monte_carlo_step();
    double total_energy();
    double magnetization();
    void simulate(int steps, int burn_in, int sample_interval);
};

#endif
