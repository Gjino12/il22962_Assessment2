#include "IsingModel1D.h"
#include <iostream>
#include <numeric>
#include <cmath>

IsingModel1D::IsingModel1D(int n, double beta_val)
    : num_spins(n), beta(beta_val), rng(std::random_device{}()), dist(0.0, 1.0) {
    spins.resize(num_spins);
    initialize_spins();
}

void IsingModel1D::initialize_spins() {
    std::uniform_int_distribution<int> spin_dist(0, 1);
    for (int i = 0; i < num_spins; ++i) {
        spins[i] = spin_dist(rng) == 0 ? -1 : 1;
    }
}

double IsingModel1D::energy_change(int index) {
    int left = spins[(index - 1 + num_spins) % num_spins];
    int right = spins[(index + 1) % num_spins];
    double dE = 2.0 * spins[index] * (left + right);
    return dE;
}