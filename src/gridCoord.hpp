//
// Created by siii on 30-08-2026.
//

#ifndef CALIBURNER_GRIDCOORD_HPP
#define CALIBURNER_GRIDCOORD_HPP
#include <cstdint>


struct GridCoord
{
	int64_t x, y, z;

	bool operator==(const GridCoord&) const = default;
};

//C++ Ceremony
struct GridCoordHash
{
	std::size_t operator()(const GridCoord& p) const noexcept
	{
		const std::size_t h1 = std::hash<int64_t>{}(p.x);
		const std::size_t h2 = std::hash<int64_t>{}(p.y);
		const std::size_t h3 = std::hash<int64_t>{}(p.z);

		return h1 ^ (h2 << 1) ^ (h3 << 2);
	}
};


#endif //CALIBURNER_GRIDCOORD_HPP
