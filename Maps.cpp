#include "Maps.h"

namespace Maps
{
	const Vecf2* getCXC()
	{
		Vecf2* map = new Vecf2[PART_NUM]{};
		size_t count(0);

		// C
		for (float x(100); x < 200; x += 16) {
			map[count++] = { x, 100 };
			map[count++] = { x, 132 };
		}

		for (float y(100); y < 500; y += 16) {
			map[count++] = { 100, y };
			map[count++] = { 84, y };
		}

		for (float x(100); x < 200; x += 16) {
			map[count++] = { x, 500 };
			map[count++] = { x, 516 };
		}

		// X
		for (float coef(0.0f); coef < 4.0; coef += 0.15f) {
			map[count++] = { 300 + coef * 50, 100 + coef * 100 };
			map[count++] = { 284 + coef * 50, 100 + coef * 100 };
		}

		for (float coef(0.0f); coef < 4.2f; coef += 0.15f) {
			if (coef < 1.5f || coef > 2.5f) {
				map[count++] = { 300 + coef * 50, 500 - coef * 100 };
				map[count++] = { 284 + coef * 50, 500 - coef * 100 };
			}
		}

		// C
		for (float x(600); x < 700; x += 16) {
			map[count++] = { x, 100 };
			map[count++] = { x, 132 };
		}

		for (float y(100); y < 500; y += 16) {
			map[count++] = { 600, y };
			map[count++] = { 584, y };
		}

		for (float x(600); x < 700; x += 16) {
			map[count++] = { x, 500 };
			map[count++] = { x, 516 };
		}

		return map;
	}
}