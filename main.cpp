#include <iostream>
#include <iomanip>
#include "IsingModel1D.h"
#include "IsingModel2d.h"

using namespace std;

void test1DModel() {
    cout << "===== Official 1D Ising Model Test =====" << endl;
    IsingModel1D model1D(3, 1.0, 1234);

    for (int s1 : {-1, 1}) {
        for (int s2 : {-1, 1}) {
            for (int s3 : {-1, 1}) {
                vector<int> config = {s1, s2, s3};
                model1D.setSpins(config);
                double E = model1D.total_energy();
                int M = model1D.magnetization();
                cout << "Config: ("
                     << (s1 > 0 ? "+1" : "-1") << ", "
                     << (s2 > 0 ? "+1" : "-1") << ", "
                     << (s3 > 0 ? "+1" : "-1") << ") | ";
                cout << "E = " << setw(3) << E << "J, ";
                cout << "M = " << setw(2) << M << endl;
            }
        }
    }

    cout << "\nMonte Carlo Simulation (1D, 3 spins):" << endl;
    model1D.simulate(100000, 10000, 10);
    cout << endl;
}

void test2DModel() {
    cout << "===== Official 2D Ising Model Test =====" << endl;

    cout << "\nLow Temperature (high beta):" << endl;
    IsingModel2D model2D_lowT(10, 1.0);
    model2D_lowT.simulate(50000, 5000, 10);

    cout << "\nHigh Temperature (low beta):" << endl;
    IsingModel2D model2D_highT(10, 0.1);
    model2D_highT.simulate(50000, 5000, 10);

    cout << "\nMedium Temperature:" << endl;
    IsingModel2D model2D_mediumT(10, 0.44);
    model2D_mediumT.simulate(50000, 5000, 10);
}

int main() {
    cout << fixed << setprecision(4);

    test1DModel();
    test2DModel();

    return 0;
}