#include "World.h"

World::World(void (*renderer)(const Vecf2 prevPartsPos[PART_NUM], const Vecf2 partsPos[PART_NUM]))
	: consoleRender(renderer)
{
	m_windowHandler = GetConsoleWindow();

	auto map = Maps::getCXC();
	for (int i(0); i < PART_NUM; ++i)
	{
		float jitter = rand() / float(RAND_MAX);
		m_particles[i].m_pos = m_partsPos + i;
		m_partsPos[i] = map[i];
		m_partsPos[i].x -= 30;
		m_partsPos[i].y += 30;
	}
}


void World::update()
{
	memcpy(m_prevPartsPos, m_partsPos, sizeof(Vecf2) * PART_NUM);
	computeDensityPressure();
	computeForces();
	integrate();
}


void World::render() const
{
	consoleRender(m_prevPartsPos, m_partsPos);
}


void World::computeDensityPressure()
{
	for (int i(0); i < PART_NUM; ++i)
	{
		m_particles[i].m_dens = 0.0f;
		for (int j(0); j < PART_NUM; ++j)
		{
			Vecf2 rij = *m_particles[j].m_pos + -*m_particles[i].m_pos;
			float r2 = rij.squaredLength();

			if (r2 < HSQ)
			{
				// this computation is symmetric
				m_particles[i].m_dens += MASS * POLY6 * pow(HSQ - r2, 3.0f);
			}
		}
		m_particles[i].m_pres = GAS_CONST * (m_particles[i].m_dens - REST_DENS);
	}
}


void World::computeForces()
{
	for (int i(0); i < PART_NUM; ++i)
	{
		Vecf2 fpress{};
		Vecf2 fvisc{};

		for (int j(0); j < PART_NUM; ++j)
		{
			if (i == j)
				continue;

			Vecf2 rij = *m_particles[j].m_pos + -*m_particles[i].m_pos;
			float r = rij.length();

			if (r < H)
			{
				// compute pressure force contribution
				fpress = fpress + -rij.normalize() * MASS * (m_particles[i].m_pres + m_particles[j].m_pres) *
					(1 / (2.0f * m_particles[j].m_dens)) * SPIKY_GRAD * pow(H - r, 2.0f);
				// compute viscosity force contribution
				fvisc = fvisc + (m_particles[j].m_vel + -m_particles[i].m_vel) * VISC * MASS *
					(1 / m_particles[j].m_dens) * VISC_LAP * (H - r);
			}
		}
		Vecf2 fgrav = G * m_particles[i].m_dens;

		Vecf2 mouseGrav{};
		if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		{
			POINT p;
			RECT winRect;
			GetCursorPos(&p);
			ScreenToClient(m_windowHandler, &p);
			GetWindowRect(m_windowHandler, &winRect);
			Vecf2 curPos = { (float)p.x, winRect.bottom - winRect.top - (float)p.y };
			mouseGrav = (curPos + -*m_particles[i].m_pos).normalize() * 10'000;
		}

		m_particles[i].m_force = fpress + fvisc + fgrav + mouseGrav;
	}
}


void World::integrate()
{
	for (int i(0); i < PART_NUM; ++i)
	{
		auto& p = m_particles[i];

		// forward Euler integration
		p.m_vel = p.m_vel + p.m_force * (DT / p.m_dens);
		*p.m_pos = *p.m_pos + p.m_vel * DT;

		// enforce boundary conditions
		if (p.m_pos->x - EPS < 0.0f)
		{
			p.m_vel.x *= BOUND_DAMPING;
			p.m_pos->x = EPS;
		}
		if (p.m_pos->x + EPS > VIEW_WIDTH)
		{
			p.m_vel.x *= BOUND_DAMPING;
			p.m_pos->x = VIEW_WIDTH - EPS;
		}
		if (p.m_pos->y - EPS < 0.0f)
		{
			p.m_vel.y *= BOUND_DAMPING;
			p.m_pos->y = EPS;
		}
		if (p.m_pos->y + EPS > VIEW_HEIGHT)
		{
			p.m_vel.y *= BOUND_DAMPING;
			p.m_pos->y = VIEW_HEIGHT - EPS;
		}
	}
}