  ## The 1d Isling Model 

We use the vector data structure to model the spins of the atoms. The vector data structure is ideal because of:
  - Dynamic Size: The number of spins (num_spins) is set dynamically during runtime, making vectors ideal for storage.
  - Efficiency: Provides fast access and modifications crucial for simulation performance.
  - Convenience: Built-in functionalities like indexing, iteration, and standard algorithms simplify operations.

Calculating alternative formula for the energy change when the spin of the atom changes: 

- Energy before flipping the spin:

$$
E_{\text{before}} = -\sigma_{\text{index}}(\sigma_{\text{left}} + \sigma_{\text{right}})
$$

- After flipping, the spin's state becomes $-\sigma_{\text{index}}$:

$$
E_{\text{after}} = -(-\sigma_{\text{index}})(\sigma_{\text{left}} + \sigma_{\text{right}})
= +\sigma_{\text{index}}(\sigma_{\text{left}} + \sigma_{\text{right}})
$$

- Therefore, the energy difference ($\Delta E$) is:

$$
\Delta E = E_{\text{after}} - E_{\text{before}} 
= \sigma_{\text{index}}(\sigma_{\text{left}} + \sigma_{\text{right}}) - \left[-\sigma_{\text{index}}(\sigma_{\text{left}} + \sigma_{\text{right}})\right]
$$

Simplifying this gives:

$$
\Delta E = 2 \cdot \sigma_{\text{index}}(\sigma_{\text{left}} + \sigma_{\text{right}})
$$
