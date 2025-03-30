#include <iostream>
#include <iomanip>
#include <fstream>
#include "IsingModel1D.h"
#include "IsingModel2d.h"

using namespace std;

// Function to test the 1D Ising model and save the simulation results to a CSV file
void test1DModelCSV(const std::string& filename) {

    // Open CSV file and write the header
    ofstream file(filename);
    file << "Temperature,Energy_per_spin,Magnetization_per_spin\n";
    file.close();

    // Array of beta values (inverse temperature) to simulate
    double betas[] = {0.1, 0.2, 0.4, 0.6, 0.8, 1.0, 2.0};
    // Fixed seed for reproducibility
    int seed = 1234;

    // Loop over each beta value to run the simulation
    for (double beta : betas) {
        // Create a 1D Ising model with 100 spins
        IsingModel1D model(100, beta, seed);
        // Run simulation: 100000 steps, 10000 burn-in steps, sample every 10 steps, output results to CSV
        model.simulate(100000, 10000, 10, filename);
    }

    // Inform user that the results have been saved
    cout << "[CSV] 1D simulation results saved to " << filename << endl;
}

// Function to test 2D Ising model and save the simulation results to a CSV file
void test2DModelCSV(const std::string& filename) {
    
    // Open CSV file and write the header
    ofstream file(filename);
    file << "Temperature,Energy_per_spin,Magnetization_per_spin\n";
    file.close();

    // Array of beta values (inverse temperature) to simulate
    double betas[] = {0.1, 0.44, 1.0};
    // Fixed seed for reproducibility.
    int seed = 4321;

    // Loop over each beta value to run the simulation
    for (double beta : betas) {
        // Create a 2D Ising model with a 10x10 lattice
        IsingModel2D model(10, beta, seed);
        // Run simulation: 50000 steps, 5000 burn-in steps, sample every 10 steps, output results to CSV
        model.simulate(50000, 5000, 10, filename);
    }

    // Inform user that the results have been saved
    cout << "[CSV] 2D simulation results saved to " << filename << endl;
}

// Function to perform an official test of the 1D Ising model by iterating over all possible 3-spin configurations
void official1DTest() {
    cout << "===== Official 1D Ising Model Test =====" << endl;
    // Create a 1D Ising model with 3 spins, beta = 1.0, and a fixed seed
    IsingModel1D model1D(3, 1.0, 1234);

    // Iterate over all possible combinations of 3 spins (-1 and +1)
    for (int s1 : {-1, 1}) {
        for (int s2 : {-1, 1}) {
            for (int s3 : {-1, 1}) {
                
                // Set up the spin configuration
                vector<int> config = {s1, s2, s3};
                model1D.setSpins(config);
                
                // Calculate total energy and magnetization for the configuration
                double E = model1D.total_energy();
                int M = model1D.magnetization();
                
                // Output the configuration, energy, and magnetization
                cout << "Config: ("
                     << (s1 > 0 ? "+1" : "-1") << ", "
                     << (s2 > 0 ? "+1" : "-1") << ", "
                     << (s3 > 0 ? "+1" : "-1") << ") | ";
                cout << "E = " << setw(3) << E << "J, ";
                cout << "M = " << setw(2) << M << endl;
            }
        }
    }

    // Run a Monte Carlo simulation on the 1D model with 3 spins
    cout << "\nMonte Carlo Simulation (1D, 3 spins):" << endl;
    // Simulate with 100000 steps, 10000 burn-in steps, and sample every 10 steps, then output to CSV
    model1D.simulate(100000, 10000, 10, "small_1d_results.csv");
    cout << "[CSV] Saved short 1D test to small_1d_results.csv\n" << endl;
}

// Function to test the 2D Ising model for different temperature regimes
void test2DModel() {
    cout << "===== Official 2D Ising Model Test =====" << endl;

    // Test for low temperature (beta = 1.0)
    cout << "\nLow Temperature (beta = 1.0):" << endl;
    IsingModel2D model2D_lowT(10, 1.0, 4321);
    model2D_lowT.simulate(50000, 5000, 10, "dummy.csv");

    // Test for high temperature (beta = 0.1)
    cout << "\nHigh Temperature (beta = 0.1):" << endl;
    IsingModel2D model2D_highT(10, 0.1, 5678);
    model2D_highT.simulate(50000, 5000, 10, "dummy.csv");

    // Test for medium temperature (beta = 0.44)
    cout << "\nMedium Temperature (beta = 0.44):" << endl;
    IsingModel2D model2D_mediumT(10, 0.44, 8765);
    model2D_mediumT.simulate(50000, 5000, 10, "dummy.csv");
}

// Main function: Executes tests for both 1D and 2D Ising models and saves simulation results to CSV files
int main() {
    // Set output formatting for floating-point numbers
    cout << fixed << setprecision(4);

    // Run the official 1D Ising model test
    official1DTest();
    // Run the official 2D Ising model test
    test2DModel();

    // Run CSV tests to generate results files for 1D and 2D models
    test1DModelCSV("ising_1d_results.csv");
    test2DModelCSV("ising_2d_results.csv");

    return 0;
}