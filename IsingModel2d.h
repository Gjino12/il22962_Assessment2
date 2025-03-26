#ifndef ISINGMODEL2D_H
#define ISINGMODEL2D_H

#include "IsingModel1D.h"
#include <vector>

class IsingModel2D : public IsingModel1D {
public:
    IsingModel2D(int size, double beta, int seed);
    void simulate(int steps, int burn_in, int sample_interval);
    void save_spins_to_file(const std::string& filename); 

private:
    int size;
    std::vector<std::vector<int>> spins;

    void initialize_spins();
    double energy_change(int x, int y);
    void monte_carlo_step();
    double total_energy();
    double magnetization();
};

#endif