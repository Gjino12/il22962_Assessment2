#include "IsingModel2d.h"
#include <iostream>
#include <numeric>
#include <cmath>

IsingModel2D::IsingModel2D(int s, double beta_val)
    : IsingModel1D(s * s, beta_val), size(s) {
    spins.resize(size, std::vector<int>(size));
    initialize_spins();
}

void IsingModel2D::initialize_spins() {
    std::uniform_int_distribution<int> spin_dist(0, 1);
    for (int x = 0; x < size; ++x)
        for (int y = 0; y < size; ++y)
            spins[x][y] = spin_dist(rng) == 0 ? -1 : 1;
}

double IsingModel2D::energy_change(int x, int y) {
    int up = spins[(x - 1 + size) % size][y];
    int down = spins[(x + 1) % size][y];
    int left = spins[x][(y - 1 + size) % size];
    int right = spins[x][(y + 1) % size];

    double dE = 2.0 * spins[x][y] * (up + down + left + right);
    return dE;
}

void IsingModel2D::monte_carlo_step() {
    std::uniform_int_distribution<int> spin_index(0, size - 1);
    int x = spin_index(rng);
    int y = spin_index(rng);

    double dE = energy_change(x, y);
    double probability = std::exp(-beta * dE);
    if (dE <= 0.0 || dist(rng) < probability)
        spins[x][y] *= -1;
}

double IsingModel2D::total_energy() {
    double E = 0.0;
    for (int x = 0; x < size; ++x)
        for (int y = 0; y < size; ++y) {
            int right = spins[x][(y + 1) % size];
            int down = spins[(x + 1) % size][y];
            E -= spins[x][y] * (right + down);
        }
    return E;
}

double IsingModel2D::magnetization() {
    double M = 0.0;
    for (const auto& row : spins)
        M += std::accumulate(row.begin(), row.end(), 0.0);
    return M;
}

void IsingModel2D::simulate(int steps, int burn_in, int sample_interval) {
    for (int i = 0; i < burn_in; ++i)
        monte_carlo_step();

    double energy_sum = 0.0, mag_sum = 0.0;
    int samples_taken = 0;

    for (int i = 0; i < steps; ++i) {
        monte_carlo_step();
        if (i % sample_interval == 0) {
            energy_sum += total_energy();
            mag_sum += magnetization();
            ++samples_taken;
        }
    }

    std::cout << "Average Energy per spin: " << energy_sum / samples_taken / (size * size) << '\n';
    std::cout << "Average Magnetization per spin: " << mag_sum / samples_taken / (size * size) << '\n';
}