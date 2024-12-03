# 🌊 FluidDynamics

![Console Adventures](https://img.shields.io/badge/Console%20Adventures-green?logo=gnometerminal&logoColor=000000
)  ![WinAPI](https://img.shields.io/badge/WinAPI-blue)

FluidDynamics is a Windows console-based simulation of water behavior. The "water" is represented visually using blue `@` symbols. By interacting with the simulation using the right mouse button (RMB), you can manipulate the water particles:

- **Hold RMB:** Attract particles to the mouse cursor and move them around.
- **Release RMB:** Allow gravity to pull particles to the bottom of the window, creating splashes and waves.

## Features

- Realistic water simulation based on Smoothed Particle Hydrodynamics (SPH).
- Interactive control using the right mouse button.
- Visual rendering using `WriteConsoleOutput` for efficient updates.

---

## Files and Responsibilities

### `FluidDynamics.cpp`
- **Program entry point** and main logic.
- Includes the `consoleRender` helper function, leveraging `WriteConsoleOutput` for high-performance text buffer updates.

### `Maps.cpp`
- Contains the **hardcoded initial particle map**, which determines the starting positions of water particles in the simulation.

### `World.cpp`
- Implements the **physics engine**:
  - **`computeDensityPressure()`**: Estimates particle density using the Poly6 smoothing kernel.
  - **`computeForces()`**: Calculates forces acting on particles (pressure, viscosity, gravity) and their interactions with neighbors.
  - **`integrate()`**: Updates particle positions and velocities based on the results of density, pressure, and force computations.

---

## Theory

### 1. **Density Computation**  
The particle density is computed using the Poly6 smoothing kernel:  
$$ \rho_i = \sum_j m_j \cdot W_{\text{poly6}}(|r_i - r_j|, h) $$  
where:  
- $\rho_i$: Density at particle $i $  
- $m_j $: Mass of particle $j $  
- $W_{\text{poly6}}$: Poly6 kernel function  
- $h $: Kernel radius  

### 2. **Pressure (Ideal Gas Law)**  
Pressure is determined by the ideal gas law:  
$$ P_i = k \cdot (\rho_i - \rho_0) $$  
where:  
- $P_i $: Pressure at particle $i $  
- $k $: Gas constant  
- $\rho_0 $: Rest density  

### 3. **Acceleration (SPH Forces)**  
The acceleration of particles is computed by combining pressure and viscosity forces:  
$$ a_i = -\sum_j m_j \left( \frac{P_i + P_j}{2 \cdot \rho_j} \right) \nabla W_{\text{spiky}} + \mu \nabla^2 W_{\text{visc}} $$  
where:  
- $\nabla W_{\text{spiky}} $: Gradient of the Spiky kernel  
- $\nabla^2 W_{\text{visc}} $: Laplacian of the viscosity kernel  
- $\mu $: Viscosity coefficient  

---

## Constants (Defined in `World.h`)

| Constant             | Value (default UoM)                  |
|----------------------|------------------------|
| **Gravity**          | $12000 \cdot -9.8 $ |
| **Rest Density**     | $1000 $             |
| **Gas Constant**     | $2000 $             |
| **Kernel Radius**    | $16 $               |
| **Particle Mass**    | $65 $               |
| **Viscosity**        | $150 $              |
| **Time-step**        | $0.8ms $           |

---

## Video Example

https://user-images.githubusercontent.com/89595575/147252970-b37a1721-33c8-4ac2-a610-bfe0a2cda62b.mp4

### Translation of Video Notes:
- **0:14**: Hold RMB to attract particles to the mouse cursor.

---

## Build Instructions

To build FluidDynamics, use the **MSVC x64 compiler**:

1. Open the project file `FluidDynamics.vcxproj` in Visual Studio.
2. Compile the project in the desired configuration (Debug or Release).
3. Run the resulting executable.
