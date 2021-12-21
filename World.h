#pragma once

#include <cmath>
#include <Windows.h>
#include <corecrt_math_defines.h>

#include "Maps.h"


class World
{
public:
	struct Particle
	{
		Particle() :
			m_vel{ 0.0f, 0.0f }, m_force{ 0.0f, 0.0f }, m_dens(0.0), m_pres(0.0f) {}

		Vecf2* m_pos = nullptr, m_vel, m_force;
		float m_dens, m_pres;
	};

	World(void (*renderer)(const Vecf2 prevPartsPos[PART_NUM], const Vecf2 partsPos[PART_NUM]));

	void update();
	void render() const;

private:
	// solver parameters
	const Vecf2 G{ 0.0f, 12000 * -9.8f }; // external (gravitational) forces
	const float REST_DENS = 1000.f; // rest density
	const float GAS_CONST = 2000.f; // const for equation of state
	const float H = 16.f; // kernel radius
	const float HSQ = H * H; // radius^2 for optimization
	const float MASS = 65.f; // assume all particles have the same mass
	const float VISC = 150.f; // viscosity constant
	const float DT = 0.0008f; // integration timestep

	// smoothing kernels defined in Muller and their gradients
	const float POLY6 = 315.f / (65.f * (float)M_PI * pow(H, 9.f));
	const float SPIKY_GRAD = -45.f / ((float)M_PI * pow(H, 6.f));
	const float VISC_LAP = 45.f / ((float)M_PI * pow(H, 6.f));

	// simulation parameters
	const float EPS = H; // boundary epsilon
	const float BOUND_DAMPING = -0.5f;

	Particle m_particles[PART_NUM];
	Vecf2 m_partsPos[PART_NUM]{};
	Vecf2 m_prevPartsPos[PART_NUM]{};

	HWND m_windowHandler;


	void computeDensityPressure();
	void computeForces();
	void integrate();
	void (*consoleRender)(const Vecf2 prevPartsPos[PART_NUM], const Vecf2 partsPos[PART_NUM]) = nullptr;
};