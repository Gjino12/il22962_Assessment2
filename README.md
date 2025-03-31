# Ising Model Monte Carlo Simulation (1D and 2D)

**Project Summary:**  
This project implements the Ising model in one and two dimensions using the Metropolis Monte Carlo method. The goal is to simulate ferromagnetic phase transition behavior by measuring average energy and magnetization of spin systems across different temperatures. The code provides a 1D ring of spins and a 2D square lattice of spins, and uses Monte Carlo sampling to evolve the system toward equilibrium at a given temperature. Results are saved to CSV files and can be visualized to observe how the magnetization drops at higher temperatures (disorder) and remains high at low temperatures (order), demonstrating the phase transition in 2D.

## Mathematical Background

The **Ising model** consists of spins $s_i$ that can take values $+1$ or $-1$. Spins sit on a lattice (a line in 1D, or a grid in 2D) and each spin interacts with its nearest neighbors. We consider a ferromagnetic interaction (favoring alignment) with coupling $J>0$. For simplicity, we take $J=1$ and no external magnetic field in our simulations. The energy of a spin configuration is given by the sum of nearest-neighbor interactions:

- **1D Total Energy:** For a chain of $N$ spins with periodic boundary conditions (spin $N+1$ is spin 1), the energy is:  

  $$
  E_{\text{1D}} \;=\; -J \sum_{i=1}^{N} s_i\, s_{i+1}
  $$

  where $s_{N+1} \equiv s_1$. Each neighboring pair $s_i s_{i+1}$ contributes $-J$ if aligned ($s_i s_{i+1}=+1$) or $+J$ if anti-aligned ($s_i s_{i+1}=-1$). A fully aligned 1D chain has minimal energy $E_{\text{1D}} = -J N$.

- **2D Total Energy:** For an $L \times L$ square lattice with periodic boundaries (a torus topology), the energy sums interactions for each spin with its four neighbors (up, down, left, right):  
  $$
  E_{\text{2D}} \;=\; -J \sum_{x=1}^{L}\sum_{y=1}^{L} \Big( s_{x,y}\,s_{x+1,y} \;+\; s_{x,y}\,s_{x,y+1} \Big),
  $$
  where indices wrap around at the boundaries. Each bond is counted once; for a fully aligned lattice, $E_{\text{2D}} = -2 J L^2$ (since each spin contributes effectively two bonds). In both formulas, we set $J=1$ for simplicity.

**Magnetization ($M$)** is defined as:
$$
M \;=\; \sum_i s_i \quad \text{(or } \sum_{x,y} s_{x,y} \text{ in 2D)},
$$
with magnetization per spin $m = M/N$ (or $M/(L^2)$ in 2D). In a fully aligned configuration, $m = \pm 1$; in a disordered state, $m \approx 0$.

**Monte Carlo and Metropolis Criterion:**  
The simulation uses the Metropolis Monte Carlo algorithm at temperature $T$ (with inverse temperature $\beta = 1/(k_BT)$, and $k_B=1$). For a proposed spin flip:
- **Energy Change Calculation:** For example, in 1D,
  $$
  \Delta E_{\text{1D}} \;=\; 2J\, s_i \big(s_{i-1} + s_{i+1}\big),
  $$
  and in 2D,
  $$
  \Delta E_{\text{2D}} \;=\; 2J\, s_{x,y}\, \big(s_{x-1,y} + s_{x+1,y} + s_{x,y-1} + s_{x,y+1}\big).
  $$
- **Acceptance Criterion:**  
  If $\Delta E \le 0$, the flip is accepted. Otherwise, the flip is accepted with probability
  $$
  P = e^{-\beta \Delta E}.
  $$
  A random number $r \in [0,1]$ is generated, and the spin is flipped if $r < P$.

## Implementation: 1D and 2D Ising Models

### 1D Ising Model (`IsingModel1D`)
- **Data Structure:** Uses `std::vector<int>` to store the spin configuration (each value is either $-1$ or $+1$).
- **Key Functions:**
  - `initialize_spins()`: Randomly assigns spins to $-1$ or $+1$.
  - `energy_change(int index)`: Computes $\Delta E = 2J\, s_i (s_{i-1}+s_{i+1})$ using periodic boundaries.
  - `monte_carlo_step()`: Performs a single Monte Carlo update.
  - `total_energy()`: Computes $E_{\text{1D}} = -\sum s_i s_{i+1}$.
  - `magnetization()`: Computes the sum of spins.
  - `simulate(...)`: Runs the simulation (including burn-in and sampling) and outputs data to CSV.

### 2D Ising Model (`IsingModel2D`)
- **Data Structure:** Uses `std::vector<std::vector<int>>` to store a square lattice of spins.
- **Key Functions (Overridden):**
  - `initialize_spins()`: Initializes the 2D lattice randomly.
  - `energy_change(int x, int y)`: Computes $\Delta E$ using four neighbors.
  - `monte_carlo_step()`: Randomly selects a lattice site and updates it.
  - `total_energy()`: Computes the energy considering right and down neighbors to avoid double counting.
  - `magnetization()`: Sums over all spins.
  - `simulate(...)`: Similar to the 1D simulation, but normalizes by $L^2$.
  - `save_spins_to_file()`: Saves the current 2D configuration for visual inspection.

### Main Driver (`main.cpp`)
- **Testing Functions:**
  - `official1DTest()`: Exhaustively tests a 3-spin 1D configuration by printing energies and magnetizations.
  - `test2DModel()`: Runs the 2D model at low, high, and near-critical temperatures.
  - `test1DModelCSV()` and `test2DModelCSV()`: Run simulations over a range of $\beta$ values and output results to CSV files.
- **Flow:** The main function calls the above tests sequentially to demonstrate and validate the models.

### Visualization Scripts
- **`visualisation_1d.py` & `visualisation_2d.py`:**
  - These Python scripts read the CSV files and plot:
    - **Energy per Spin vs Temperature**
    - **Magnetization per Spin vs Temperature**
  - Plots are generated using matplotlib and saved as PNG files.

## Required Dependencies

Before compiling and running the project, ensure that the following dependencies are installed on your system:

- **C++ Compiler:**
  - A C++17-compliant compiler (e.g., `g++` version 7 or later).
- **Make:**
  - GNU Make or any compatible build system to use the provided Makefile.
- **Python 3:**
  - For running the visualization scripts.
- **Python Packages:**
  - **matplotlib:** For generating plots.
    ```bash
    pip install matplotlib
    ```
  - **csv:** This is part of Python's standard library, so no additional installation is needed.
- **Standard C++ Libraries:**
  - The code uses standard libraries like `<vector>`, `<random>`, `<fstream>`, `<cmath>`, and `<numeric>` which are included with most modern C++ compilers.

## How to Compile and Run

1. **Compile the code:**
   - In the project directory, run:
     ```bash
     make
     ```
     This will compile the C++ source files (`IsingModel1D.cpp`, `IsingModel2D.cpp`, `main.cpp`) into an executable (e.g., `ising_model`).

2. **Run the Simulation:**
   - Execute the program:
     ```bash
     ./ising_model
     ```
     This will:
     - Run the 1D exhaustive test (3-spin system) and print configurations.
     - Perform Monte Carlo simulations for both 1D and 2D models.
     - Save simulation results to CSV files (`ising_1d_results.csv`, `ising_2d_results.csv`).

3. **Visualize the Results:**
   - Run the visualization scripts (ensure Python 3 and matplotlib are installed):
     ```bash
     python3 visualisation_1d.py
     python3 visualisation_2d.py
     ```
     These scripts will read the CSV files and generate plots (also saving them as PNG files).

## Expected Output

- **CSV Files:**
  - **`ising_1d_results.csv`** – Contains data with columns: Temperature (1/β), average energy per spin, and average magnetization per spin for the 1D model.
  - **`ising_2d_results.csv`** – Contains similar data for the 2D model.
- **Console Output:**
  - For the 1D 3-spin test, configurations with their energies and magnetizations are printed.

===== Official 1D Ising Model Test =====

Config: (-1, -1, -1) | E = -3.0000J, M = -3

Config: (-1, -1, +1) | E = 1.0000J, M = -1

Config: (-1, +1, -1) | E = 1.0000J, M = -1

Config: (-1, +1, +1) | E = 1.0000J, M =  1

Config: (+1, -1, -1) | E = 1.0000J, M = -1

Config: (+1, -1, +1) | E = 1.0000J, M =  1

Config: (+1, +1, -1) | E = 1.0000J, M =  1

Config: (+1, +1, +1) | E = -3.0000J, M =  3

Monte Carlo Simulation (1D, 3 spins):
[CSV] Saved short 1D test to small_1d_results.csv

  - Average energy and magnetization for the 2D tests at different temperatures are printed.
  
  ===== Official 2D Ising Model Test =====

Low Temperature (beta = 1.0):

Average Energy per spin: -1.9969

Average Magnetization per spin: -0.9991


High Temperature (beta = 0.1):

Average Energy per spin: -0.1931

Average Magnetization per spin: -0.0033

Medium Temperature (beta = 0.44):

Average Energy per spin: -1.5436

Average Magnetization per spin: -0.8205

  - Confirmation messages for CSV file creation. CSV files should 
- **Plots:**
  - *Energy per Spin vs Temperature* and *Magnetization per Spin vs Temperature* graphs for both 1D and 2D models are generated.

## Testing and Verification

- **Exhaustive State Test (1D, 3 Spins):**
  - The `official1DTest()` function iterates through all 8 possible configurations of a 3-spin chain, printing the computed energy and magnetization for each.
- **Monte Carlo Behavior Checks (2D):**
  - `test2DModel()` runs the 2D simulation at:
    - **Low Temperature:** Expect high magnetization (close to ±1) and energy near $-2$ per spin.
    - **High Temperature:** Expect near-zero magnetization and energy approaching $0$.
    - **Near Critical Temperature:** Expect intermediate values and significant fluctuations.
- **CSV Data Consistency:**
  - The CSV output functions (`simulate()`) in both models ensure that the average energy per spin and magnetization per spin are correctly computed and normalized.

## Version Control Practices

- **Branching Strategy:**
  - The project development involved separate branches for the 1D model, the 2D model, and visualization, which were later merged to ensure a stable main branch.
- **Commit History:**
  - Frequent, descriptive commits (e.g., "Implemented energy_change for 2D model") help track changes.
- **Merging and Integration:**
  - Feature branches were merged into the main branch after thorough testing.
- **.gitignore:**
  - A `.gitignore` file is maintained to exclude compiled objects, executables, CSV output files, and other non-source files.

