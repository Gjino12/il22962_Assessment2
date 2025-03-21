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

void IsingModel1D::monte_carlo_step() {
    std::uniform_int_distribution<int> spin_index(0, num_spins - 1);
    int idx = spin_index(rng);
    double dE = energy_change(idx);
    double probability = std::exp(-beta * dE);
    if (dE <= 0.0 || dist(rng) < probability) {
        spins[idx] *= -1;
    }
}

double IsingModel1D::total_energy() {
    double E = 0.0;
    for (int i = 0; i < num_spins; ++i) {
        E -= spins[i] * spins[(i + 1) % num_spins];
    }
    return E;
}

double IsingModel1D::magnetization() {
    return std::accumulate(spins.begin(), spins.end(), 0);
}

void IsingModel1D::simulate(int steps, int burn_in, int sample_interval) {
    for (int i = 0; i < burn_in; ++i) {
        monte_carlo_step();
    }

    double energy_sum = 0.0;
    double mag_sum = 0.0;
    int samples_taken = 0;

    for (int i = 0; i < steps; ++i) {
        monte_carlo_step();
        if (i % sample_interval == 0) {
            energy_sum += total_energy();
            mag_sum += magnetization();
            ++samples_taken;
        }
    }

    std::cout << "Average Energy per spin: " << energy_sum / samples_taken / num_spins << '\n';
    std::cout << "Average Magnetization per spin: " << mag_sum / samples_taken / num_spins << '\n';
}