#include "IsingModel1D.h"

// Parameters not final

int main() {
    int num_spins = 100;
    double beta = 0.5;

    int total_steps = 100000;
    int burn_in_steps = 10000;
    int sample_interval = 10;

    IsingModel1D model(num_spins, beta);
    model.simulate(total_steps, burn_in_steps, sample_interval);

    return 0;
}